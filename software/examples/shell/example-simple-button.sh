#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your RGB LED Button Bricklet

# Get current button state
tinkerforge call rgb-led-button-bricklet $uid get-button-state
