/*
 * heaters.c
 *
 *  Created on: May 29, 2023
 *      Author: Jacob Petersen
 */

#include <stdint.h>

const uint8_t HEATERIDS[11] = {-1, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};

void HEAT_enableHeater(uint8_t heaterID) {
	MAX7300_setPin(HEATERIDS[heaterID], 1);
}

void HEAT_disableHeater(uint8_t heaterID) {
	MAX7300_setPin(HEATERIDS[heaterID], 0);
}
