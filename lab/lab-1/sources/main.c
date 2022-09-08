#include "Toggle.h"
#include "msp.h"
#include "pinsInint.h"
#include "readInputs.h"
#include "pinsInint.h"
#include "port3PinsInit.h"
#include "port3ReadInputs.h"

#define NUM_STATES 3
#define PART_TWO 1

/**
 * main.c
 *
 * PIN 2.4 B
 * PIN 2.5 G
 * PIN 2.6 R
 */

port2GPIO_t s_redLed;
port2GPIO_t s_greenLed;
port2GPIO_t s_blueLed;
port2GPIO_t s_fowardPushButton;
port3GPIO_t s_backwardsPushButton;

typedef void(*vMain_LedState_ptr)(void);

void vMain_InitOutputs(void);
void vMain_TurnRedLedOn(void);
void vMain_TurnGreenLedOn(void);
void vMain_TurnBlueLedOn(void);

static const vMain_LedState_ptr ledState_t[NUM_STATES] =
{
 vMain_TurnRedLedOn,
 vMain_TurnGreenLedOn,
 vMain_TurnBlueLedOn,
};

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    vpinsInit_GPIO(&s_fowardPushButton, pin7, input, pullup);

    #if PART_TWO
    vpinsInit_3GPIO(&s_backwardsPushButton, pin32, input3, pullup3);
    #endif

	int8_t currentButtonState = 0;

	while((xReadInputs_ReadPin(s_fowardPushButton) || xReadInputs_3ReadPin(s_backwardsPushButton)) == false); // Waiting to start LED's

	while(1)
	{
	    ledState_t[currentButtonState]();

	    if(xReadInputs_ReadPin(s_fowardPushButton) != false)
	    {
	        currentButtonState = ++currentButtonState % NUM_STATES;
	    }

        #if PART_TWO
	    if(xReadInputs_3ReadPin(s_backwardsPushButton) != false)
	    {
	        if(--currentButtonState < 0)
	        {
	            currentButtonState = 2;
	        }
	    }
        #endif
	}
}

void vMain_InitOutputs(void)
{
    vpinsInit_GPIO(&s_greenLed, pin5, output, pullup);
    vpinsInit_GPIO(&s_redLed, pin6, output, pullup);
    vpinsInit_GPIO(&s_blueLed, pin4, output, pullup);
}

void vMain_TurnRedLedOn(void)
{
    vMain_InitOutputs();
    vToggle_turnPinLow(s_blueLed);
    vToggle_turnPinLow(s_greenLed);
    vToggle_turnPinHigh(s_redLed);
}

void vMain_TurnGreenLedOn(void)
{
    vMain_InitOutputs();
    vToggle_turnPinLow(s_redLed);
    vToggle_turnPinLow(s_blueLed);
    vToggle_turnPinHigh(s_greenLed);
}

void vMain_TurnBlueLedOn(void)
{
    vMain_InitOutputs();
    vToggle_turnPinLow(s_greenLed);
    vToggle_turnPinLow(s_redLed);
    vToggle_turnPinHigh(s_blueLed);
}
