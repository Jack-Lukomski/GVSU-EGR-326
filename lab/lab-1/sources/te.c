#include "msp.h"
#include "../../../libaries/GVSU_debouncer/debouncer.h"
#include <stdint.h>

void main (void)
{
    volatile uint32_t i;

    int x = xDebouncer_Port2IsPressed(pin4);

    WDT_A->CTL = WDT_A_CTL_PW |             // Stop WDT
                 WDT_A_CTL_HOLD;

    P1->DIR |= BIT0;                        // P1.0 set as output

    while (1)                               // continuous loop
    {
        P1->OUT ^= BIT0;                    // Blink P1.0 LED
        for (i = 40000; i > 0; i--);        // Delay
    }
}