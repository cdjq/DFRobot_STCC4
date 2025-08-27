# DFRobot_STCC4

- [中文版](./README_CN.md)

The STCC4 is Sensirion’s next generation miniature CO2 sensor for indoor air quality applications. Based on the
thermal conductivity sensing principle and Sensirion’s CMOSens® technology, the STCC4 enables monitoring
of CO2 gas concentration in ambient indoor air conditions at an unmatched cost-effectiveness and form factor.<br>
SMD assembly as well as tape & reel packaging allows cost- and space-effective integration of the STCC4 for
high-volume applications. The STCC4 is 100% factory-calibrated and enables automatic on-board
compensation of the CO2 output for humidity and temperature through an external SHT4x sensor.
![Fermion_BMV080](image/Fermion_BMV080.JPG)
 
## Product Link
    SKU:XXXXX

## Table of Contents

  * [Summary](#summary)
  * [Installation](#installation)
  * [Methods](#methods)
  * [Compatibility](#compatibility)
  * [History](#history)
  * [Credits](#credits)

## Summary

DFRobot_STCC4 is an Arduino and raspberrypi library specifically designed to drive the new CO2 measurement chip STCC4 produced by Sensirion. <br>
This library only provides one type of communication method: IIC, along with some basic routines. In theory, it supports all platforms that can use IIC.

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.


## Methods

```C++
/**
     * @fn calculationCRC
     * @brief Calculate the CRC of the data
     * @param data Pointer to the data array
     * @param length Length of the data array
     * @return Calculated CRC value
     */
  uint8_t calculationCRC(uint16_t *data, size_t length);

  /**
     * @fn getID
     * @brief Get the ID of the sensor
     * @param id Pointer to a character array to store the ID
     * @return true if successful, false otherwise
     */
  bool getID(char *id);

  /**
     * @fn startMeasurement
     * @brief Start continuous measurement
     * @return true if successful, false otherwise
     */
  bool startMeasurement(void);

  /**
     * @fn stopMeasurement
     * @brief Stop continuous measurement
     * @n The sensor needs 1200 milliseconds to execute this instruction.
     * @return true if successful, false otherwise
     */
  bool stopMeasurement(void);

  /**
     * @fn measurement
     * @brief Read measurement data
     * @param co2Concentration Pointer to store CO2 concentration
     * @param temperature Pointer to store temperature
     * @param humidity Pointer to store humidity
     * @param sensorStatus Pointer to store sensor status
     * @return true if successful, false otherwise
     */
  bool measurement(uint16_t* co2Concentration, 
                                        float* temperature, 
                                        float* humidity, 
                                        uint16_t* sensorStatus);

  /**
     * @fn setRHTcompensation
     * @brief Set temperature and humidity compensation
     * @param temperature Temperature compensation value
     * @param humidity Humidity compensation value
     * @return true if successful, false otherwise
     */
  bool setRHTcompensation(uint16_t temperature, uint16_t humidity);

  /**
     * @fn setPressureCompensation
     * @brief Set pressure compensation
     * @param pressure Pressure compensation value
     * @return true if successful, false otherwise
     */
  bool setPressureCompensation(uint16_t pressure);

  /**
     * @fn singleShot
     * @brief Perform a single shot measurement
     * @n The sensor needs 500 milliseconds to execute this instruction.
     * @return true if successful, false otherwise
     */
  bool singleShot(void);

  /**
     * @fn sleep
     * @brief Put the sensor into sleep mode
     * @return true if successful, false otherwise
     */
  bool sleep(void);

  /**
     * @fn wakeup
     * @brief Wake up the sensor from sleep mode
     * @return true if successful, false otherwise
     */
  bool wakeup(void);

  /**
     * @fn softRest
     * @brief Perform a soft reset of the sensor
     * @return true if successful, false otherwise
     */
  bool softRest(void);

  /**
     * @fn factoryReset
     * @brief Perform a factory reset of the sensor
     * @return true if successful, false otherwise
     */
  bool factoryReset(void);

  /**
     * @fn enableTestingMode
     * @brief Enable testing mode
     * @return true if successful, false otherwise
     */
  bool enableTestingMode(void);

  /**
     * @fn disableTestingMode
     * @brief Disable testing mode
     * @return true if successful, false otherwise
     */
  bool disableTestingMode(void);

  /**
     * @fn forcedRecalibration
     * @brief Perform forced recalibration
     * @param targetPpm Target PPM value for recalibration
     * @param frcCorrection Pointer to store the correction value
     * @return true if successful, false otherwise
     */
  bool forcedRecalibration(uint16_t targetPpm, uint16_t* frcCorrection);
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno        |      √       |              |             | 
Mega2560           |      √       |              |             | 
Leonardo           |      √       |              |             | 
ESP32              |      √       |              |             | 
micro:bit          |      √       |              |             | 
raspberry pi       |      √       |              |             |     
<br>

## History

- 2025/08/15 - Version 1.0.0 released.

## Credits

Written by Alexander(ouki.wang@dfrobot.com), 2025. (Welcome to our [website](https://www.dfrobot.com/))
