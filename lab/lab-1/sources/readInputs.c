#include "readInputs.h"
/*
 * readInputs.c
 *
 *  Created on: Sep 2, 2022
 *      Author: jtluk
 */
bool xReadInputs_ReadPin(port2Pins_t e_userPin)
{
    bool b_retVal = false;
    static uint16_t currDebounceState_t = 0;

    currDebounceState_t = (currDebounceState_t << 1) | !(xPrv_ReadInputs_read(e_userPin)) | MIN_DEBOUNCE_VAL;

    if(currDebounceState_t == MAX_DEBOUNCE_VAL)
    {
        b_retVal = true;
    }

    return b_retVal;

}

static bool xPrv_ReadInputs_read(port2Pins_t e_userPin)
{
    return ((bool)(P2->IN & BIT(e_userPin)));
}
