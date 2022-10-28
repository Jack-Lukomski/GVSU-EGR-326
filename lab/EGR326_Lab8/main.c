#include "msp.h"
#include "spi.h"
#include "SysTickTimer.h"
#include "debounce.h"
#include "GPIO_Interrupt.h"


/**
 * main.c
 */

int i;
int j;
int k;
int numPress2;

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	SysTickInit();
	spi_init();
	pin_init();
	NVIC->ISER[1] = 1 << ((PORT1_IRQn) & 31);
    __enable_interrupt();
    __enable_irq();

//    spi_write(0xf, 0x00);           //normal operation, data 1 for display test
	spi_write(0x9, 0xff);           //set decode mode
	spi_write(0xa, 0x05);           //intensity
    spi_write(0xb, 0x07);           //display on digits, data for amount of digits
    spi_write(0x0c, 0x01);          //
    for (j=1; j<=8; j++){
        spi_write(j, 0);
    }
    j=0;
	while(1){
	    spi_write(0x01, i);
	    spi_write(0x02, j);
	    spi_write(0x03, k);
	    if(numPress == 10)
	    {
	        numPress2++;
	        numPress=0;
	    }
	    spi_write(0x05, numPress);
	    SysTickTimer(999);
	    if(pressed == 0) i++;
	    if(i==10)
        {
	        j++;
	        i=0;
        }
	    if(j==10)
	    {
	        k++;
	        j=0;
	    }
	    spi_write(0x01, i);
	}
}