/*******************************************************************************
* Name:             Samuel DeJong
* Course:           EGR 227 - Microcontroller Programming and Applications Lab
* Project:          Lab 04 - Digital Inputs and Outputs – Interfacing Switches
*                            and LEDs to the MSP432
* File:             debounce.c
* Description:      The function in this library will debounce a switch
********************************************************************************/
#include <SysTickTimer.h>
#include "msp.h"
#include "stdint.h"
#include "debounce.h"

uint8_t debounce_press(time){
    static uint16_t check=0;            //16 bit integer for checking debounce
//    time = time/11;                     //time will be delayed 11 times

    /** check shifted left one, reads in P1.1, moves reading to least significant
       and sets check's first 5 bits to 1, if 0 is not read in for 11 consecutive
       reads of switch 1, it will not return true. **/
    check = (check<<1)|(P4->IN & BIT2)>>2 | 0xf800;
    SysTickTimer(time);
    if (check == 0xf800){               //check if switch remained pressed
        return 1;                       //return true if remained pressed
    }
    return 0;                           //if any bounce return 0
}

uint8_t press(time, bit_read){
    while(1){                           //repeat until both if statements true
        if(P4->IN & bit_read){              //read switch 1
            SysTickTimer(time);                //delay function
                if(P4->IN & bit_read){      //read switch 1
                    return 1;           //if both true, return true
                }
        }
    }
}

uint8_t release(time, bit_read){
    while(1){                           //repeat until both if statements true
        if(P4->IN & bit_read){              //read switch 1
            SysTickTimer(time);                //delay function
                if(P4->IN & bit_read){      //read switch 1
                    return 1;           //if both true, return true
                }
        }
    }
}

//uint8_t debounce_release(time){
//    static uint16_t check=0xffff;       //16 bit integer for checking debounce
//    time = time/11;                     //time will be delayed 11 times
//
//    /** check shifted left one, reads in P1.1, moves reading to least significant
//       and sets check's first 5 bits to 0, if 1 is not read in for 11 consecutive
//       reads of switch 1, it will not return true. **/
//    check = ((check<<1)|((P4->IN & BIT2)>>2)) & 0x07ff;
//    SysTickTimer(time);
//    if (check == 0x07ff){               //check if switch remained pressed
//        return 1;                       //return true if remained pressed
//    }
//    return 0;                           //if any bounce return 0
//}

