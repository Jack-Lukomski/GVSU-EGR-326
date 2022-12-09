#include "finalProjectMenu.h"
/*
 * finalProjectMenu.c
 *
 *  Created on: Nov 30, 2022
 *      Author: jtluk
 */

uint8_t month, day, year;

static const uint8_t decimalToHex_t[60] =
{
 0x00, 0x01, 0x02, 0x03, 0x4, 0x05, 0x06,
 0x07, 0x08, 0x09, 0x10, 0x11, 0x12, 0x13,
 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x20,
 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
 0x28, 0x29, 0x30, 0x31, 0x32, 0x33, 0x34,
 0x35, 0x36, 0x37, 0x38, 0x39, 0x40, 0x41,
 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
 0x49, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55,
 0x56, 0x57, 0x58, 0x59
};

static const vMenu_menuOption_ptr openMenuSelect_t[4] =
{
 vMenu_OpenQuitMenu,
 vMenu_OpenSetTimeMenu,
 vMenu_OpenSetDateMenu,
 vMenu_OpenPlayNoteMenu,
};

static const vMenu_menuStateMachiene_ptr LCD_StateM_t[3] =
{
 vMenu_MainScreen,
 vMenu_FillOptionMenu,
};

bool tempMenuFlag = false; // Remove
uint8_t currEncoderVal = 0;
uint8_t prevEncoderVal = 0;

uint8_t menuSelectState = 0;
e_menuTransistionStates menuDisplayState = mainScreen;
uint8_t optionMenuArrowPosition[4] = {20, 33, 46, 59};



void vMenu_UpdateScreen(encoder_t * s_encoderData)
{
    if(s_encoderData->b_buttonStatus && menuDisplayState == mainScreen)
    {
        menuDisplayState = menuSelectScreen;
        LCD_StateM_t[menuDisplayState](s_encoderData);
        s_encoderData->b_buttonStatus = false;
    }

    if(menuDisplayState == menuSelectScreen)
    {
        vMenu_UpdateOptionMenu(s_encoderData);
    }

    if(s_encoderData->b_buttonStatus && menuDisplayState == selectedMenuItem)
    {
        s_encoderData->b_buttonStatus = false;
        __delay_cycles(300000);
        openMenuSelect_t[menuSelectState](s_encoderData);
        s_encoderData->b_buttonStatus = false;
        menuDisplayState = mainScreen;
    }
}

void vMenu_Init(void)
{
    vClk_Initlize48MHz();
    ST7735_InitR(INITR_REDTAB);
    vMenu_MainScreen(NULL);
}

void vMenu_MainScreen(encoder_t * s_encoderData)
{
    uint8_t offSet = 25;
//
//    vI2C_Initlize();
//    xI2C_Read(RTC_SLAVE_ADDRESS, MONTH_ADDRESS, &month);
//    xI2C_Read(RTC_SLAVE_ADDRESS, DAYS_ADDRESS, &day);
//    xI2C_Read(RTC_SLAVE_ADDRESS, YEAR_ADDRESS, &year);
//    vI2C_Initlize();
//
//    month--;
//    day--;
//    year--;

    ST7735_FillScreen(0x0000);
    vMenu_DrawString(0, 2, 0x0000, 0xFFFF, "   Sound Generator   ", 1);

    if(month < 10)
    {
        ST7735_DrawChar(0+offSet, 140, '0', 0xFFFF, 0x0000, 1);
        ST7735_DrawChar(8+offSet, 140, month + 48, 0xFFFF, 0x0000, 1);
    }
    else
    {
        ST7735_DrawChar(0+offSet, 140, month/10 + 48, 0xFFFF, 0x0000, 1);
        ST7735_DrawChar(8+offSet, 140, month - ((month/10)*10) + 48, 0xFFFF, 0x0000, 1);
    }

    ST7735_DrawChar(16+offSet, 140, '/', 0xFFFF, 0x0000, 1);

    if(day < 10)
    {
        ST7735_DrawChar(24+offSet, 140, '0', 0xFFFF, 0x0000, 1);
        ST7735_DrawChar(32+offSet, 140, day + 48, 0xFFFF, 0x0000, 1);
    }
    else
    {
        ST7735_DrawChar(24+offSet, 140, day/10 + 48, 0xFFFF, 0x0000, 1);
        ST7735_DrawChar(32+offSet, 140, day - ((day/10)*10) + 48, 0xFFFF, 0x0000, 1);
    }

    ST7735_DrawChar(40+offSet, 140, '/', 0xFFFF, 0x0000, 1);

    ST7735_DrawChar(48+offSet, 140, '2', 0xFFFF, 0x0000, 1);
    ST7735_DrawChar(56+offSet, 140, '0', 0xFFFF, 0x0000, 1);
    ST7735_DrawChar(64+offSet, 140, year/10 + 48, 0xFFFF, 0x0000, 1);
    ST7735_DrawChar(72+offSet, 140, year - ((year/10)*10) + 48, 0xFFFF, 0x0000, 1);
}

void vMenu_FillOptionMenu(encoder_t * s_encoderData)
{
    ST7735_FillScreen(ST7735_Color565(198, 237, 175));
    vMenu_DrawString(0, 2, 0x0000, ST7735_Color565(198, 237, 175), "   Function Select   ", 1);
    ST7735_DrawFastHLine(0, 15, 128, 0x0000);
    vMenu_DrawString(0, 20, 0x0000, ST7735_Color565(198, 237, 175), "     1. Set Time    ", 1);
    vMenu_DrawString(0, 33, 0x0000, ST7735_Color565(198, 237, 175), "    2. Set Date  ", 1);
    vMenu_DrawString(0, 46, 0x0000, ST7735_Color565(198, 237, 175), "    3. Play Note    ", 1);
    vMenu_DrawString(0, 59, 0x0000, ST7735_Color565(198, 237, 175), "      4. Quit       ", 1);
}

void vMenu_UpdateOptionMenu(encoder_t * s_encoderData)
{
    while(!(s_encoderData->b_buttonStatus))
    {
        currEncoderVal = s_encoderData->encoderVal;
        if(currEncoderVal != prevEncoderVal)
        {
            if(menuSelectState == 0)
            {
                vMenu_moveSelectionArrow(optionMenuArrowPosition[menuSelectState], optionMenuArrowPosition[3]);
            }
            else
            {
                vMenu_moveSelectionArrow(optionMenuArrowPosition[menuSelectState], optionMenuArrowPosition[menuSelectState-1]);
            }

            if(++menuSelectState > 3)
            {
                 menuSelectState = 0;
            }
        }
        prevEncoderVal = currEncoderVal;
    }
    menuDisplayState = selectedMenuItem;
}


static void vMenu_DrawString(int x, int y, int textColor, int colorBg, char * string, int fontSize)
{
    int numChar;
    int charOffSet = 0;
    for(numChar = 0; numChar < strlen(string); numChar++)
    {
        ST7735_DrawChar(x + charOffSet, y, string[numChar], textColor, colorBg, fontSize);
        charOffSet += 6*fontSize;
    }
}

static void vMenu_moveSelectionArrow(uint8_t nextArrowPositionY, uint8_t prevArrowPositionY)
{
    if(prevArrowPositionY == 255)
    {
        prevArrowPositionY = 59;
    }
    vMenu_DrawString(6, prevArrowPositionY, 0x0000, ST7735_Color565(198, 237, 175), "  ", 1);
    vMenu_DrawString(6, nextArrowPositionY, 0x0000, ST7735_Color565(198, 237, 175), "->", 1);
}

static void vMenu_OpenSetTimeMenu(encoder_t * s_encoderData)
{

    uint8_t userSetHours = xMenu_SetHoursSubMenu(s_encoderData);
    uint8_t userSetMin = xMenu_SetMinSubMenu(s_encoderData);
    uint8_t userSetSec = xMenu_SetSecSubMenu(s_encoderData);

    vfinalPrjTime_Initlize();
    vfinalPrjTime_setSevenSegTime(decimalToHex_t[userSetHours-1], decimalToHex_t[userSetMin-1], decimalToHex_t[userSetSec-1]);
    vSysTick_IntteruptInit(5000);
}

static void vMenu_OpenSetDateMenu(encoder_t * s_encoderData)
{
    uint8_t userSetMonth = xMenu_SetMonthSubMenu(s_encoderData);
    uint8_t userSetDay = xMenu_SetDaySubMenu(s_encoderData);
    uint8_t userSetYear = xMenu_SetYearSubMenu(s_encoderData);
    vfinalPrjTime_Initlize();
    vfinalPrjTime_setMDYdate(userSetMonth, userSetDay, userSetYear);
    vSysTick_IntteruptInit(5000);

    vMenu_MainScreen(s_encoderData);
}

static void vMenu_OpenPlayNoteMenu(encoder_t * s_encoderData)
{
    int x;
}

static void vMenu_OpenQuitMenu(encoder_t * s_encoderData)
{
    vMenu_MainScreen(NULL);
    menuDisplayState = mainScreen;
    s_encoderData->b_buttonStatus = false;
}

static uint8_t xMenu_SetHoursSubMenu(encoder_t * s_encoderData)
{
    uint8_t userSetHours = 0;

    ST7735_FillScreen(0x0000);
    vMenu_DrawString(0, 2, 0x0000, 0xFFFF, "      Set Time       ", 1);
    vMenu_DrawString(0, 20, 0x0FF0, 0x0000, "   Hour   ", 2);
    s_encoderData->b_buttonStatus = false;

    while(!(s_encoderData->b_buttonStatus))
    {
        currEncoderVal = s_encoderData->encoderVal;
        if(currEncoderVal != prevEncoderVal)
        {
            if(userSetHours < 10)
            {
                ST7735_DrawChar(64, 48, userSetHours + 48, 0xFFFF, 0x0000, 4);
            }
            else if(userSetHours >= 10)
            {
                ST7735_DrawChar(48, 48, (userSetHours/10) + 48, 0xFFFF, 0x0000, 4);
                ST7735_DrawChar(48+24, 48, (userSetHours-(userSetHours/10)*10) + 48, 0xFFFF, 0x0000, 4);
            }

            if(++userSetHours > 24)
            {
                userSetHours = 0;
                ST7735_DrawChar(48, 48, ' ', 0xFFFF, 0x0000, 4);
                ST7735_DrawChar(48+24, 48, ' ', 0xFFFF, 0x0000, 4);
            }
        }
        prevEncoderVal = currEncoderVal;
    }
    return userSetHours;
}

static uint8_t xMenu_SetMinSubMenu(encoder_t * s_encoderData)
{
    uint8_t userSetMin = 0;

    ST7735_FillScreen(0x0000);
    vMenu_DrawString(0, 2, 0x0000, 0xFFFF, "      Set Time       ", 1);
    vMenu_DrawString(0, 20, 0x0FF0, 0x0000, "          ", 2);
    vMenu_DrawString(0, 20, 0x0FF0, 0x0000, " Minutes  ", 2);
    s_encoderData->b_buttonStatus = false;

    while(!(s_encoderData->b_buttonStatus))
    {
        currEncoderVal = s_encoderData->encoderVal;
        if(currEncoderVal != prevEncoderVal)
        {
            if(userSetMin < 10)
            {
                ST7735_DrawChar(64, 48, userSetMin + 48, 0xFFFF, 0x0000, 4);
            }
            else if(userSetMin >= 10)
            {
                ST7735_DrawChar(48, 48, (userSetMin/10) + 48, 0xFFFF, 0x0000, 4);
                ST7735_DrawChar(48+24, 48, (userSetMin-(userSetMin/10)*10) + 48, 0xFFFF, 0x0000, 4);
            }

            if(++userSetMin > 60)
            {
                userSetMin = 0;
                ST7735_DrawChar(48, 48, ' ', 0xFFFF, 0x0000, 4);
                ST7735_DrawChar(48+24, 48, ' ', 0xFFFF, 0x0000, 4);
            }
        }
        prevEncoderVal = currEncoderVal;
    }
    return userSetMin;
}

static uint8_t xMenu_SetSecSubMenu(encoder_t * s_encoderData)
{
    uint8_t userSetSec = 0;

    ST7735_FillScreen(0x0000);
    vMenu_DrawString(0, 2, 0x0000, 0xFFFF, "      Set Time       ", 1);
    vMenu_DrawString(0, 20, 0x0FF0, 0x0000, "          ", 2);
    vMenu_DrawString(0, 20, 0x0FF0, 0x0000, " Seconds  ", 2);
    s_encoderData->b_buttonStatus = false;

    while(!(s_encoderData->b_buttonStatus))
    {
        currEncoderVal = s_encoderData->encoderVal;
        if(currEncoderVal != prevEncoderVal)
        {
            if(userSetSec < 10)
            {
                ST7735_DrawChar(64, 48, userSetSec + 48, 0xFFFF, 0x0000, 4);
            }
            else if(userSetSec >= 10)
            {
                ST7735_DrawChar(48, 48, (userSetSec/10) + 48, 0xFFFF, 0x0000, 4);
                ST7735_DrawChar(48+24, 48, (userSetSec-(userSetSec/10)*10) + 48, 0xFFFF, 0x0000, 4);
            }

            if(++userSetSec > 60)
            {
                userSetSec = 0;
                ST7735_DrawChar(48, 48, ' ', 0xFFFF, 0x0000, 4);
                ST7735_DrawChar(48+24, 48, ' ', 0xFFFF, 0x0000, 4);
            }
        }
        prevEncoderVal = currEncoderVal;
    }
    vMenu_MainScreen(s_encoderData);
    menuDisplayState = mainScreen;
    return userSetSec;
}

static uint8_t xMenu_SetMonthSubMenu(encoder_t * s_encoderData)
{
    uint8_t userSetMonth = 0;

    ST7735_FillScreen(0x0000);
    vMenu_DrawString(0, 2, 0x0000, 0xFFFF, "      Set Date       ", 1);
    vMenu_DrawString(0, 20, 0x0FF0, 0x0000, "   Month   ", 2);
    s_encoderData->b_buttonStatus = false;

    while(!(s_encoderData->b_buttonStatus))
    {
        currEncoderVal = s_encoderData->encoderVal;
        if(currEncoderVal != prevEncoderVal)
        {
            if(userSetMonth < 10)
            {
                ST7735_DrawChar(64, 48, userSetMonth + 48, 0xFFFF, 0x0000, 4);
            }
            else if(userSetMonth >= 10)
            {
                ST7735_DrawChar(48, 48, (userSetMonth/10) + 48, 0xFFFF, 0x0000, 4);
                ST7735_DrawChar(48+24, 48, (userSetMonth-(userSetMonth/10)*10) + 48, 0xFFFF, 0x0000, 4);
            }

            if(++userSetMonth > 13)
            {
                userSetMonth = 0;
                ST7735_DrawChar(48, 48, ' ', 0xFFFF, 0x0000, 4);
                ST7735_DrawChar(48+24, 48, ' ', 0xFFFF, 0x0000, 4);
            }
        }
        prevEncoderVal = currEncoderVal;
    }
    month = userSetMonth-1;
    return userSetMonth;
}

static uint8_t xMenu_SetDaySubMenu(encoder_t * s_encoderData)
{
    uint8_t userSetDay = 0;

    ST7735_FillScreen(0x0000);
    vMenu_DrawString(0, 2, 0x0000, 0xFFFF, "      Set Date       ", 1);
    vMenu_DrawString(0, 20, 0x0FF0, 0x0000, "          ", 2);
    vMenu_DrawString(0, 20, 0x0FF0, 0x0000, "   Day    ", 2);
    s_encoderData->b_buttonStatus = false;

    while(!(s_encoderData->b_buttonStatus))
    {
        currEncoderVal = s_encoderData->encoderVal;
        if(currEncoderVal != prevEncoderVal)
        {
            if(userSetDay < 10)
            {
                ST7735_DrawChar(64, 48, userSetDay + 48, 0xFFFF, 0x0000, 4);
            }
            else if(userSetDay >= 10)
            {
                ST7735_DrawChar(48, 48, (userSetDay/10) + 48, 0xFFFF, 0x0000, 4);
                ST7735_DrawChar(48+24, 48, (userSetDay-(userSetDay/10)*10) + 48, 0xFFFF, 0x0000, 4);
            }

            if(++userSetDay > 32)
            {
                userSetDay = 0;
                ST7735_DrawChar(48, 48, ' ', 0xFFFF, 0x0000, 4);
                ST7735_DrawChar(48+24, 48, ' ', 0xFFFF, 0x0000, 4);
            }
        }
        prevEncoderVal = currEncoderVal;
    }
    day = userSetDay-1;
    return userSetDay;
}

static uint8_t xMenu_SetYearSubMenu(encoder_t * s_encoderData)
{
    uint8_t userSetYear = 0;

    ST7735_FillScreen(0x0000);
    vMenu_DrawString(0, 2, 0x0000, 0xFFFF, "      Set Date       ", 1);
    vMenu_DrawString(0, 20, 0x0FF0, 0x0000, "          ", 2);
    vMenu_DrawString(0, 20, 0x0FF0, 0x0000, "  Year    ", 2);
    s_encoderData->b_buttonStatus = false;

    while(!(s_encoderData->b_buttonStatus))
    {
        currEncoderVal = s_encoderData->encoderVal;
        if(currEncoderVal != prevEncoderVal)
        {
            if(userSetYear < 10)
            {
                ST7735_DrawChar(64, 48, userSetYear + 48, 0xFFFF, 0x0000, 4);
            }
            else if(userSetYear >= 10)
            {
                ST7735_DrawChar(48, 48, (userSetYear/10) + 48, 0xFFFF, 0x0000, 4);
                ST7735_DrawChar(48+24, 48, (userSetYear-(userSetYear/10)*10) + 48, 0xFFFF, 0x0000, 4);
            }

            if(++userSetYear > 100)
            {
                userSetYear = 0;
                ST7735_DrawChar(48, 48, ' ', 0xFFFF, 0x0000, 4);
                ST7735_DrawChar(48+24, 48, ' ', 0xFFFF, 0x0000, 4);
            }
        }
        prevEncoderVal = currEncoderVal;
    }
    year = userSetYear-1;
    vMenu_MainScreen(s_encoderData);
    menuDisplayState = mainScreen;
    return userSetYear;
}
