/*********************************************************************************
* Name:             Caleb Capps & Sam DeJong
* Course:           EGR 227 - Microcontroller Programming and Applications Lab
* Project:          Lab 10 - Interfacing the MSP432 with a Temperature Sensor,
* Converting the Analog Voltage to Digital Samples, and Displaying on the LCD
*
* File:             ADC.c
* Description:      This header file is used to declare ADC functions
*
*                   CODE USED FROM GVSU EGR 226 LECTURE SLIDES
*
**********************************************************************************/


#include "msp.h"
#include "ADC.h"


//Code used from EGR 226 Lecture Slides
void ADC_port_init(void){
    P5 -> SEL0 |= BIT5;         //Enable P5.5 as analog connected to A0
    P5 -> SEL1 |= BIT5;
}


void ADC_init(void){
    ADC14->CTL0  &=~ 0x00000002;   // disable ADC converter during initialization
    ADC14->CTL0 |=   0x04240210;     // S/H pulse mode, SMCLK, Repeat Single Channel, 16 sample clocks, ADC ON
    ADC14->CTL1  =   0x00000030;     // 14 bit resolution
    ADC14->CTL1 |=   0x00000000;     // convert for mem0 register
    ADC14->MCTL[0] = 0x00000000;     // ADC14INCHx = 0 for mem[0]
    ADC14->CTL0 |=   ADC14_CTL0_ENC; // enable ADC14ENC, Starts the ADC after confg.
}


