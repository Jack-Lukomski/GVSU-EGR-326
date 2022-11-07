/*
 * timer32.c
 *
 *  Created on: Nov 4, 2022
 *      Author: samde
 */
#include "timer32.h"
#include "msp.h"

void vTimer32_init(void)
{
    TIMER32_1->CONTROL = 0b10000011;   //Enabled,Periodic,Interrupt,32-bit,Wrapping Mode
    TIMER32_1->LOAD = 0XFFFFFFFF;
}



