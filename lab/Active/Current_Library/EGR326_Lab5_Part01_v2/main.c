/*********************************************************************************
* Name:             Samuel DeJong
* Course:           EGR 326 -
* Project:          Lab 05 -
* File:             EGR326_Lab5_Part1.c
* Description:      Code is adapted from Mazidi and Naimi ARM Series
* ********************************************************************************/

#include <msp.h>
//#include <stdint.h>
#include <stdio.h>
#include "SysTickTimer.h"
#include "Read_Keypad.h"
#include "I2C.h"

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
unsigned char timeDateWrite[7]={0x00, 0x30, 0x16, 0x05, 0x06, 0x0A, 0x22};
unsigned char timeDateRead[7];

uint8_t readData;


void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
//    int pressed;
//    NVIC->ISER[0] = EUSCIB0_IRQn;             // EUSCI_B0 interrupt is enabled in NVIC
//    __enable_irq();                     // All interrupts are enabled

//    int i;
//    SysTickInit();
//    keypad_initialize();
//    i2c_init();
//    i2c_burstWrite(0x68, 0, 7, timeDateWrite);
//    i2c_init();
//    i2c_burstRead(0x68, 0, 7, timeDateRead);

    vI2C_Initlize();
    xI2C_Write(SLAVE_ADDY, 0, 0);
    __delay_cycles(3000);
    for(;;)
    {
        xI2C_Read(SLAVE_ADDY, 0, &readData);
        __delay_cycles(3000);
        printf("%x\n", readData);
    }
//    while(1){
////        pressed = Read_Keypad();                    //check if key is entered
////        if(pressed){
////            print_keys(key);                        //call function to print
////            printf("Press a key \n");
////        }
////        for(i=0; i<7; i++){
////                printf("%x\n", timeDateRead[i]);
////        }
//
////        printf("debug");
////        SysTickTimer(2);                           //wait 10 ms before reading again
//    }
//}
