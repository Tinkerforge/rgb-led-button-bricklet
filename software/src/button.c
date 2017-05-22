/* rgb-button-bricklet
 * Copyright (C) Bastian Nordmeyer <bastian@tinkerforge.com>
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

#include <string.h>


void button_init(Button * button) {

	XMC_GPIO_CONFIG_t led_red_config = {
		.mode             = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
		.output_level     = XMC_GPIO_OUTPUT_LEVEL_LOW
	};

	XMC_GPIO_CONFIG_t led_green_config = {
		.mode             = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
		.output_level     = XMC_GPIO_OUTPUT_LEVEL_LOW
	};

	XMC_GPIO_CONFIG_t led_blue_config = {
		.mode             = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
		.output_level     = XMC_GPIO_OUTPUT_LEVEL_LOW
	};

	XMC_GPIO_CONFIG_t button_pin_config = {
		.mode             = XMC_GPIO_MODE_INPUT_PULL_UP,
		.output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
		.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
	};

	memset(button, 0, sizeof(Button));
	XMC_GPIO_Init(LED_RED_PIN, &led_red_config);
	XMC_GPIO_Init(LED_GREEN_PIN, &led_green_config);
	XMC_GPIO_Init(LED_BLUE_PIN, &led_blue_config);
	XMC_GPIO_Init(BUTTON_PIN, &button_pin_config);

	button->period = 0;
}


void button_tick(Button * button) {

	button->period++;


	if(button->red == 255)
		XMC_GPIO_SetOutputLow(LED_RED_PIN); //led on
	else if(button->red <= button->period)
		XMC_GPIO_SetOutputHigh(LED_RED_PIN); //led off
	else
		XMC_GPIO_SetOutputLow(LED_RED_PIN); //led on

	if(button->green == 255)
		XMC_GPIO_SetOutputLow(LED_GREEN_PIN); //led on
	else if(button->green <= button->period)
		XMC_GPIO_SetOutputHigh(LED_GREEN_PIN);
	else
		XMC_GPIO_SetOutputLow(LED_GREEN_PIN);

	if(button->blue == 255)
		XMC_GPIO_SetOutputLow(LED_BLUE_PIN); //led on
	else if(button->blue <= button->period)
		XMC_GPIO_SetOutputHigh(LED_BLUE_PIN);
	else
		XMC_GPIO_SetOutputLow(LED_BLUE_PIN);

	button->state = XMC_GPIO_GetInput(BUTTON_PIN);
}
