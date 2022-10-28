/*
 * SysTick.h
 *
 *  Created on: Feb 11, 2022
 *      Author: samde
 */
volatile int intervalCnt;
volatile int timeout;
//int intervalCnt = 0;
//int timeout = 0;

#ifndef SYSTICKTIMER_H_
#define SYSTICKTIMER_H_



void SysTickTimer(int delay);

void SysTick_init (void);

void SysTick_init_interrupt (void);

#endif /* SYSTICKTIMER_H_ */
