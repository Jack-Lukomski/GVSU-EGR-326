/*
 * stepperMotor.h
 *
 *  Created on: Oct 19, 2022
 *      Author: jtluk
 */

#ifndef STEPPERMOTOR_H_
#define STEPPERMOTOR_H_
#include "pinsInit4.h"
#include "systick.h"


typedef enum stepperMotorDirection_t
{
    clockwise,
    counterclockwise,
}stepperMotorDirection_t;

void vStepperMotor_turnDeg(uint16_t numberSteps, uint16_t direction, uint32_t delayTime);
static void stepperMotorCW(uint16_t numberSteps, uint32_t delay);
static void stepperMotorCCW(uint16_t numberSteps, uint32_t delay);
static void stepFour(void);
static void stepThree(void);
static void stepTwo(void);
static void stepOne(void);
void stepperInit(void);

#endif /* STEPPERMOTOR_H_ */
