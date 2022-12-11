/*
 * SamsSonarLib.h
 *
 *  Created on: Dec 9, 2022
 *      Author: jtluk
 */

#ifndef SAMSSONARLIB_H_
#define SAMSSONARLIB_H_
#include "msp.h"
// sonar, speakersound, steppermotor,
#include <stdio.h>
#include "pinsInint.h"
#include "readInputs.h"
#include "msp.h"
#include "HC-SR04.h"
#include "speakerSound.h"
#include "stepperMotorSam.h"
#include "I2C.h"

#define R BIT0
#define G BIT1
#define B BIT2

volatile char CurrNotePlaying;
volatile uint8_t CurrentVolume8Scale;

void vMusicDriver(void);

void preMusicInit(void);
void postMusicDisable(void);

void RGB_pin_initialize(void);

void vTimerA_InteruptHelper(void);
void vAdjustVolume_IQR(void);

#endif /* SAMSSONARLIB_H_ */
