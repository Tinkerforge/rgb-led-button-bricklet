

#include "bindings/hal_common.h"
#include "bindings/bricklet_rgb_led_button.h"

#define UID "XYZ" // Change XYZ to the UID of your RGB LED Button Bricklet

void check(int rc, const char* msg);




TF_RGBLEDButton rlb;

void example_setup(TF_HalContext *hal) {
	// Create device object
	check(tf_rgb_led_button_create(&rlb, UID, hal), "create device object");


	// Get current button state
	uint8_t state;
	check(tf_rgb_led_button_get_button_state(&rlb, &state), "get button state");

	if(state == TF_RGB_LED_BUTTON_BUTTON_STATE_PRESSED) {
		tf_hal_printf("State: Pressed\n");
	} else if(state == TF_RGB_LED_BUTTON_BUTTON_STATE_RELEASED) {
		tf_hal_printf("State: Released\n");
	}

}

void example_loop(TF_HalContext *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
