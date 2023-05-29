/*
 * tlv2553.c
 *
 *  Created on: May 15, 2023
 *      Author: Jascha
 */

#include <stdint.h>
#include "gpio.h"
#include "spi.h"

void TLV2553_enableCS(void);
void TLV2553_disableCS(void);

// CS Pin: GPIOA, GPIO_PIN_8

// We will be using the 16 bit input mode. See tables 2 and 3 and figure 37 in the datasheet.

// I messed up the well mapping in hardware so this will rectify that
//                    No well 0  1  2  3  4  5  6   7  8  9  10
const int wellMapping[11] = {-1, 5, 4, 3, 2, 1, 10, 9, 8, 7, 6};

uint16_t readingData[10];	// array of 16 bit ints for raw temperature data

// returns a 12-bit resolution ADC reading. Left 4 bits will be padded 0s
// see table 2 and figure 37 in datasheet
uint16_t TLV2553_measureChannel(int channelNumber) {
	uint8_t response[2] = {0,0};
	uint16_t result = 0;
	uint8_t command = 0;

	command = command | (channelNumber << 4); 	// indicates ADC channel (pin) number
	command = command | (0b11 << 2);			// indicates a 16 bit message length (LSBs padded with 0s)
	command = command & 0b11111101;				// D1 is 0 to indicate MSB out first
	command = command & 0b11111110; 			// D0 is 0 to indicate unipolar binary

	TLV2553_enableCS();

	HAL_SPI_Transmit(&hspi3, &command, 1, 10);

	TLV2553_disableCS();
	// I forgot to wire the end-of-conversion pin. So I am waiting 5ms since the maximum conversion time is 1.6ms.
	HAL_Delay(5);
	TLV2553_enableCS();

	HAL_SPI_Receive(&hspi3, response, 2, 10);

	result = (response[0] << 8) | (response[1]);
	result = result >> 4;						// move padded 0s from LSB to MSB

	return result;

}

void TLV2553_enableCS(void) {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
}

void TLV2553_disableCS(void) {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
}
