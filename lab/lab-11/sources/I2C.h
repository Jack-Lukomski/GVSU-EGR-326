/*
 * I2C.h
 *
 *  Created on: Sep 30, 2022
 *      Author: jtluk
 */

#ifndef I2C_H_
#define I2C_H_
#include "msp.h"
#include <stdbool.h>
#include <stdio.h>

#define TEMPATURE_ADDRESS 17
#define SECONDS_ADDRESS 0x00
#define MINUETS_ADDRESS 0x01
#define HOURS_ADDRESS 0x02
#define DAYS_ADDRESS 0x04
#define DATE_ADDRESS 0x04
#define MONTH_ADDRESS 0x05
#define YEAR_ADDRESS 0x06

void vI2C_Initlize(void);
uint16_t xI2C_Write(int8_t slaveAddress, uint8_t memoryAddress, uint8_t startValue);
uint16_t xI2C_WriteBurst(int8_t slaveAddress, uint8_t memoryAddress, int byteCount, uint8_t * data);
bool xI2C_Read(uint8_t slaveAddress, uint8_t memoryAddress, uint8_t * readData);
bool xI2C_Readburst(uint8_t slaveAddress, uint8_t memoryAddress, uint8_t byteCount, uint8_t * readData);

#endif /* I2C_H_ */