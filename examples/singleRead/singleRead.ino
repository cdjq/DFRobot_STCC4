/*!
 * @file singleRead.ino
 * @brief This routine employs a single-sampling method, sampling once every 10 seconds and then entering the sleep mode.
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


/**
 * Set temperature compensation.
 * The unit is degrees Celsius.
 * It only takes effect when the temperature and humidity sensor is disconnected from the STCC4.
 */
uint16_t tCompensation = 26;

/**
 * Set humidity compensation.
 * It only takes effect when the temperature and humidity sensor is disconnected from the STCC4.
 */
uint16_t hCompensation = 55;

/**
 * Set humidity compensation.
 * Unit is hPa.
 */
uint16_t pCompensation = 950;

/**
 * The environmental temperature obtained from STCC4. 
 * If no temperature and humidity sensor is connected, this value will be the default value or the set value.
 */
float temperature;

/**
 * The environmental humidity obtained from STCC4. 
 * If no temperature and humidity sensor is connected, this value will be the default value or the set value.
 */
float humidity;

/* The CO2 concentration obtained from STCC4. */
uint16_t co2Concentration;

/* The status of the sensor. */
uint16_t sensorStatus;

/**
 * The sensor can communicate via two specific addresses (0x64 and 0x65).
 * "Dip switch" (for Gravity version): A small switch on the board that you can toggle by hand.
 */
const uint8_t ADDR = 0x64;

DFRobot_STCC4_I2C sensor(&Wire, ADDR); // Create an instance of the DFRobot_STCC4_I2C class with the I2C address ADDR.


void setup() {
  Serial.begin(115200);
  while(!Serial) delay(100); // Wait for the serial port to be ready.
  Serial.println("This is a demo of single reading sensor data.");
  Serial.println("This demo will display a \"Data write failed\", but this is a normal occurrence.");
  Serial.println("Because the sensor has entered sleep mode, there will be no response when it is awakened.\n\n");

  /* Initialize the sensor */
  while(!sensor.begin()){
    Serial.println("Init error!!!");
    delay(500);
  }

  /* Wake up the sensor */
  sensor.wakeup();

  /**
   * Get the ID of the sensor.
   * The ID values read should all be 0x0901018a.
   */
  char id[15];
  while(!sensor.getID(id)){
    delay(500);
    Serial.println("Get ID error!");
  }
  sprintf(id, "ID: %02x%02x%02x%02x", id[0], id[1], id[2], id[3]);
  Serial.println(id);

  /**
    * @brief Set temperature and humidity compensation
    * @param temperature Temperature compensation value
    * @param humidity Humidity compensation value
    * @return true if successful, false otherwise
    */
  if(sensor.setRHTcompensation(tCompensation, hCompensation)){
    Serial.println("Set RHT compensation successful.");
  }else{
    Serial.println("Set RHT compensation error!");
  }

  /**
    * @brief Set pressure compensation
    * @param pressure Pressure compensation value
    * @return true if successful, false otherwise
    */
  if(sensor.setPressureCompensation(pCompensation)){
    Serial.println("Set pressure compensation successful.");
  }else{
    Serial.println("Set pressure compensation error!");
  }
}

void loop() {
  /* Wake up the sensor */
  sensor.wakeup();
  delay(100);

  /* Start a single-shot measurement */
  sensor.singleShot();
  delay(900);

  /* Read sensor data */
  if(sensor.measurement(&co2Concentration,&temperature,&humidity,&sensorStatus)){
    Serial.print("CO2:");
    Serial.print(co2Concentration);
    Serial.print(" ppm ");
    Serial.print(" temperature:");
    Serial.print(temperature);
    Serial.print(" ℃ ");
    Serial.print(" humidity:");
    Serial.print(humidity);
    Serial.println(" % ");
  }

  /* Enter sleep mode */
  sensor.sleep();
  Serial.println("sleep 10s");
  delay(9000);
}

