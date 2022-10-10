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
bool xI2C_Write(uint8_t slaveAddress, uint8_t memoryAddress, uint8_t transferData);
bool xI2C_Read(uint8_t slaveAddress, uint8_t memoryAddress, uint8_t * readData);

void i2c_burstRead(int slaveAddy, int memAddy, int byteCount, unsigned char* data);
void i2c_burstWrite(int slaveAddy, int memAddy, int byteCount, unsigned char* data);

#endif /* I2C_H_ */
