/*********************************************************************************
* Name:             Caleb Capps & Sam DeJong
* Course:           EGR 227 - Microcontroller Programming and Applications Lab
* Project:          Lab 08 - Creating a Pulse Width Modulated (PWM) Pseudo Analog
*                   Voltage Using Timer Peripherals of a Microcontroller
* File:             PWM_btn_set.c
* Description:      This file change motor speed through PWM from TimerA using
*                   inputs from the btn ports to stop, increase by 10%, and
*                   decrease by 10%
* ********************************************************************************/

#include "msp.h"
#include "GPIO_Interrupt.h"



void PORT6_IRQHandler(void){
//    __delay_cycles(15000);
    if(ENCODE_PORT->IFG & CLK){
        if (ENCODE_PORT->IN & DT)
            CCW++;
        else
            CW++;
    }
    ENCODE_PORT->IFG &=~ (CLK);
}

void encoder_pin_init(void){
    ENCODE_PORT->SEL0 &=~ CLK;      //standard I/O P4.4 Switch 1
    ENCODE_PORT->SEL1 &=~ CLK;
    ENCODE_PORT->SEL0 &=~ DT;      //standard I/O P4.4 Switch 2
    ENCODE_PORT->SEL1 &=~ DT;
    ENCODE_PORT->DIR &=~ CLK;      //Set Switch 1 to input
    ENCODE_PORT->DIR &=~ DT;      //Set Switch 2 to input
    ENCODE_PORT->IES  |=  (CLK);
    ENCODE_PORT->IE   |=  (CLK);
    ENCODE_PORT->IFG  &= ~(CLK);
}

//
//
//void timerA_init(void){
//    /*  Configure TimerA0.4 as PWM*/
//    TIMER_A0->CCR[0] = PWM_Period;
//    TIMER_A0->CCR[4] = 0;               //initially set to 0
//    TIMER_A0->CCTL[4] = resetSet;
//    TIMER_A0->CTL = (SMCLK | countUp | timerAClear);
//}
