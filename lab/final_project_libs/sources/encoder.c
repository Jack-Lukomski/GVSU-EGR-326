#include "encoder.h"
/*
 * encoder.c
 *
 *  Created on: Nov 30, 2022
 *      Author: jtluk
 */

static port4GPIO_t s_encoderButton;
static port4GPIO_t s_encoderCW;
static port4GPIO_t s_encoderCCW;

void vEncoder_Init(port4GPIO_t * s_encoderPorts_ptr)
{
    vpinsInit_GPIO4(&s_encoderButton, s_encoderPorts_ptr[0].e_IOpinNumber, s_encoderPorts_ptr[0].e_IO, s_encoderPorts_ptr[0].e_GPIOType, s_encoderPorts_ptr[0].e_Interrupt);
    vpinsInit_GPIO4(&s_encoderCCW, s_encoderPorts_ptr[1].e_IOpinNumber, s_encoderPorts_ptr[1].e_IO, s_encoderPorts_ptr[1].e_GPIOType, s_encoderPorts_ptr[1].e_Interrupt);
    vpinsInit_GPIO4(&s_encoderCW, s_encoderPorts_ptr[2].e_IOpinNumber, s_encoderPorts_ptr[2].e_IO, s_encoderPorts_ptr[2].e_GPIOType, s_encoderPorts_ptr[2].e_Interrupt);
}

void vEncoder_GetEncoderData(encoder_t * s_encoderData)
{
    s_encoderData->b_buttonStatus = false;

    if(P4->IN & BIT(6))
    {
        s_encoderData->encoderVal++;
    }
    else
    {
        s_encoderData->encoderVal--;
    }

    if(!(P4->IN & BIT(4)))
    {
        __delay_cycles(300000);
        if(!(P4->IN & BIT(4)))
            s_encoderData->b_buttonStatus = true;
    }
}
