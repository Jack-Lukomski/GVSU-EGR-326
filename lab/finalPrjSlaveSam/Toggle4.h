/*
 * cycleRGB.h
 *
 *  Created on: Sep 2, 2022
 *      Author: jtluk
 */

#ifndef TOGGLE_H_
#define TOGGLE_H_
#include "msp.h"
#include "pinsInit4.h"

void vToggle_turnPinHigh(port4GPIO_t e_userColor);
void vToggle_turnPinLow(port4GPIO_t e_userColor);
void vToggle_toggle(port4GPIO_t e_userColor);

#endif /* TOGGLE_H_ */
