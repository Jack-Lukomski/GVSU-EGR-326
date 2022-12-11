#include "msp.h"
#include "timerA.h"
#include "pinsInint.h"
#include "systick.h"

// 5% Error Margin
#define UPPERLIMIT48HZ 8008
#define LOWERLIMIT48HZ 7618

void vMain_triggerSonarInput(void);

/**
 * main.c
 */
port2GPIO_t echoPin;
port2GPIO triggerPin;

uint8_t currentEdge;
uint8_t lastEdge;
uint8_t period;

bool b_48HzDecected = false;

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	vpinsInit_GPIO(&echoPin, pin5, input, pullup);


    NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);
    __enable_irq ( );

	while(1)
	{
	    printf("period = %d\n", period);
	}
}

void TA0_N_IRQHandler(void)
{
    currentEdge = TIMERA0->CCR[2];
    period = currentEdge - lastEdge;
    lastEdge = currentEdge;

    if((LOWERLIMIT48HZ < period) && (UPPERLIMIT48HZ < period))
    {
        b_48HzDecected = true;
    }

    TIMER_A0->CCTL[2] &= ~(TIMER_A_CCTLN_CCIFG);
}

void vMain_triggerSonarInput(void)
{

}
