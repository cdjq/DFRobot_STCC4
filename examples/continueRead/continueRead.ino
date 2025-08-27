/*!
 * @file continueRead.ino
 * @brief This routine continuously reads sensor data via the IIC interface and can obtain one piece of data per second. 
 * @n If you connect the humidity and temperature sensor, you can obtain the concentration of carbon dioxide and temperature and humidity.
 * @n If the temperature and humidity sensors are not connected, the obtained temperature and humidity values is the default values.
 * @n The demo supports FireBeetle-ESP32, and FireBeetle-ESP8266, Arduino Uno, Leonardo, Mega2560, FireBeetle-M0
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


DFRobot_STCC4_I2C sensor(&Wire, 0x64); // Create an instance of the DFRobot_STCC4_I2C class with the I2C address 0x64.

void setup() {
  char id[18];
  Serial.begin(115200);
  while(!Serial) delay(100); // Wait for the serial port to be ready.

  Serial.println("This is a demo of continuous reading sensor data.\n\n");
  delay(500);
  while(sensor.begin()){
    Serial.println("Init error!");
    delay(500);
  }
  sensor.wakeup();
  /* Read sensor ID */
  while(!sensor.getID(id)){
    delay(500);
    Serial.println("Get ID error!");
  }
  sprintf(id, "%02x%02x%02x%02x", id[0], id[1], id[3], id[4]);
  Serial.print("ID: ");
  Serial.println(id);
  sensor.startMeasurement();
}

uint16_t co2Concentration;
float temperature;
float humidity;
uint16_t sensorStatus;

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
