#include "I2C.h"
/*
 * I2C.c
 *
 *  Created on: Sep 30, 2022
 *      Author: jtluk
 */

void vI2C_Initlize(void)
{
    EUSCI_B1->CTLW0 |= 1;
    EUSCI_B1->CTLW0 |= 0x0F81; /* 7 bit slave address, master, I2C, sync mode, use SMCLK */
    EUSCI_B1->BRW = 30;        /* Set clock prescaler 3MHz / 30 = 100kHz */
    P1->SEL0 |= 0x30;          /* P1.6, P1.7 */
    P1->SEL1 &= ~0x30;
    EUSCI_B1->CTLW0 &= ~1;     /* Enable UCB1 after config */
}

bool xI2C_Write(uint8_t slaveAddress, uint8_t memoryAddress, uint8_t transferData)
{
    vI2C_Initlize();

    EUSCI_B1->I2CSA = slaveAddress;      /* Setup slave address */
    EUSCI_B1->CTLW0 |= 0x0010;           /* Enable transmitter */
    EUSCI_B1->CTLW0 |= 0x0002;           /* Genorate start and send the slave address */

    __delay_cycles(300000);

    while(!(EUSCI_B1->IFG & 2));         /* Wait until it is ready to transmit */

    EUSCI_B1->TXBUF = memoryAddress;

    while(!(EUSCI_B1->IFG & 2));

    EUSCI_B1->TXBUF = transferData;

    while(!(EUSCI_B1->IFG & 2));

    EUSCI_B1->CTLW0 |= 0x0004;

    while(!(EUSCI_B1->CTLW0 & 4));

    return true; /* No error */
}

bool xI2C_Read(uint8_t slaveAddress, uint8_t memoryAddress, uint8_t * readData)
{
    vI2C_Initlize();

    EUSCI_B1->I2CSA = slaveAddress;
    EUSCI_B1->CTLW0 |= 0x0010;
    EUSCI_B1->CTLW0 |= 0x0002;

    while(!(EUSCI_B1->IFG & 2));

    EUSCI_B1->TXBUF = memoryAddress;

    while(!(EUSCI_B1->IFG & 2));

    EUSCI_B1->CTLW0 &= ~0x0010;
    EUSCI_B1->CTLW0 |= 0x0002;

    while(!(EUSCI_B1->CTLW0 & 2));

    EUSCI_B1->CTLW0 |= 0x0004;

    while(!(EUSCI_B1->IFG & 1));

    *readData = EUSCI_B1->RXBUF;

    while(!(EUSCI_B1->CTLW0 & 4));

    return true;
}

//void i2c_burstWrite(int slaveAddy, int memAddy, int byteCount, unsigned char* data){
//    EUSCI_B1->IFG &=~ 0xff;
//    EUSCI_B1->I2CSA = slaveAddy;            //slave adress
//    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TR;    //transmit mode
//    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TXSTT; //send start condition
//    while(!(EUSCI_B1->CTLW0 & 2));          //wait until ready to transmit
//    EUSCI_B1->TXBUF = memAddy;              //send address
//
//    do{
//        while((EUSCI_B1->IFG & 2));     //wait until ready to send
//        EUSCI_B1->TXBUF = *data++;          //send data
//        byteCount--;
//    }while(byteCount>0);
//
//    while((EUSCI_B1->IFG & 2));             //wait until done sending
//    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TXSTP;    //transmit stop
//    while((EUSCI_B1->IFG & 4));          //wait until stop is sent
//
//    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_SWRST;         // Hold EUSCI_B1 module in reset state
//    EUSCI_B1->CTLW0 &= ~EUSCI_B_CTLW0_SWRST;         // Clear SWRST to resume operation
//    EUSCI_B1->CTLW0 &=~ (EUSCI_B_CTLW0_TXSTT|EUSCI_B_CTLW0_TXSTP);
//}
//
//void i2c_burstRead(int slaveAddy, int memAddy, int byteCount, unsigned char* data){
//    EUSCI_B1->I2CSA = slaveAddy;            //slave adress
//    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TR;    //transmit mode
//    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TXSTT; //send start condition
//    while(!(EUSCI_B1->CTLW0 & 2));
//    EUSCI_B1->TXBUF = memAddy;              //send address
//    while((EUSCI_B1->IFG & 2));     //wait until ready to send
//    EUSCI_B1->CTLW0 &=~ EUSCI_B_CTLW0_TR;    //transmit mode
//    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TXSTT;    //transmit mode
//    while(!(EUSCI_B1->CTLW0 & 2));
//
//    do{
//        if(byteCount==1)
//            EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_TXSTP;
//        while((EUSCI_B1->IFG & 1));     //wait until ready to read
//        *data++ = EUSCI_B1->RXBUF;          //read data
//        byteCount--;
//    }while(byteCount);
//
//    while(!(EUSCI_B1->CTLW0 & 4));             //wait until done sending
//
//    EUSCI_B1->CTLW0 |= EUSCI_B_CTLW0_SWRST;         // Hold EUSCI_B1 module in reset state
//    EUSCI_B1->CTLW0 &= ~EUSCI_B_CTLW0_SWRST;         // Clear SWRST to resume operation
//    EUSCI_B1->CTLW0 &=~ (EUSCI_B_CTLW0_TXSTT|EUSCI_B_CTLW0_TXSTP);
//}

