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

#define SLAVE_ADDRESS 0x68

void vI2C_Initlize(void);
uint16_t xI2C_Write(int8_t slaveAddress, uint8_t memoryAddress, uint8_t startValue);
bool xI2C_Read(uint8_t slaveAddress, uint8_t memoryAddress, uint8_t * readData);
int hexToDec(uint8_t hexVal);

#endif /* I2C_H_ */
