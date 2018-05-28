#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

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

# Register button state changed callback
rlb.register_callback(BrickletRGBLEDButton::CALLBACK_BUTTON_STATE_CHANGED) do |state|
  if state == BrickletRGBLEDButton::BUTTON_STATE_PRESSED
    puts "State: Pressed"
  elsif state == BrickletRGBLEDButton::BUTTON_STATE_RELEASED
    puts "State: Released"
  end
end

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
