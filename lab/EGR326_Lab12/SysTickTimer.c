#include "SysTickTimer.h"

#include "msp.h"


void SysTickTimer_ms(int delay){
    SysTick -> LOAD = ((delay*3000)-1);
    SysTick -> VAL =0;
    while((SysTick -> CTRL & 0x00010000)==0);
}

void SysTick_init ()
{
    SysTick -> CTRL    = 0;                             // disable SysTick during step
    SysTick -> LOAD    = 0X00FFFFFF;                    // max reload value
    SysTick -> VAL     = 0;                             // any write to current clears it
    SysTick -> CTRL    = 0x05;                    // enable SysTick, 3MHz, No Interrupts
}
