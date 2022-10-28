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

#include <SysTickTimer.h>
#include <msp.h>
#include <stdint.h>
#include "debounce.h"
#include "Read_Keypad.h"



uint8_t Read_Keypad(){
    uint8_t col, row;
    for (col=0;col<3;col++){
        P4->DIR = 0x00;                     //safety measure ensure all columns are inputs
        P4->DIR |= BIT(4+col);              //set column to output
        P4->OUT &=~BIT(4+col);              //set column to ground
        SysTickTimer(10);                   //delay for moment so read is good
        row=P4->IN & 0x0F;                  //read input of port 4
        //effective debounce
        while( !(P4->IN & BIT0) | !(P4->IN & BIT1) | !(P4->IN & BIT2) | !(P4->IN & BIT3));
        if(row != 0x0f) break;              //if key is pressed break out
    }
    P4->DIR = 0x00;                         //return columns to inputs
    if (col==3) return 0;
    if (row==0x0e)  key = 48+col+1;         //1-3
    if (row==0x0d)  key = 51+col+1;         //4-6
    if (row==0x0b)  key = 54+col+1;         //7-9
    if (row==0x07)  key = 57+col+1;         //10-12

    /*******************************************
     *  * = 10  |  0 = 11   |  #=12
     *******************************************/

    return 1;
    }
