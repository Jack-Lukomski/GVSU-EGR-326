#include "msp.h"
#include <stdint.h>
#include <stdio.h>

typedef enum GPIO_status_t
{
    status_sucess,
    status_failure,
}GPIO_status_t;

typedef enum GPIO_IO_t
{
    input,
    output,
}GPIO_IO_t;

typedef enum GPIO_portNumber_t
{
    port1,
    port2,
    port3,
    port4,
    port5,
    port6,
    port7,
    port8,
    port9,
    port10,
}GPIO_portNumber_t;

typedef enum GPIO_pinNumber_t
{
    pin1,
    pin2,
    pin3,
    pin4,
    pin5,
    pin6,
    pin7,
    pin8,
    pin9,
    pinA = 0x0400,
    pinB = 0x0800,
    pinC = 0x1000,
    pinD = 0x2000,
    pinE = 0x4000,
    pinF = 0x8000,
}GPIO_pinNumber_t;

typedef struct s_GVSU_GPIO
{
    GPIO_IO_t e_IO;
    GPIO_portNumber_t e_portNumber;
    GPIO_pinNumber_t e_pinNumber;
}s_GVSU_GPIO;

void vGPIO_setPinNumber(s_GVSU_GPIO * s_userGPIO_ptr, GPIO_pinNumber_t e_userPinNumber);
void vGPIO_setPort(s_GVSU_GPIO * s_userGPIO_ptr, GPIO_portNumber_t e_userPortNumber);
void vGPIO_setIO(s_GVSU_GPIO * s_userGPIO_ptr, GPIO_IO_t e_userIOType);
GPIO_status_t xGPIO_InitlizePinGPIO(s_GVSU_GPIO * s_userGPIO_ptr);
static GPIO_status_t xPrv_GPIO_setInput(s_GVSU_GPIO * s_userGPIO_ptr);
static GPIO_status_t xPrv_GPIO_setOutput(s_GVSU_GPIO * s_userGPIO_ptr);
