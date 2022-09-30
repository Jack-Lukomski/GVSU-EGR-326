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

volatile uint16_t CW;
volatile uint16_t CCW;

#define ENCODE_PORT P6
#define SW BIT1
#define CLK BIT4
#define DT BIT5

#ifndef GPIO_INTERRUPT_H_
#define GPIO_INTERRUPT_H_


void pin_init(void);

void encoder_pin_init(void);

void timerA_init(void);

#endif /* PWM_BTN_SET_H_ */
