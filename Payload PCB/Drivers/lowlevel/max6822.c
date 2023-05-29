/*
 * max6822.c
 *
 *  Created on: May 29, 2023
 *      Author: Jacob Petersen
 */

#include <stdint.h>
#include "gpio.h"

#define WDI_PIN 	GPIOC, GPIO_PIN_9 	// watchdog input pin
#define MR_PIN		GPIOC, GPIO_PIN_8	// master reset pin

void MAX6822_Toggle_WDI() {
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_9);
}

// This will force a reset of the STM32 by pulling the Manual Reset line low on the watchdog
void MAX6822_Manual_Reset() {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
}
