# DFRobot_STCC4

- [中文版](./README_CN.md)

The STCC4 is Sensirion’s next generation miniature CO2 sensor for indoor air quality applications. Based on the
thermal conductivity sensing principle and Sensirion’s CMOSens® technology, the STCC4 enables monitoring
of CO2 gas concentration in ambient indoor air conditions at an unmatched cost-effectiveness and form factor.<br>
SMD assembly as well as tape & reel packaging allows cost- and space-effective integration of the STCC4 for
high-volume applications. The STCC4 is 100% factory-calibrated and enables automatic on-board
compensation of the CO2 output for humidity and temperature through an external SHT4x sensor.
![Fermion_BMV080](image/Fermion_BMV080.JPG)
 
## Product Link（[https://www.dfrobot.com.cn](https://www.dfrobot.com.cn)）
    SKU:SEN0678

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

To use this library, first download the library file, upload the file to your Raspberry Pi device, and then enter the "examples" folder and run the sample programs.


## Methods

```python
def get_id(self) -> Optional[bytes]:
        """
        Get the sensor ID
        :return: Sensor ID as bytes if successful, None otherwise
        """
        raise NotImplementedError
 
def start_measurement(self) -> bool:
    """
    Start continuous measurement
    :return: True if successful, False otherwise
    """
    raise NotImplementedError

def stop_measurement(self) -> bool:
    """
    Stop continuous measurement
    :return: True if successful, False otherwise
    """
    raise NotImplementedError

def measurement(self) -> Optional[Tuple[int, float, float, int]]:
    """
    Read measurement data
    :return: Tuple of (co2_concentration, temperature, humidity, sensor_status).
    co2_concentration : CO2 concentration
    temperature : Temperature
    humidity : Humidity
    sensor_status : Sensor status
    None : error
    """
    raise NotImplementedError

def set_rht_compensation(self, temperature: int, humidity: int) -> bool:
    """
    Set temperature and humidity compensation
    :param temperature: Temperature compensation value
    :param humidity: Humidity compensation value
    :return: True if successful, False otherwise
    """
    raise NotImplementedError

def set_pressure_compensation(self, pressure: int) -> bool:
    """
    Set pressure compensation
    :param pressure: Pressure compensation value
    :return: True if successful, False otherwise
    """
    raise NotImplementedError

def single_measurement(self) -> bool:
    """
    Perform a single shot measurement
    :return: True if successful, False otherwise
    """
    raise NotImplementedError

def fall_asleep(self) -> bool:
    """
    Put the sensor into sleep mode
    :return: True if successful, False otherwise
    """
    raise NotImplementedError

def wakeup(self) -> bool:
    """
    Wake up the sensor from sleep mode
    :return: True if successful, False otherwise
    """
    raise NotImplementedError

def soft_reset(self) -> bool:
    """
    Perform a soft reset of the sensor
    :return: True if successful, False otherwise
    """
    raise NotImplementedError

def factory_reset(self) -> bool:
    """
    Perform a factory reset of the sensor
    :return: True if successful, False otherwise
    """
    raise NotImplementedError

def enable_testing_mode(self) -> bool:
    """
    Enable testing mode
    :return: True if successful, False otherwise
    """
    raise NotImplementedError

def disable_testing_mode(self) -> bool:
    """
    Disable testing mode
    :return: True if successful, False otherwise
    """
    raise NotImplementedError

def forced_recalibration(self, target_ppm: int) -> Optional[int]:
    """
    Perform forced recalibration
    :param target_ppm: Target PPM value for recalibration
    :return: Correction value if successful, None otherwise
    """
    raise NotImplementedError
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
raspberry pi 4     |      √       |              |             |     
raspberry pi 5     |              |              |      √      |     
<br>

## History

- 2025/10/23 - Version 1.0.0 released.

## Credits

Written by lbx(liubx8023@gmail.com), 2025. (Welcome to our [website](https://www.dfrobot.com/))
