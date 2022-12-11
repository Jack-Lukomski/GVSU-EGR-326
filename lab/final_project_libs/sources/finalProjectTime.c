#include "finalProjectTime.h"
/*
 * finalProjectTime.c
 *
 *  Created on: Dec 2, 2022
 *      Author: jtluk
 */

uint8_t hexToDecRangeTable[5][2] =
{
 {15, 26},
 {31, 42},
 {47, 58},
 {63, 74},
 {79, 90},
};

uint8_t test = 0;

void vfinalPrjTime_Initlize()
{
    vSPI_Initlize();
    vI2C_Initlize();

    // Initlize Routiene for 7-Segment
    vSPI_writeByte(0x9, 0xFF);
    __delay_cycles(30000);
    vSPI_writeByte(0xA, 0x7);
    __delay_cycles(30000);
    vSPI_writeByte(0xB, 0x7);
    __delay_cycles(30000);
    vSPI_writeByte(0xC, 0x1);
    __delay_cycles(30000);

    vfinalPrjTime_ClearSegment();
}

void vfinalPrjTime_setMDYdate(uint8_t userMonth, uint8_t userDay, uint8_t userYear)
{
    xI2C_Write(RTC_SLAVE_ADDRESS, MONTH_ADDRESS, userMonth);
    xI2C_Write(RTC_SLAVE_ADDRESS, DAYS_ADDRESS, userDay);
    xI2C_Write(RTC_SLAVE_ADDRESS, YEAR_ADDRESS, userYear);
}

void vfinalPrjTime_getMDYdate(uint8_t MDY_ptr[3])
{
    uint8_t I2C_recieveByte;

    xI2C_Read(RTC_SLAVE_ADDRESS, MONTH_ADDRESS, &I2C_recieveByte);
    test = I2C_recieveByte;
    MDY_ptr[0] = I2C_recieveByte;
    xI2C_Read(RTC_SLAVE_ADDRESS, DAYS_ADDRESS, &I2C_recieveByte);
    MDY_ptr[1] = I2C_recieveByte;
    xI2C_Read(RTC_SLAVE_ADDRESS, YEAR_ADDRESS, &I2C_recieveByte);
    MDY_ptr[2] = I2C_recieveByte;
}

void vfinalPrjTime_setSevenSegTime(uint8_t userHour, uint8_t userMin, uint8_t userSecond)
{
    xI2C_Write(RTC_SLAVE_ADDRESS, HOURS_ADDRESS, userHour);
    xI2C_Write(RTC_SLAVE_ADDRESS, MINUETS_ADDRESS, userMin);
    xI2C_Write(RTC_SLAVE_ADDRESS, SECONDS_ADDRESS, userSecond);

    vfinalPrjTime_writeTime(userHour, 0x8);
    vfinalPrjTime_writeTime(userMin, 0x5);
    vfinalPrjTime_writeTime(userSecond, 0x2);
}

static void vfinalPrjTime_writeTime(uint8_t timeValue, uint8_t segmentStartValue)
{
    uint8_t tensDigit;
    uint8_t onesDigit;

    if(timeValue < 10)
    {
        vSPI_writeByte(segmentStartValue-1, timeValue);
        vSPI_writeByte(segmentStartValue, 0);
    }
    else
    {
        tensDigit = timeValue / 10;
        onesDigit = timeValue - (tensDigit*10);
        vSPI_writeByte(segmentStartValue, tensDigit);
        vSPI_writeByte(segmentStartValue-1, onesDigit);
    }
}

static void vfinalPrjTime_ClearSegment()
{
    uint8_t registerSegment;
    for(registerSegment = 1; registerSegment < 9; registerSegment++)
    {
        vSPI_writeByte(registerSegment, 0x0);
        __delay_cycles(30000);
    }
    vSPI_writeByte(0x3, 0b1111111);
    vSPI_writeByte(0x6, 0b1111111);
}

void vfinalPrjTime_UpdateSegmentTime()
{
    uint8_t hour, min, sec;

    xI2C_Read(RTC_SLAVE_ADDRESS, HOURS_ADDRESS, &hour);
    xI2C_Read(RTC_SLAVE_ADDRESS, MINUETS_ADDRESS, &min);
    xI2C_Read(RTC_SLAVE_ADDRESS, SECONDS_ADDRESS, &sec);

    test = hour;

    hour = xfinalPrjTime_HexToDec(hour);
    min = xfinalPrjTime_HexToDec(min);
    sec = xfinalPrjTime_HexToDec(sec);

    vfinalPrjTime_writeTime(hour, 0x8);
    vfinalPrjTime_writeTime(min, 0x5);
    vfinalPrjTime_writeTime(sec, 0x2);
}

static uint8_t xfinalPrjTime_HexToDec(uint8_t hexValue)
{
    uint8_t convertedNumRetVal = hexValue;

    if(hexValue > 15 && hexValue < 26)
    {
        convertedNumRetVal = convertedNumRetVal - 6;
    }
    if(hexValue > 31 && hexValue < 42)
    {
        convertedNumRetVal = convertedNumRetVal - 12;
    }
    if(hexValue > 47 && hexValue < 58)
    {
        convertedNumRetVal = convertedNumRetVal - 18;
    }
    if(hexValue > 63 && hexValue < 74)
    {
        convertedNumRetVal = convertedNumRetVal - 24;
    }
    if(hexValue > 79 && hexValue < 90)
    {
        convertedNumRetVal = convertedNumRetVal - 30;
    }

    return convertedNumRetVal;
}
