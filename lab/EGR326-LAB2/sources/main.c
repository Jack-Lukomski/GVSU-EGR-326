#include "msp.h"
#include "pinsInint.h"
#include "systick.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "Toggle.h"
#include "readInputs.h"

#define PART_1 0
#define PART_2 0
#define PART_3 1

void vMain_minBlinkRate();

port2GPIO_t s_fowardPushButton;
port2GPIO_t s_backwardsPushButton;
port2GPIO_t s_redLED;
port2GPIO_t s_greenLED;
port2GPIO_t s_blueLED;

#if PART_1
volatile uint16_t blinkRate = 4000;
bool initialPress = false;
bool b_turnOffFlag = false;

/**
 * main.c
 */

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	vSysTick_Init();
	vpinsInit_GPIO(&s_fowardPushButton, pin7, input, pullup, enableInterrupt);
    vpinsInit_GPIO(&s_backwardsPushButton, pin5, input, pullup, enableInterrupt);
	vpinsInit_GPIO(&s_blueLED, pin6, output, pullup, disableInterrupt);

	NVIC_EnableIRQ(PORT2_IRQn);
	__enable_interrupt();

	while(1)
	{
	    if(initialPress)
	    {
	        if(blinkRate <= 0)
	        {
	            blinkRate = 1;
	        }
	        if(!b_turnOffFlag && blinkRate < 4000)
	        {
	            b_turnOffFlag = false;
                vSysTick_mSecDelay((uint16_t)blinkRate/2);
	            vToggle_turnPinHigh(s_blueLED);
	            vSysTick_mSecDelay((uint16_t)blinkRate/2);
	            vToggle_turnPinLow(s_blueLED);
	            printf("blink rate: %d\n", (uint16_t)blinkRate);
	        }
	    }
	}
}

void PORT2_IRQHandler(void)
{
    if(P2->IFG & BIT(s_fowardPushButton.e_IOpinNumber))
    {
        vSysTick_mSecDelay(10);
        if(P2->IFG & BIT(s_fowardPushButton.e_IOpinNumber))
        {

            blinkRate = blinkRate / 2;
            initialPress = true;
            vMain_minBlinkRate();
        }
    }

    if(P2->IFG & BIT(s_backwardsPushButton.e_IOpinNumber))
    {
        vSysTick_mSecDelay(10);
        if(P2->IFG & BIT(s_backwardsPushButton.e_IOpinNumber))
        {
            blinkRate = blinkRate * 2;
            initialPress = true;
            vMain_minBlinkRate();
        }
    }
    P2->IFG &= ~BIT(s_fowardPushButton.e_IOpinNumber);
    P2->IFG &= ~BIT(s_backwardsPushButton.e_IOpinNumber);
}

void vMain_minBlinkRate()
{
    if(blinkRate >= 4000)
    {
        b_turnOffFlag = true;
        blinkRate = 4000;
    }
    else
    {
        b_turnOffFlag = false;
    }
}
#endif
#if PART_2

#define NUM_FUNCTIONS 3

uint8_t functionOrder = 0;
int8_t functionCall = 0;
bool b_isButtonHeld = false;

typedef void(*vMain_ledColor_ptr)(void);

void vMain_BlueOn(void);
void vMain_GreenOn(void);
void vMain_RedOn(void);

static const vMain_ledColor_ptr ledColor_t[NUM_FUNCTIONS] =
{
 vMain_RedOn,
 vMain_GreenOn,
 vMain_BlueOn,
};

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    vSysTick_IntteruptInit(1000);
    vpinsInit_GPIO(&s_fowardPushButton, pin7, input, pullup, disableInterrupt);
    vpinsInit_GPIO(&s_blueLED, pin2, output, pulldown, disableInterrupt);
    vpinsInit_GPIO(&s_redLED, pin0, output, pulldown, disableInterrupt);
    vpinsInit_GPIO(&s_greenLED, pin1, output, pulldown, disableInterrupt);

    NVIC_EnableIRQ(PORT2_IRQn);
    __enable_interrupt();

    while(1)
    {
        if(!xReadInputs_read(s_fowardPushButton))
        {
            while(!xReadInputs_read(s_fowardPushButton))
            {
                b_isButtonHeld = true;
            }
            functionOrder = !functionOrder;
            printf("%d\n", functionOrder);
        }
        b_isButtonHeld = false;
    }
}

void SysTick_Handler(void)
{
    if(b_isButtonHeld)
    {
        if(functionOrder == 0)
        {
            ledColor_t[functionCall]();
            if(++functionCall == NUM_FUNCTIONS)
            {
                functionCall = 0;
            }
        }

        if(functionOrder == 1)
        {
            if(--functionCall < 0)
            {
                functionCall = NUM_FUNCTIONS-1;
            }
            ledColor_t[functionCall]();
        }
    }
}

void vMain_BlueOn(void)
{
    vToggle_turnPinHigh(s_blueLED);
    vToggle_turnPinLow(s_redLED);
    vToggle_turnPinLow(s_greenLED);
}

void vMain_GreenOn(void)
{
    vToggle_turnPinHigh(s_greenLED);
    vToggle_turnPinLow(s_redLED);
    vToggle_turnPinLow(s_blueLED);
}

void vMain_RedOn(void)
{
    vToggle_turnPinHigh(s_redLED);
    vToggle_turnPinLow(s_blueLED);
    vToggle_turnPinLow(s_greenLED);
}

#endif

#if PART_3
#define NUM_FUNCTIONS 3

int8_t functionCall = 0;
bool b_isButtonHeld = false;
bool b_toggleLed = false;
uint8_t systikDivider = 0;

typedef void(*vMain_ledColor_ptr)(void);

void vMain_BlueOn(void);
void vMain_GreenOn(void);
void vMain_RedOn(void);
void vMain_TurnAllOff(void);

static const vMain_ledColor_ptr ledColor_t[NUM_FUNCTIONS] =
{
 vMain_RedOn,
 vMain_GreenOn,
 vMain_BlueOn,
};

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    vSysTick_IntteruptInit(500);
    vpinsInit_GPIO(&s_fowardPushButton, pin7, input, pullup, disableInterrupt);
    vpinsInit_GPIO(&s_backwardsPushButton, pin5, input, pullup, disableInterrupt);
    vpinsInit_GPIO(&s_blueLED, pin2, output, pulldown, disableInterrupt);
    vpinsInit_GPIO(&s_redLED, pin0, output, pulldown, disableInterrupt);
    vpinsInit_GPIO(&s_greenLED, pin1, output, pulldown, disableInterrupt);

    NVIC_EnableIRQ(PORT2_IRQn);
    __enable_interrupt();

    while(1)
    {
        if(!xReadInputs_read(s_fowardPushButton))
        {
            while(!xReadInputs_read(s_fowardPushButton))
            {
                b_isButtonHeld = true;
            }
        }

        if(!xReadInputs_read(s_backwardsPushButton))
        {
            vMain_TurnAllOff();
            while(!xReadInputs_read(s_backwardsPushButton))
            {
                b_toggleLed = true;
            }
            if(functionCall == 1)
            {
                vToggle_turnPinHigh(s_redLED);
            }
            if(functionCall == 2)
            {
                vToggle_turnPinHigh(s_greenLED);
            }
            if(functionCall == 0)
            {
                vToggle_turnPinHigh(s_blueLED);
            }
        }
        b_toggleLed = false;
        b_isButtonHeld = false;
    }
}

void SysTick_Handler(void)
{
    if(b_toggleLed)
    {
        if(functionCall == 1)
        {
            vToggle_toggle(s_redLED);
        }
        if(functionCall == 2)
        {
            vToggle_toggle(s_greenLED);
        }
        if(functionCall == 0)
        {
            vToggle_toggle(s_blueLED);
        }
    }

    if(b_isButtonHeld && systikDivider == 1)
    {
        ledColor_t[functionCall]();
        if(++functionCall == NUM_FUNCTIONS)
        {
            functionCall = 0;
        }
    }

    if(++systikDivider > 1)
    {
        systikDivider = 0;
    }
}

void vMain_BlueOn(void)
{
    vToggle_turnPinHigh(s_blueLED);
    vToggle_turnPinLow(s_redLED);
    vToggle_turnPinLow(s_greenLED);
}

void vMain_GreenOn(void)
{
    vToggle_turnPinHigh(s_greenLED);
    vToggle_turnPinLow(s_redLED);
    vToggle_turnPinLow(s_blueLED);
}

void vMain_RedOn(void)
{
    vToggle_turnPinHigh(s_redLED);
    vToggle_turnPinLow(s_blueLED);
    vToggle_turnPinLow(s_greenLED);
}

void vMain_TurnAllOff(void)
{
    vToggle_turnPinLow(s_redLED);
    vToggle_turnPinLow(s_blueLED);
    vToggle_turnPinLow(s_greenLED);
}

#endif
