/*********************************************************************************
* Name:             Caleb Capps & Sam DeJong
* Course:           EGR 227 - Microcontroller Programming and Applications Lab
* Project:          Lab 08 - Creating a Pulse Width Modulated (PWM) Pseudo Analog
*                   Voltage Using Timer Peripherals of a Microcontroller
* File:             PWM_btn_set.h
* Description:      This file change motor speed through PWM from TimerA using
*                   inputs from the btn ports to stop, increase by 10%, and
*                   decrease by 10%
* ********************************************************************************/
#include "stdint.h"

#define increase BIT4
#define decrease BIT5
#define btnPort P4

//static int freqHalf;
//static int freqDouble;
int freqHalf;
int freqDouble;




#ifndef GPIO_INTERRUPT_H_
#define GPIO_INTERRUPT_H_


void pin_init(void);

void timerA_init(void);

#endif /* PWM_BTN_SET_H_ */
