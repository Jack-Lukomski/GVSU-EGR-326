#include "SamsSonarLib.h"
/*
 * SamsSonarLib.c
 *
 *  Created on: Dec 9, 2022
 *      Author: jtluk
 */

float HC_SRO4_Distance;

uint16_t HC_SRO4_ConvertedValue;
uint16_t HC_SRO4_lastConvertedValue;
uint16_t speakerVolume = 2;
uint16_t noteFreq;
uint16_t noteCycles;

port2GPIO_t s_VolUpButton;
port2GPIO_t s_VolDownButton;

void vMusicDriver(void)
{
    __delay_cycles(50000);
    //        TIMER_A1 -> R =0;
            TIMER_A1-> CCR[1] = 5;
            HC_SRO4_lastConvertedValue = HC_SRO4_ConvertedValue;

            if(HC_SRO4_ConvertedValue < 16)
            {
                if(HC_SRO4_ConvertedValue<2)
                {
                    noteFreq = 440;     //A4
                    CurrNotePlaying = 'A';
    //                printf("A\n");
                    P4->OUT &=~ 0X7;
                    P4->OUT |= 0B001;
                }
                else if(HC_SRO4_ConvertedValue<4)
                {
                    noteFreq = 494;     //B4
                    CurrNotePlaying = 'B';
    //                printf("B\n");
                    P4->OUT &=~ 0X7;
                    P4->OUT |= 0B011;

                }
                else if(HC_SRO4_ConvertedValue<6)
                {
                    noteFreq = 523;     //C5
                    CurrNotePlaying = 'C';
    //                printf("C\n");
                    P4->OUT &=~ 0X7;
                    P4->OUT |= 0B010;
                }
                else if(HC_SRO4_ConvertedValue<8)
                {
                    noteFreq = 587;     //D5
                    CurrNotePlaying = 'D';
    //                printf("D\n");
                    P4->OUT &=~ 0X7;
                    P4->OUT |= 0B110;
                }
                else if(HC_SRO4_ConvertedValue<10)
                {
                    noteFreq = 659;     //E5
                    CurrNotePlaying = 'E';
    //                printf("E\n");
                    P4->OUT &=~ 0X7;
                    P4->OUT |= 0B100;
                }
                else
                {
                    noteFreq = 698;     //F5
                    CurrNotePlaying = 'F';
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

void preMusicInit(void)
{
    xHCSR04_InitlizeTimerA(22500);
    vSpeakerSound_Initlize();
    RGB_pin_initialize();
    stepperInit();
    vpinsInit_GPIO(&s_VolUpButton, pin7, input, pullup, enableInterrupt);
    vpinsInit_GPIO(&s_VolDownButton, pin5, input, pullup, enableInterrupt);

    NVIC_EnableIRQ(TA1_N_IRQn);
    NVIC_EnableIRQ(PORT2_IRQn);
    __enable_interrupt();
}

void postMusicDisable(void)
{
    NVIC_DisableIRQ(TA1_N_IRQn);
    NVIC_DisableIRQ(PORT2_IRQn);
}

void vAdjustVolume_IQR(void)
{
    xI2C_Read(EEPROM_SLAVE_ADDRESS, 3, &CurrentVolume8Scale);
    __delay_cycles(300000);
       if(xReadInputs_read(s_VolUpButton))
       {
           CurrentVolume8Scale++;
           speakerVolume *= 2;
           vStepperMotor_turnDeg(1, 0, 20);
           if(speakerVolume > 256)
           {
               speakerVolume = 2;
           }
           if(CurrentVolume8Scale > 8)
           {
               CurrentVolume8Scale = 1;
           }
       vSpeakerSound_AdjustNoteVol(noteCycles, noteCycles/speakerVolume);
       }

       if(xReadInputs_read(s_VolDownButton))
       {
           CurrentVolume8Scale--;
           speakerVolume /= 2;
           vStepperMotor_turnDeg(1, 1, 20);
           if(speakerVolume <= 1)
           {
               speakerVolume = 256;
           }
           if(CurrentVolume8Scale < 1)
           {
               CurrentVolume8Scale = 8;
           }
       vSpeakerSound_AdjustNoteVol(noteCycles, noteCycles/speakerVolume);
       }
       xI2C_Write(EEPROM_SLAVE_ADDRESS, 3, CurrentVolume8Scale);
}

void vTimerA_InteruptHelper(void)
{
    HC_SRO4_Distance = xHCSR04_GetSonarValue();
    HC_SRO4_ConvertedValue = (uint16_t)((((HC_SRO4_Distance*8)/3)/148));  //converted to inches
}

void RGB_pin_initialize(void)
{
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
