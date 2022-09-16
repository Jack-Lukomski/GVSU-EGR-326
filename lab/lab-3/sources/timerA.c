#include "timerA.h"
/*
 * timerA.c
 *
 *  Created on: Sep 16, 2022
 *      Author: jtluk
 */

void vtimerA0_CaputureInitlize(void)
{

    TIMER_A0->CTL |= TIMER_A_CTL_TASSEL_2 | // SMCLK
                     TIMER_A_CTL_MC_UP    | // Up mode
                     TIMER_A_CTL_ID_3     | // Divide by 8 -> 377kHz
                     TIEMR_A_CTL_CLR;       // Clear TA0R

    TIMER_A0->CCTL[2] = TIMER_A_CCTLN_CM_1   | // Capture rising edge,
                        TIMER_A_CCTLN_CCIS_0 | // Use CCI2A=ACLK,
                        TIMER_A_CCTLN_CCIE   | // Enable capture interrupt
                        TIMER_A_CCTLN_CAP    | // Enable capture mode,
                        TIMER_A_CCTLN_SCS;
}

void vtimerA1_PWMInitlize(uint16_t period, uint16_t dutyCycle)
{
    TIMER_A1->CCR[0] = period - 1;
    TIMER_A1->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A1->CCR[1] = dutyCycle;

    TIMER_A1->CTL = TIMER_A_CTL_SSEL_SMCLK |
                    TIMER_A_CTL_MC__UP     |
                    TIMER_A_CTL_CLR;
}

