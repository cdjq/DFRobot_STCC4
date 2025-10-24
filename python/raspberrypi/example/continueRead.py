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

# Set temperature compensation.
# The range is 10 - 40℃.
# The unit is degrees Celsius.
# It only takes effect when the temperature and humidity sensor is disconnected from the STCC4.
tCompensation = 26

# Set humidity compensation.
# The range is 20 - 80%RH.
# It only takes effect when the temperature and humidity sensor is disconnected from the STCC4.
hCompensation = 55

# Set pressure compensation.
# The range is 400 - 1100 hPa.
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
ADDR = 0x64

# Create an instance of the DFRobot_STCC4_I2C class with the I2C address ADDR.
sensor = DFRobot_STCC4_I2C(ADDR)

def setup():
    print("This is a demo of continuous reading sensor data.\n")
    
    # Wake up the sensor
    sensor.wakeup()
    time.sleep(0.01)
    
    # Get the ID of the sensor.
    # The ID values read should all be 0x901018A.
    sensor_id = sensor.get_id()
    if sensor_id is not None:
        print(f"ID: 0x{sensor_id:X}")
    else:
        print("Failed to read sensor ID")
    
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
    
    sensor.start_measurement()  # Start measurement

def loop():
    while True:
        time.sleep(2)
        
        # Read measurement data
        result = sensor.measurement()
        if result is not None:
            co2Concentration, temperature, humidity, sensorStatus = result
            print(f"CO2: {co2Concentration} ppm  temperature: {temperature:.2f} ℃  humidity: {humidity:.2f} %  status: {sensorStatus}")

if __name__ == "__main__":
    try:
        setup()
        loop()
    except KeyboardInterrupt:
        print("\nProgram interrupted by user")