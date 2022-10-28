/*********************************************************************************
* Name:             Samuel DeJong
* Course:           EGR 326 -
* Project:          Lab 05 -
* File:             EGR326_Lab5_Part1.c
* Description:      Code taken from
* ********************************************************************************/
#include "msp.h"
#include "I2C.h"



void i2c_init(void){
    P1->SEL0 |= BIT6 | BIT7;
    P1->SEL0 &= ~(BIT6 | BIT7);
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_SWRST;         // Hold EUSCI_B0 module in reset state
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_MODE_3|EUSCI_B_CTLW0_MST|EUSCI_B_CTLW0_SYNC|EUSCI_B_CTLW0_UCSSEL_2;   //I2C mode, set as master, synchronous, Select SMCLK as EUSCI_B0 clock
//    EUSCI_B0->BRW = 0x001E;      // Set BITCLK = BRCLK / (UCBRx+1) = 3 MHz / 30 = 100 kHz
    EUSCI_B0->BRW = 0x001E;      // Set BITCLK = BRCLK / (UCBRx+1) = 3 MHz / 30 = 100 kHz
    EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_SWRST;         // Clear SWRST to resume operation
//    EUSCI_B0->IE |= 0xFF;
}

void i2c_burstWrite(int slaveAddy, int memAddy, int byteCount, unsigned char* data){
//    if (byteCount <-0)
//        return -1;
    EUSCI_B0->IFG &=~ 0xff;
    EUSCI_B0->I2CSA = slaveAddy;            //slave adress
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TR;    //transmit mode
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTT; //send start condition
    while(!(EUSCI_B0->CTLW0 & BIT1));          //wait until ready to transmit
    EUSCI_B0->TXBUF = memAddy;              //send address

    do{
        while((EUSCI_B0->IFG & BIT1));     //wait until ready to send
        EUSCI_B0->TXBUF = *data++;          //send data
        byteCount--;
    }while(byteCount>0);

    while((EUSCI_B0->IFG & BIT1));             //wait until done sending
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTP;    //transmit stop
    while((EUSCI_B0->IFG & BIT3));          //wait until stop is sent

    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_SWRST;         // Hold EUSCI_B0 module in reset state
    EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_SWRST;         // Clear SWRST to resume operation
    EUSCI_B0->CTLW0 &=~ (EUSCI_B_CTLW0_TXSTT|EUSCI_B_CTLW0_TXSTP);

//    return 0;
}

void i2c_burstRead(int slaveAddy, int memAddy, int byteCount, unsigned char* data){
//    if (byteCount <=0)
//        return -1;

    EUSCI_B0->I2CSA = slaveAddy;            //slave adress
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TR;    //transmit mode
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTT; //send start condition
    while(!(EUSCI_B0->CTLW0 & BIT1));
    EUSCI_B0->TXBUF = memAddy;              //send address
    while((EUSCI_B0->IFG & BIT2));     //wait until ready to send
    EUSCI_B0->CTLW0 &=~ EUSCI_B_CTLW0_TR;    //transmit mode
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTT;    //transmit mode
//    while((EUSCI_B0->CTLW0 & BIT1));

    do{
        if(byteCount==1)
            EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTP;
        while((EUSCI_B0->IFG & BIT0));     //wait until ready to read
        *data++ = EUSCI_B0->RXBUF;          //read data
        byteCount--;
    }while(byteCount);

    while(!(EUSCI_B0->CTLW0 & BIT2));             //wait until done sending

    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_SWRST;         // Hold EUSCI_B0 module in reset state
    EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_SWRST;         // Clear SWRST to resume operation
    EUSCI_B0->CTLW0 &=~ (EUSCI_B_CTLW0_TXSTT|EUSCI_B_CTLW0_TXSTP);


//    return 0;
}

