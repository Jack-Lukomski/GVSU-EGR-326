#include "systick.h"
/*
 * systick.c
 *
 *  Created on: Sep 9, 2022
 *      Author: jtluk
 */

void vSysTick_Init(void)
{
    SysTick->CTRL = 0;
    SysTick->LOAD = 0x00FFFFFF;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x5;
}

void vSysTick_mSecDelay(uint16_t msDelayTime)
{
    SysTick->LOAD = ((msDelayTime * 3000 * 16) - 1);
    SysTick->VAL = 0;
    while((SysTick->CTRL & 0x00010000) == 0);
}

void vSysTick_IntteruptInit(uint16_t msDelayTime)
{
    SysTick->CTRL = 0;
    SysTick->LOAD = ((msDelayTime * 3000) - 1);
    SysTick->VAL = 0;
    SysTick->CTRL = 0x00000007;
}
