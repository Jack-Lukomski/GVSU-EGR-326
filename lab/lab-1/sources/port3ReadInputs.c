#include "port3ReadInputs.h"
/*
 * readInputs.c
 *
 *  Created on: Sep 2, 2022
 *      Author: jtluk
 */
bool xReadInputs_3ReadPin(port3GPIO_t e_userPin)
{
    bool b_retVal = false;
    static uint16_t currDebounceState_t = 0;

    currDebounceState_t = (currDebounceState_t << 1) | !(xPrv_ReadInputs_3read(e_userPin)) | MIN_DEBOUNCE_VAL;

    if(currDebounceState_t == MAX_DEBOUNCE_VAL)
    {
        b_retVal = true;
    }

    return b_retVal;

}

static bool xPrv_ReadInputs_3read(port3GPIO_t e_userPin)
{
    bool b_retVal;

    if(e_userPin.e_GPIOType == pullup3)
    {
        b_retVal = ((bool)(P3->IN & BIT(e_userPin.e_IOpinNumber)));
    }
    else if (e_userPin.e_GPIOType == pulldown3)
    {
        b_retVal = !((bool)(P3->IN & BIT(e_userPin.e_IOpinNumber)));
    }
    else
    {
        b_retVal = false;
    }

    return b_retVal;
}
/*
 * port3ReadInputs.c
 *
 *  Created on: Sep 7, 2022
 *      Author: jtluk
 */


