#include "msp.h"
#include "stdbool.h"
#include "GPIO_Interrupt.h"
#include "Read_Keypad.h"
#include "SysTickTimer.h"
#include "stepperMotor.h"

#define S1 BIT4
#define IN1 BIT4
#define IN2 BIT5
#define IN3 BIT6
#define IN4 BIT7

int prevKey;
int motorTurned;

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    SysTickInit();
    keypad_initialize();
    pin_init();
    motorPinInitialize();
    NVIC->ISER[1] = 1<< ((PORT6_IRQn) & 31);
    __enable_interrupt();


    while(1)
    {
        while(pressed && (motorTurned<4))
        {
            motorTurn(4, 6, 5, 7, 10);
            motorTurned++;
        }
        while(~pressed && (motorTurned>0))
        {
            motorTurn(7, 5, 6, 4, 10);
            motorTurned--;
        }
    }

}
