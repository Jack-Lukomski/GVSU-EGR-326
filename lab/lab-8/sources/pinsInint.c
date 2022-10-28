/*
 * pinsInint.c
 *
 *  Created on: Sep 2, 2022
 *      Author: jtluk
 */
#include "pinsInint.h"

void vpinsInit_GPIO(port2GPIO_t * s_userGPIO_ptr, port2Pins_t e_userPin, port2IO_t e_userPortIO, port2GPIOConfig_t e_userGPIO, port2Inturrupt_t e_Interrupt)
{
    s_userGPIO_ptr->e_GPIOType = e_userGPIO;
    s_userGPIO_ptr->e_IO = e_userPortIO;
    s_userGPIO_ptr->e_IOpinNumber = e_userPin;
    s_userGPIO_ptr->e_Interrupt = e_Interrupt;

    P2->SEL0 &= ~BIT(e_userPin);
    P2->SEL1 &= ~BIT(e_userPin);
    vPrv_pinsInit_InitIO(e_userPin, e_userPortIO);
    vPrv_pinsInit_InitConfig(e_userPin, e_userGPIO, e_Interrupt);
}

static void vPrv_pinsInit_InitIO(port2Pins_t e_userPin, port2IO_t e_userPortIO)
{
    if(e_userPortIO == output)
    {
        P2->DIR |= BIT(e_userPin);
    }
    else
    {
        P2->DIR &= ~BIT(e_userPin);
    }
}

void vPrv_pinsInit_InitConfig(e_userPin, e_userGPIO, e_Interrupt)
{
    if(e_userGPIO == pullup)
    {
        P2->REN |= BIT(e_userPin); // pull up resistor
        P2->OUT |= BIT(e_userPin); //
        if(e_Interrupt == enableInterrupt)
        {
            P2->IES |= BIT(e_userPin);
            P2->IE |= BIT(e_userPin);
            P2->IFG = 0;
        }
    }
    else
    {
        P2->REN &= ~BIT(e_userPin); // pull down resistor
        P2->OUT &= ~BIT(e_userPin); //
        if(e_Interrupt == enableInterrupt)
        {
            P2->IES &= ~BIT(e_userPin);
            P2->IE &= ~BIT(e_userPin);
            P2->IFG = 0;
        }
    }
}


