/*
 * HC-SR04.h
 *
 *  Created on: Dec 1, 2022
 *      Author: jtluk
 */

#ifndef HC_SR04_H_
#define HC_SR04_H_
#include "msp.h"
#include "pinsInint.h"
#include "Toggle.h"

uint16_t xHCSR04_GetSonarValue(void);
void xHCSR04_InitlizeTimerA(uint16_t periodValue);
static void vHCSR04_InitPins(void);

#endif /* HC_SR04_H_ */
