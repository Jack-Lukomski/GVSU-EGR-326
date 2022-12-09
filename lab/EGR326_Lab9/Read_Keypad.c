/*******************************************************************************
* Name:             Samuel DeJong
* Course:           EGR 227 - Microcontroller Programming and Applications Lab
* Project:          Lab 06 - Interfacing a keypad with the MSP432
* File:             Read_Keypad.c
* Description:      The function will read in the keypad ports and return the
*                   value that is pressed
*
* Code inspired by GVSU EGR 226 Lecture Slides
********************************************************************************/

#include <msp.h>
#include <stdint.h>
#include "Read_Keypad.h"

void keypad_initialize(void){
    P4->SEL0 &=~ 0x7f;      //set all pins connected to keypad to GPIO
    P4->SEL1 &=~ 0x7f;

    P4->DIR &=~ 0x7f;      //set all pins connected to keypad to input

    P4->REN |= 0x0f;        //Enable resistor in all keypad ports
    P4->OUT |= 0x0f;        //set all inputs to pull up resistor inputs
}

uint8_t Read_Keypad(){
    uint8_t col, row;
    for (col=0;col<3;col++){
        P4->DIR = 0x00;                     //safety measure ensure all columns are inputs
        P4->DIR |= BIT(4+col);              //set column to output
        P4->OUT &=~BIT(4+col);              //set column to ground
        __delay_cycles(100);                   //delay for moment so read is good
        row=P4->IN & 0x0F;                  //read input of port 4
        //effective debounce
        while( !(P4->IN & BIT0) | !(P4->IN & BIT1) | !(P4->IN & BIT2) | !(P4->IN & BIT3));
        if(row != 0x0f) break;              //if key is pressed break out
    }
    P4->DIR = 0x00;                         //return columns to inputs
    if (col==3) return 0;
    if (row==0x0e)  key = col+1;         //1-3
    if (row==0x0d)  key = col+4;         //4-6
    if (row==0x0b)  key = col+7;         //7-9
    if (row==0x07)  key = col+10;         //10-12

    /*******************************************
     *  * = 10  |  0 = 11   |  #=12
     *******************************************/

    return 1;
    }