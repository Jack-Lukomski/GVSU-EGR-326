/*********************************************************************************
* Name:             Samuel DeJong
* Course:           EGR 326 -
* Project:          Lab 05 -
* File:             EGR326_Lab5_Part1.c
* Description:
* ********************************************************************************/
#ifndef I2C_H_
#define I2C_H_
#include <msp.h>
#include <stdbool.h>
#include <stdint.h>
#define SLAVE_ADDY 0x68


void i2c_init(void);
void vI2C_Initlize(void);
bool i2c_burstWrite(int slaveAddy, int memAddy, int byteCount, unsigned char* data);
bool xI2C_Write(uint8_t slaveAddress, uint8_t memoryAddress, uint8_t transferData);
bool i2c_burstRead(int slaveAddy, int memAddy, int byteCount, unsigned char* data);
bool xI2C_Read(uint8_t slaveAddress, uint8_t memoryAddress, uint8_t * readData);
uint16_t I2C_Send1(int8_t slave, uint8_t data1);
uint8_t I2C_Recv(int8_t slave);
uint16_t I2C_Send2(int8_t slave, uint8_t data1, uint8_t data2);
uint16_t I2C_Recv2(int8_t slave, uint8_t data1);


#endif /* I2C_H_ */
