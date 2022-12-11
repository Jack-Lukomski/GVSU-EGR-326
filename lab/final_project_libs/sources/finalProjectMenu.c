#include "finalProjectMenu.h"
/*
 * finalProjectMenu.c
 *
 *  Created on: Nov 30, 2022
 *      Author: jtluk
 */

uint8_t month, day, year;
uint8_t date_ptr[3];
uint8_t mainMenuDateYPosition = 150;

static const noteColorValue_t noteToColor_t[6] =
{
 {.note = 'A', .RGB_Color = ST7735_RED},
 {.note = 'B', .RGB_Color = ST7735_CYAN},
 {.note = 'C', .RGB_Color = ST7735_YELLOW},
 {.note = 'D', .RGB_Color = ST7735_GREEN},
 {.note = 'E', .RGB_Color = ST7735_BLUE},
 {.note = 'F', .RGB_Color = ST7735_MAGENTA},
};

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


uint8_t currEncoderVal = 0;
uint8_t prevEncoderVal = 0;
uint8_t menuSelectState = 0;
uint8_t optionMenuArrowPosition[4] = {20, 33, 46, 59};

e_menuTransistionStates menuDisplayState = mainScreen;

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
        WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
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

    ST7735_FillScreen(0x0000);
    vMenu_DrawString(0, 2, 0x0000, 0xFFFF, "   Sound Generator   ", 1);

    vMenu_DrawString(0, 70, 0xFFFF, 0x0000,"(Press To Enter Menu)", 1);
    vMenu_DrawString(0, 128, 0xFFFF, 0x0000,"    Current Date:    ", 1);

    if(month < 10)
    {
        ST7735_DrawChar(0+offSet, mainMenuDateYPosition, '0', 0xFFFF, 0x0000, 1);
        ST7735_DrawChar(8+offSet, mainMenuDateYPosition, month + 48, 0xFFFF, 0x0000, 1);
    }
    else
    {
        ST7735_DrawChar(0+offSet, mainMenuDateYPosition, month/10 + 48, 0xFFFF, 0x0000, 1);
        ST7735_DrawChar(8+offSet, mainMenuDateYPosition, month - ((month/10)*10) + 48, 0xFFFF, 0x0000, 1);
    }

    ST7735_DrawChar(16+offSet, mainMenuDateYPosition, '/', 0xFFFF, 0x0000, 1);

    if(day < 10)
    {
        ST7735_DrawChar(24+offSet, mainMenuDateYPosition, '0', 0xFFFF, 0x0000, 1);
        ST7735_DrawChar(32+offSet, mainMenuDateYPosition, day + 48, 0xFFFF, 0x0000, 1);
    }
    else
    {
        ST7735_DrawChar(24+offSet, mainMenuDateYPosition, day/10 + 48, 0xFFFF, 0x0000, 1);
        ST7735_DrawChar(32+offSet, mainMenuDateYPosition, day - ((day/10)*10) + 48, 0xFFFF, 0x0000, 1);
    }

    ST7735_DrawChar(40+offSet, mainMenuDateYPosition, '/', 0xFFFF, 0x0000, 1);

    ST7735_DrawChar(48+offSet, mainMenuDateYPosition, '2', 0xFFFF, 0x0000, 1);
    ST7735_DrawChar(56+offSet, mainMenuDateYPosition, '0', 0xFFFF, 0x0000, 1);
    ST7735_DrawChar(64+offSet, mainMenuDateYPosition, year/10 + 48, 0xFFFF, 0x0000, 1);
    ST7735_DrawChar(72+offSet, mainMenuDateYPosition, year - ((year/10)*10) + 48, 0xFFFF, 0x0000, 1);
}

void vMenu_FillOptionMenu(encoder_t * s_encoderData)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_IS_1 | WDT_A_CTL_SSEL__SMCLK |  WDT_A_CTL_CNTCL | WDT_A_CTL_TMSEL;
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

    uint8_t userSetHours = xMenu_SetDateTimeSubMenus(s_encoderData, "   Hour   ", "      Set Time       ", 24);
    uint8_t userSetMin = xMenu_SetDateTimeSubMenus(s_encoderData, " Minutes  ", "      Set Time       ", 60);
    uint8_t userSetSec = xMenu_SetDateTimeSubMenus(s_encoderData, " Seconds  ", "      Set Time       ", 60);

    vfinalPrjTime_Initlize();
    vfinalPrjTime_setSevenSegTime(decimalToHex_t[userSetHours-1], decimalToHex_t[userSetMin-1], decimalToHex_t[userSetSec-1]);
    vSysTick_IntteruptInit(5000);
}

static void vMenu_OpenSetDateMenu(encoder_t * s_encoderData)
{
    uint8_t userSetMonth = xMenu_SetDateTimeSubMenus(s_encoderData, " Month  ", "      Set Time       ", 13);
    uint8_t userSetDay = xMenu_SetDateTimeSubMenus(s_encoderData, " Day  ", "      Set Time       ", 32);
    uint8_t userSetYear = xMenu_SetDateTimeSubMenus(s_encoderData, " Year  ", "      Set Time       ", 100);

    vfinalPrjTime_Initlize();
    vfinalPrjTime_setMDYdate(userSetMonth, userSetDay, userSetYear);
    vSysTick_IntteruptInit(5000);

    vMenu_MainScreen(s_encoderData);
}

static void vMenu_OpenPlayNoteMenu(encoder_t * s_encoderData)
{
    char currNote;
    char prevNote;
    uint8_t currVolume;

    ST7735_FillScreen(0x0000);
    vMenu_DrawString(0, 2, 0x0000, 0xFFFF, "     Play Music      ", 1);
    vMenu_DrawString(0, 136, 0xFFFF,0x0000,"   (Press To Quit)   ", 1);
    vMenu_DrawString(0, 120, 0xFFFF,0x0000,"   Volume:", 1);

    preMusicInit();
    RGB_pin_initialize();
    s_encoderData->b_buttonStatus = false;
    xI2C_Read(EEPROM_SLAVE_ADDRESS, 3, &currVolume);


    while(!(s_encoderData->b_buttonStatus))
    {
        vMusicDriver();
        currNote = CurrNotePlaying;
        if(currNote != prevNote)
        {
            ST7735_DrawChar(64-8, 48+16, CurrNotePlaying, xMenu_NoteColorLookUpTbl(currNote), 0x0000, 4);
        }
        prevNote = currNote;
        xI2C_Read(EEPROM_SLAVE_ADDRESS, 3, &currVolume);
        __delay_cycles(3000000);
        ST7735_DrawCharS(64, 120, currVolume + 48, 0xFFFF, 0x0000, 1);
    }
    postMusicDisable();

    vMenu_MainScreen(NULL);
    menuDisplayState = mainScreen;
    s_encoderData->b_buttonStatus = false;
}

static uint16_t xMenu_NoteColorLookUpTbl(char currentNote)
{
    uint8_t numNotes;
    uint16_t colorRetVal;

    for(numNotes = 0; numNotes < 6; numNotes++)
    {
        if(noteToColor_t[numNotes].note == currentNote)
        {
            colorRetVal = noteToColor_t[numNotes].RGB_Color;
        }
    }
    return colorRetVal;
}

static void vMenu_OpenQuitMenu(encoder_t * s_encoderData)
{
    vMenu_MainScreen(NULL);
    menuDisplayState = mainScreen;
    s_encoderData->b_buttonStatus = false;
}

static uint8_t xMenu_SetDateTimeSubMenus(encoder_t * s_encoderData, char ** displayString, char ** titleString, uint8_t maxLimit)
{
    uint8_t userSetValue = 0;

    ST7735_FillScreen(0x0000);
    vMenu_DrawString(0, 2, 0x0000, 0xFFFF, titleString, 1);
    vMenu_DrawString(0, 20, 0x0FF0, 0x0000, displayString, 2);
    s_encoderData->b_buttonStatus = false;

    while(!(s_encoderData->b_buttonStatus))
    {
        currEncoderVal = s_encoderData->encoderVal;
        if(currEncoderVal != prevEncoderVal)
        {
            if(userSetValue < 10)
            {
                ST7735_DrawChar(64, 48, userSetValue + 48, 0xFFFF, 0x0000, 4);
            }
            else if(userSetValue >= 10)
            {
                ST7735_DrawChar(48, 48, (userSetValue/10) + 48, 0xFFFF, 0x0000, 4);
                ST7735_DrawChar(48+24, 48, (userSetValue-(userSetValue/10)*10) + 48, 0xFFFF, 0x0000, 4);
            }

            if(++userSetValue > maxLimit)
            {
                userSetValue = 0;
                ST7735_DrawChar(48, 48, ' ', 0xFFFF, 0x0000, 4);
                ST7735_DrawChar(48+24, 48, ' ', 0xFFFF, 0x0000, 4);
            }
        }
        prevEncoderVal = currEncoderVal;
    }
    return userSetValue;
}