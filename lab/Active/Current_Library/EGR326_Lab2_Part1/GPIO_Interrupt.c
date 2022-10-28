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
#include "msp.h"
#include "stdio.h"

//int freqHalf;
//int freqDouble;

void PORT4_IRQHandler(void){
    if(btnPort->IFG & increase){
        if(debounce_sw1_press(5)){  //check debounce function
            freqDouble=1;
        }
    }
    else if(btnPort->IFG & decrease){
        if(debounce_sw2_press(5)){  //call function from library, check cycle
            freqHalf=1;
        }
    }
    btnPort->IFG &= ~(increase|decrease);
}


void pin_init (void){
    P4->IES  |=  (S1);
    P4->IE   |=  (S1);
    P4->IFG  &= ~(S1);
    P4->DIR &=~ S1;      //Set Switch 1 to input

    P4->REN |= S1;        //Enable resistor in switch 1
    P4->OUT |= S1;        //Make switch 1 pull up

    P4->SEL0 &=~ S1;      //standard I/O P4.4 Switch 1
    P4->SEL1 &=~ S1;
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
