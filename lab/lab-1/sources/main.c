#include "Toggle.h"
#include "msp.h"
#include "pinsInint.h"
#include "readInputs.h"
#include "pinsInint.h"

#define NUM_STATES 2

port2GPIO_t s_redLed;
port2GPIO_t s_greenLed;
port2GPIO_t s_blueLed;
port2GPIO_t s_pushButton;
/**
 * main.c
 *
 * PIN 2.4 B
 * PIN 2.5 G
 * PIN 2.6 R
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    vpinsInit_GPIO(&s_pushButton, pin7, input, pullup);

	uint8_t currentButtonState = 0;

	while(1)
	{
	    if(xReadInputs_ReadPin(s_pushButton) != false)
	    {
	        if(currentButtonState == 0)
	        {
	            vpinsInit_GPIO(&s_greenLed, pin5, output, pullup);
	            vpinsInit_GPIO(&s_redLed, pin6, output, pullup);
	            vpinsInit_GPIO(&s_blueLed, pin4, output, pullup);


	            vToggle_turnPinLow(s_blueLed);
	            vToggle_turnPinLow(s_greenLed);
	            vToggle_turnPinHigh(s_redLed);
	        }
            if(currentButtonState == 1)
            {
                vToggle_turnPinLow(s_redLed);
                vToggle_turnPinLow(s_blueLed);
                vToggle_turnPinHigh(s_greenLed);
            }
            if(currentButtonState == 2)
            {
                vToggle_turnPinLow(s_greenLed);
                vToggle_turnPinLow(s_redLed);
                vToggle_turnPinHigh(s_blueLed);
            }

	        if(++currentButtonState == 3)
	        {
	            currentButtonState = 1;
	        }
	    }
	}
}
