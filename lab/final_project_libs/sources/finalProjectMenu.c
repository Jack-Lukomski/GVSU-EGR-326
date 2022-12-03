#include "finalProjectMenu.h"
/*
 * finalProjectMenu.c
 *
 *  Created on: Nov 30, 2022
 *      Author: jtluk
 */
static const vMenu_menuOption_ptr openMenuSelect_t[4] =
{
 vMenu_OpenQuitMenu,
 vMenu_OpenSetTimeMenu,
 vMenu_OpenNotePeriodMenu,
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
    currEncoderVal = s_encoderData->encoderVal;

    if(s_encoderData->b_buttonStatus && menuDisplayState == mainScreen)
    {
        menuDisplayState = menuSelectScreen;
        LCD_StateM_t[menuDisplayState](s_encoderData);
        s_encoderData->b_buttonStatus = false;
    }

    if(currEncoderVal != prevEncoderVal && menuDisplayState == menuSelectScreen)
    {
        vMenu_UpdateOptionMenu(s_encoderData);
    }

    if(s_encoderData->b_buttonStatus && menuDisplayState == selectedMenuItem)
    {
        s_encoderData->b_buttonStatus = false;
        openMenuSelect_t[menuSelectState](s_encoderData);
        menuDisplayState = mainScreen;
    }

    prevEncoderVal = currEncoderVal;
}

void vMenu_Init(void)
{
    vClk_Initlize48MHz();
    ST7735_InitR(INITR_REDTAB);
    vMenu_MainScreen(NULL);
}

void vMenu_MainScreen(encoder_t * s_encoderData)
{
    ST7735_FillScreen(0x0000);
    vMenu_DrawString(0, 2, 0x0000, 0xFFFF, "   Sound Generator   ", 1);
}

void vMenu_FillOptionMenu(encoder_t * s_encoderData)
{
    ST7735_FillScreen(0xFFFF);
    vMenu_DrawString(0, 2, 0x0000, 0xFFFF, "   Function Select   ", 1);
    ST7735_DrawFastHLine(0, 15, 128, 0x0000);
    vMenu_DrawString(0, 20, 0x0000, 0xFFFF, "     1. Set Time    ", 1);
    vMenu_DrawString(0, 33, 0x0000, 0xFFFF, "    2. Note Period  ", 1);
    vMenu_DrawString(0, 46, 0x0000, 0xFFFF, "    3. Play Note    ", 1);
    vMenu_DrawString(0, 59, 0x0000, 0xFFFF, "      4. Quit       ", 1);
}

void vMenu_UpdateOptionMenu(encoder_t * s_encoderData)
{
    while(!(s_encoderData->b_buttonStatus))
    {
        currEncoderVal = s_encoderData->encoderVal;
        if(currEncoderVal != prevEncoderVal)
        {
            if(menuSelectState == 0 && !(s_encoderData->b_buttonStatus))
            {
                vMenu_moveSelectionArrow(optionMenuArrowPosition[menuSelectState], optionMenuArrowPosition[3]);
            }
            else if(!(s_encoderData->b_buttonStatus))
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
    s_encoderData->b_buttonStatus = false;
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
    vMenu_DrawString(6, prevArrowPositionY, 0x0000, 0xFFFF, "  ", 1);
    vMenu_DrawString(6, nextArrowPositionY, 0x0000, 0xFFFF, "->", 1);
}

static void vMenu_OpenSetTimeMenu(encoder_t * s_encoderData)
{
    uint8_t userSetTime = 0;
    char * userSetTime_str;

    ST7735_FillScreen(0x0000);
    vMenu_DrawString(0, 2, 0x0000, 0xFFFF, "      Set Time       ", 1);
    vMenu_DrawString(0, 20, 0x0FF0, 0x0000, "   Hour   ", 2);

    while(!(s_encoderData->b_buttonStatus))
    {
        currEncoderVal = s_encoderData->encoderVal;
        if(currEncoderVal != prevEncoderVal)
        {
            vMenu_intToStr(userSetTime, userSetTime_str, 1);

            if(userSetTime < 10)
            {
                vMenu_DrawString(76, 48, 0x0000, 0x0000, " ", 4);
            }
            vMenu_DrawString(52, 48, 0xFFFF, 0x0000, userSetTime_str, 4);

            if(++userSetTime > 24)
            {
                userSetTime = 0;
            }
        }
        prevEncoderVal = currEncoderVal;
    }
}

static void vMenu_OpenNotePeriodMenu(encoder_t * s_encoderData)
{
    int x;
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

static void vMenu_reverseStr(char * convertedStr, int StrLen)
{
    int i = 0, j = StrLen - 1, temp;
    while (i < j) {
        temp = convertedStr[i];
        convertedStr[i] = convertedStr[j];
        convertedStr[j] = temp;
        i++;
        j--;
    }
}

static int vMenu_intToStr(int convertValue, char * convertedStr, uint8_t numberBase)
{
    int i = 0;
    while (convertValue) {
        convertedStr[i++] = (convertValue % 10) + '0';
        convertValue = convertValue / 10;
    }
    while (i < numberBase)
        convertedStr[i++] = '0';

    vMenu_reverseStr(convertedStr, i);
    convertedStr[i] = '\0';
    return i;
}

