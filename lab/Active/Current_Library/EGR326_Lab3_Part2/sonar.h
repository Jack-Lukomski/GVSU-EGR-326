/*********************************************************************************
* Name:             Caleb Capps & Sam DeJong
* Course:           EGR 227 - Microcontroller Programming and Applications Lab
* Project:          Lab 11 - Implement traffic light sequence override using IR
*                           signals
*
* File:             IR.h
* Description:      This file will set the PWM of the IR signal
**********************************************************************************/
#include "stdint.h"


int echo_on;

#ifndef SONAR_H_
#define SONAR_H_

#define ECHO_PORT P2
#define ECHO_PIN BIT4
#define TRIG_PORT P5
#define TRIG_PIN BIT6
#define LED_PORT P6
#define LED_PIN BIT0
#define FREQ 40


void sonar_trig(void);

void sonar_pin_init(void);

void timerA_init_trigger(void);

void timerA_init_echo(void);

#endif /* IR_H_ */
