// This example is not self-contained.
// It requires usage of the example driver specific to your platform.
// See the HAL documentation.

#include "src/bindings/hal_common.h"
#include "src/bindings/bricklet_rgb_led_button.h"

void check(int rc, const char *msg);
void example_setup(TF_HAL *hal);
void example_loop(TF_HAL *hal);

static TF_RGBLEDButton rlb;

void example_setup(TF_HAL *hal) {
	// Create device object
	check(tf_rgb_led_button_create(&rlb, NULL, hal), "create device object");

	// Get current button state
	uint8_t state;
	check(tf_rgb_led_button_get_button_state(&rlb, &state), "get button state");

	if (state == TF_RGB_LED_BUTTON_BUTTON_STATE_PRESSED) {
		tf_hal_printf("State: Pressed\n");
	} else if (state == TF_RGB_LED_BUTTON_BUTTON_STATE_RELEASED) {
		tf_hal_printf("State: Released\n");
	}
}

void example_loop(TF_HAL *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
