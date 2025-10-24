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

要使用此库，请首先下载库文件，将文件上传至你的树莓派设备上，然后进入examples文件夹，运行示例程序。


## 方法

```python
def get_id(self) -> Optional[bytes]:
        """
        获取传感器ID
        :return: 如果成功返回传感器ID字节，否则返回None
        """
        raise NotImplementedError
 
def start_measurement(self) -> bool:
    """
    开始连续测量
    :return: 如果成功返回True，否则返回False
    """
    raise NotImplementedError

def stop_measurement(self) -> bool:
    """
    停止连续测量
    :return: 如果成功返回True，否则返回False
    """
    raise NotImplementedError

def measurement(self) -> Optional[Tuple[int, float, float, int]]:
    """
    读取测量数据
    :return: (co2_concentration, temperature, humidity, sensor_status)元组。
    co2_concentration : CO2浓度
    temperature : 温度
    humidity : 湿度
    sensor_status : 传感器状态
    None : 错误
    """
    raise NotImplementedError

def set_rht_compensation(self, temperature: int, humidity: int) -> bool:
    """
    设置温湿度补偿
    :param temperature: 温度补偿值
    :param humidity: 湿度补偿值
    :return: 如果成功返回True，否则返回False
    """
    raise NotImplementedError

def set_pressure_compensation(self, pressure: int) -> bool:
    """
    设置压力补偿
    :param pressure: 压力补偿值
    :return: 如果成功返回True，否则返回False
    """
    raise NotImplementedError

def single_measurement(self) -> bool:
    """
    执行单次测量
    :return: 如果成功返回True，否则返回False
    """
    raise NotImplementedError

def fall_asleep(self) -> bool:
    """
    使传感器进入睡眠模式
    :return: 如果成功返回True，否则返回False
    """
    raise NotImplementedError

def wakeup(self) -> bool:
    """
    唤醒传感器从睡眠模式
    :return: 如果成功返回True，否则返回False
    """
    raise NotImplementedError

def soft_reset(self) -> bool:
    """
    执行传感器软重置
    :return: 如果成功返回True，否则返回False
    """
    raise NotImplementedError

def factory_reset(self) -> bool:
    """
    执行传感器出厂重置
    :return: 如果成功返回True，否则返回False
    """
    raise NotImplementedError

def enable_testing_mode(self) -> bool:
    """
    启用测试模式
    :return: 如果成功返回True，否则返回False
    """
    raise NotImplementedError

def disable_testing_mode(self) -> bool:
    """
    禁用测试模式
    :return: 如果成功返回True，否则返回False
    """
    raise NotImplementedError

def forced_recalibration(self, target_ppm: int) -> Optional[int]:
    """
    执行强制重新校准
    :param target_ppm: 重新校准的目标PPM值
    :return: 如果成功返回校正值，否则返回None
    """
    raise NotImplementedError
```

## 兼容性

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
raspberry pi 4     |      √       |              |             |     
raspberry pi 5     |              |              |      √      |     
<br>

## 历史

- 2025/10/23 - Version 1.0.0  版本

## 创作者

作者： lbx(liubx8023@gmail.com), 2025. (欢迎访问我们的 [网站](https://www.dfrobot.com/))
