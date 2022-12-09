/*
 * systick.h
 *
 *  Created on: Sep 9, 2022
 *      Author: jtluk
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_
#include "msp.h"
#include "pinsInint.h"
#include <stdint.h>

void vSysTick_Init(void);
void vSysTick_IntteruptInit(uint32_t msDelayTime);
void vSysTick_mSecDelay(uint16_t msDelayTime);


#endif /* SYSTICK_H_ */
