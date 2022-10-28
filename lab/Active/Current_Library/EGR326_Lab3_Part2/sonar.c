/*********************************************************************************
* Name:             Sam DeJong
* Course:           EGR 326
* Project:          Lab 3
*
* File:             sonar.c
* Description:
**********************************************************************************/

#include "sonar.h"
#include "msp.h"
#include "stdint.h"
#include "SysTickTimer.h"


void sonar_trig(void){
    TIMER_A2->CCR[0] = (int) (((3e6)/8)/FREQ);
    TIMER_A2->CCR[1] = (int) (3e6)*(1e-6)*8;               //initially set to 0
}

void sonar_pin_init(void){
    TRIG_PORT-> SEL0 |=  TRIG_PIN;
    TRIG_PORT-> SEL1 &=~ TRIG_PIN;
    TRIG_PORT-> DIR  |=  TRIG_PIN;

    ECHO_PORT-> SEL0 |=  ECHO_PIN;
    ECHO_PORT-> SEL1 &=~ ECHO_PIN;
    ECHO_PORT-> DIR  &=~ ECHO_PIN;

    LED_PORT-> SEL0 &=~ LED_PIN;
    LED_PORT-> SEL1 &=~ LED_PIN;
    LED_PORT-> DIR  |=  LED_PIN;
}


void timerA_init_trigger(void){
    /*  Configure TimerA0.1 as PWM*/
//    TIMER_A2->CCR[0] = (int) (((3e6)/8)/FREQ);
    TIMER_A2->CCR[0] = 0xffff;
    TIMER_A2->CCR[1] = (int) (3e6)*(1e-6)*8;               //initially set to 0
    TIMER_A2->CTL = 0x02D4;        // SMCLK, divide by 8, up mode, timer clear
    TIMER_A2->CCTL[1] = 0x00e0;        //reset/set outmode 7
            //(SMCLK | countUp | timerAClear);
}


void timerA_init_echo(void){
    /*  Configure TimerA0.1 as PWM*/
    TIMER_A0->CCR[0] = 0xffff;
    TIMER_A0->CCR[1] = 0;               //initially set to 0
    TIMER_A0->CTL    = 0x0226;        // SMCLK, divide by 8, up mode, timer clear
    TIMER_A0->CCTL[1] = 0xc914;         //rising edge, sync, capture mode, interrupt enable
    TIMER_A0->CCTL[1] &=~ (BIT0 | BIT1);
            //(SMCLK | countUp | timerAClear);
}


void TA0_N_IRQHandler(void){
    if((TIMER_A0->CCTL[1]) & BIT0){
//        flag=1;
        echo_on = TIMER_A0->CCR[1];
    }
    TIMER_A0->CCTL[1] &=~ (BIT0 | BIT1);
    TIMER_A0->CTL &=~ BIT0;
//    TIMER_A0->CTL |= BIT2;
//    TIMER_A0->CTL &=~ BIT2;
}

