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

void PORT1_IRQHandler(void){
    if(btnPort->IFG & btn){
        __delay_cycles(3000000);
        if(~(btnPort->IN & btn)){
//        if(debounce_sw1_press(5)){  //check debounce function
            done=0;
            if(pressed){
                pressed=0;
            }
            else{
                pressed=1;
            }
        }
    }
    btnPort->IFG &= ~(0xff);
}


void pin_init(void){
    btnPort->IES  |=  (btn);
    btnPort->IE   |=  (btn);
    btnPort->IFG  &= ~(btn);
    btnPort->DIR  &=~ btn;      //Set Switch 1 to input

    btnPort->REN |= btn;        //Enable resistor in switch 1
    btnPort->OUT |= btn;        //Make switch 1 pull up

    btnPort->SEL0 &=~ btn;      //standard I/O P4.4 Switch 1
    btnPort->SEL1 &=~ btn;
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
