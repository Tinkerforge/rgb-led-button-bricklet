

#include "bindings/hal_common.h"
#include "bindings/bricklet_rgb_led_button.h"

#define UID "XYZ" // Change XYZ to the UID of your RGB LED Button Bricklet

void check(int rc, const char* msg);




TF_RGBLEDButton rlb;

void example_setup(TF_HalContext *hal) {
	// Create device object
	check(tf_rgb_led_button_create(&rlb, UID, hal), "create device object");


	// Set light blue color
	check(tf_rgb_led_button_set_color(&rlb, 0, 170, 234), "call set_color");

}

void example_loop(TF_HalContext *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
