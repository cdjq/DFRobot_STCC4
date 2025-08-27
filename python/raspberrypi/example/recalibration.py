"""!
    * @file reaclibration.py
    * @brief This routine first conducts 35 consecutive samplings, then performs calibration, and subsequently continues with continuous sampling.
    * @n If you connect the humidity and temperature sensor, you can obtain the concentration of carbon dioxide and temperature and humidity.
    * @n If the temperature and humidity sensors are not connected, the obtained temperature and humidity values is the default values.
    * @details Experimental phenomenon: The read data will be output in the terminal.
    * 
    * @copyright Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
    * @license The MIT License (MIT)
    * @author [lbx](liubx8023@gmail.com)
    * @version V1.0
    * @date 2025-08-14
    * @url https://github.com/DFRobot/DFRobot_STCC4
"""

import sys
import time
sys.path.append("./..")  
from DFRobot_STCC4 import DFRobot_STCC4_I2C

# Initialize the sensor
sensor = DFRobot_STCC4_I2C(addr = 0x64)

target = 500  #Correction target
correction = [0]
co2Concentration = [0]
temperature = [0.0]
humidity = [0.0]
sensorStatus = [0]

print("This demo will force-calibrate the sensor based on the CO2 concentration you input.\n\n")
time.sleep(1)

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

# Start 35 consecutive samplings
for i in range(35):
    data = sensor.measurement()
    if data:
        co2, temp, hum, status = data
        print(f"Before calibration CO2: {co2} ppm, Temperature: {temp:.2f}°C, Humidity: {hum:.2f}%")
    else:
        print("Failed to read measurements")
    time.sleep(1)

sensor.stop_measurement()
time.sleep(1)

# Start calibration
correction = sensor.forced_recalibration(target)
if correction != 65535:
    print(f"CO2 concentration correction: {correction}")
else:
    print("CO2 concentration correction error")

sensor.wakeup()
time.sleep(0.1)  # 10ms delay
sensor.start_measurement()
time.sleep(1)
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