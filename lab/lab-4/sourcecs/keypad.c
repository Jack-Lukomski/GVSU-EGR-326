#include "keypad.h"
/*
 * keypad.c
 *
 *  Created on: Sep 30, 2022
 *      Author: jtluk
 */
void vkeypad_Initialize(void)
{
    P4->SEL0 &=~ 0x7f;      //set all pins connected to keypad to GPIO
    P4->SEL1 &=~ 0x7f;

    P4->DIR &=~ 0x7f;      //set all pins connected to keypad to input

    P4->REN |= 0x0f;        //Enable resistor in all keypad ports
    P4->OUT |= 0x0f;        //set all inputs to pull up resistor inputs
}

uint8_t xkeypad_ReadKeypad(void)
{
    uint8_t col, row;
    for (col=0;col<3;col++){
        P4->DIR = 0x00;                     //safety measure ensure all columns are inputs
        P4->DIR |= BIT(4+col);              //set column to output
        P4->OUT &=~BIT(4+col);              //set column to ground
        vSysTick_mSecDelay(10);             //delay for moment so read is good
        row=P4->IN & 0x0F;                  //read input of port 4
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

void vkeypad_PrintKeys(char key)
{
    if((key-48)>=0 && (key-48)<=9){
        printf("%c\n", key);
    }
    else if(key==58){
        printf("*\n");
    }
    else if(key==59){
        printf("0\n");
    }
    else if(key==60){
        printf("#\n");
    }

}



