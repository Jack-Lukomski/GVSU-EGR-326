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
    P2->DIR |= BIT4;  // P2.4 set TA0.1
    P2->SEL0 |= BIT4;
    P2->SEL1 &= ~(BIT4);

    //TIMER_A0->CCR[0] = period_note - 1;              // PWM Period (# cycles of clock)
    TIMER_A0->CCTL[1] = 0b0000000001110000;      // CCR1 reset/set mode 7
    //TIMER_A0->CCR[1] = DC_volume;       // CCR1 PWM duty cycle in 10ths of percent

    TIMER_A0->CTL = 0b0000001000010100;     // SMCLK, Up Mode, clear TAR to start

    TIMER_A0->CTL = TASSEL_2 | MC_1 | TACLR;   // SMCLK, Up Mode, clear TAR to start
    TIMER_A0->CTL = 0x0214;                   // SMCLK, Up Mode, clear TAR to start
}

void vSpeakerSound_AdjustNoteVol(uint16_t period_note, uint16_t DC_volume)
{
    TIMER_A0->CCR[0] = period_note - 1;              // PWM Period (# cycles of clock)
    TIMER_A0->CCR[1] = DC_volume;       // CCR1 PWM duty cycle in 10ths of percent
}
