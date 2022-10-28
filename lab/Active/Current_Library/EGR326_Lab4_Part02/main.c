/*******************************************************************************
* Name:             Samuel DeJong
* Course:           EGR 326 - Embedded System Design
* Project:          Lab 03 -Part 1
* File:             main.c
* Description:
* ********************************************************************************/

#include <msp.h>
#include <stdint.h>
#include <stdio.h>

#include "GPIO_Interrupt.h"
#include "SysTickTimer.h"

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	encoder_pin_init();
    NVIC->ISER[1] = 1<< ((PORT6_IRQn) & 31);
    __enable_interrupt();
    __enable_irq();

	while(1)
	    ;
}
