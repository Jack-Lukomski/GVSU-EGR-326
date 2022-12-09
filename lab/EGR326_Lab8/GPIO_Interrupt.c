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
    if(btnPort->IFG & (btn|onboardS1)){
        __delay_cycles(1500000);
        if(~(btnPort->IN & (btn|onboardS1))){
//        if(debounce_sw1_press(5)){  //check debounce function
            numPress++;
            if(numPress==10)
            {
                numPress=0;
                numPress2++;
            }
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
    btnPort->IES  |=  (btn|onboardS1);
    btnPort->IE   |=  (btn|onboardS1);
    btnPort->IFG  &= ~(btn|onboardS1);
    btnPort->DIR  &=~ (btn|onboardS1);      //Set Switch 1 to input

    btnPort->REN |= (btn|onboardS1);        //Enable resistor in switch 1
    btnPort->OUT |= (btn);        //Make switch 1 pull up


    btnPort->SEL0 &=~ (btn|onboardS1);      //standard I/O P4.4 Switch 1
    btnPort->SEL1 &=~ (btn|onboardS1);
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