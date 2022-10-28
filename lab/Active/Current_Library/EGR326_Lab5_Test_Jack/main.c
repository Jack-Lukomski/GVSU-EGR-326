#include <stdio.h>
#include "msp.h"
//#include "pinsInint.h"
#include "I2C.h"

uint8_t readData;

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	EUSCI_B0->CTLW0 &=~ 0x0002;
	vI2C_Initlize();
	xI2C_Write(SLAVE_ADDRESS, 0, 0);
	__delay_cycles(3000);
	for(;;)
	{
	    xI2C_Read(SLAVE_ADDRESS, 0, &readData);
	    __delay_cycles(3000);
	    printf("%x\n", readData);
	}
}
