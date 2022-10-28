/*******************************************************************************
* Name:             Samuel DeJong
* Course:           EGR 326 - Microcontroller Programming and Applications Lab
* Project:          Lab 01 - Digital Inputs and Outputs � Interfacing Switches
*                            and LEDs to the MSP432
* File:             debounce.c
* Description:      The function in this library will debounce a switch
********************************************************************************/
//#include <SysTickTimer.h>
#include "msp.h"
#include "stdint.h"
#include "debounce.h"

uint8_t debounce_sw1_press_os(time){
    static uint16_t check=0;            //16 bit integer for checking debounce
//    time = time/11;                     //time will be delayed 11 times

    /** check shifted left one, reads in P1.1, moves reading to least significant
       and sets check's last 4 bits to 1, if 0 is not read in for 11 consecutive
       reads of switch 1, it will not return true. **/
    check = (check<<1)|(P4->IN & BIT4)>>4 | 0xf000;
//    SysTickTimer(time);
    if (check == 0xf800){               //check if switch remained pressed
        return 1;                       //return true if remained pressed
    }
    return 0;                           //if any bounce return 0
}

uint8_t debounce_sw2_press_os(time){
    static uint16_t check=0;            //16 bit integer for checking debounce
//    time = time/11;                     //time will be delayed 11 times

    /** check shifted left one, reads in P1.1, moves reading to least significant
       and sets check's last 4 bits to 1, if 0 is not read in for 11 consecutive
       reads of switch 1, it will not return true. **/
    check = (check<<1)|(P4->IN & BIT5)>>5 | 0xf000;
//    SysTickTimer(time);
    if (check == 0xf800){               //check if switch remained pressed
        return 1;                       //return true if remained pressed

    }
    return 0;                           //if any bounce return 0
}

uint8_t debounce_sw1_press(void){
    static uint16_t check=0;            //16 bit integer for checking debounce
//    time = time/11;                     //time will be delayed 11 times

    /** check shifted left one, reads in P1.1, moves reading to least significant
       and sets check's last 5 bits to 1, if 0 is not read in for 11 consecutive
       reads of switch 1, it will not return true. **/
    check = (check<<1)|(P4->IN & BIT4)>>4 | 0xf800;
    __delay_cycles(6000);               //delay for 2 ms
    if (check == 0xf800){               //check if switch remained pressed
        return 1;                       //return true if remained pressed
    }
    return 0;                           //if any bounce return 0
}

uint8_t debounce_sw2_press(void){
    static uint16_t check=0;            //16 bit integer for checking debounce
//    time = time/11;                     //time will be delayed 11 times

    /** check shifted left one, reads in P1.1, moves reading to least significant
       and sets check's last 5 bits to 1, if 0 is not read in for 11 consecutive
       reads of switch 1, it will not return true. **/
    check = (check<<1)|(P4->IN & BIT5)>>5 | 0xf800;
    __delay_cycles(6000);               //delay for 2 ms
    if (check == 0xf800){               //check if switch remained pressed
        return 1;                       //return true if remained pressed

    }
    return 0;                           //if any bounce return 0
}

uint8_t release_sw2(void){
        if(P4->IN & BIT5){              //read switch 1
            __delay_cycles(15000);               //delay for 2 ms
                if(P4->IN & BIT5){      //read switch 1
                    return 1;           //if both true, return true
                }
        }
        return 0;
}

