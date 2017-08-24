/* rgb-led-button-bricklet
 * Copyright (C) 2017 Bastian Nordmeyer <bastian@tinkerforge.com>
 * Copyright (C) 2017 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.c: TFP protocol message handling
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

#include "communication.h"

#include "bricklib2/utility/communication_callback.h"
#include "bricklib2/protocols/tfp/tfp.h"
#include "button.h"

extern Button button;

BootloaderHandleMessageResponse handle_message(const void *message, void *response) {
	switch(tfp_get_fid_from_message(message)) {
		case FID_SET_COLOR: return set_color(message);
		case FID_GET_COLOR: return get_color(message, response);
		case FID_GET_BUTTON_STATE: return get_button_state(message, response);
		case FID_SET_COLOR_CALIBRATION: return set_color_calibration(message);
		case FID_GET_COLOR_CALIBRATION: return get_color_calibration(message, response);
		default: return HANDLE_MESSAGE_RESPONSE_NOT_SUPPORTED;
	}
}


BootloaderHandleMessageResponse set_color(const SetColor *data) {
	button.red   = data->red;
	button.green = data->green;
	button.blue  = data->blue;
	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_color(const GetColor *data, GetColor_Response *response) {
	response->header.length = sizeof(GetColor_Response);
	response->red   = button.red;
	response->green = button.green;
	response->blue  = button.blue;
	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse get_button_state(const GetButtonState *data, GetButtonState_Response *response) {
	response->header.length = sizeof(GetButtonState_Response);
	response->state = button.state;
	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse set_color_calibration(const SetColorCalibration *data) {
	if((data->red > 100) || (data->green > 100) || (data->blue > 100)) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	button_write_calibration(&button, data->red, data->green, data->blue);

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_color_calibration(const GetColorCalibration *data, GetColorCalibration_Response *response) {
	response->header.length = sizeof(GetColorCalibration_Response);
	response->red   = button.calibration_page[LED_CALIBRATION_RED_POS];
	response->green = button.calibration_page[LED_CALIBRATION_GREEN_POS];
	response->blue  = button.calibration_page[LED_CALIBRATION_BLUE_POS];

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}


bool handle_button_state_changed_callback(void) {
	static uint8_t last_button_state = 0xFF; // Set to invalid value, so we always get one callback in the beginning
	static bool is_buffered = false;
	static ButtonStateChanged_Callback cb;

	if(!is_buffered) {
		if(last_button_state != button.state) {
			//button state has changed
			tfp_make_default_header(&cb.header, bootloader_get_uid(), sizeof(ButtonStateChanged_Callback), FID_CALLBACK_BUTTON_STATE_CHANGED);
			get_button_state(NULL, (GetButtonState_Response *) &cb);
			last_button_state = button.state;
		} else {
			return false;
		}
	}

	if(bootloader_spitfp_is_send_possible(&bootloader_status.st)) {
		bootloader_spitfp_send_ack_and_message(&bootloader_status, (uint8_t*)&cb, sizeof(ButtonStateChanged_Callback));
		is_buffered = false;
		return true;
	} else {
		is_buffered = true;
	}

	return false;
}

void communication_tick(void) {
	communication_callback_tick();
}

void communication_init(void) {
	communication_callback_init();
}
