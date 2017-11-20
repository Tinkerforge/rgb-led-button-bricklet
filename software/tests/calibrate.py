#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "X6z6j" # Change XYZ to the UID of your RGB LED Bricklet

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_rgb_led_button import BrickletRGBLEDButton

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    button = BrickletRGBLEDButton(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    button.set_color_calibration(100, 100, 55)
    print(button.get_color_calibration())
    print(button.get_color())

    raw_input("Press key to exit\n") # Use input() in Python 3
    ipcon.disconnect()
