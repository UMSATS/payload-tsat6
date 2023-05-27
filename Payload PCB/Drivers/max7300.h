/*
 * max7300.h
 *
 *  Created on: May 15, 2023
 *      Author: Jascha
 */

#ifndef MAX7300_H_
#define MAX7300_H_

void MAX7300_Init(void);
void MAX7300_setPin(int pinNumber, int pinValue);
void MAX7300_clearPins(void);

#endif /* MAX7300_H_ */
