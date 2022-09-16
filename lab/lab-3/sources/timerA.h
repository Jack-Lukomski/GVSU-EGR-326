/*
 * timerA.h
 *
 *  Created on: Sep 16, 2022
 *      Author: jtluk
 */

#ifndef TIMERA_H_
#define TIMERA_H_
#include "msp.h"
#include "pinsInint.h"

void vtimerA0_CaputureInitlize(void);
void vtimerA1_PWMInitlize(uint16_t period, uint16_t dutyCycle);


#endif /* TIMERA_H_ */
