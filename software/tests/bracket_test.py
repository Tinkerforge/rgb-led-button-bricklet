HOST = "localhost"
PORT = 4223
UID1 = "D1i"
UID2 = "D1u"
UID3 = "D1t"

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_rgb_led_button import BrickletRGBLEDButton
import time
import colorsys

b1 = None
b2 = None
b3 = None

color = 0

off = False

def b1_cb(state):
    global b2, b3, off
    if state == 0:
        off = True
        b1.set_color(255, 0, 0)
        b2.set_color(0, 0, 0)
        b3.set_color(0, 0, 0)

def b2_cb(state):
    global color, b1, b3, off
    off = False
    b1.set_color(255, 255, 255)
    if state == 1:
        if color == 0:
            b3.set_color(255, 0, 0)
            color = 1
        elif color == 1:
            b3.set_color(0, 255, 0)
            color = 2
        elif color == 2:
            b3.set_color(0, 0, 255)
            color = 0

def b3_cb(state):
    global b1, off
    off = False
    b1.set_color(255, 255, 255)

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    ipcon.connect(HOST, PORT)
    b1 = BrickletRGBLEDButton(UID1, ipcon)
    b2 = BrickletRGBLEDButton(UID2, ipcon)
    b3 = BrickletRGBLEDButton(UID3, ipcon)

    b1.register_callback(b1.CALLBACK_BUTTON_STATE_CHANGED, b1_cb)
    b2.register_callback(b2.CALLBACK_BUTTON_STATE_CHANGED, b2_cb)
    b3.register_callback(b3.CALLBACK_BUTTON_STATE_CHANGED, b3_cb)

    b1.set_color(255, 255, 255)

    gradient = 0
    count = 0

    while True:
        time.sleep(0.01)
        if b3.get_button_state() == 0:
            r, g, b = colorsys.hsv_to_rgb(1.0*gradient/50, 1, 1)
            b2.set_color(int(r*255), int(g*255), int(b*255))
            gradient += 1
            if gradient > 50:
                gradient  = 0
        elif off:
            continue
            count += 5
            if count < 256 > 125:
                b2.set_color(count, count, count)
                b3.set_color(count, count, count)
            else:
                b2.set_color(510-count, 510-count, 510-count)
                b3.set_color(510-count, 510-count, 510-count)
            if count >= 510:
                count = 0
        
    raw_input("Press key to exit\n") 
    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected
