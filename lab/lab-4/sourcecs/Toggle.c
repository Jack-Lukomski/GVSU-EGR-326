#include "Toggle.h"
/*
 * cycleRGB.c
 *
 *  Created on: Sep 2, 2022
 *      Author: jtluk
 */

void vToggle_turnPinHigh(port2GPIO_t e_userColor)
{
    if(e_userColor.e_GPIOType == pullup)
    {
        P2->OUT &= ~BIT(e_userColor.e_IOpinNumber);
    }
    else if(e_userColor.e_GPIOType == pulldown)
    {
        P2->OUT |= BIT(e_userColor.e_IOpinNumber);
    }
}

void vToggle_turnPinLow(port2GPIO_t e_userColor)
{
    if(e_userColor.e_GPIOType == pullup)
    {
        P2->OUT |= BIT(e_userColor.e_IOpinNumber);
    }
    else if(e_userColor.e_GPIOType == pulldown)
    {
        P2->OUT &= ~BIT(e_userColor.e_IOpinNumber);
    }
}

void vToggle_toggle(port2GPIO_t e_userColor)
{
    P2->OUT ^= BIT(e_userColor.e_IOpinNumber);
}
