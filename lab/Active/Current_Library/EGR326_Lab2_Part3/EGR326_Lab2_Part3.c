/*******************************************************************************
* Name:             Samuel DeJong
* Course:           EGR 326 - Embedded System Design
* Project:          Lab 02 -Part 3
* File:             main.c
* Description:      This code uses interrupts to cycle through the onboard LED
*                   and switches the order every falling edge of the button,
*                   button 2 is used to blink the LED while it is pressed
* ********************************************************************************/


#include "msp.h"
#include "stdint.h"

#include "debounce.h"
#include "GPIO_Interrupt.h"
#include "SysTickTimer.h"

//macros for easier coding
#define R BIT0
#define G BIT1
#define B BIT2
#define S1 BIT4
#define S2 BIT5


int delay = 5;
uint8_t order;          //1 (rgb); 0(bgr)
int color = 3;
uint8_t debug;
uint8_t blinkOn;


void pin_initialize(void);

void main(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    pin_initialize();
    SysTick_init_interrupt();
    NVIC->ISER[1] = 1<< ((PORT4_IRQn) & 31);
    __enable_interrupt();
    __enable_irq();
    P2->OUT &=~ 0x07;           //clear all colors


    while (1){                      //continous loop
        if(blinkOn==1){
            if(intervalCnt%2){
                P2->OUT |= BIT(color);
            }
            else{
                P2->OUT &=~ 0x07;
            }
        }
        if(riseFlag_1){
            if(debounce_sw1_press()){
                if (order) order=0;
                else order =1;
                riseFlag_1 = 0;
            }
        }
        if(riseFlag_2){
            if(debounce_sw2_press()){
                blinkOn = 1;
                riseFlag_2 = 0;
            }
        }
        if(release_sw2()){
            blinkOn=0;
        }
        if ((order) && (debounce_sw1_press())){
            if (timeout){
                color++;
                if (color > 2) color=0;
                P2->OUT &=~ 0x07;           //clear all colors
                P2->OUT |= BIT(color);
                timeout=0;
            }
        }
        if (~(order) && (debounce_sw1_press())){
            if (timeout){
                color--;
                if (color < 0) color=2;
                P2->OUT &=~ 0x07;           //clear all colors
                P2->OUT |= BIT(color);
                timeout=0;
            }
        }
    }
}

void pin_initialize(void){
    P2->SEL0 &=~ R;      //standard I/O P4.0 LED Red
    P2->SEL1 &=~ R;
    P2->SEL0 &=~ G;      //standard I/O P4.1 LED Green
    P2->SEL1 &=~ G;
    P2->SEL0 &=~ B;      //standard I/O P4.2 LED Blue
    P2->SEL1 &=~ B;
    P4->SEL0 &=~ S1;      //standard I/O P4.4 Switch 1
    P4->SEL1 &=~ S1;
    P4->SEL0 &=~ S2;      //standard I/O P4.4 Switch 2
    P4->SEL1 &=~ S2;

    P2->DIR |= R;        //Set LED Red to output
    P2->DIR |= G;        //Set LED Green to output
    P2->DIR |= B;        //Set LED Blue to output
    P4->DIR &=~ S1;      //Set Switch 1 to input
    P4->DIR &=~ S2;      //Set Switch 2 to input

    P4->REN |= S1;        //Enable resistor in switch 1
    P4->OUT |= S1;        //Make switch 1 pull up
    P4->REN |= S2;        //Enable resistor in switch 2
    P4->OUT |= S2;        //Make switch 2 pull up

    P4->OUT &=~ R;       //Set LED RED to off
    P4->OUT &=~ G;       //Set LED GREEN to off
    P4->OUT &=~ B;       //Set LED BLUE to off

    P4->IES  |=  (S1|S2);
    P4->IE   |=  (S1|S2);
    P4->IFG  &= ~(S1|S2);
}
