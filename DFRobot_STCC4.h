/*!
 * @file DFRobot_STCC4.h
 * @brief Declaration the basic structure of class DFRobot_STCC4
 * @n It is possible to measure the concentration of carbon dioxide in the air.
 * @n If the humidity and temperature sensor is connected, temperature and humidity can also be obtained.
 * @n Only supports IIC communication interface
 * @copyright	Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [lbx](liubx8023@gmail.com)
 * @version V1.0
 * @date 2025-08-15
 * @url https://github.com/DFRobot/DFRobot_STCC4
 */

#ifndef __DFROBOT_STCC4_H
#define __DFROBOT_STCC4_H

#include <Arduino.h>
#include <Wire.h>


#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

#define DFRobot_STCC4_I2C_ADDR 0x64

#define STCC4_GET_ID                      0x365B // Get the ID of the sensor
#define STCC4_START_CONT_MEASURE          0x218B // Start continuous measurement
#define STCC4_STOP_CONT_MEASURE           0x3F86 // Stop continuous measurement
#define STCC4_READ_MEASURE                0xEC05 // Read measurement data
#define STCC4_SET_RHT_COMPENSATION        0xE000 // Set temperature and humidity compensation
#define STCC4_SET_PRESSURE_COMPENSATION   0xE016 // Set pressure compensation
#define STCC4_SINGLE_SHOT                 0x219D // Single shot measurement
#define STCC4_SLEEP                       0x3650 // Sleep mode
#define STCC4_WAKEUP                      0x00   // Wake up from sleep mode
#define STCC4_SOFT_RESET                  0x06   // Soft reset
#define STCC4_FACTORY_RESET               0x3632 // Factory reset
#define STCC4_ENABLE_TESTING_MODE         0x3FBC // Enable testing mode
#define STCC4_DISABLE_TESTING_MODE        0x3F3D // Disable testing mode
#define STCC4_FORC_CALIBRATION            0x362F // Force calibration


class DFRobot_STCC4
{
public:
  #define ERR_OK            0      ///< success
  #define ERR_DATA_BUS      1      ///< bus error
  #define ERR_DATA_READ     2      ///< read error
  #define ERR_DATA_WRITE    3      ///< write error
  #define ERR_IC_VERSION    4      ///< The chip versions do not match

public:
  /**
     * @fn DFRobot_STCC4
     * @brief Constructor of DFRobot_STCC4 class
     * @retunr None
     */
  DFRobot_STCC4(void);
  ~DFRobot_STCC4();

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

private:
   /**
     * @fn writeData
     * @brief Write data to the sensor
     * @param cmd Command to write
     * @param pBuf Pointer to the data buffer
     * @param size Size of the data buffer
     * @return true if successful, false otherwise
     */
   virtual bool writeData(uint16_t cmd, uint16_t * pBuf, size_t size) = 0;

   /**
     * @fn writeCMD8
     * @brief Write an 8-bit command to the sensor
     * @param cmd Command to write
     * @return true if successful, false otherwise
     */
   virtual bool writeCMD8(uint8_t cmd) = 0;

   /**
     * @fn writeCMD16
     * @brief Write a 16-bit command to the sensor
     * @param cmd Command to write
     * @return true if successful, false otherwise
     */
   virtual bool writeCMD16(uint16_t cmd) = 0;

   /**
     * @fn readData
     * @brief Read data from the sensor
     * @param pBuf Pointer to the data buffer
     * @param size Size of the data buffer
     * @return Number of bytes read, or 0 if an error occurred
     */
   virtual size_t readData(uint8_t * pBuf, size_t size) = 0;
};

class DFRobot_STCC4_I2C:public DFRobot_STCC4{
public:  
  /**
     * @fn DFRobot_STCC4_I2C
     * @brief Constructor of DFRobot_STCC4_I2C class
     * @param pWire Pointer to the TwoWire object for I2C communication
     * @param addr I2C address of the sensor
     */
  DFRobot_STCC4_I2C(TwoWire *pWire = &Wire, uint8_t addr = DFRobot_STCC4_I2C_ADDR);

  /**
     * @fn begin
     * @brief Initialize the sensor
     * @return true if successful, false otherwise
     */
  bool begin();
  
  /**
     * @fn writeData
     * @brief Write data to the sensor
     * @param cmd Command to write
     * @param pBuf Pointer to the data buffer
     * @param size Size of the data buffer
     * @return true if successful, false otherwise
     */
  bool writeData(uint16_t cmd, uint16_t * pBuf, size_t size);

  /**
     * @fn writeCMD8
     * @brief Write an 8-bit command to the sensor
     * @param cmd Command to write
     * @return true if successful, false otherwise
     */
  bool writeCMD8(uint8_t cmd);

  /**
     * @fn writeCMD16
     * @brief Write a 16-bit command to the sensor
     * @param cmd Command to write
     * @return true if successful, false otherwise
     */
  bool writeCMD16(uint16_t cmd);

  /**
     * @fn readData
     * @brief Read data from the sensor
     * @param pBuf Pointer to the data buffer
     * @param size Size of the data buffer
     * @return Number of bytes read, or 0 if an error occurred
     */
  size_t readData(uint8_t * pBuf, size_t size);

private:
  TwoWire *_pWire; ///< Pointer to the TwoWire object for I2C communication
  uint8_t _deviceAddr; ///< I2C address of the sensor
};

#endif
