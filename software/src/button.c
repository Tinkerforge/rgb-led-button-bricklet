/* rgb-led-button-bricklet
 * Copyright (C) Bastian Nordmeyer <bastian@tinkerforge.com>
 * Copyright (C) Olaf Lüke <olaf@tinkerforge.com>
 *
 * button.c: RGB LED Button driver
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "button.h"

#include "xmc_spi.h"
#include "xmc_gpio.h"

#include "configs/config_button.h"
#include "configs/config.h"

#include "bricklib2/hal/system_timer/system_timer.h"
#include "bricklib2/hal/ccu4_pwm/ccu4_pwm.h"

#include "bricklib2/bootloader/bootloader.h"

#include <string.h>


void button_read_calibration(Button *button) {
	bootloader_read_eeprom_page(LED_CALIBRATION_PAGE, button->calibration_page);

	if(button->calibration_page[LED_CALIBRATION_MAGIC_POS] != LED_CALIBRATION_MAGIC) {
		button->calibration_page[LED_CALIBRATION_R_POS] = 100;
		button->calibration_page[LED_CALIBRATION_G_POS] = 100;
		button->calibration_page[LED_CALIBRATION_B_POS] = 56;
	}
}

void button_write_calibration(Button *button, const uint32_t r, const uint32_t g, const uint32_t b) {
	button->calibration_page[LED_CALIBRATION_MAGIC_POS] = LED_CALIBRATION_MAGIC;
	button->calibration_page[LED_CALIBRATION_R_POS]     = r;
	button->calibration_page[LED_CALIBRATION_G_POS]     = g;
	button->calibration_page[LED_CALIBRATION_B_POS]     = b;

	bootloader_write_eeprom_page(LED_CALIBRATION_PAGE, button->calibration_page);
}

void button_init(Button *button) {
	ccu4_pwm_init(LED_RED_PIN,   LED_RED_CCU4_SLICE,   LED_PERIOD_VALUE);
	ccu4_pwm_init(LED_GREEN_PIN, LED_GREEN_CCU4_SLICE, LED_PERIOD_VALUE);
	ccu4_pwm_init(LED_BLUE_PIN,  LED_BLUE_CCU4_SLICE,  LED_PERIOD_VALUE);

	XMC_GPIO_CONFIG_t button_pin_config = {
		.mode             = XMC_GPIO_MODE_INPUT_PULL_UP,
		.output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
		.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
	};

	XMC_GPIO_Init(BUTTON_PIN, &button_pin_config);

	button->period = 0;

	button_read_calibration(button);
}


void button_tick(Button *button) {
	static uint8_t last_red = 0;
	static uint8_t last_green = 0;
	static uint8_t last_blue = 0;

	if(last_red != button->red) {
		ccu4_pwm_set_duty_cycle(LED_RED_CCU4_SLICE, button->red*25*button->calibration_page[LED_CALIBRATION_R_POS]/100);
		last_red = button->red;
	}

	if(last_green != button->green) {
		ccu4_pwm_set_duty_cycle(LED_GREEN_CCU4_SLICE, button->green*25*button->calibration_page[LED_CALIBRATION_G_POS]/100);
		last_green = button->green;
	}

	if(last_blue != button->blue) {
		ccu4_pwm_set_duty_cycle(LED_BLUE_CCU4_SLICE, button->blue*25*button->calibration_page[LED_CALIBRATION_B_POS]/100);
		last_blue = button->blue;
	}

	button->state = XMC_GPIO_GetInput(BUTTON_PIN);
}
