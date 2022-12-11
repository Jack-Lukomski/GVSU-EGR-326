#include <stdio.h>
#include "msp.h"
#include "pinsInint.h"
#include "I2C.h"
#include "keypad.h"
#include "systick.h"
#define PART3 1


uint8_t recieveData;
uint8_t recieveDataCount = 0;

uint16_t hour, sec, min, day, month, year, temp;
float tempdec;
float tempcel;

#define NUM_STATES 6

void vMain_SetHour(void);
void vMain_SetMin(void);
void vMain_SetSecond(void);
void vMain_SetDay(void);
void vMain_SetMonth(void);
void vMain_SetYear(void);

typedef void(*vMain_SetRTC_ptr)(void);

uint8_t stateCount = 0;

#if !PART3
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	vI2C_Initlize();
	vkeypad_Initialize();
	vSysTick_Init();

	printf("Please enter the time and date in the following format: HH:MM:SS and MM:DD:YYYY\n");

	printf("Enter the hour\n");
	vMain_SetHour();
	printf("Enter the min\n");
	vMain_SetMin();
	printf("Enter the sec\n");
	vMain_SetSecond();
	printf("Enter the month\n");
    vMain_SetMonth();
    printf("Enter the day\n");
	vMain_SetDay();
	printf("Enter the year\n");
	vMain_SetYear();

	for(;;)
	{
	        xI2C_Read(SLAVE_ADDRESS, SECONDS_ADDRESS, &recieveData);
	        sec = recieveData;
	        vSysTick_mSecDelay(10);
            xI2C_Read(SLAVE_ADDRESS, MINUETS_ADDRESS, &recieveData);
            min = recieveData;
            vSysTick_mSecDelay(10);
            xI2C_Read(SLAVE_ADDRESS, HOURS_ADDRESS, &recieveData);
            hour = recieveData;
            vSysTick_mSecDelay(10);
            xI2C_Read(SLAVE_ADDRESS, DATE_ADDRESS, &recieveData);
            day = recieveData;
            vSysTick_mSecDelay(10);
            xI2C_Read(SLAVE_ADDRESS, MONTH_ADDRESS, &recieveData);
            month = recieveData;
            vSysTick_mSecDelay(10);
            xI2C_Read(SLAVE_ADDRESS, YEAR_ADDRESS, &recieveData);
            year = recieveData;
            vSysTick_mSecDelay(10);
            xI2C_Read(SLAVE_ADDRESS, TEMPATURE_ADDRESS, &recieveData);
            tempdec = (recieveData>>6);
            vSysTick_mSecDelay(10);
            xI2C_Read(SLAVE_ADDRESS, 0x12, &recieveData);
            temp = recieveData;
            tempcel = (tempdec * .25) + temp;
            vSysTick_mSecDelay(10);
        printf("TIME: %x : %x : %x\nDATE: %x : %x : 20%d\n\n\n\n", hour, min, sec, month, day, year);
        recieveDataCount = 0;
	}
}

void vMain_SetMin(void)
{
    uint8_t isTwoNumbersEntered = 0;
    char userEnteredValue = 0;
    while(isTwoNumbersEntered < 2)
    {
        if(isTwoNumbersEntered == 0 && xkeypad_ReadKeypad())
        {
            userEnteredValue = (keypad_keyPressed - 48) * 10;
            if(keypad_keyPressed == 59)
            {
                userEnteredValue = 0;
            }
            isTwoNumbersEntered++;
        }
        else if(isTwoNumbersEntered == 1 && xkeypad_ReadKeypad())
        {
            if(!(keypad_keyPressed == 59))
            {
                userEnteredValue = userEnteredValue + (keypad_keyPressed - 48);
            }
            isTwoNumbersEntered++;
        }
    }
    printf("The chosen min is %d\n", userEnteredValue);
    xI2C_Write(SLAVE_ADDRESS, MINUETS_ADDRESS, userEnteredValue);
}

void vMain_SetSecond(void)
{
    uint8_t isTwoNumbersEntered = 0;
    char userEnteredValue = 0;
    while(isTwoNumbersEntered < 2)
    {
        if(isTwoNumbersEntered == 0 && xkeypad_ReadKeypad())
        {
            userEnteredValue = (keypad_keyPressed - 48) * 10;
            if(keypad_keyPressed == 59)
            {
                userEnteredValue = 0;
            }
            isTwoNumbersEntered++;
        }
        else if(isTwoNumbersEntered == 1 && xkeypad_ReadKeypad())
        {
            if(!(keypad_keyPressed == 59))
            {
                userEnteredValue = userEnteredValue + (keypad_keyPressed - 48);
            }
            isTwoNumbersEntered++;
        }
    }
    printf("The chosen sec is %d\n", userEnteredValue);
    xI2C_Write(SLAVE_ADDRESS, SECONDS_ADDRESS, userEnteredValue);
}

void vMain_SetHour(void)
{
    uint8_t isTwoNumbersEntered = 0;
    char userEnteredValue = 0;
    while(isTwoNumbersEntered < 2)
    {
        if(isTwoNumbersEntered == 0 && xkeypad_ReadKeypad())
        {
            userEnteredValue = (keypad_keyPressed - 48) * 10;
            if(keypad_keyPressed == 59)
            {
                userEnteredValue = 0;
            }
            isTwoNumbersEntered++;
        }
        else if(isTwoNumbersEntered == 1 && xkeypad_ReadKeypad())
        {
            if(!(keypad_keyPressed == 59))
            {
                userEnteredValue = userEnteredValue + (keypad_keyPressed - 48);
            }
            isTwoNumbersEntered++;
        }
    }
    printf("The chosen hour is %d\n", userEnteredValue);
    xI2C_Write(SLAVE_ADDRESS, HOURS_ADDRESS, userEnteredValue);
}

void vMain_SetDay(void)
{
    uint8_t isTwoNumbersEntered = 0;
    char userEnteredValue = 0;
    while(isTwoNumbersEntered < 2)
    {
        if(isTwoNumbersEntered == 0 && xkeypad_ReadKeypad())
        {
            userEnteredValue = (keypad_keyPressed - 48) * 10;
            if(keypad_keyPressed == 59)
            {
                userEnteredValue = 0;
            }
            isTwoNumbersEntered++;
        }
        else if(isTwoNumbersEntered == 1 && xkeypad_ReadKeypad())
        {
            if(!(keypad_keyPressed == 59))
            {
                userEnteredValue = userEnteredValue + (keypad_keyPressed - 48);
            }
            isTwoNumbersEntered++;
        }
    }
    printf("The chosen day is %d\n", userEnteredValue);
    xI2C_Write(SLAVE_ADDRESS, DAYS_ADDRESS, userEnteredValue);
}
void vMain_SetMonth(void)
{
    uint8_t isTwoNumbersEntered = 0;
    char userEnteredValue = 0;
    while(isTwoNumbersEntered < 2)
    {
        if(isTwoNumbersEntered == 0 && xkeypad_ReadKeypad())
        {
            userEnteredValue = (keypad_keyPressed - 48) * 10;
            if(keypad_keyPressed == 59)
            {
                userEnteredValue = 0;
            }
            isTwoNumbersEntered++;
        }
        else if(isTwoNumbersEntered == 1 && xkeypad_ReadKeypad())
        {
            if(!(keypad_keyPressed == 59))
            {
                userEnteredValue = userEnteredValue + (keypad_keyPressed - 48);
            }
            isTwoNumbersEntered++;
        }
    }
    printf("The chosen month is %d\n", userEnteredValue);
    xI2C_Write(SLAVE_ADDRESS, MONTH_ADDRESS, userEnteredValue);
}

void vMain_SetYear(void)
{
    uint8_t isTwoNumbersEntered = 0;
    uint16_t userEnteredValue = 0;
    while(isTwoNumbersEntered < 2)
    {
        if(isTwoNumbersEntered == 0 && xkeypad_ReadKeypad())
        {
            userEnteredValue = (keypad_keyPressed - 48) * 10;
            isTwoNumbersEntered++;
        }
        else if(isTwoNumbersEntered == 1 && xkeypad_ReadKeypad())
        {
            if(!(keypad_keyPressed == 59))
            {
                userEnteredValue = userEnteredValue + (keypad_keyPressed - 48);
            }
            isTwoNumbersEntered++;
        }
    }
    printf("The chosen year is %d\n", userEnteredValue);
    xI2C_Write(SLAVE_ADDRESS, YEAR_ADDRESS, userEnteredValue);
}
#endif

void vMain_displayMDY(void);
void vMain_displayTime(void);
void vMain_displayTemp(void);

void main (void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

        vI2C_Initlize();
        vkeypad_Initialize();
        vSysTick_Init();
        // SET CURRENT TIME HERE
        xI2C_Write(SLAVE_ADDRESS, SECONDS_ADDRESS, 0x00);
        xI2C_Write(SLAVE_ADDRESS, MINUETS_ADDRESS, 0x45);
        xI2C_Write(SLAVE_ADDRESS, HOURS_ADDRESS, 0x05);
        printf("Press * followed by a 1, 2, or 3\n1) Will display the current day month and year\n2) will display the current hour, min, and second\n3) will display the tempature in celcius\n");

        for(;;)
        {
            if(xkeypad_ReadKeypad() && keypad_keyPressed == 58)
            {
                while(!xkeypad_ReadKeypad())
                {
                    ;
                }
                if(keypad_keyPressed == '1')
                {
                    vMain_displayMDY();
                }
                else if(keypad_keyPressed == '2')
                {
                    vMain_displayTime();
                }
                else if(keypad_keyPressed == '3')
                {
                    vMain_displayTemp();
                }
            }
        }
}

void vMain_displayMDY(void)
{
    xI2C_Write(SLAVE_ADDRESS, MONTH_ADDRESS, 0x10);
    vSysTick_mSecDelay(30);
    xI2C_Read(SLAVE_ADDRESS, MONTH_ADDRESS, &recieveData);
    month = recieveData;
    xI2C_Write(SLAVE_ADDRESS, DAYS_ADDRESS, 0x11);
    vSysTick_mSecDelay(30);
    xI2C_Read(SLAVE_ADDRESS, DAYS_ADDRESS, &recieveData);
    day = recieveData;
    xI2C_Write(SLAVE_ADDRESS, YEAR_ADDRESS, 0x22);
    vSysTick_mSecDelay(30);
    xI2C_Read(SLAVE_ADDRESS, YEAR_ADDRESS, &recieveData);
    year = recieveData;
    printf("The current MDY is: %x/%x/20%x\n", month, day, year);
}

void vMain_displayTime(void)
{
    vSysTick_mSecDelay(30);
    xI2C_Read(SLAVE_ADDRESS, SECONDS_ADDRESS, &recieveData);
    sec = recieveData;
    vSysTick_mSecDelay(30);
    xI2C_Read(SLAVE_ADDRESS, MINUETS_ADDRESS, &recieveData);
    min = recieveData;
    vSysTick_mSecDelay(30);
    xI2C_Read(SLAVE_ADDRESS, HOURS_ADDRESS, &recieveData);
    hour = recieveData;
    printf("The current time is: %x:%x:%x\n", hour, min, sec);
}

void vMain_displayTemp(void)
{
    xI2C_Read(SLAVE_ADDRESS, TEMPATURE_ADDRESS, &recieveData);
    tempdec = (recieveData>>6);
    vSysTick_mSecDelay(10);
    xI2C_Read(SLAVE_ADDRESS, 0x12, &recieveData);
    temp = recieveData;
    tempcel = (tempdec * .25) + temp;
    vSysTick_mSecDelay(10);
    printf("The current tempature is: %f\n", tempcel);
}


