#include "speakerSound.h"
/*
 * speakerSound.c
 *
 *  Created on: Dec 5, 2022
 *      Author: jtluk
 */

void vSpeakerSound_Initlize()
{
    // Configure GPIO for PWM output
    P8->DIR |= BIT2;  // P2.4 set TA0.1
    P8->SEL0 |= BIT2;
    P8->SEL1 &= ~(BIT2);

//    TIMER_A0->CCR[0] = period_note - 1;              // PWM Period (# cycles of clock)
    TIMER_A3->CCTL[2] = 0b0000000001110000;      // CCR1 reset/set mode 7
//    TIMER_A0->CCR[1] = DC_volume;       // CCR1 PWM duty cycle in 10ths of percent

//    TIMER_A0->CTL = TASSEL_2 | MC_1 | TACLR;   // SMCLK, Up Mode, clear TAR to start
    TIMER_A3->CTL = 0X294;        // SMCLK, Up Mode, clear TAR to start,
}

void vSpeakerSound_AdjustNoteVol(uint16_t period_note, uint16_t DC_volume)
{
    TIMER_A3->CCR[0] = period_note - 1;              // PWM Period (# cycles of clock)
    TIMER_A3->CCR[2] = DC_volume;       // CCR1 PWM duty cycle in 10ths of percent
}
