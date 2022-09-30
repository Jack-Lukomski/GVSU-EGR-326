/*******************************************************************************
* Name:             Samuel DeJong
* Course:           EGR 227 - Microcontroller Programming and Applications Lab
* Project:          Lab 04 - Digital Inputs and Outputs – Interfacing Switches
*                            and LEDs to the MSP432
* File:             debounce.c
* Description:      The function in this library will debounce a switch
********************************************************************************/

#ifndef DEBOUNCE_H_
#define DEBOUNCE_H_

uint8_t debounce_press(int time);

uint8_t release(int time, int bit_read);

uint8_t press(int time, int bit_read);

#endif /* DEBOUNCE_H_ */
