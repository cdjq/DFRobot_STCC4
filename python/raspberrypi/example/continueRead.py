"""!
    @file continueRead.py
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

"""
 The sensor can communicate via two specific addresses (0x64 and 0x65).
 "Dip switch" (for Gravity version): A small switch on the board that you can toggle by hand.
"""
ADDR = 0x64

# Set temperature compensation.
# The unit is degrees Celsius.
# It only takes effect when the temperature and humidity sensor is disconnected from the STCC4.
tCompensation = 26

# Set humidity compensation.
# It only takes effect when the temperature and humidity sensor is disconnected from the STCC4.
hCompensation = 55

# Set humidity compensation.
# Unit is hPa.
pCompensation = 950

# Initialize the sensor
sensor = DFRobot_STCC4_I2C(addr = ADDR)

def setup():
    print("This is a demo of continuous reading sensor data.\n")

    # Wake up the sensor
    sensor.wakeup()
    
    # Get the ID of the sensor.
    # The ID values read should all be 0x0901018a.
    ID = sensor.get_id()
    if ID:
        # Only use indices 0,1,3,4 as shown in the original print statement
        print(f"ID: {ID[0]:02x}{ID[1]:02x}{ID[3]:02x}{ID[4]:02x}")
    else:
        print("Get ID error!")
        return False

    # Set temperature and humidity compensation
    if sensor.set_rht_compensation(tCompensation, hCompensation):
        print("Set RHT compensation successful.")
    else:
        print("Set RHT compensation error!")

    # Set pressure compensation
    if sensor.set_pressure_compensation(pCompensation):
        print("Set pressure compensation successful.")
    else:
        print("Set pressure compensation error!")

    # Start measurement
    if sensor.start_measurement():
        print("Measurement started")
        return True
    else:
        print("Failed to start measurement")
        return False

def loop():
    # Read measurement data
    data = sensor.measurement()
    if data:
        co2, temp, hum, status = data
        print(f"CO2: {co2} ppm  temperature: {temp:.2f} ℃  humidity: {hum:.2f} % ")
        return True
    else:
        print("Failed to read measurements")
        return False

if __name__ == "__main__":
    if not setup():
        sys.exit(1)
    
    try:
        while True:
            loop()
            time.sleep(2)  # 1500ms delay
    except KeyboardInterrupt:
        print("\nStopping...")
        sensor.stop_measurement()