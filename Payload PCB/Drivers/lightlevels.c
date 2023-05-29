/*
 * lightlevels.c
 *
 *  Created on: May 29, 2023
 *      Author: Jacob Petersen
 */

#include <stdint.h>
#include "spi.h"
#include "gpio.h"

uint16_t LIGHT_getWellLightReading(uint8_t wellID) {
	uint16_t result;
	result = TLV2553_measureChannel(wellId - 1);
	return result;
}
