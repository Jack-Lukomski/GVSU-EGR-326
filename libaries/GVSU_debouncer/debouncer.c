#include "debouncer.h"

bool xDebouncer_Port2IsPressed(port2Pins_t e_userPinNumber)
{
    bool retVal = FALSE;
    static uint16_t s_currentDebounceStatus = 0;

    s_currentDebounceStatus = (s_currentDebounceStatus << 1) | xPrv_Debouncer_ReadPort2(e_userPinNumber) | MIN_DEBOUNCE_VALUE;

    if(s_currentDebounceStatus == MAX_DEBOUNCE_VALUE)
    {
        retVal = TRUE;
    }

    return retVal; 
}

static bool xPrv_Debouncer_ReadPort2(port2Pins_t e_userPinNumber)
{
    bool retVal = FALSE;

    if (~(P2->IN & BIT((uint8_t)e_userPinNumber)) == TRUE)
    {
        retVal = TRUE;
    }

    return retVal;
}