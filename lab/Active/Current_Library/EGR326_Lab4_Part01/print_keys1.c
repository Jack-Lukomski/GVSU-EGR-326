/*******************************************************************************
* Name:             Samuel DeJong
* Course:           EGR 227 - Microcontroller Programming and Applications Lab
* Project:          Lab 06 - Interfacing a keypad with the MSP432
* File:             print_keys.c
* Description:      The function will print the value read by keypad
********************************************************************************/

#include "stdio.h"
#include "msp.h"
#include "stdint.h"
#include "print_keys.h"

void print_keys(char key){
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
