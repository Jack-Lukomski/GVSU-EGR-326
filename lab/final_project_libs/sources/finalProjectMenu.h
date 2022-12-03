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

typedef enum e_menuTransistionStates
{
    mainScreen,
    menuSelectScreen,
    selectedMenuItem,
}e_menuTransistionStates;

void vMenu_Init(void);


void vMenu_MainScreen(void);
void vMenu_FillOptionMenu(void);
void vMenu_UpdateOptionMenu(encoder_t * s_encoderData);

static void vMenu_DrawString(int x, int y, int textColor, int colorBg, char * string, int fontSize);
static void vMenu_moveSelectionArrow(uint8_t nextArrowPositionY, uint8_t prevArrowPositionY);

typedef void(*vMenu_menuOption_ptr)(encoder_t *);
static void vMenu_OpenSetTimeMenu(encoder_t * s_encoderData);
static void vMenu_OpenNotePeriodMenu(encoder_t * s_encoderData);
static void vMenu_OpenPlayNoteMenu(encoder_t * s_encoderData);
static void vMenu_OpenQuitMenu(encoder_t * s_encoderData);

int intToStr(int x, char str[], int d);
void reverse(char* str, int len);

void vMenu_UpdateScreen(encoder_t * s_encoderData);


#endif /* FINALPROJECTMENU_H_ */
