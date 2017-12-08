#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

# FIXME: This example is incomplete

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_rgb_led_button'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change XYZ to the UID of your RGB LED Button Bricklet

ipcon = IPConnection.new # Create IP connection
rlb = BrickletRGBLEDButton.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Get current button state
state = rlb.get_button_state
puts "State: #{state}"

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
