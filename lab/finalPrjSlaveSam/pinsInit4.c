#include "pinsInit4.h"

void vpinsInit_GPIO4(port4GPIO_t * s_userGPIO_ptr, port4Pins_t e_userPin, port4IO_t e_userPortIO, port4GPIOConfig_t e_userGPIO, port4Inturrupt_t e_Interrupt)
{
    s_userGPIO_ptr->e_GPIOType4 = e_userGPIO;
    s_userGPIO_ptr->e_IO4 = e_userPortIO;
    s_userGPIO_ptr->e_IOpinNumber4 = e_userPin;
    s_userGPIO_ptr->e_Interrupt4 = e_Interrupt;

    P4->SEL0 &= ~BIT(e_userPin);
    P4->SEL1 &= ~BIT(e_userPin);
    vPrv_pinsInit_InitIO4(e_userPin, e_userPortIO);
    vPrv_pinsInit_InitConfig4(e_userPin, e_userGPIO, e_Interrupt);
}

static void vPrv_pinsInit_InitIO4(port4Pins_t e_userPin, port4IO_t e_userPortIO)
{
    if(e_userPortIO == output4)
    {
        P4->DIR |= BIT(e_userPin);
    }
    else
    {
        P4->DIR &= ~BIT(e_userPin);
    }
}

static void vPrv_pinsInit_InitConfig4(port4Pins_t e_userPin, port4GPIOConfig_t e_userGPIO, port4Inturrupt_t e_Interrupt)
{
    if(e_userGPIO == pullup4)
    {
        P4->REN |= BIT(e_userPin); // pull up resistor
        P4->OUT |= BIT(e_userPin); //
        if(e_Interrupt == enableInterrupt4)
        {
            P4->IES |= BIT(e_userPin);
            P4->IE |= BIT(e_userPin);
            P4->IFG = 0;
        }
    }
    else
    {
        P4->REN &= ~BIT(e_userPin); // pull down resistor
        P4->OUT &= ~BIT(e_userPin); //
        if(e_Interrupt == enableInterrupt4)
        {
            P4->IES &= ~BIT(e_userPin);
            P4->IE &= ~BIT(e_userPin);
            P4->IFG = 0;
        }
    }
}
