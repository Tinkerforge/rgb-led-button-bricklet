package main

import (
	"fmt"
	"tinkerforge/ipconnection"
	"tinkerforge/rgb_led_button_bricklet"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your RGB LED Button Bricklet.

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	rlb, _ := rgb_led_button_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	// Get current button state.
	state, _ := rlb.GetButtonState()

	if state == rgb_led_button_bricklet.ButtonStatePressed {
		fmt.Println("State: Pressed")
	} else if state == rgb_led_button_bricklet.ButtonStateReleased {
		fmt.Println("State: Released")
	}

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

}
