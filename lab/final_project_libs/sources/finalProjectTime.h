/*
 * finalProjectTime.h
 *
 *  Created on: Dec 2, 2022
 *      Author: jtluk
 */

#ifndef FINALPROJECTTIME_H_
#define FINALPROJECTTIME_H_
#include <stdint.h>
#include "I2C.h"
#include "SPI.h"

#define SEGMENT_COLIN 0b0011000

void vfinalPrjTime_Initlize();
void vfinalPrjTime_UpdateSegmentTime();
void vfinalPrjTime_setSevenSegTime(uint8_t userHour, uint8_t userMin, uint8_t userSecond);
static void vfinalPrjTime_writeTime(uint8_t timeValue, uint8_t segmentStartValue);
static void vfinalPrjTime_ClearSegment();
static uint8_t xfinalPrjTime_HexToDec(uint8_t hexValue);



#endif /* FINALPROJECTTIME_H_ */
