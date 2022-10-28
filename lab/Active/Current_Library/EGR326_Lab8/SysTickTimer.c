#include <SysTickTimer.h>
#include "msp.h"
#include "stdint.h"

void SysTickTimer(delay){
    SysTick -> LOAD = ((delay*3000)-1);
    SysTick -> VAL =0;
    while((SysTick -> CTRL & 0x00010000)==0);
}

void SysTickInit(void){
    SysTick -> CTRL =0;                 //turn off timer
    SysTick -> LOAD = 0x00ffffff;        //Maximum value of timer
    SysTick -> VAL =0;                  //clear timer
    SysTick -> CTRL = 0x05;             //turn on timer
}
