#include <stdbool.h>
#include "msp.h"
#include "SPI.h"
uint8_t tens;

static void vMain_Init7Seg(void);
static void vMain_Count100(void);
static void vMain_allZeros(void);

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	vSPI_Initlize();
	vMain_Init7Seg();

	while(1)
	{
	    vMain_Count100();
	}
}

static void vMain_Init7Seg(void)
{
    vSPI_writeByte(0x9, 0xFF);
    __delay_cycles(30000);
    vSPI_writeByte(0xA, 0x7);
    __delay_cycles(30000);
    vSPI_writeByte(0xB, 0x7);
    __delay_cycles(30000);
    vSPI_writeByte(0xC, 0x1);
    __delay_cycles(30000);

    vMain_allZeros();
}

static void vMain_Count100(void)
{
    uint8_t onesPlace;
    for(onesPlace = 0; onesPlace < 10; onesPlace++)
    {
        vSPI_writeByte(tens, 0);
        vSPI_writeByte(0x1, onesPlace);
        vSysTick_mSecDelay(1000);
    }
    vMain_allZeros();
    tens++;
    vSPI_writeByte(0x2, tens);
}

static void vMain_allZeros(void)
{
    uint8_t registerSegment;
    for(registerSegment = 1; registerSegment < 9; registerSegment++)
    {
        vSPI_writeByte(registerSegment, 0x0);
        __delay_cycles(30000);
    }
}
