/*
 * stepperMotor.h
 *
 *  Created on: Oct 20, 2022
 *      Author: samde
 */

#define STEP_PORT P5

#ifndef STEPPERMOTOR_H_
#define STEPPERMOTOR_H_


void motorPinInitialize(void);

void motorTurn(int in1, int in2, int in3, int in4, int time);


#endif /* STEPPERMOTOR_H_ */
