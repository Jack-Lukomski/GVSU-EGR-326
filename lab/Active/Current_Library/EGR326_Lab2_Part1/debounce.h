/*******************************************************************************
* Name:             Samuel DeJong
* Course:           EGR 227 - Microcontroller Programming and Applications Lab
* Project:          Lab 04 - Digital Inputs and Outputs – Interfacing Switches
*                            and LEDs to the MSP432
* File:             debounce.h
* Description:      The function in this library will debounce a switch
********************************************************************************/

#ifndef DEBOUNCE_H_
#define DEBOUNCE_H_

//static int delay = 5;

uint8_t debounce_sw1_press_os(int time);

uint8_t debounce_sw2_press_os(int time);

uint8_t debounce_sw1_press(int time);

uint8_t debounce_sw2_press(int time);

uint8_t release(int time);

#endif /* DEBOUNCE_H_ */
