/*
 * port3PinsInit.h
 *
 *  Created on: Sep 7, 2022
 *      Author: jtluk
 */

#ifndef PORT3PINSINIT_H_
#define PORT3PINSINIT_H_

#include <stdint.h>
#include "msp.h"

typedef enum port3Pins_t
{
    pin30,
    pin31,
    pin32,
    pin33,
    pin34,
    pin35,
    pin36,
    pin37,
}port3Pins_t;

typedef enum port3IO_t
{
    input3,
    output3,
}port3IO_t;

typedef enum port3GPIOConfig_t
{
   pullup3,
   pulldown3,
}port3GPIOConfig_t;

typedef struct port3GPIO_t
{
    port3Pins_t e_IOpinNumber;
    port3GPIOConfig_t e_GPIOType;
    port3GPIOConfig_t e_IO;
}port3GPIO_t;

void vpinsInit_3GPIO(port3GPIO_t * s_userGPIO_ptr, port3Pins_t e_userPin, port3IO_t e_userPortIO, port3GPIOConfig_t e_userGPIO);
static void vPrv_pinsInit_3InitIO(port3Pins_t e_userPin, port3IO_t e_userPortIO);
static void vPrv_pinsInit_3InitConfig(port3Pins_t e_userPin, port3GPIOConfig_t e_userGPIO);



#endif /* PORT3PINSINIT_H_ */
