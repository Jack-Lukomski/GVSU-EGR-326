/*
 * stepperMotor.h
 *
 *  Created on: Oct 19, 2022
 *      Author: jtluk
 */

#ifndef STEPPERMOTOR_H_
#define STEPPERMOTOR_H_
#include "pinsInint.h"
#include "systick.h"
#include "Toggle.h"

typedef enum stepperMotorDirection_t
{
    clockwise,
    counterclockwise,
}stepperMotorDirection_t;

void vStepperMotor_turnDeg(port2GPIO_t * s_userPorts_ptr, uint16_t numberSteps, stepperMotorDirection_t e_motorDirection, uint32_t delayTime);
static void stepperMotorCW(port2GPIO_t * s_userPorts_ptr, uint16_t numberSteps, uint32_t delay);
static void stepperMotorCCW(port2GPIO_t * s_userPorts_ptr, uint16_t numberSteps);
static void stepFour(port2GPIO_t * s_userPorts_ptr);
static void stepThree(port2GPIO_t * s_userPorts_ptr);
static void stepTwo(port2GPIO_t * s_userPorts_ptr);
static void stepOne(port2GPIO_t * s_userPorts_ptr);

#endif /* STEPPERMOTOR_H_ */
