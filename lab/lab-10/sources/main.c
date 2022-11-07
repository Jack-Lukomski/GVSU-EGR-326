#include <stdio.h>
#include <string.h>
#include "msp.h"
#include "pinsInint.h"
#include "Toggle.h"
#include "ST7735.h"
#include "systick.h"
#include "readInputs.h"

void vMain_InitRTC(void);
void vMain_Initlize48MHz(void);
void vMain_InitPushButton(void);

port2GPIO_t s_pushButton;

uint16_t WDTResetCount;
char WDTResetCount_str[100] = "0";

void main(void)
{
    vMain_Initlize48MHz();
    ST7735_InitR(none);
	ST7735_FillScreen(ST7735_WHITE);
    vSysTick_Init();
	vMain_InitRTC();
	vpinsInit_GPIO(&s_pushButton, pin2, input, pullup, disableInterrupt);

	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_IS_3 | WDT_A_CTL_SSEL__ACLK |  WDT_A_CTL_CNTCL | WDT_A_CTL_TMSEL;

	NVIC_EnableIRQ(WDT_A_IRQn);
	NVIC_EnableIRQ(PORT1_IRQn);

	while(1)
	{
	    ST7735_DrawCharS(55, 45, RTCSEC + 48, ST7735_BLACK, ST7735_WHITE, 4);
	    if(!xReadInputs_read(s_pushButton))
	    {
	        WDT_A -> CTL = 0;
	    }
	}
}

void WDT_A_IRQHandler()
{
    ST7735_FillScreen(ST7735_WHITE);
    vMain_InitRTC();
}

void vMain_InitRTC(void)
{
    RTCCTL0_H = RTCKEY_H;
    RTCSEC = 0;
    RTCCTL1 &= ~(RTCHOLD);
}

void PORT1_IRQHandler()
{

    //WDT_A -> CTL = 0;
    P1->IFG = 0;
}

void vMain_Initlize48MHz(void)
{
    // Configure Flash wait-state to 1 for both banks 0 & 1
       FLCTL->BANK0_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK0_RDCTL_WAIT_MASK)) |
       FLCTL_BANK0_RDCTL_WAIT_1;
       FLCTL->BANK1_RDCTL = (FLCTL->BANK0_RDCTL & ~(FLCTL_BANK0_RDCTL_WAIT_MASK)) |
       FLCTL_BANK1_RDCTL_WAIT_1;

    //Configure HFXT to use 48MHz crystal, source to MCLK & HSMCLK*
       PJ->SEL0 |= BIT2 | BIT3;                     // Configure PJ.2/3 for HFXT function
       PJ->SEL1 &= ~(BIT2 | BIT3);
       CS->KEY = CS_KEY_VAL;                       // Unlock CS module for register access
       CS->CTL2 |= CS_CTL2_HFXT_EN | CS_CTL2_HFXTFREQ_6 | CS_CTL2_HFXTDRIVE;
          while(CS->IFG & CS_IFG_HFXTIFG)
                    CS->CLRIFG |= CS_CLRIFG_CLR_HFXTIFG;

    /* Select MCLK & HSMCLK = HFXT, no divider */
      CS->CTL1 = CS->CTL1 & ~(CS_CTL1_SELM_MASK     |
                              CS_CTL1_DIVM_MASK     |
                              CS_CTL1_SELS_MASK     |
                              CS_CTL1_DIVHS_MASK)   |
                              CS_CTL1_SELM__HFXTCLK |
                              CS_CTL1_SELS__HFXTCLK |
                              CS_CTL1_SELA__REFOCLK;

      CS->CTL1 = CS->CTL1 | CS_CTL1_DIVS_2;    // change the SMCLK clock speed to 12 MHz.

      CS->CLKEN = CS->CLKEN | CS_CLKEN_ACLK_EN | CS_CLKEN_REFO_EN | CS_CLKEN_REFOFSEL;

      CS->KEY = 0;                            // Lock CS module from unintended accesses
}
