/*!
 * @file DFRobot_STCC4.cpp
 * @brief Implement the basic structure of class DFRobot_STCC4
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

#include <DFRobot_STCC4.h>
DFRobot_STCC4::DFRobot_STCC4(void) {}

DFRobot_STCC4::~DFRobot_STCC4(void) {}

uint8_t DFRobot_STCC4::calculationCRC(uint16_t *data, size_t length)
{
  uint8_t crc = 0xFF;

  for (size_t i = 0; i < length; i++) {
    uint8_t high_byte = (data[i] >> 8) & 0xFF; 
    uint8_t low_byte = data[i] & 0xFF;          
    crc ^= high_byte;
    for (uint8_t bit = 0; bit < 8; bit++) {
        if (crc & 0x80) {
            crc = (crc << 1) ^ 0x31;
        } else {
            crc <<= 1;
        }
    }
    crc ^= low_byte;
    for (uint8_t bit = 0; bit < 8; bit++) {
        if (crc & 0x80) {
            crc = (crc << 1) ^ 0x31;
        } else {
            crc <<= 1;
        }
    }
  }

  return crc;
}

uint32_t DFRobot_STCC4::getID(void)  
{
  for (uint8_t i = 0; i < 5; i++){
    delay(200);
    uint8_t rBuf[18] = {0};
    uint32_t id;
    writeCMD16(STCC4_GET_ID);
    readData(rBuf, 18);
    
    uint16_t data1 = ((uint16_t)rBuf[0] << 8) | rBuf[1];
    uint16_t data2 = ((uint16_t)rBuf[3] << 8) | rBuf[4];
    uint8_t crc1 = rBuf[2];
    uint8_t crc2 = rBuf[5];
    
    uint8_t calculatedCrc1 = calculationCRC(&data1, 1);
    uint8_t calculatedCrc2 = calculationCRC(&data2, 1);
    
    if(crc1 == calculatedCrc1 || crc2 == calculatedCrc2) {
      id = ((uint32_t)rBuf[0] << 24) | ((uint32_t)rBuf[1] << 16) | ((uint32_t)rBuf[3] << 8) | (uint32_t)rBuf[4];
      return id;
    }
  }
  
  return 0;
}

bool DFRobot_STCC4::startMeasurement(void)
{
  if(writeCMD16(STCC4_START_CONT_MEASURE)){
    return false;
  }

  return true;
}

bool DFRobot_STCC4::stopMeasurement(void)
{
  if(writeCMD16(STCC4_STOP_CONT_MEASURE)){
    return false;
  }

  return true;
}

bool DFRobot_STCC4::measurement(uint16_t* co2Concentration, 
                                        float* temperature, 
                                        float* humidity, 
                                        uint16_t* sensorStatus)
{
  uint8_t rBuf[12];
  if(writeCMD16(STCC4_READ_MEASURE) != ERR_OK){
    return false;
  }
  if(readData(rBuf, 12) != 12){
    return false;
  }

  *co2Concentration = (rBuf[0] << 8) | rBuf[1];
  int16_t tempRaw = (rBuf[3] << 8) | rBuf[4];
  *temperature = -45.0 + ((175.0 * tempRaw) / 65535.0);
  uint16_t humRaw = (rBuf[6] << 8) | rBuf[7];
  *humidity = -6.0 + ((125.0 * humRaw) / 65535.0);
  *sensorStatus = (rBuf[9] << 8) | rBuf[10];

  return true;
}

bool DFRobot_STCC4::setRHTcompensation(uint16_t temperature, uint16_t humidity)
{
  if(temperature < 10 || temperature > 40 || humidity < 20 || humidity > 80)
  {
    return false;
  }
  uint16_t wBuf[2];
  temperature = (temperature + 45) * 65535 / 175; 
  humidity = (humidity + 6) * 65535 / 125; 
  wBuf[0] = temperature;
  wBuf[1] = humidity;
  if(writeData(STCC4_SET_RHT_COMPENSATION, wBuf, 2) != ERR_OK){
    return false;
  }

  return true;
}

bool DFRobot_STCC4::setPressureCompensation(uint16_t pressure)
{
  if(pressure < 400 || pressure > 1100)
  {
    return false;
  }
  pressure = pressure  * 50;
  if(writeData(STCC4_SET_PRESSURE_COMPENSATION, &pressure, 1) != ERR_OK){
    return false;
  }

  return true;
}

bool DFRobot_STCC4::singleMeasurement(void)
{
  if(writeCMD16(STCC4_SINGLE_SHOT) != ERR_OK){
    return false;
  }

  return true;
}

bool DFRobot_STCC4::sleep(void)
{
  if(writeCMD16(STCC4_SLEEP) != ERR_OK){
    return false;
  }

  return true;
}

bool DFRobot_STCC4::wakeup(void)
{
  if(writeCMD8(STCC4_WAKEUP) != ERR_OK){
    return false;
  }

  return true;
}

bool DFRobot_STCC4::softRest(void)
{
  if(writeCMD8(STCC4_SOFT_RESET) != ERR_OK){
    return false;
  }

  return true;
}

bool DFRobot_STCC4::factoryReset(void)
{
  uint8_t rBuf[2];
  if(writeCMD16(STCC4_FACTORY_RESET) != ERR_OK){
    return false;
  }
  if(readData(rBuf, 2) != 2)
    return false;
  
  uint16_t response = (rBuf[0] << 8) | rBuf[1];
  if(response == 0)
    return true;
  
  return false;
}

bool DFRobot_STCC4::enableTestingMode(void)
{
  if(writeCMD16(STCC4_ENABLE_TESTING_MODE) != ERR_OK){
    return false;
  }

  return true;
}

bool DFRobot_STCC4::disableTestingMode(void)
{
  if(writeCMD16(STCC4_DISABLE_TESTING_MODE) != ERR_OK){
    return false;
  }

  return true;
}

bool DFRobot_STCC4::forcedRecalibration(uint16_t targetPpm, uint16_t* frcCorrection)
{
  if(targetPpm > 32000)
  {
    return false;
  }
  uint16_t wBuf[1];
  uint8_t rBuf[3];
  wBuf[0] = targetPpm;
  if(writeData(STCC4_FORC_CALIBRATION, wBuf, 1) != ERR_OK){
    return false;
  }
  delay(200);
  if(readData(rBuf, 3) != 3){
    return false;
  }
  *frcCorrection = rBuf[0] << 8 | rBuf[1];

  return true;
}

bool DFRobot_STCC4_I2C::begin(void) 
{
  _pWire->begin();
  _pWire->beginTransmission(_deviceAddr);
  
  if(_pWire == NULL)
  {
    Serial.println("_pWire == NULL");
    return ERR_DATA_BUS;
  }
  return _pWire->endTransmission() == 0 ? true : false; 
}

DFRobot_STCC4_I2C::DFRobot_STCC4_I2C(TwoWire *pWire, uint8_t addr) {
  _pWire = pWire;
  _deviceAddr = addr;
  _pWire->setClock(100000);
}

bool DFRobot_STCC4_I2C::writeData(uint16_t cmd, uint16_t * pBuf, size_t size)
{
  uint8_t buf[2];
  buf[0] = (cmd >> 8) & 0xFF;
  buf[1] = cmd & 0xFF;

  if(_pWire == NULL) {
    Serial.println("_pWire == NULL");
  }

  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(buf[0]);
  _pWire->write(buf[1]);

  for (size_t i = 0; i < size; i++) {
    buf[0] = (pBuf[i] >> 8) & 0xFF;
    buf[1] = pBuf[i] & 0xFF;
    _pWire->write(buf[0]);
    _pWire->write(buf[1]);
    _pWire->write(calculationCRC(&pBuf[i], 1));
  }

  if(_pWire->endTransmission() != 0) {
    //DBG("I2C write error");
    return ERR_DATA_WRITE;
  }

  return ERR_OK;
}

bool DFRobot_STCC4_I2C::writeCMD8(uint8_t cmd)
{
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(cmd);

  if(_pWire->endTransmission() != 0) {
    //DBG("I2C write error");
    return ERR_DATA_WRITE;
  }

  return ERR_OK;
}

bool DFRobot_STCC4_I2C::writeCMD16(uint16_t cmd)
{
  uint8_t buf[2];
  buf[0] = (cmd >> 8) & 0xFF;
  buf[1] = cmd & 0xFF;

  if(_pWire == NULL) {
    Serial.println("_pWire == NULL");
  }

  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(buf[0]);
  _pWire->write(buf[1]);

  if(_pWire->endTransmission() != 0) {
    //DBG("I2C write error");
    return ERR_DATA_WRITE;
  }

  return ERR_OK;
}

size_t DFRobot_STCC4_I2C::readData(uint8_t * pBuf, size_t size)
{
  size_t ret = 0;

  if(_pWire == NULL) {
    Serial.println("_pWire == NULL");
  }

  ret = _pWire->requestFrom(_deviceAddr, (uint8_t) size);
  for (size_t i = 0; i < ret; i++) {
    pBuf[i] = _pWire->read();
  }

  return ret;
}