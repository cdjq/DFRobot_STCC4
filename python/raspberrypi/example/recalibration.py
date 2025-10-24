"""!
    @file recalibration.py
    @brief This routine will calibrate the sensor, but it requires the actual CO2 concentration in the environment to be known. 
    @n The routine will perform 30 pre-calibration samplings, then conduct the calibration, and continue sampling after the calibration.
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

# The target CO2 concentration to calibrate. 
# The input range of CO2 concentration is 0 - 32000 ppm.
target = 600

# The frc correction values returned by the sensor are generally not used.
frcCorrection = 0

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

# The sensor can communicate via two specific addresses (0x64 and 0x65).
# "Dip switch" (for Gravity version): A small switch on the board that you can toggle by hand.
ADDR = 0x64

# Initialize the sensor
sensor = DFRobot_STCC4_I2C(addr = ADDR)

def setup():
    print("This demo will force-calibrate the sensor based on the CO2 concentration you input.\n")
    
    # Wake up the sensor
    sensor.wakeup()
    time.sleep(0.01)  # 10ms delay

    # Get the ID of the sensor.
    # The ID values read should all be 0x0901018a.
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

    # Start 30 consecutive samplings
    if not sensor.start_measurement():
        print("Failed to start measurement")
        return False
        
    for i in range(30):
        time.sleep(2)  # 2000ms delay
        
        # Read measurement data
        result = sensor.measurement()
        if result is not None:
            co2Concentration, temperature, humidity, sensorStatus = result
            print(f"CO2: {co2Concentration} ppm  temperature: {temperature:.2f} ℃  humidity: {humidity:.2f} %  status: {sensorStatus}")
        else:
            print("Failed to read measurements")

    # Stop sampling
    sensor.stop_measurement()
    time.sleep(1)  # 1000ms delay

    # Start calibration
    global frcCorrection
    frcCorrection = sensor.forced_recalibration(target)

    # The calibration is determined to be valid by checking the value of frc. 
    # If frc is equal to 0xffff or 0, it is invalid; otherwise, it is valid.
    while frcCorrection == 0xFFFF or frcCorrection == 0:
        print("Calibration failed!\n")
        time.sleep(1)  # 1000ms delay
        frcCorrection = sensor.forced_recalibration(target)
        
    print(f"CO2 concentration correction: {frcCorrection}")

    # Start sampling
    if not sensor.start_measurement():
        print("Failed to start measurement after calibration")
        return False
        
    return True

def loop():
    time.sleep(2)  # 2000ms delay
    
    # Read measurement data
    result = sensor.measurement()
    if result is not None:
        co2Concentration, temperature, humidity, sensorStatus = result
        print(f"CO2: {co2Concentration} ppm  temperature: {temperature:.2f} ℃  humidity: {humidity:.2f} %  status: {sensorStatus}")
    else:
        print("Failed to read measurements")

if __name__ == "__main__":
    if not setup():
        sys.exit(1)

    try:
        while True:
            loop()
    except KeyboardInterrupt:
        print("\nStopping...")
        sensor.stop_measurement()