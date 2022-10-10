#include <stdio.h>
#include "msp.h"
#include "pinsInint.h"
#include "I2C.h"

uint8_t recieveData;

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	vI2C_Initlize();
	xI2C_Write(SLAVE_ADDRESS, 0, 0);

	for(;;)
	{
	    xI2C_Read(SLAVE_ADDRESS, 0, &recieveData);
	    printf("%x\n", recieveData);
	}
}
