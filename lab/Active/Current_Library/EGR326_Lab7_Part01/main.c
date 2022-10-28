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
int motorTurned=0;

typedef void(*functionptr)(void);

void vMain_spinfowards(void);
void vMain_spinbackwards(void);

static const functionptr state[2] =
{
 vMain_spinfowards,
 vMain_spinbackwards,
};




void main(void){
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    SysTickInit();
    keypad_initialize();
    pin_init();
    motorPinInitialize();
    NVIC->ISER[1] = 1 << ((PORT1_IRQn) & 31);
    __enable_interrupt();
    __enable_irq();



    while(1)
    {
//        motorTurn(4, 6, 5, 7, 10, 20);
        if(pressed)
        {
            state[motorTurned]();
            if(++motorTurned > 1)
            {
                motorTurned = 0;
            }
        }

//        if(pressed && (~done))
//        {
//            motorTurn(4, 6, 5, 7, 10, 4);
//            done=1;
//        }
//        else if(~pressed && (~done))
//        {
//            motorTurn(7, 5, 6, 4, 10, 4);
//            done=1;
//        }
//        else
//        {
//            P5->OUT &=~ 0xf0;
//        }
    }

}

void vMain_spinbackwards(void)
{
    printf("backwards\n");
    motorTurn(7, 5, 6, 4, 10, 4);
}

void vMain_spinfowards(void)
{
    printf("fowards\n");
    motorTurn(4, 6, 5, 7, 10, 4);
}
