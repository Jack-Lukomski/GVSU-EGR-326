/*********************************************************************************
* Name:             Samuel DeJong
* Course:           EGR 326 -
* Project:          Lab 05 -
* File:             EGR326_Lab5_Part1.c
* Description:      Code is adapted from Mazidi and Naimi ARM Series
* ********************************************************************************/

#include <msp.h>
#include <stdbool.h>
//#include <stdint.h>
#include <stdio.h>
#include "SysTickTimer.h"
#include "Read_Keypad.h"
#include "I2C.h"


#define SLAVE_ADDY 0x68


/**********************************************************************************
 * Pin connections for keypad
 *      MSP432 Pins |   Keypad  |   Function
 *      ---------------------------------------
 *       P4.0       |   7       |   Row 1
 *       P4.1       |   6       |   Row 2
 *       P4.2       |   5       |   Row 3
 *       P4.3       |   4       |   Row 4
 *       --------------------------------------
 *       P4.4       |   3       |   Column 1
 *       P4.5       |   2       |   Column 2
 *       P4.6       |   1       |   Column 3
 **********************************************************************************
 * Pin connections for RTC
 *      MSP432 Pins |   RTC  |   Function
 *      ---------------------------------------
 *       P1.6       |    SDA      |
 *       P1.7       |    SCL      |
 **********************************************************************************/
int success;


uint8_t readData;
uint16_t status;

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    unsigned char timeDateWrite[7]={0x00, 0x30, 0x16, 0x05, 0x06, 0x0A, 0x22};
    unsigned char timeDateRead[7];
    int i;

    SysTickInit();
    keypad_initialize();
    i2c_init();

    for (i=0; i<7; i++){
        I2C_Send2(0x68, i, timeDateWrite[i]);
        __delay_cycles(300000);
    }


    while(1){
        ;
    }
}
