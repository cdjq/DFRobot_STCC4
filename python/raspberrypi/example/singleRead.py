"""!
    * @file singleRead.ino
    * @brief This routine employs a single-sampling method, sampling once every 10 seconds and then entering the sleep mode.
    * @n If the SHT4x is connected, it can obtain the CO2 concentration as well as temperature and humidity.
    * @n If the SHT4x is not connected, the obtained temperature and humidity will be the manually compensated values.
    * @details Experimental phenomenon: The read data will be output in the terminal.
    * 
    * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
    * @license The MIT License (MIT)
    * @author [Ouki](ouki.wang@dfrobot.com)
    * @version V1.0
    * @date 2025-08-25
    * @url https://github.com/DFRobot/DFRobot_STCC4
 """

import sys
import time
sys.path.append("./..")  
from DFRobot_STCC4 import DFRobot_STCC4_I2C

# Initialize the sensor
sensor = DFRobot_STCC4_I2C(addr = 0x64)

co2Concentration = [0]
temperature = [0.0]
humidity = [0.0]
sensorStatus = [0]

print("This is a demo of single reading sensor data.")
print("This demo will display a \"Data write failed\", but this is a normal occurrence.")
print("Because the sensor has entered sleep mode, there will be no response when it is awakened.\n\n")
time.sleep(1)

# Read ID
ID = sensor.get_id()
if ID:
    print(f"ID:{ID[0]:02x}{ID[1]:02x}{ID[3]:02x}{ID[4]:02x}")
time.sleep(1)

sensor.wakeup()
time.sleep(0.1)  # 10ms delay

# Start continuous measurement
if sensor.start_measurement():
    print("Measurement started")
else:
    print("Failed to start measurement")

# Read measurements
try:
    while True:
        sensor.wakeup()
        time.sleep(1)
        sensor.single_shot()
        time.sleep(1)
        data = sensor.measurement()
        if data:
            co2, temp, hum, status = data
            print(f"CO2: {co2} ppm, Temperature: {temp:.2f}°C, Humidity: {hum:.2f}%")
        else:
            print("Failed to read measurements")
        #enter sleep mood
        sensor.fall_asleep() 
        print("sleep 10s")
        time.sleep(8)
except KeyboardInterrupt:
    print("Stopping...")
    sensor.stop_measurement()