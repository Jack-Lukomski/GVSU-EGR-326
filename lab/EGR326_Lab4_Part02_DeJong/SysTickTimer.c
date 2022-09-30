#include <SysTickTimer.h>
#include "msp.h"
#include "stdint.h"

void SysTickTimer(delay){
    SysTick -> LOAD = ((delay*3000)-1);
    SysTick -> VAL =0;
    while((SysTick -> CTRL & 0x00010000)==0);
}
