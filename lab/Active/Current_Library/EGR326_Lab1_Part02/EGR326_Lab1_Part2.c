/*******************************************************************************
* Name:             Samuel DeJong
* Course:           EGR 326 - Embedded System Design
* Project:          Lab 01 -Part 2
* File:             main.c
* Description:      This file is used to change the color of the LED, as well as
*                   turn it off and on through transistors, inputs are taken from
*                   both of the buttons
* ********************************************************************************/

#include "msp.h"
#include "debounce.h"
#include "stdint.h"
#include "SysTickTimer.h"

//macros for easier coding
#define R BIT0
#define G BIT1
#define B BIT2
#define S1 BIT4
#define S2 BIT5

void pin_initialize(void);
void SysTickInit(void);

void main(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    pin_initialize();
    SysTickInit();
    int delay = 1;               //time in ms
    int color = 3;                  //integer for which LED to turn on

    while (1){                      //continous loop
        if(debounce_sw1_press(delay)){  //check debounce function
            color++;
            if (color > 2) color=0;
            P4->OUT &=~ 0x07;           //clear all colors
            while(~(P4->IN) & S1){
                if (debounce_sw2_press(delay)){
                    color=3;
                    P4->OUT &=~ 0x07;   //clear all colors
                    SysTickTimer(100);  //delay after turning off
                }
                if (color!=3) P4->OUT |= BIT(color);    //turn on LED if valid
            }
        }
        if(debounce_sw2_press(delay)){  //call function from library, check cycle
            color--;
            if (color < 0) color=2;
            P4->OUT &=~ 0x07;           //clear all colors
            while(~(P4->IN) & S2){
                if (debounce_sw1_press(delay)){
                    color=3;
                    P4->OUT &=~ 0x07;   //clear all colors
                    SysTickTimer(100);  //delay after turning off
                }
                if (color!=3) P4->OUT |= BIT(color);    //turn on LED if valid

            }
        }
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
}
