#include <stdbool.h>
#include "msp.h"
#include "SPI.h"

uint8_t data = 1;

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	vSPI_Initlize();

	while(1)
	{
	    vSPI_writeByte(data >> 1);
	    __delay_cycles(300000);
	}

}
