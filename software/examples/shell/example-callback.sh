#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your RGB LED Button Bricklet

# Handle incoming button state changed callbacks
tinkerforge dispatch rgb-led-button-bricklet $uid button-state-changed &

echo "Press key to exit"; read dummy

kill -- -$$ # Stop callback dispatch in background
