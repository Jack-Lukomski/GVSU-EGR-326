#include <stdio.h>
#include "msp432p401r.h"
#include "msp.h"
#include "Toggle.h"
#include "pinsInint.h"
#include "readInputs.h"
#include "encoder.h"
#include "finalProjectMenu.h"
#include "pinsInit4.h"
#include "HC-SR04.h"
#include "I2C.h"
#include "SPI.h"
#include "finalProjectTime.h"
#include "systick.h"

encoder_t encoder;

static const port4GPIO_t s_encoderTable[3] =
{
 {.e_IO = input4, .e_IOpinNumber = pin4_4, .e_GPIOType = pullup4, .e_Interrupt = enableInterrupt4}, // Button
 {.e_IO = input4, .e_IOpinNumber = pin4_5, .e_GPIOType = pullup4, .e_Interrupt = enableInterrupt4}, // Direction DT
 {.e_IO = input4, .e_IOpinNumber = pin4_6, .e_GPIOType = pullup4, .e_Interrupt = disableInterrupt4}, // Direction CLK
};

void main(void){
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	vEncoder_Init(s_encoderTable);
    vMenu_Init();
    vfinalPrjTime_Initlize();
    vfinalPrjTime_setSevenSegTime(11, 59, 0);
    vfinalPrjTime_setMDYdate(2, 1, 1);
    vSysTick_IntteruptInit(5000);

	NVIC_EnableIRQ(PORT4_IRQn);
	__enable_interrupt();

	while(1)
	{
	    vMenu_UpdateScreen(&encoder);
	}
}

void PORT4_IRQHandler(void)
{
    vEncoder_GetEncoderData(&encoder);
    P4->IFG = 0;
}

void SysTick_Handler(void)
{
    vfinalPrjTime_UpdateSegmentTime();
}