/*********************************************************************************
* Name:             Samuel DeJong
* Course:           EGR 227 - Microcontroller Programming and Applications Lab
* Project:          Lab 06 -
* File:             EGR227_Lab6_Part1.c
* Description:      This file will read in digits from the keypad and print them
*                   to the console window
* ********************************************************************************/

#include "msp.h"
#include "debounce.h"
#include "stdint.h"
#include <stdio.h>
#include "SysTickTimer.h"
#include "Read_Keypad.h"
#include "print_keys.h"

/**********************************************************************************
 * Pin connections for keypad
 *      MSP432 Pins |   Keypad  |   Function
 *      ---------------------------------------
 *       P4.0       |   7       |   Row 1
 *       P4.1       |   6       |   Row 2
 *       P4.2       |   5       |   Row 3
 *       P4.3       |   4       |   Row 4
 *       --------------------------------------
 *       P4.4       |   3       |   Column 1
 *       P4.5       |   2       |   Column 2
 *       P4.6       |   1       |   Column 3
 **********************************************************************************/

void keypad_initialize(void);
void SysTickInit(void);

void main(void)
{
    printf("Press a key \n");
    int pressed;
    SysTickInit();
    keypad_initialize();
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	while(1){
	    pressed = Read_Keypad();                    //check if key is entered
	    if(pressed){
	        print_keys(key);                        //call function to print
	        printf("Press a key \n");
	    }
	    SysTickTimer(10);                           //wait 10 ms before reading again
	}
}


void SysTickInit(void){
    SysTick -> CTRL =0;                 //turn off timer
    SysTick -> LOAD = 0x00ffffff;        //Maximum value of timer
    SysTick -> VAL =0;                  //clear timer
    SysTick -> CTRL = 0x05;             //turn on timer
}


void keypad_initialize(void){
    P4->SEL0 &=~ 0x7f;      //set all pins connected to keypad to GPIO
    P4->SEL1 &=~ 0x7f;

    P4->DIR &=~ 0x7f;      //set all pins connected to keypad to input

    P4->REN |= 0x0f;        //Enable resistor in all keypad ports
    P4->OUT |= 0x0f;        //set all inputs to pull up resistor inputs
}
