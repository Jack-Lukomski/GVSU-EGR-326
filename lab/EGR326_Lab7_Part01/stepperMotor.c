/*
 * stepperMotor.c
 *
 *  Created on: Oct 20, 2022
 *      Author: samde
 */
#include "msp.h"
#include "stepperMotor.h"
#include "SysTickTimer.h"
#include "stdbool.h"



void motorPinInitialize(void)
{
    P5->SEL0 &=~ 0XF0;
    P5->SEL1 &=~ 0XF0;
    P5->DIR |= 0XF0;
}


void motorTurn(int in1, int in2, int in3, int in4, int time)
{
    STEP_PORT->OUT &=~ BIT(in3);
    STEP_PORT->OUT |= BIT(in1);
    SysTickTimer(time);
    STEP_PORT->OUT &=~ BIT(in4);
    STEP_PORT->OUT |= BIT(in2);
    SysTickTimer(time);
    STEP_PORT->OUT &=~ BIT(in1);
    STEP_PORT->OUT |= BIT(in3);
    SysTickTimer(time);
    STEP_PORT->OUT &=~ BIT(in2);
    STEP_PORT->OUT |= BIT(in4);
    SysTickTimer(time);
}
