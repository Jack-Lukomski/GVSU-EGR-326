#include "I2C.h"
/*
 * I2C.c
 *
 *  Created on: Sep 30, 2022
 *      Author: jtluk
 */
bool xI2C_Read(uint8_t slaveAddress, uint8_t memoryAddress, uint8_t * readData)
{
    vI2C_Initlize();

    EUSCI_B0->I2CSA = slaveAddress;
    EUSCI_B0->CTLW0 |= 0x0010;
    EUSCI_B0->CTLW0 |= 0x0002;

    while(!(EUSCI_B0->IFG & 2));

    EUSCI_B0->TXBUF = memoryAddress;

    while(!(EUSCI_B0->IFG & 2));

    EUSCI_B0->CTLW0 &= ~0x0010;
    EUSCI_B0->CTLW0 |= 0x0002;

    while(!(EUSCI_B0->CTLW0 & 2));

    EUSCI_B0->CTLW0 |= 0x0004;

    while(!(EUSCI_B0->IFG & 1));

    *readData = EUSCI_B0->RXBUF;

    while(EUSCI_B0->CTLW0 & 4);

    return true;
}

void vI2C_Initlize(void)
{
  UCB0CTLW0 = 0x0001;
  UCB0CTLW0 = 0x0F81;
  UCB0CTLW1 = 0x00C8;
  UCB0TBCNT = 2;                     // generate stop condition after this many bytes
  UCB0BRW = 30;
  P1SEL0 |= 0xC0;
  P1SEL1 &= ~0xC0;                   // configure P1.7 and P1.6 as primary module function
  UCB0CTLW0 &= ~0x0007;              // enable eUSCI module
  UCB0IE = 0x0000;                   // disable interrupts
}

uint16_t xI2C_Write(int8_t slaveAddress, uint8_t memoryAddress, uint8_t startValue)
{
  uint16_t status;                   // save status register here in case of error
  while(UCB0STATW&0x0010){};         // wait for I2C ready

  UCB0CTLW0 |= 0x0001;               // hold the eUSCI module in reset mode
  UCB0TBCNT = 2;                     // generate stop condition after this many bytes
  UCB0CTLW0 &= ~0x0001;              // enable eUSCI module
  UCB0I2CSA = slaveAddress;          // I2CCSA[6:0] is slave address

  UCB0CTLW0 = ((UCB0CTLW0&~0x0004) | 0x0012);   // clear bit2 (UCTXSTP) for no transmit stop condition

  while(UCB0CTLW0&0x0002){};         // wait for slave address sent

  UCB0TXBUF = memoryAddress&0xFF;    // TXBUF[7:0] is data

  while((UCB0IFG&0x0002) == 0)
  {
    if(UCB0IFG&0x0030)
    {
      status = UCB0IFG;              // snapshot flag register for calling program
      vI2C_Initlize();                    // reset to known state
      return status;
    }
  }
  UCB0TXBUF = startValue&0xFF;            // TXBUF[7:0] is data
  while(UCB0STATW&0x0010)
  {
    if(UCB0IFG&0x0030)
    {
      status = UCB0IFG;              // snapshot flag register for calling program
      vI2C_Initlize();                    // reset to known state
      return status;
    }
  }
  return 0;
}

