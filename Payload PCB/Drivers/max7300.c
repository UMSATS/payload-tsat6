/*
 * max7300.c
 *
 *  Created on: May 15, 2023
 *      Author: Jascha
 */

#include <stdint.h>
#include "i2c.h"

#define MAX7300_ADDRESS 			0b01000000 // MAX7300 I2C address (ADR0 and ADR1 are pulled to GND, which defines this)
#define MAX7300_REG_CONFIG 			0x04 // configuration register address
#define MAX7300_REG_TRANSDETECT 	0x06 // transition detection mask register address

#define MAX7300_REG_CONFIG_P15_P12	0x0B // ports 15 through 12 config register
#define MAX7300_REG_CONFIG_P19_P16	0x0C
#define MAX7300_REG_CONFIG_P23_P20	0x0D
#define MAX7300_REG_CONFIG_P27_P24	0x0E
#define MAX7300_REG_CONFIG_P31_P28	0x0F

uint8_t PORTREGISTERS[32]; // array of dataport addresses. Only 12-31 will be populated

uint8_t payloadBuffer[128]; // array of bytes to use as payload buffer

// Initialize the device with all required settings
void MAX7300_Init(void) {

	// initialize the PORTREGISTERS array (addresses as per datasheet)
	int portAddress = 0x2C; // port 12 is 2C, we increment by one
	for (int i = 12; i < 32; i++) {
		PORTREGISTERS[i] = portAddress;
		portAddress++;
	}

	//TODO: configure P12-P31 as OUTPUTS with no transition detection or any other stuff

	// sending on peripheral I2C1, at the above address, from payloadBuffer, 2 bytes, max timeout time
	payloadBuffer[0] = MAX7300_REG_CONFIG; // define command address as the configuration register
	payloadBuffer[1] = 0b00000001; // MSB is 0 for no transition detection, LSB is 1 for normal operation
	HAL_I2C_Master_Transmit(&hi2c1, MAX7300_ADDRESS, payloadBuffer, 2, HAL_MAX_DELAY);

	// MAX7300 should now be on and in normal operation
	// now to configure the ports. See tables 1 and 2 in the datasheet

	// part 1: we first have to set the register bits (LSB contained in PORTREGISTERS) to 1 to indicate active high output
	// writing more than 1 byte will automatically increment the command address. So we can just keep writing bytes and it will continue
	// to increment. We write all ports from 12 to 31 this way very quickly (see autoincrementing in datasheet)
	payloadBuffer[0] = PORTREGISTERS[12];
	for (int i = 12; i < 32; i++) {
		payloadBuffer[i] = 1;
	}

	HAL_I2C_Master_Transmit(&hi2c1, MAX7300_ADDRESS, payloadBuffer, 21, HAL_MAX_DELAY);

	// part 2: we write the 'output' bit pair to each port's configuration bits (see datasheet table 2)
	payloadBuffer[0] = MAX7300_REG_CONFIG_P15_P12;
	payloadBuffer[1] = 0b01010101;
	payloadBuffer[2] = 0b01010101;
	payloadBuffer[3] = 0b01010101;
	payloadBuffer[4] = 0b01010101;
	HAL_I2C_Master_Transmit(&hi2c1, MAX7300_ADDRESS, payloadBuffer, 5, HAL_MAX_DELAY);

	// MAX7300 is now configured for all pins 12-31 to be outputs

	// we will now set all of the LOW just in case
	for (int i = 12; i < 32; i++) {
		payloadBuffer[0] = PORTREGISTERS[i]; // set the address to the relevant port's setting address
		payloadBuffer[1] = 0; // set the data to be written to 0
		HAL_I2C_Master_Transmit(&hi2c1, MAX7300_ADDRESS, payloadBuffer, 2, HAL_MAX_DELAY);
	}

	// now all outputs are off

}

// set pin "pinNumber" to the value in "pinValue"
void setPin(int pinNumber, int pinValue) {
	if ((pinNumber >= 12) & (pinNumber <= 31) & ((pinValue == 1) | (pinValue == 0))) {
		payloadBuffer[0] = PORTREGISTERS[pinNumber];
		payloadBuffer[1] = pinValue;
		HAL_I2C_Master_Transmit(&hi2c1, MAX7300_ADDRESS, payloadBuffer, 2, HAL_MAX_DELAY);
	}
}

// sets all pins to 0 (LOw)
void clearPins(void) {
	for (int i = 12; i < 32; i++) {
		payloadBuffer[0] = PORTREGISTERS[i]; // set the address to the relevant port's setting address
		payloadBuffer[1] = 0; // set the data to be written to 0
		HAL_I2C_Master_Transmit(&hi2c1, MAX7300_ADDRESS, payloadBuffer, 2, HAL_MAX_DELAY);
	}
}
