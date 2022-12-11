#include "readInputs.h"
/*
 * readInputs.c
 *
 *  Created on: Sep 2, 2022
 *      Author: jtluk
 */
bool xReadInputs_ReadPin(port2GPIO_t e_userPin)
{
    bool b_retVal = false;
    static uint16_t currDebounceState_t = 0;

    currDebounceState_t = (currDebounceState_t << 1) | !(xReadInputs_read(e_userPin)) | MIN_DEBOUNCE_VAL;

    if(currDebounceState_t == MAX_DEBOUNCE_VAL)
    {
        b_retVal = true;
    }

    return b_retVal;

}

bool xReadInputs_read(port2GPIO_t e_userPin)
{
    bool b_retVal;

    if(e_userPin.e_GPIOType == pullup)
    {
        b_retVal = ((bool)(P2->IN & BIT(e_userPin.e_IOpinNumber)));
    }
    else if (e_userPin.e_GPIOType == pulldown)
    {
        b_retVal = !((bool)(P2->IN & BIT(e_userPin.e_IOpinNumber)));
    }
    else
    {
        b_retVal = false;
    }

    return b_retVal;
}
