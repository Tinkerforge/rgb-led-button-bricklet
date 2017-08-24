/* rgb-led-button-bricklet
 * Copyright (C) 2017 Bastian Nordmeyer <bastian@tinkerforge.com>
 *
 * communication.h: TFP protocol message handling
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

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>
#include <stdbool.h>

#include "bricklib2/protocols/tfp/tfp.h"
#include "bricklib2/bootloader/bootloader.h"

// Default functions
BootloaderHandleMessageResponse handle_message(const void *data, void *response);
void communication_tick(void);
void communication_init(void);

// Constants
#define RGB_LED_BUTTON_BUTTON_STATE_PRESSED 0
#define RGB_LED_BUTTON_BUTTON_STATE_RELEASED 1

#define RGB_LED_BUTTON_BOOTLOADER_MODE_BOOTLOADER 0
#define RGB_LED_BUTTON_BOOTLOADER_MODE_FIRMWARE 1
#define RGB_LED_BUTTON_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2
#define RGB_LED_BUTTON_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3
#define RGB_LED_BUTTON_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

#define RGB_LED_BUTTON_BOOTLOADER_STATUS_OK 0
#define RGB_LED_BUTTON_BOOTLOADER_STATUS_INVALID_MODE 1
#define RGB_LED_BUTTON_BOOTLOADER_STATUS_NO_CHANGE 2
#define RGB_LED_BUTTON_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3
#define RGB_LED_BUTTON_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4
#define RGB_LED_BUTTON_BOOTLOADER_STATUS_CRC_MISMATCH 5

#define RGB_LED_BUTTON_STATUS_LED_CONFIG_OFF 0
#define RGB_LED_BUTTON_STATUS_LED_CONFIG_ON 1
#define RGB_LED_BUTTON_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2
#define RGB_LED_BUTTON_STATUS_LED_CONFIG_SHOW_STATUS 3

// Function and callback IDs and structs
#define FID_SET_COLOR 1
#define FID_GET_COLOR 2
#define FID_GET_BUTTON_STATE 3
#define FID_SET_RGB_CALIBRATION 5
#define FID_GET_RGB_CALIBRATION 6

#define FID_CALLBACK_BUTTON_STATE_CHANGED 4

typedef struct {
	TFPMessageHeader header;
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} __attribute__((__packed__)) SetColor;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetColor;

typedef struct {
	TFPMessageHeader header;
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} __attribute__((__packed__)) GetColor_Response;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetButtonState;

typedef struct {
	TFPMessageHeader header;
	uint8_t state;
} __attribute__((__packed__)) GetButtonState_Response;

typedef struct {
	TFPMessageHeader header;
	uint8_t state;
} __attribute__((__packed__)) ButtonStateChanged_Callback;

typedef struct {
	TFPMessageHeader header;
	uint8_t r;
	uint8_t g;
	uint8_t b;
} __attribute__((__packed__)) SetRGBCalibration;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetRGBCalibration;

typedef struct {
	TFPMessageHeader header;
	uint8_t r;
	uint8_t g;
	uint8_t b;
} __attribute__((__packed__)) GetRGBCalibration_Response;


// Function prototypes
BootloaderHandleMessageResponse set_color(const SetColor *data);
BootloaderHandleMessageResponse get_color(const GetColor *data, GetColor_Response *response);
BootloaderHandleMessageResponse get_button_state(const GetButtonState *data, GetButtonState_Response *response);
BootloaderHandleMessageResponse set_rgb_calibration(const SetRGBCalibration *data);
BootloaderHandleMessageResponse get_rgb_calibration(const GetRGBCalibration *data, GetRGBCalibration_Response *response);

// Callbacks
bool handle_button_state_changed_callback(void);

#define COMMUNICATION_CALLBACK_TICK_WAIT_MS 1
#define COMMUNICATION_CALLBACK_HANDLER_NUM 1
#define COMMUNICATION_CALLBACK_LIST_INIT \
	handle_button_state_changed_callback, \


#endif
