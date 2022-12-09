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
//    TIMER_A0 -> CTL = 0b0000001011010000; //SMCLK, Up mode, 8 div, clear.
//    TIMER_A0->CTL = 0X2D4;      // SMCLK, Up Mode, clear TAR to start, DIV 8
//    TIMER_A0 -> CCR[0] = TriggerPinPeriodVal; //set the period of CCR
//    TIMER_A0 -> CCTL[2] = 0xE0;  //reset / set
    TIMER_A1 -> CCTL[1] = 0xE0;  //reset / set


//    TIMER_A0 -> EX0 = 0; //divider expansion  /8*(8) 1Hz signal =~ 187500 counts

    TIMER_A1 -> CCR[0] = TriggerPinPeriodVal; //set the period of CCR
    //timerA initialization for Echo pin
    TIMER_A1->CTL = 0X2D4;      // SMCLK, Up Mode, clear TAR to start, DIV 8
//    TIMER_A1 -> CTL = 0b0000001011100010; //SMCLK, continuous mode, 8 div, clear.
    TIMER_A1-> CCTL[2] = 0b1100100100010100;  //Capture on rising / falling edge,
    TIMER_A1 -> EX0 = 3; //divider expansion  /8*(8) 1Hz signal =~ 187500 counts
    TIMER_A1-> R = 0;  //reset count value
}

uint16_t xHCSR04_GetSonarValue()
{
    if(TIMER_A1->CCTL[2] & BIT3)
    {
        TIMER_A1->R = 0;
    }
    else if(TIMER_A1->CCTL[2] &~ BIT3)
    {

        fallingEdge = TIMER_A1->CCR[2];
        TIMER_A1->R = 0;
    }

    TIMER_A1->CCTL[2] &= ~BIT(1);
    TIMER_A1->CCTL[2] &= ~BIT(0);

    return fallingEdge;
}

static void vHCSR04_InitPins()
{
    P7->SEL0 |= BIT(7);
    P7->SEL1 &= ~BIT(7);
    P7->DIR |= BIT(7); // Trigger Pin

    P7->SEL0 |= BIT(6);
    P7->SEL1 &= ~BIT(6);
    P7->DIR &= ~BIT(6); // Echo Pin

}
