/*****************************************************************************
 * Course:          EGR 326 Section 903
 * Instructor:      Dr. Kandalaft
 * Laboratory 6:    Interfacing a Graphic LCD to the MSP432 MCU
 * Part:            I
 * Description:     This program sets up the MCLK for 48 MHz and the SMCLK for
 *                  12 MHz. It also configures these clocks to be connected
 *                  to the appropriate pins to be checked on an oscilloscope.
 * MSP Pins:        MSP432          CLOCK
 *                  ---------------------
 *                  P4.3            MCLK
 *                  P4.4            HSMCLK
 *                  P7.0            SMCLK
 *****************************************************************************/

#include "msp.h"
#include <ST7735.h>
#include <stdio.h>
#include <stdint.h>

void Clock_Init48MHz(void);                             //Initialize the clock

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;         //Stop WatchDog timer
    Clock_Init48MHz();

     //Output MCLK and SMCLK to port pin to demonstrate 48MHz operation
     P4->DIR  |=   (BIT3 | BIT4);
     P4->SEL0 |=   (BIT3 | BIT4);                       //Output MCLK
     P4->SEL1 &= ~ (BIT3 | BIT4);

     P7->DIR  |=   (BIT0);
     P7->SEL0 |=   (BIT0);                              //Output SMCLK
     P7->SEL1 &= ~ (BIT0);

    while(1)
    {
       ;
    }
}

void Clock_Init48MHz(void)
{
    // Configure Flash wait-state to 1 for both banks 0 & 1
       FLCTL->BANK0_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK0_RDCTL_WAIT_MASK)) |
       FLCTL_BANK0_RDCTL_WAIT_1;
       FLCTL->BANK1_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK0_RDCTL_WAIT_MASK)) |
       FLCTL_BANK1_RDCTL_WAIT_1;

    //Configure HFXT to use 48MHz crystal, source to MCLK & HSMCLK*
       PJ->SEL0 |= BIT2 | BIT3;                     // Configure PJ.2/3 for HFXT function
       PJ->SEL1 &= ~(BIT2 | BIT3);
       CS->KEY = CS_KEY_VAL ;                       // Unlock CS module for register access
       CS->CTL2 |= CS_CTL2_HFXT_EN | CS_CTL2_HFXTFREQ_6 | CS_CTL2_HFXTDRIVE;
          while(CS->IFG & CS_IFG_HFXTIFG)
                    CS->CLRIFG |= CS_CLRIFG_CLR_HFXTIFG;

    /* Select MCLK & HSMCLK = HFXT, no divider */
      CS->CTL1 = CS->CTL1 & ~(CS_CTL1_SELM_MASK     |
                              CS_CTL1_DIVM_MASK     |
                              CS_CTL1_SELS_MASK     |
                              CS_CTL1_DIVHS_MASK)   |
                              CS_CTL1_SELM__HFXTCLK |
                              CS_CTL1_SELS__HFXTCLK;

      CS->CTL1 = CS->CTL1 |CS_CTL1_DIVS_2;    // change the SMCLK clock speed to 12 MHz.

      CS->KEY = 0;                            // Lock CS module from unintended accesses
}
