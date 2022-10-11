/*
 * keypad.h
 *
 *  Created on: Sep 30, 2022
 *      Author: jtluk
 */
#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "msp.h"
#include "systick.h"
#include <stdio.h>

char keypad_keyPressed;
void vkeypad_Initialize(void);
uint8_t xkeypad_ReadKeypad(void);
void vkeypad_PrintKeys(char key);

#endif /* KEYPAD_H_ */
