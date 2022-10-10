#include <stdio.h>
#include "msp.h"
#include "pinsInint.h"
#include "I2C.h"
#include "Read_Keypad.h"

uint8_t recieveData;
uint8_t currDate[7];
uint16_t currTemp;
double TempCelc;
int tempInt;
int tempDec;
char prevKey;


void main(void)
{
    int i;
    int pressed;
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
//    unsigned char timeDateWrite[7]={0x00, 0x00, 0x15, 0x02, 0x0A, 0x0A, 0x22};
    SysTickInit();
    keypad_initialize();
	__delay_cycles(300000);
	vI2C_Initlize();
    __delay_cycles(300000);
//    for (i=0; i<7; i++){
//        xI2C_Write(0x68, i, timeDateWrite[i]);
//        __delay_cycles(300000);
//    }

	while(1)
	{
	    xI2C_Read(0x68, 0x11, &recieveData);
	    __delay_cycles(300000);
	    tempInt = recieveData;
	    xI2C_Read(0x68, 0x12, &recieveData);
	    tempDec = (recieveData>>6);
	    TempCelc = (tempDec * 0.25) + tempInt;

        for (i=0; i<7; i++){
            xI2C_Read(0x68, i, &recieveData);
            __delay_cycles(300000);
            currDate[i] = recieveData;
        }

        pressed = Read_Keypad();                    //check if key is entered
        if(pressed){
            prevKey = key;
            while (prevKey == 58){
                while(!Read_Keypad());
                if(pressed){
                    if(key == 49){
                        for (i=4; i<7; i++){
                            printf("%x\n", currDate[i]);
                         }
                        prevKey = 0;
                        printf("\n");
                    }
                    else if(key == 50){
                        for (i=2; i>=0; i--){
                            printf("%x\n", currDate[i]);
                         }
                        prevKey = 0;
                        printf("\n");
                    }
                    else if(key == 51){
                        printf("%f\n", TempCelc);
                        prevKey = 0;
                        printf("\n");
                    }
                    else
                        prevKey = 0;
                }
            }
        }
        SysTickTimer(10);                           //wait 10 ms before reading again
	}
}
