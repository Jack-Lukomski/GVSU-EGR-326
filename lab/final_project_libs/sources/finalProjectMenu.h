/*
 * finalProjectMenu.h
 *
 *  Created on: Nov 30, 2022
 *      Author: jtluk
 */

#ifndef FINALPROJECTMENU_H_
#define FINALPROJECTMENU_H_
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ST7735.h"
#include "clk48MHz.h"
#include "encoder.h"
#include "finalProjectTime.h"
#include "I2C.h"
#include "SamsSonarLib.h"

#define MSP_SALVE_ADDRESS 0x48

typedef enum e_menuTransistionStates
{
    mainScreen,
    menuSelectScreen,
    selectedMenuItem,
}e_menuTransistionStates;

void vMenu_Init(void);

typedef void(*vMenu_menuStateMachiene_ptr)(encoder_t * s_encoderData);
void vMenu_MainScreen(encoder_t * s_encoderData);
void vMenu_FillOptionMenu(encoder_t * s_encoderData);
void vMenu_UpdateOptionMenu(encoder_t * s_encoderData);

static void vMenu_DrawString(int x, int y, int textColor, int colorBg, char * string, int fontSize);
static void vMenu_moveSelectionArrow(uint8_t nextArrowPositionY, uint8_t prevArrowPositionY);

typedef void(*vMenu_menuOption_ptr)(encoder_t *);
static void vMenu_OpenSetTimeMenu(encoder_t * s_encoderData);
static void vMenu_OpenSetDateMenu(encoder_t * s_encoderData);
static void vMenu_OpenPlayNoteMenu(encoder_t * s_encoderData);
static void vMenu_OpenQuitMenu(encoder_t * s_encoderData);

static uint8_t xMenu_SetHoursSubMenu(encoder_t * s_encoderData);
static uint8_t xMenu_SetMinSubMenu(encoder_t * s_encoderData);
static uint8_t xMenu_SetSecSubMenu(encoder_t * s_encoderData);

static uint8_t xMenu_SetMonthSubMenu(encoder_t * s_encoderData);
static uint8_t xMenu_SetDaySubMenu(encoder_t * s_encoderData);
static uint8_t xMenu_SetYearSubMenu(encoder_t * s_encoderData);

void vMenu_UpdateScreen(encoder_t * s_encoderData);


#endif /* FINALPROJECTMENU_H_ */
