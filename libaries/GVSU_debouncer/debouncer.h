/* Designed for pull-down buttons */
#ifndef DEBOUNCER_H
#define DEBOUNCER_H

#include "msp.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define MIN_DEBOUNCE_VALUE 0xe000;
#define MAX_DEBOUNCE_VALUE 0xf000;

typedef enum port2Pins_t
{
    pin0,
    pin1,
    pin2,
    pin3,
    pin4,
    pin5,
    pin6,
    pin7,
}port2Pins_t;

bool xDebouncer_Port2IsPressed(port2Pins_t e_userPinNumber);
static bool xPrv_Debouncer_ReadPort2(port2Pins_t e_userPinNumber);


#endif /* DEBOUNCER_H */