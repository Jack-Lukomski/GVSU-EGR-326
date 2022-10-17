#include "msp.h"
#include "pinsInint.h"
#include "Toggle.h"

port2GPIO_t motor_a;
port2GPIO_t motor_b;
port2GPIO_t motor_ap;
port2GPIO_t motor_bp;

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	vpinsInit_GPIO(&motor_a, pin7, output, pullup, disableInterrupt);
	vpinsInit_GPIO(&motor_b, pin6, output, pullup, disableInterrupt);
	vpinsInit_GPIO(&motor_ap, pin5, output, pullup, disableInterrupt);
	vpinsInit_GPIO(&motor_bp, pin4, output, pullup, disableInterrupt);


	while(1)
	{
	    vToggle_turnPinHigh(motor_a);
	    vToggle_turnPinHigh(motor_b);
	    vToggle_turnPinLow(motor_ap);
	    vToggle_turnPinLow(motor_bp);
	    __delay_cycles(30000);
        vToggle_turnPinHigh(motor_b);
        vToggle_turnPinHigh(motor_ap);
        vToggle_turnPinLow(motor_a);
        vToggle_turnPinLow(motor_bp);
        __delay_cycles(30000);
        vToggle_turnPinHigh(motor_ap);
        vToggle_turnPinHigh(motor_bp);
        vToggle_turnPinLow(motor_a);
        vToggle_turnPinLow(motor_b);
        __delay_cycles(30000);
        vToggle_turnPinHigh(motor_a);
        vToggle_turnPinHigh(motor_bp);
        vToggle_turnPinLow(motor_ap);
        vToggle_turnPinLow(motor_b);
        __delay_cycles(30000);
	}
}
