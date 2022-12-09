/*
 * pinsInit4.h
 *
 *  Created on: Dec 1, 2022
 *      Author: jtluk
 */

#ifndef PINSINIT4_H_
#define PINSINIT4_H_

#include <stdint.h>
#include "msp.h"

typedef enum port4Pins_t
{
    pin4_0,
    pin4_1,
    pin4_2,
    pin4_3,
    pin4_4,
    pin4_5,
    pin4_6,
    pin4_7,
}port4Pins_t;

typedef enum port4IO_t
{
    input4,
    output4,
}port4IO_t;

typedef enum port4GPIOConfig_t
{
   pullup4,
   pulldown4,
}port4GPIOConfig_t;

typedef enum port4Inturrupt_t
{
    enableInterrupt4,
    disableInterrupt4,
}port4Inturrupt_t;

typedef struct port4GPIO_t
{
    port4Pins_t e_IOpinNumber4;
    port4IO_t e_IO4;
    port4GPIOConfig_t e_GPIOType4;
    port4Inturrupt_t e_Interrupt4;
}port4GPIO_t;

void vpinsInit_GPIO4(port4GPIO_t * s_userGPIO_ptr, port4Pins_t e_userPin, port4IO_t e_userPortIO, port4GPIOConfig_t e_userGPIO, port4Inturrupt_t e_Interrupt);
static void vPrv_pinsInit_InitIO4(port4Pins_t e_userPin, port4IO_t e_userPortIO);
static void vPrv_pinsInit_InitConfig4(port4Pins_t e_userPin, port4GPIOConfig_t e_userGPIO, port4Inturrupt_t e_Interrupt);

#endif /* PINSINIT4_H_ */
