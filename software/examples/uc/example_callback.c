

#include "bindings/hal_common.h"
#include "bindings/bricklet_rgb_led_button.h"

#define UID "XYZ" // Change XYZ to the UID of your RGB LED Button Bricklet

void check(int rc, const char* msg);



// Callback function for button state changed callback
void button_state_changed_handler(TF_RGBLEDButton *device, uint8_t state,
                                  void *user_data) {
	(void)device; (void)user_data; // avoid unused parameter warning

	if(state == TF_RGB_LED_BUTTON_BUTTON_STATE_PRESSED) {
		tf_hal_printf("State: Pressed\n");
	} else if(state == TF_RGB_LED_BUTTON_BUTTON_STATE_RELEASED) {
		tf_hal_printf("State: Released\n");
	}
}


TF_RGBLEDButton rlb;

void example_setup(TF_HalContext *hal) {
	// Create device object
	check(tf_rgb_led_button_create(&rlb, UID, hal), "create device object");


	// Register button state changed callback to function button_state_changed_handler
	tf_rgb_led_button_register_button_state_changed_callback(&rlb,
	                                                        button_state_changed_handler,
	                                                        NULL);

}

void example_loop(TF_HalContext *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
