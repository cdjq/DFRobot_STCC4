# DFRobot_STCC4

- [English Version](./README.md)

STCC4 是森思罗公司推出的下一代微型二氧化碳传感器，专为室内空气质量应用而设计。它基于热导率传感原理，并采用了森思罗公司的 CMOSens® 技术，能够以极高的性价比和紧凑的尺寸实现对室内空气环境中二氧化碳浓度的监测。STCC4 支持 SMD 组装以及卷带式封装，这使得其能够以经济且高效的方式集成到大规模应用中。STCC4 100% 在工厂进行校准，并可通过外部 SHT4x 传感器自动对二氧化碳输出进行补偿，以适应湿度和温度的变化。
![Fermion_STCC4](image/Fermion_STCC4.JPG)

## 产品链接（[https://www.dfrobot.com.cn](https://www.dfrobot.com.cn)）
    SKU:SEN0678

## 目录

  * [概述](#概述)
  * [库安装](#库安装)
  * [方法](#方法)
  * [兼容性](#兼容性)
  * [历史](#历史)
  * [创作者](#创作者)

## 概述

DFRobot_STCC4 是一个为驱动Sensirion公司新型CO2测量芯片 STCC4 而设计的 Arduino 和 raspberrypi库。<br>
此库只提供了一种种通信方式：IIC，以及一些基本的例程。理论上它支持所有能使用IIC的平台。

## 库安装

要使用此库，请首先下载库文件，将其粘贴到“Arduino\libraries”目录中，然后打开“示例”文件夹并运行该文件夹中的演示程序。


## 方法

```C++
/**
     * @fn calculationCRC
     * @brief 计算数据的循环冗余校验码（CRC）
     * @param data 需要计算的CRC数据
     * @param length 数据长度
     * @return CRC
     */
  uint8_t calculationCRC(uint16_t *data, size_t length);

  /**
     * @fn getID
     * @brief 获取传感器的ID
     * @param id 获取的ID
     * @return true 成功， false 失败
     */
  bool getID(char *id);

  /**
     * @fn startMeasurement
     * @brief 开启传感器连续测量
     * @return true 启动成功， false 启动失败
     */
  bool startMeasurement(void);

  /**
     * @fn stopMeasurement
     * @brief 停止传感器连续测量
     * @n 该传感器执行此指令需要 1200 毫秒。
     * @return true 停止成功， false 停止失败
     */
  bool stopMeasurement(void);

  /**
     * @fn measurement
     * @brief 读取测量数据
     * @param co2Concentration 用于存储二氧化碳浓度的指针
     * @param temperature 用于存储温度的指针
     * @param humidity 用于存储湿度的指针
     * @param sensorStatus 用于存储传感器状态的指针
     * @return true 获取成功， false 获取失败
     */
  bool measurement(uint16_t* co2Concentration, 
                                        float* temperature, 
                                        float* humidity, 
                                        uint16_t* sensorStatus);

  /**
     * @fn setRHTcompensation
     * @brief 手动设置温度和湿度补偿
     * @param temperature 温度补偿值
     * @param humidity 湿度补偿值
     * @return true 设置成功， false 设置失败
     */
  bool setRHTcompensation(uint16_t temperature, uint16_t humidity);

  /**
     * @fn setPressureCompensation
     * @brief 手动设定压力补偿
     * @param pressure 压力补偿值
     * @return true 设置成功， false 设置失败
     */
  bool setPressureCompensation(uint16_t pressure);

  /**
     * @fn singleShot
     * @brief 进行一次单次测量
     * @n 该传感器执行此指令需要 500 毫秒的时间。
     * @return true 成功， false 失败
     */
  bool singleShot(void);

  /**
     * @fn sleep
     * @brief 将传感器置于休眠模式
     * @return true 设置成功， false 设置失败
     */
  bool sleep(void);

  /**
     * @fn wakeup
     * @brief 将传感器从休眠模式唤醒
     * @return true 设置成功， false 设置失败
     */
  bool wakeup(void);

  /**
     * @fn softRest
     * @brief 对传感器进行软复位操作
     * @return true 设置成功， false 设置失败
     */
  bool softRest(void);

  /**
     * @fn factoryReset
     * @brief 对传感器进行工厂复位操作
     * @return true 设置成功， false 设置失败
     */
  bool factoryReset(void);

  /**
     * @fn enableTestingMode
     * @brief 启用测试模式
     * @return true 设置成功， false 设置失败
     */
  bool enableTestingMode(void);

  /**
     * @fn disableTestingMode
     * @brief 禁用测试模式
     * @return true 设置成功， false 设置失败
     */
  bool disableTestingMode(void);

  /**
     * @fn forcedRecalibration
     * @brief 进行强制重新校准
     * @param targetPpm 重新校准的目标 PPM 值
     * @param frcCorrection 用于存储修正值的指针
     * @return true 校准成功， false 校准失败
     */
  bool forcedRecalibration(uint16_t targetPpm, uint16_t* frcCorrection);
```

## 兼容性

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno        |      √       |              |             | 
Mega2560           |      √       |              |             | 
Leonardo           |      √       |              |             | 
ESP32              |      √       |              |             | 
micro:bit          |      √       |              |             | 
raspberry pi       |      √       |              |             |     
<br>

## 历史

- 2025/10/23 - Version 1.0.0  版本

## 创作者

作者： lbx(liubx8023@gmail.com), 2025. (欢迎访问我们的 [网站](https://www.dfrobot.com/))
