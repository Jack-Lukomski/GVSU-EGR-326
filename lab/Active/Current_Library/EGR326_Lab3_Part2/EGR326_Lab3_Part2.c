/*******************************************************************************
* Name:             Samuel DeJong
* Course:           EGR 326 - Embedded System Design
* Project:          Lab 03 -Part 1
* File:             main.c
* Description:
* ********************************************************************************/

#include <msp.h>
#include <stdint.h>
#include <stdio.h>

#include "sonar.h"
#include "SysTickTimer.h"

double echo_length;
double distance;
double distance_in;
int blinkOn;

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    sonar_pin_init();
    timerA_init_trigger();
    timerA_init_echo();
    SysTick_init_interrupt();

//    NVIC->ISER[0] = 1 << ((TA0_N_IRQn) & 31);
    NVIC_EnableIRQ(TA0_N_IRQn);

//    __enable_interrupt();
    __enable_irq();

	while(1){
        echo_length = echo_on / ((3e6)/8);
	    distance = ((echo_length*330) - 6);
	    distance_in = (distance/4)*10;
	    if (distance_in<=10 && distance_in>1){
	        blinkOn=1;
	    }
	    else{
	        blinkOn=0;
	        P6->OUT &=~ BIT0;
	    }
        if (blinkOn){
            if(distance_in < 2){
                if(intervalCnt<=(distance_in)){
                    __delay_cycles(1500000);
                    P6->OUT |= BIT0;
                }
                else{
                    __delay_cycles(1500000);
                    P6->OUT &=~ BIT0;
                }
            }
            else
            {
                if(intervalCnt <= (distance_in))
                    P6->OUT |= BIT0;
                else
                    P6->OUT &=~ BIT0;
            }
        }
	}
}
