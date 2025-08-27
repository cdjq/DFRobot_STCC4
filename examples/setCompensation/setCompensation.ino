/*!
 * @file setCompensation.ino
 * @brief This routine can adjust the air pressure, temperature and humidity compensation through variables.
 * @n If you connect the humidity and temperature sensor, you can obtain the concentration of carbon dioxide and temperature and humidity.
 * @n When manually changing the temperature and humidity compensation values, the connection of the humidity and temperature sensor 
 *    needs to be disconnected, otherwise, the manually set compensation values will become invalid.
 * @n If the SHT4x is not connected, the obtained temperature and humidity will be the manually compensated values.
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

uint16_t pressureCompensation = 950; // Set the pressure compensation value to 950 hPa.
uint16_t temperatureCompensation = 27; // Set the temperature compensation value to 28 degrees Celsius.
uint16_t humidityCompensation = 53; // Set the humidity compensation value to

void setup() {
  char id[18];
  Serial.begin(115200);
  while(!Serial) delay(100); // Wait for the serial port to be ready.
  Serial.println("This demo will adjust the sensor's compensation settings based on the provided values.");
  Serial.println("The SHT4x must be disconnected from the sensor.\n\n");

  while(sensor.begin()){
    Serial.println("Init error!!!");
    delay(500);
  }
  /* Read sensor ID */
  while(!sensor.getID(id)){
    delay(500);
  }
  sprintf(id, "%02x%02x%02x%02x", id[0], id[1], id[3], id[4]);
  Serial.print("ID: ");
  Serial.println(id);
  /* Set compensation */
  if(sensor.setPressureCompensation(pressureCompensation))
    Serial.print("The pressure compensation has been changed to: ");
    Serial.println(pressureCompensation);
  if(sensor.setRHTcompensation(temperatureCompensation,humidityCompensation))
    Serial.print("The temperature compensation has been changed to ");
    Serial.print(temperatureCompensation);
    Serial.print(" and the humidity compensation has been changed to ");
    Serial.println(humidityCompensation);
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
