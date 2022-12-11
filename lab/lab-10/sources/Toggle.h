/*
 * cycleRGB.h
 *
 *  Created on: Sep 2, 2022
 *      Author: jtluk
 */

#ifndef TOGGLE_H_
#define TOGGLE_H_
#include "msp.h"
#include "pinsInint.h"

void vToggle_turnPinHigh(port2GPIO_t e_userColor);
void vToggle_turnPinLow(port2GPIO_t e_userColor);
void vToggle_toggle(port2GPIO_t e_userColor);

#endif /* TOGGLE_H_ */
