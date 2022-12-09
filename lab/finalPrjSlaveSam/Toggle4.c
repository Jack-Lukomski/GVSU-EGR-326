#include "Toggle4.h"
/*
 * cycleRGB.c
 *
 *  Created on: Sep 2, 2022
 *      Author: jtluk
 */

void vToggle_turnPinHigh(port4GPIO_t e_userColor)
{
    if(e_userColor.e_GPIOType4 == pullup4)
    {
        P4->OUT &= ~BIT(e_userColor.e_IOpinNumber4);
    }
    else if(e_userColor.e_GPIOType4 == pulldown4)
    {
        P4->OUT |= BIT(e_userColor.e_IOpinNumber4);
    }
}

void vToggle_turnPinLow(port4GPIO_t e_userColor)
{
    if(e_userColor.e_GPIOType4 == pullup4)
    {
        P4->OUT |= BIT(e_userColor.e_IOpinNumber4);
    }
    else if(e_userColor.e_GPIOType4 == pulldown4)
    {
        P4->OUT &= ~BIT(e_userColor.e_IOpinNumber4);
    }
}

void vToggle_toggle(port4GPIO_t e_userColor)
{
    P4->OUT ^= BIT(e_userColor.e_IOpinNumber4);
}
