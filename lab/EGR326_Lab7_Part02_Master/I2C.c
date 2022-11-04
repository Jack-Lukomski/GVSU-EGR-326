#include "I2C.h"
/*
 * I2C.c
 *
 *  Created on: Sep 30, 2022
 *      Author: jtluk
 */

void vI2C_Initlize(void)
{
    EUSCI_B0->CTLW0 |= 1;
    EUSCI_B0->CTLW0 |= 0x0F81; /* 7 bit slave address, master, I2C, sync mode, use SMCLK */
    EUSCI_B0->BRW = 30;        /* Set clock prescaler 3MHz / 30 = 100kHz */
    P1->SEL0 |= 0xC0;          /* P1.6, P1.7 */
    P1->SEL1 &= ~0xC0;
    EUSCI_B0->CTLW0 &= ~1;     /* Enable UCB0 after config */
}

bool xI2C_Write(uint8_t slaveAddress, uint8_t transferData)
{
    vI2C_Initlize();

    EUSCI_B0->I2CSA = 0x48;      /* Setup slave address */
    EUSCI_B0->CTLW0 |= 0x0010;           /* Enable transmitter */
    EUSCI_B0->CTLW0 |= 0x0002;           /* Genorate start and send the slave address */

    while((EUSCI_B0->IFG & 2));         /* Wait until it is ready to transmit */

    EUSCI_B0->TXBUF = transferData;

    while((EUSCI_B0->IFG & 2));

    EUSCI_B0->CTLW0 |= 0x0004;

    while(EUSCI_B0->CTLW0 & 4);

    return true; /* No error */
}

bool xI2C_Read(uint8_t slaveAddress, uint8_t memoryAddress, uint8_t * readData)
{
    vI2C_Initlize();

    EUSCI_B0->I2CSA = slaveAddress;
    EUSCI_B0->CTLW0 |= 0x0010;
    EUSCI_B0->CTLW0 |= 0x0002;

    while((EUSCI_B0->IFG & 2));

    EUSCI_B0->TXBUF = memoryAddress;

    while((EUSCI_B0->IFG & 2));

    EUSCI_B0->CTLW0 &= ~0x0010;
    EUSCI_B0->CTLW0 |= 0x0002;

//    while(!(EUSCI_B0->CTLW0 & 2));

    EUSCI_B0->CTLW0 |= 0x0004;

    while((EUSCI_B0->IFG & 1));

    *readData = EUSCI_B0->RXBUF;

//    while(EUSCI_B0->CTLW0 & 4);

    return true;
}