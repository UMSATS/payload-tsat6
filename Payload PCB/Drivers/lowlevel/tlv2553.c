/*
 * tlv2553.c
 *
 *  Created on: May 15, 2023
 *      Author: Jascha
 */

#include <stdint.h>

// CS Pin: GPIOA, GPIO_PIN_8

// We will be using the 16 bit input mode. See tables 2 and 3 and figure 37 in the datasheet.

// I messed up the well mapping in hardware so this will rectify that
//                    No well 0  1  2  3  4  5  6   7  8  9  10
const int wellMapping[11] = {-1, 5, 4, 3, 2, 1, 10, 9, 8, 7, 6};

uint16_t readingData[10];	// array of 16 bit ints for raw temperature data

// returns a 12-bit resolution ADC reading. Left 4 bits will be padded 0s
uint16_t TLV2553_measureChannel(int channelNumber) {
	uint16_t result;
}
