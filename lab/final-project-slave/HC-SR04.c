#include "HC-SR04.h"
/*
 * HC-SR04.c
 *
 *  Created on: Dec 1, 2022
 *      Author: jtluk
 */

volatile uint16_t risingEdge = 1;
uint16_t fallingEdge;

void xHCSR04_InitlizeTimerA(uint16_t TriggerPinPeriodVal)
{
    vHCSR04_InitPins();

    //timerA initialization for Trigger pin
    TIMER_A0 -> CTL = 0b0000001010010000; //SMCLK, Up mode, 4 div, clear.
    TIMER_A0 -> CCR[0] = TriggerPinPeriodVal; //set the period of CCR
    TIMER_A0 -> CCTL[2] = 0xE0;  //reset / set
    TIMER_A0 -> EX0 = 5; //divider expansion  /4*(6+1) 1Hz signal =~ 107142 counts

    //timerA initialization for Echo pin
    TIMER_A2 -> CTL = 0b0000001010100010; //SMCLK, continuous mode, 4 div, clear.

    TIMER_A2-> CCTL[2] = 0b1100100100010100;  //Capture on rising / falling edge,
    TIMER_A2 -> EX0 = 5; //divider expansion  /4*(6+1) 1Hz signal =~ 107142 counts
    TIMER_A2-> R = 0;  //reset count value
}

uint16_t xHCSR04_GetSonarValue()
{
    if(risingEdge == 1)
    {
        TIMER_A2->R = 0;
        risingEdge = 0;
    }
    if(risingEdge == 0)
    {
        fallingEdge = TIMER_A2->CCR[2];
        TIMER_A2->R = 0;
        risingEdge = 1;
    }

    TIMER_A2->CCTL[2] &= ~BIT(1);
    TIMER_A2->CCTL[2] &= ~BIT(0);

    return fallingEdge;
}

static void vHCSR04_InitPins()
{
    P2->SEL0 |= BIT(5);
    P2->SEL1 &= ~BIT(5);
    P2->DIR |= BIT(5); // Trigger Pin

    P5->SEL0 |= BIT(7);
    P5->SEL1 &= ~BIT(7);
    P5->DIR &= ~BIT(7); // Echo Pin

}
