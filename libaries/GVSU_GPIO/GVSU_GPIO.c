#include "GVSU_GPIO.h"
/*
 * GVSU_GPIO.c
 *
 *  Created on: Aug 29, 2022
 *      Author: jtluk
 */
void vGPIO_setPinNumber(s_GVSU_GPIO * s_userGPIO_ptr, GPIO_pinNumber_t e_userPinNumber)
{
    s_userGPIO_ptr->e_pinNumber = e_userPinNumber;
}

void vGPIO_setPort(s_GVSU_GPIO * s_userGPIO_ptr, GPIO_portNumber_t e_userPortNumber)
{
    s_userGPIO_ptr->e_portNumber = e_userPortNumber;
}

void vGPIO_setIO(s_GVSU_GPIO * s_userGPIO_ptr, GPIO_IO_t e_userIOType);
{
    s_userGPIO_ptr->e_IO = e_userIOType;
}

GPIO_status_t xGPIO_InitlizePinGPIO(s_GVSU_GPIO * s_userGPIO_ptr)
{
    GPIO_status_t e_retVal = status_failure;

    if (s_userGPIO_ptr->e_IO == input)
    {
        e_retVal = xPrv_GPIO_setInput(s_userGPIO_ptr);
    }
    else if (s_userGPIO_ptr->e_IO == output)
    {
        e_retVal = xPrv_GPIO_setOutput(s_userGPIO_ptr);
    }

    return e_retVal;
}

static GPIO_status_t xPrv_GPIO_setInput(s_GVSU_GPIO * s_userGPIO_ptr)
{
    P(s_userGPIO_ptr->e_portNumber)->SEL0 &= ~BIT(s_userGPIO_ptr->e_pinNumber;  // set as TA0
    P(s_userGPIO_ptr->e_portNumber)->SEL1 &= ~BIT(s_userGPIO_ptr->e_pinNumber; // set as TA0
    P(s_userGPIO_ptr->e_portNumber)->DIR  &= ~BIT(s_userGPIO_ptr->e_pinNumber;  // set as input
    return status_sucess;
}

static GPIO_status_t xPrv_GPIO_setOutput(s_GVSU_GPIO * s_userGPIO_ptr)
{
    P(s_userGPIO_ptr->e_portNumber)->SEL0 |= BIT(s_userGPIO_ptr->e_pinNumber;  // set as TA0
    P(s_userGPIO_ptr->e_portNumber)->SEL1 &= ~BIT(s_userGPIO_ptr->e_pinNumber; // set as TA0
    P(s_userGPIO_ptr->e_portNumber)->DIR  |= BIT(s_userGPIO_ptr->e_pinNumber;  // set as output
    return status_sucess;
}
