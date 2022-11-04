/******char key;*************************************************************************
* Name:             Samuel DeJong
* Course:           EGR 227 - Microcontroller Programming and Applications Lab
* Project:          Lab 06 - Interfacing a keypad with the MSP432
* File:             Read_Keypad.h
* Description:      The function will read in the keypad ports and return the
*                   value that is pressed
********************************************************************************/

#include "stdint.h"
uint8_t key;

#ifndef READ_KEYPAD_H_
#define READ_KEYPAD_H_

void keypad_initialize(void);

uint8_t Read_Keypad (void);

#endif /* READ_KEYPAD_H_ */
