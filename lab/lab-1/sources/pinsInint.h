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

void vpinsInit_GPIO(port2Pins_t e_userPin, port2IO_t e_userPortIO, port2GPIOConfig_t e_userGPIO);
static void vPrv_pinsInit_InitIO(port2Pins_t e_userPin, port2IO_t e_userPortIO);
static void vPrv_pinsInit_InitConfig(port2Pins_t e_userPin, port2GPIOConfig_t e_userGPIO);

#endif /* PINSININT_H_ */
