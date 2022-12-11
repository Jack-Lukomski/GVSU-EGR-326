#include <stdio.h>
#include "pinsInint.h"
#include "readInputs.h"
#include "msp.h"
#include "HC-SR04.h"
#include "speakerSound.h"
#define SPEAKER_MSP_SLAVE_ADDRESS 0x48

float HC_SRO4_Distance;

uint16_t HC_SRO4_ConvertedValue;
uint16_t HC_SRO4_lastConvertedValue;
uint16_t speakerVolume = 25;

port2GPIO_t s_VolUpButton;
port2GPIO_t s_VolDownButton;

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	xHCSR04_InitlizeTimerA(6429);
	vSpeakerSound_Initlize();
	vpinsInit_GPIO(&s_VolUpButton, pin7, input, pullup, enableInterrupt);
	vpinsInit_GPIO(&s_VolDownButton, pin3, input, pullup, enableInterrupt);

    NVIC_EnableIRQ(TA2_N_IRQn);
    NVIC_EnableIRQ(PORT2_IRQn);
    __enable_interrupt();

    while(1)
    {
        __delay_cycles(500000);
        TIMER_A2 -> R =0;
        TIMER_A0-> CCR[2] = 1;

        if(HC_SRO4_ConvertedValue < 5000)
        {
            if(HC_SRO4_ConvertedValue > HC_SRO4_lastConvertedValue+150 || HC_SRO4_ConvertedValue < HC_SRO4_lastConvertedValue-150)
            {
                vSpeakerSound_AdjustNoteVol(HC_SRO4_ConvertedValue, HC_SRO4_ConvertedValue/speakerVolume);
                HC_SRO4_lastConvertedValue = HC_SRO4_ConvertedValue;
                printf("%d\n", HC_SRO4_ConvertedValue);
            }
        }
        else
        {
            vSpeakerSound_AdjustNoteVol(HC_SRO4_ConvertedValue, 0);
        }
    }

}

void TA2_N_IRQHandler(void)
{
    HC_SRO4_Distance = xHCSR04_GetSonarValue();
    HC_SRO4_ConvertedValue = (uint16_t)((HC_SRO4_Distance*9.333/148)*800);
}

void PORT2_IRQHandler(void)
{
    __delay_cycles(300000);
    if(xReadInputs_read(s_VolUpButton))
    {
        speakerVolume += 25;
        if(speakerVolume > 250)
        {
            speakerVolume = 25;
        }
    vSpeakerSound_AdjustNoteVol(HC_SRO4_ConvertedValue, HC_SRO4_ConvertedValue/speakerVolume);
    printf("%d volume\n", speakerVolume);
    }

    if(xReadInputs_read(s_VolDownButton))
    {
        speakerVolume -= 25;
        if(speakerVolume <= 0)
        {
            speakerVolume = 250;
        }
    vSpeakerSound_AdjustNoteVol(HC_SRO4_ConvertedValue, HC_SRO4_ConvertedValue/speakerVolume);
    printf("%d volume\n", speakerVolume);
    }
    P2->IFG = 0;
}
