#include <stdio.h>
#include "pinsInint.h"
#include "readInputs.h"
#include "msp.h"
#include "HC-SR04.h"
#include "speakerSound.h"
#include "stepperMotorSam.h"
#include "clk48MHz.h"
#define SPEAKER_MSP_SLAVE_ADDRESS 0x48
#define R BIT0
#define G BIT1
#define B BIT2

void RGB_pin_initialize(void);

//port4GPIO_t motor_a;
//port4GPIO_t motor_b;
//port4GPIO_t motor_ap;
//port4GPIO_t motor_bp;

//static const port4GPIO_t motorPortPins[4] =
//{
// {.e_GPIOType4 = pullup4, .e_IO4 = output4, .e_IOpinNumber4 = pin4_4, .e_Interrupt4 = disableInterrupt4}, // A
// {.e_GPIOType4 = pullup4, .e_IO4 = output4, .e_IOpinNumber4 = pin4_5, .e_Interrupt4 = disableInterrupt4}, // B
// {.e_GPIOType4 = pullup4, .e_IO4 = output4, .e_IOpinNumber4 = pin4_6, .e_Interrupt4 = disableInterrupt4}, // Ap
// {.e_GPIOType4 = pullup4, .e_IO4 = output4, .e_IOpinNumber4 = pin4_7, .e_Interrupt4 = disableInterrupt4}, // Bp
//};


float HC_SRO4_Distance;

uint16_t HC_SRO4_ConvertedValue;
uint16_t HC_SRO4_lastConvertedValue;
uint16_t speakerVolume = 2;
uint16_t noteFreq;
uint16_t noteCycles;

port2GPIO_t s_VolUpButton;
port2GPIO_t s_VolDownButton;



void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	vClk_Initlize48MHz();
	xHCSR04_InitlizeTimerA(22500);
	vSpeakerSound_Initlize();
	RGB_pin_initialize();
	stepperInit();
	vpinsInit_GPIO(&s_VolUpButton, pin7, input, pullup, enableInterrupt);
	vpinsInit_GPIO(&s_VolDownButton, pin5, input, pullup, enableInterrupt);
//	  vpinsInit_GPIO4(&motor_ap, pin4_7, output4, pullup4, disableInterrupt4);
//    vpinsInit_GPIO4(&motor_a, pin4_6, output4, pullup4, disableInterrupt4);
//    vpinsInit_GPIO4(&motor_bp, pin4_5, output4, pullup4, disableInterrupt4);
//    vpinsInit_GPIO4(&motor_b, pin4_4, output4, pullup4, disableInterrupt4);

    NVIC_EnableIRQ(TA2_N_IRQn);
    NVIC_EnableIRQ(PORT2_IRQn);
    __enable_interrupt();

    while(1)
    {
        __delay_cycles(50000);
//        TIMER_A2 -> R =0;
        TIMER_A2-> CCR[1] = 5;
        HC_SRO4_lastConvertedValue = HC_SRO4_ConvertedValue;

        if(HC_SRO4_ConvertedValue < 16)
        {
            if(HC_SRO4_ConvertedValue<2)
            {
                noteFreq = 440;     //A4
//                printf("A\n");
                P4->OUT &=~ 0X7;
                P4->OUT |= 0B001;
            }
            else if(HC_SRO4_ConvertedValue<4)
            {
                noteFreq = 494;     //B4
//                printf("B\n");
                P4->OUT &=~ 0X7;
                P4->OUT |= 0B011;

            }
            else if(HC_SRO4_ConvertedValue<6)
            {
                noteFreq = 523;     //C5
//                printf("C\n");
                P4->OUT &=~ 0X7;
                P4->OUT |= 0B010;
            }
            else if(HC_SRO4_ConvertedValue<8)
            {
                noteFreq = 587;     //D5
//                printf("D\n");
                P4->OUT &=~ 0X7;
                P4->OUT |= 0B110;
            }
            else if(HC_SRO4_ConvertedValue<10)
            {
                noteFreq = 659;     //E5
//                printf("E\n");
                P4->OUT &=~ 0X7;
                P4->OUT |= 0B100;
            }
            else // if(HC_SRO4_ConvertedValue<12)
            {
                noteFreq = 698;     //F5
//                printf("F\n");
                P4->OUT &=~ 0X7;
                P4->OUT |= 0B101;
            }

            noteCycles = (uint16_t)(3000000/noteFreq);
            vSpeakerSound_AdjustNoteVol(noteCycles, noteCycles/speakerVolume);
//            printf("%d\n", HC_SRO4_ConvertedValue);
        }
        else
        {
            if(HC_SRO4_lastConvertedValue > 16)
            {
                vSpeakerSound_AdjustNoteVol(noteCycles, 0);
                P4->OUT &=~ 0X7;
            }
        }
    }

}

void TA2_N_IRQHandler(void)
{

    HC_SRO4_Distance = xHCSR04_GetSonarValue();
    HC_SRO4_ConvertedValue = (uint16_t)((((HC_SRO4_Distance*8)/3)/148));  //converted to inches
    TIMER_A2->CTL &=~ (BIT0);
}

void PORT2_IRQHandler(void)
{
    __delay_cycles(300000);
    if(xReadInputs_read(s_VolUpButton))
    {
        speakerVolume *= 2;
        vStepperMotor_turnDeg(1, 0, 20);
        if(speakerVolume > 256)
        {
            speakerVolume = 2;
        }
    vSpeakerSound_AdjustNoteVol(noteCycles, noteCycles/speakerVolume);
    printf("%d volume\n", speakerVolume);
    }

    if(xReadInputs_read(s_VolDownButton))
    {
        speakerVolume /= 2;
        vStepperMotor_turnDeg(1, 1, 20);
        if(speakerVolume <= 1)
        {
            speakerVolume = 256;
        }
    vSpeakerSound_AdjustNoteVol(noteCycles, noteCycles/speakerVolume);
    printf("%d volume\n", speakerVolume);
    }
    P2->IFG = 0;
}


void RGB_pin_initialize(void){
    P4->SEL0 &=~ R;      //standard I/O P4.0 LED Red
    P4->SEL1 &=~ R;
    P4->SEL0 &=~ G;      //standard I/O P4.1 LED Green
    P4->SEL1 &=~ G;
    P4->SEL0 &=~ B;      //standard I/O P4.2 LED Blue
    P4->SEL1 &=~ B;

    P4->DIR |= R;        //Set LED Red to output
    P4->DIR |= G;        //Set LED Green to output
    P4->DIR |= B;        //Set LED Blue to output

    P4->OUT &=~ R;       //Set LED RED to off
    P4->OUT &=~ G;       //Set LED GREEN to off
    P4->OUT &=~ B;       //Set LED BLUE to off
}

