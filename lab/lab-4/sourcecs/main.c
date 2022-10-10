#include "msp.h"
#include "pinsInint.h"
#include "systick.h"
#include "readInputs.h"
#include "Toggle.h"
#include "keypad.h"
#include <stdio.h>
#include <stdbool.h>

void vMain_CCWTurn(void);
void vMain_CWTurn(void);
void vMain_ReadTwoDigits(void);

port2GPIO_t encoder_button;
port2GPIO_t encoder_cw;
port2GPIO_t encoder_ccw;
port2GPIO_t blue_LED;
port2GPIO_t red_LED;

int16_t encoder_count = 0;
uint8_t encoderButton_count = 0;
uint8_t userInputtedValue = 1;

bool b_cw = false;
bool b_ccw = false;
bool b_button = false;
bool b_encoderState = false;

uint8_t stateCount = 0;
uint8_t userVal1 = 1;
uint8_t userVal2 = 1;

/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    vpinsInit_GPIO(&encoder_button, pin4, input, pullup, disableInterrupt);
    vpinsInit_GPIO(&encoder_cw, pin5, input, pullup, enableInterrupt);
    vpinsInit_GPIO(&encoder_ccw, pin6, input, pullup, enableInterrupt);
    vpinsInit_GPIO(&red_LED, pin3, output, pullup, disableInterrupt);
    vpinsInit_GPIO(&blue_LED, pin7, output, pullup, disableInterrupt);

    vSysTick_Init();
    vkeypad_Initialize();

    NVIC_EnableIRQ(PORT2_IRQn);
    __enable_interrupt();

    while(1)
    {
        if(xkeypad_ReadKeypad())
        {
            vMain_ReadTwoDigits();
        }
        if(b_cw)
        {
            vMain_CWTurn();
        }
        if(b_ccw)
        {
            vMain_CCWTurn();
        }
        if(encoder_count == userInputtedValue && stateCount == 2)
        {
            vToggle_turnPinLow(red_LED);
            vToggle_turnPinHigh(blue_LED);
        }
        if(encoder_count*-1 == userInputtedValue && stateCount == 2)
        {
            vToggle_turnPinLow(blue_LED);
            vToggle_turnPinHigh(red_LED);
        }
        if(xReadInputs_read(encoder_button) != true)
        {
            printf("Resetting..\n");
            vToggle_turnPinLow(red_LED);
            vToggle_turnPinLow(blue_LED);
            userInputtedValue = 1;
            encoder_count = 0;
            stateCount = 0;
        }
    }
}

void PORT2_IRQHandler(void)
{
    if((P2->IFG & BIT(encoder_cw.e_IOpinNumber)) && !(P2->IN & BIT(encoder_ccw.e_IOpinNumber)))
    {
        b_cw = true;
    }

    if(!(P2->IN & BIT(encoder_cw.e_IOpinNumber)) && (P2->IFG & BIT(encoder_ccw.e_IOpinNumber)))
    {
        b_ccw = true;
    }
    P2->IFG = 0;
}

void vMain_CWTurn(void)
{
    if(xReadInputs_ReadPin(encoder_cw) != true)
    {
        encoder_count++;
    }
    b_cw = false;
    b_ccw = false;
    b_button = false;
}

void vMain_CCWTurn(void)
{
    if(xReadInputs_ReadPin(encoder_ccw) != true)
    {
        encoder_count--;
    }
    b_ccw = false;
    b_button = false;
    b_cw = false;
}

void vMain_ReadTwoDigits(void)
{
    while(stateCount < 2)
    {
        if(stateCount == 0)
        {
            userVal1 = key - 48;
            stateCount++;
        }
        if(stateCount == 1 && xkeypad_ReadKeypad())
        {
            userVal2 = key - 48;
            if(key == ';')
            {
                userVal2 = 0;
            }
            stateCount++;
        }

        userInputtedValue = userVal1*10 + userVal2*1;
    }
    printf("%d\n", userInputtedValue);
}
