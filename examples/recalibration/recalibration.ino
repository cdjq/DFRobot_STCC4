/*!
 * @file reaclibration.ino
 * @brief This routine first conducts 30 consecutive samplings, then performs calibration, and subsequently continues with continuous sampling.
 * @n If you connect the humidity and temperature sensor, you can obtain the concentration of carbon dioxide and temperature and humidity.
 * @n If the temperature and humidity sensors are not connected, the obtained temperature and humidity values is the default values.
 * @n The demo supports FireBeetle-ESP32, and FireBeetle-ESP8266, Arduino Uno, Leonardo, Mega2560, FireBeetle-M0.
 * @details Experimental phenomenon: The read data will be output in the serial port monitor.
 * 
 * @copyright Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [lbx](liubx8023@gmail.com)
 * @version V1.0
 * @date 2025-08-14
 * @url https://github.com/DFRobot/DFRobot_STCC4
 */

#include "DFRobot_STCC4.h"
#include <string.h>

DFRobot_STCC4_I2C sensor(&Wire, 0x64); // Create an instance of the DFRobot_STCC4_I2C class with the I2C address 0x64.

uint16_t target = 500; // Target CO2 concentration for calibration
uint16_t correction;
uint16_t co2Concentration;
float temperature;
float humidity;
uint16_t sensorStatus;


void setup() {
  char id[18];

  Serial.begin(115200);
  while(!Serial) delay(100); // Wait for the serial port to be ready.

  Serial.println("This demo will force-calibrate the sensor based on the CO2 concentration you input.\n\n");
  delay(1000);
  while(sensor.begin()){
    Serial.println("Init error!");
    delay(500);
  }
  /* Read sensor ID */
  while(!sensor.getID(id)){
    delay(500);
    Serial.println("Get ID error!");
  }
  sprintf(id, "%02x%02x%02x%02x", id[0], id[1], id[3], id[4]);
  Serial.print("ID: ");
  Serial.println(id);
  
  sensor.wakeup();
  delay(10);
  /* Start 30 consecutive samplings */
  sensor.startMeasurement();
  for(uint8_t i = 0; i < 30; i++){
    delay(1000);
    if(sensor.measurement(&co2Concentration,&temperature,&humidity,&sensorStatus)){
      String output = "Before calibration CO2: " + String(co2Concentration) + 
                      " ppm   Temperature: " + String(temperature, 2) + 
                      " C   Humidity: " + String(humidity, 2) + " %";
      Serial.println(output);
    }
  }
  sensor.stopMeasurement();
  delay(1000);
  /* Start calibration */
  sensor.forcedRecalibration(target, &correction);
  while(correction == 0xffff || correction == 0){
    Serial.println("Calibration failed!\n");
    delay(1000);
    sensor.forcedRecalibration(target, &correction);
  }
  Serial.print("CO2 concentration correction:");
  Serial.println(correction);
  sensor.wakeup();
  delay(10);
  sensor.startMeasurement();
  delay(500);
}

void loop() {
  delay(1000);
  /* Read sensor data */
  if(sensor.measurement(&co2Concentration,&temperature,&humidity,&sensorStatus)){
    String output = "CO2: " + String(co2Concentration) + 
                    " ppm   Temperature: " + String(temperature, 2) + 
                    " C   Humidity: " + String(humidity, 2) + " %";
    Serial.println(output);
  }
}
