/*******************************************************************************
* Name:             Samuel DeJong
* Course:           EGR 326 - Embedded System Design
* Project:          Lab 02 -Part 1
* File:             main.c
* Description:      This file blinks an LED at a freq that doubles from button 1
*                   and is halved when button 2 is pressed
* ********************************************************************************/

#include "msp.h"
#include "debounce.h"
#include "GPIO_Interrupt.h"
#include "stdint.h"
#include "SysTickTimer.h"

//macros for easier coding
#define R BIT0
#define G BIT1
#define B BIT2
#define S1 BIT4
#define S2 BIT5

void pin_initialize(void);

int freq = 1;
//int intervalCnt = 0;
//int timeout = 0;
//int freqHalf;
//int freqDouble;
int delay = 5;

void main(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    pin_initialize();
    SysTick_init();
    NVIC->ISER[1] = 1<< ((PORT4_IRQn) & 31);
    __enable_interrupt();
//    __enable_irq();

//    int delay = 5;
    int blinkOn = 0;
//    int intervalCnt = 0;


    while (1){                      //continous loop

        if (freqHalf){
            if (freq > 1){
                freq=freq/2;
            }
            else blinkOn=0;
            freqHalf=0;
        }
        else if (freqDouble){
            if (blinkOn)
            freq=freq*2;
            freqDouble=0;
            blinkOn = 1;
        }
        if (blinkOn){
            P4->OUT ^= R;
            SysTickTimer(500/freq);
        }
        else P4->OUT &=~ R;


    }
}



void pin_initialize(void){
    P4->SEL0 &=~ R;      //standard I/O P4.0 LED Red
    P4->SEL1 &=~ R;
    P4->SEL0 &=~ G;      //standard I/O P4.1 LED Green
    P4->SEL1 &=~ G;
    P4->SEL0 &=~ B;      //standard I/O P4.2 LED Blue
    P4->SEL1 &=~ B;
    P4->SEL0 &=~ S1;      //standard I/O P4.4 Switch 1
    P4->SEL1 &=~ S1;
    P4->SEL0 &=~ S2;      //standard I/O P4.4 Switch 2
    P4->SEL1 &=~ S2;

    P4->DIR |= R;        //Set LED Red to output
    P4->DIR |= G;        //Set LED Green to output
    P4->DIR |= B;        //Set LED Blue to output
    P4->DIR &=~ S1;      //Set Switch 1 to input
    P4->DIR &=~ S2;      //Set Switch 2 to input

    P4->REN |= S1;        //Enable resistor in switch 1
    P4->OUT |= S1;        //Make switch 1 pull up
    P4->REN |= S2;        //Enable resistor in switch 2
    P4->OUT |= S2;        //Make switch 2 pull up

    P4->OUT &=~ R;       //Set LED RED to off
    P4->OUT &=~ G;       //Set LED GREEN to off
    P4->OUT &=~ B;       //Set LED BLUE to off

    P4->IES  |=  (S1|S2);
    P4->IE   |=  (S1|S2);
    P4->IFG  &= ~(S1|S2);
}


