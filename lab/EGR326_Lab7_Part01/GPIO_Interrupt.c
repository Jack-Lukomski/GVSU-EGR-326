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

#include <GPIO_Interrupt.h>
#include "debounce.h"
#include "msp.h"
#include "stdio.h"
#include "stdbool.h"


//int freqHalf;
//int freqDouble;

void PORT6_IRQHandler(void){
    if(btnPort->IFG & btn){
        if(debounce_sw1_press(5)){  //check debounce function
            pressed^=1;
        }
    }
    btnPort->IFG &= ~(btn);
}


void pin_init(void){
    btnPort->IES  |=  (BIT0);
    btnPort->IE   |=  (BIT0);
    btnPort->IFG  &= ~(BIT0);
    btnPort->DIR  &=~ BIT0;      //Set Switch 1 to input

    btnPort->REN |= BIT0;        //Enable resistor in switch 1
    btnPort->OUT |= BIT0;        //Make switch 1 pull up

    btnPort->SEL0 &=~ BIT0;      //standard I/O P4.4 Switch 1
    btnPort->SEL1 &=~ BIT0;
}
//

//
//
//void timerA_init(void){
//    /*  Configure TimerA0.4 as PWM*/
//    TIMER_A0->CCR[0] = PWM_Period;
//    TIMER_A0->CCR[4] = 0;               //initially set to 0
//    TIMER_A0->CCTL[4] = resetSet;
//    TIMER_A0->CTL = (SMCLK | countUp | timerAClear);
//}
