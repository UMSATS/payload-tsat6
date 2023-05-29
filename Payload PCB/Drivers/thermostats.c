/*
 * thermostats.c
 *
 *  Created on: May 20, 2023
 *      Author: Jacob Petersen
 */

#include <stdint.h>
#include "gpio.h"

const uint16_t THERMPINS[11] = {-1, GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_4, GPIO_PIN_5,
								   GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10};

void THERM_enableThermostat(uint8_t thermID) {
	HAL_GPIO_WritePin(GPIOB, THERMPINS[thermID], GPIO_PIN_SET);
}

void THERM_disableThermostat(uint8_t thermID) {
	HAL_GPIO_WritePin(GPIOB, THERMPINS[thermID], GPIO_PIN_RESET);
}
