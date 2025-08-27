"""!
    @file continueRead.ino
    @brief This routine continuously reads sensor data via the IIC interface and can obtain one piece of data per second. 
    @n If you connect the humidity and temperature sensor, you can obtain the concentration of carbon dioxide and temperature and humidity.
    @n If the temperature and humidity sensors are not connected, the obtained temperature and humidity values is the default values.
    @details Experimental phenomenon: The read data will be output in the terminal.

    @copyright Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
    @license The MIT License (MIT)
    @author [lbx](liubx8023@gmail.com)
    @version V1.0
    @date 2025-08-25
    @url https://github.com/DFRobot/DFRobot_STCC4
 """

import sys
import time
sys.path.append("./..")  
from DFRobot_STCC4 import DFRobot_STCC4_I2C

# Initialize the sensor
sensor = DFRobot_STCC4_I2C(addr = 0x64)

print("This is a demo of continuous reading sensor data.\n\n")
# Read ID
ID = sensor.get_id()
if ID:
    print(f"ID:{ID[0]:02x}{ID[1]:02x}{ID[3]:02x}{ID[4]:02x}")
time.sleep(1)

# Start continuous measurement
if sensor.start_measurement():
    print("Measurement started")
else:
    print("Failed to start measurement")

# Read measurements
try:
    while True:
        data = sensor.measurement()
        if data:
            co2, temp, hum, status = data
            print(f"CO2: {co2} ppm, Temperature: {temp:.2f}°C, Humidity: {hum:.2f}%")
        else:
            print("Failed to read measurements")
        time.sleep(1)
except KeyboardInterrupt:
    print("Stopping...")
    sensor.stop_measurement()