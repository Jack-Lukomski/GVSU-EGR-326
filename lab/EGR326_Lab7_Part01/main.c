#include "msp.h"
#include "GPIO_Interrupt.h"
#include "Read_Keypad.h"
#include "SysTickTimer.h"
#include "stepperMotor.h"


/**
 * main.c
 */

int prevKey;

#define S1 BIT4
#define IN1 BIT4
#define IN2 BIT5
#define IN3 BIT6
#define IN4 BIT7

int complete;
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    SysTickInit();
    keypad_initialize();
    pin_init();
    motorPinInitialize();
    NVIC->ISER[1] = 1<< ((PORT4_IRQn) & 31);
    __enable_interrupt();
    int i;

    for (i=1;i<5;i++)
    {
    motorTurn(4, 6, 5, 7, 10);
    complete++;
    }

    while(1){


//        pressed=Read_Keypad();
//        if(pressed){
//            key = (key-48);
//            STEP_PORT->OUT |= BIT(key);
//            STEP_PORT->OUT &=~ BIT(prevKey);
//            prevKey=key;
//        }
    }

}
