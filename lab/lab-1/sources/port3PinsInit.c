/*
 * port3PinsInit.c
 *
 *  Created on: Sep 7, 2022
 *      Author: jtluk
 */
#include "port3PinsInit.h"

/*
 * pinsInint.c
 *
 *  Created on: Sep 2, 2022
 *      Author: jtluk
 */

void vpinsInit_3GPIO(port3GPIO_t * s_userGPIO_ptr, port3Pins_t e_userPin, port3IO_t e_userPortIO, port3GPIOConfig_t e_userGPIO)
{
    s_userGPIO_ptr->e_GPIOType = e_userGPIO;
    s_userGPIO_ptr->e_IO = e_userPortIO;
    s_userGPIO_ptr->e_IOpinNumber = e_userPin;

    P3->SEL0 &= ~BIT(e_userPin);
    P3->SEL1 &= ~BIT(e_userPin);
    vPrv_pinsInit_3InitIO(e_userPin, e_userPortIO);
    vPrv_pinsInit_3InitConfig(e_userPin, e_userGPIO);
}

static void vPrv_pinsInit_3InitIO(port3Pins_t e_userPin, port3IO_t e_userPortIO)
{
    if(e_userPortIO == output3)
    {
        P3->DIR |= BIT(e_userPin);
    }
    else
    {
        P3->DIR &= ~BIT(e_userPin);
    }
}

static void vPrv_pinsInit_3InitConfig(port3Pins_t e_userPin, port3GPIOConfig_t e_userGPIO)
{
    if(e_userGPIO == pullup3)
    {
        P3->REN |= BIT(e_userPin); // pull up resistor
        P3->OUT |= BIT(e_userPin); //
    }
    else
    {
        P3->REN &= ~BIT(e_userPin); // pull down resistor
        P3->OUT &= ~BIT(e_userPin); //
    }
}





