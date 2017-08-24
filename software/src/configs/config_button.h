/* rgb-led-button-bricklet
 * Copyright (C) 2017 Olaf Lüke <olaf@tinkerforge.com>
 *
 * conig_button.c: Configuration for RGB LED Button
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


#ifndef CONFIG_BUTTON_H
#define CONFIG_BUTTON_H

#include "xmc_gpio.h"

#define LED_PERIOD_VALUE        6399

#define LED_GREEN_PIN           P1_0
#define LED_GREEN_CCU4_SLICE    0

#define LED_RED_PIN             P1_1
#define LED_RED_CCU4_SLICE      1

#define LED_BLUE_PIN            P1_2
#define LED_BLUE_CCU4_SLICE     2

#define BUTTON_PIN              P2_11

#endif
