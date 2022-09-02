#include "msp.h"
#include "pinsInint.h"
#include "readInputs.h"

/**
 * main.c
 *
 * PIN 2.4 B
 * PIN 2.5 G
 * PIN 2.6 R
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	vpinsInit_GPIO(pin7, input, pullup);
	vpinsInit_GPIO(pin5, output, pullup);

	while(1)
	{
	    P2->OUT ^= BIT(pin5);
	}
}
