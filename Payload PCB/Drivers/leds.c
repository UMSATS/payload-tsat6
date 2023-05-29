/*
 * leds.c
 *
 *  Created on: May 28, 2023
 *      Author: Jascha
 */

#include <stdint.h>
#include "lowlevel/max7300.h"

const uint8_t LEDPINS[11] = {-1, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21};

void LED_enableLED(uint8_t ledID) {
	MAX7300_setPin(LEDPINS[ledID], 1);
}

void LED_disableLED(uint8_t ledID) {
	MAX7300_setPin(LEDPINS[ledID], 0);
}
