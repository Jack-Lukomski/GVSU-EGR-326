/*********************************************************************************
* Name:             Samuel DeJong
* Course:           EGR 326 -
* Project:          Lab 05 -
* File:             EGR326_Lab5_Part1.c
* Description:
* ********************************************************************************/

#include "stdint.h"
char key;

#ifndef READ_KEYPAD_H_
#define READ_KEYPAD_H_


void keypad_initialize(void);

uint8_t Read_Keypad (void);

#endif /* READ_KEYPAD_H_ */
