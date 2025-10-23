"""!
    @file singleRead.py
    @brief This routine employs a single-sampling method, sampling once every 10 seconds and then entering the sleep mode.
    @n If you connect the humidity and temperature sensor, you can obtain the concentration of carbon dioxide and temperature and humidity.
    @n If the temperature and humidity sensors are not connected, the obtained temperature and humidity values is the default values.
    @details Experimental phenomenon: The read data will be output in the terminal.

    @copyright Copyright (c) 2025 DFRobot Co.Ltd (http://www.dfrobot.com)
    @license The MIT License (MIT)
    @author [lbx](liubx8023@gmail.com)
    @version V1.0
    @date 2025-08-14
    @url https://github.com/DFRobot/DFRobot_STCC4
"""

import sys
import time
sys.path.append("./..")  
from DFRobot_STCC4 import DFRobot_STCC4_I2C

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

# The environmental temperature obtained from STCC4. 
# If no temperature and humidity sensor is connected, this value will be the default value or the set value.
temperature = 0.0

# The environmental humidity obtained from STCC4. 
# If no temperature and humidity sensor is connected, this value will be the default value or the set value.
humidity = 0.0

# The CO2 concentration obtained from STCC4.
co2Concentration = 0

# The status of the sensor.
sensorStatus = 0

# The sensor can communicate via two specific addresses (0x64 and 0x65).
# "Dip switch" (for Gravity version): A small switch on the board that you can toggle by hand.
ADDR = 0x64

# Create an instance of the DFRobot_STCC4_I2C class with the I2C address ADDR.
sensor = DFRobot_STCC4_I2C(addr = ADDR)

def setup():
    print("This is a demo of single reading sensor data.")
    print("This demo will display a \"Data write failed\", but this is a normal occurrence.")
    print("Because the sensor has entered sleep mode, there will be no response when it is awakened.\n\n")

    # Wake up the sensor
    sensor.wakeup()
    time.sleep(0.1)  # 100ms delay

    # Get the ID of the sensor.
    # The ID values read should all be 0x0901018a.
    ID = sensor.get_id()
    if ID:
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
        
    return True

def loop():
    # Wake up the sensor
    sensor.wakeup()
    time.sleep(0.1)  # 100ms delay

    # Start a single-shot measurement
    if sensor.single_shot():
        time.sleep(0.9)  # 900ms delay

        # Read sensor data
        data = sensor.measurement()
        if data:
            co2, temp, hum, status = data
            print(f"CO2: {co2} ppm  temperature: {temp:.2f} ℃  humidity: {hum:.2f} % ")
        else:
            print("Failed to read measurements")
    else:
        print("Failed to start single shot measurement")

    # Enter sleep mode
    if sensor.fall_asleep():
        print("sleep 10s")
    else:
        print("Failed to put sensor to sleep")
        
    time.sleep(9)  # 9000ms delay

if __name__ == "__main__":
    if not setup():
        sys.exit(1)
        
    try:
        while True:
            loop()
    except KeyboardInterrupt:
        print("\nStopping...")
        sensor.stop_measurement()