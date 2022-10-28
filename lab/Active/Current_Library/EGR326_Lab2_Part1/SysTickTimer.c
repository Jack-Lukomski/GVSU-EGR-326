#include "SysTickTimer.h"

#include "msp.h"

//int intervalCnt=0;

void SysTickTimer(int delay){
    SysTick -> LOAD = ((delay*3000)-1);
    SysTick -> VAL =0;
    while((SysTick -> CTRL & 0x00010000)==0);
}

void SysTick_init (void)
{
    SysTick -> CTRL    = 0;                       // disable SysTick during step
    SysTick -> LOAD    = 0x00FFFFFF;              // max reload value
    SysTick -> VAL     = 0;                       // any write to current clears it
    SysTick -> CTRL    = 0x05;                    // enable SysTick, 3MHz, No Interrupts
}

void SysTick_init_interrupt (void)
{
    SysTick -> CTRL    = 0;                       // disable SysTick during step
    SysTick -> LOAD    = 1500000;                 // load value for 0.5 s increments for 3Mhz
    SysTick -> VAL     = 0;                       // any write to current clears it
    SysTick -> CTRL    = 0x07;                    // enable SysTick, 3MHz, With Interrupt
}

void SysTick_Handler (void)
{
  intervalCnt++;       // increment interval timer by 1ms, reset in main ( )
  timeout = 1 ;             // set flag for timeout of SysTick, reset in main
}
