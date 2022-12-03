/*
 * pinsInint.h
 *
 *  Created on: Sep 2, 2022
 *      Author: jtluk
 */

#ifndef PINSININT_H_
#define PINSININT_H_
#include <stdint.h>
#include "msp.h"

typedef enum port2Pins_t
{
    pin0,
    pin1,
    pin2,
    pin3,
    pin4,
    pin5,
    pin6,
    pin7,
}port2Pins_t;

typedef enum port2IO_t
{
    input,
    output,
}port2IO_t;

typedef enum port2GPIOConfig_t
{
   pullup,
   pulldown,
}port2GPIOConfig_t;

typedef enum port2Inturrupt_t
{
    enableInterrupt,
    disableInterrupt,
}port2Inturrupt_t;

typedef struct port2GPIO_t
{
    port2Pins_t e_IOpinNumber;
    port2IO_t e_IO;
    port2GPIOConfig_t e_GPIOType;
    port2Inturrupt_t e_Interrupt;
}port2GPIO_t;

void vpinsInit_GPIO(port2GPIO_t * s_userGPIO_ptr, port2Pins_t e_userPin, port2IO_t e_userPortIO, port2GPIOConfig_t e_userGPIO, port2Inturrupt_t e_Interrupt);
static void vPrv_pinsInit_InitIO(port2Pins_t e_userPin, port2IO_t e_userPortIO);
static void vPrv_pinsInit_InitConfig(port2Pins_t e_userPin, port2GPIOConfig_t e_userGPIO, port2Inturrupt_t e_Interrupt);

#endif /* PINSININT_H_ */
