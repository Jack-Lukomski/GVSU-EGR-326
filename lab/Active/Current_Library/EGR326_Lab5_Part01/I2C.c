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

void vI2C_Initlize(void)
{
    EUSCI_B0->CTLW0 |= 1;
    EUSCI_B0->CTLW0 |= 0x0F81; /* 7 bit slave address, master, I2C, sync mode, use SMCLK */
    EUSCI_B0->BRW = 30;        /* Set clock prescaler 3MHz / 30 = 100kHz */
    P1->SEL0 |= 0xC0;          /* P1.6, P1.7 */
    P1->SEL1 &= ~0xC0;
    EUSCI_B0->CTLW0 &= ~1;     /* Enable UCB0 after config */
}

bool xI2C_Write(uint8_t slaveAddress, uint8_t memoryAddress, uint8_t transferData)
{
    vI2C_Initlize();

    EUSCI_B0->I2CSA = slaveAddress;      /* Setup slave address */
    EUSCI_B0->CTLW0 |= 0x0010;           /* Enable transmitter */
    EUSCI_B0->CTLW0 |= 0x0002;           /* Genorate start and send the slave address */

    while(!(EUSCI_B0->CTLW0 & BIT1));          //wait until ready to transmit

    EUSCI_B0->TXBUF = memoryAddress;

    while(!(EUSCI_B0->CTLW0 & BIT1));          //wait until ready to transmit

    EUSCI_B0->TXBUF = transferData;

    while((EUSCI_B0->IFG & BIT1));             //wait until done sending

    EUSCI_B0->CTLW0 |= 0x0004;

    while((EUSCI_B0->IFG & BIT3));          //wait until stop is sent

    return true; /* No error */
}


bool i2c_burstWrite(int slaveAddy, int memAddy, int byteCount, unsigned char* data){
    if (byteCount <-0)
        return 0;
    EUSCI_B0->IFG &=~ 0xff;
    EUSCI_B0->I2CSA = slaveAddy;            //slave adress
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TR;    //transmit mode
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTT; //send start condition
    while(UCB0STATW&0x0010);          //wait until ready to transmit
    EUSCI_B0->TXBUF = memAddy;              //send address
    do{
        while((UCB0IFG&0x0002) == 0);      // wait for first data sent
//            if(UCB0IFG&0x0030){              // bit5 set on not-acknowledge; bit4 set on arbitration lost
//              status = UCB0IFG;              // snapshot flag register for calling program
//              i2c_init();                    // reset to known state
//              return 0;
//            }
//          }
        EUSCI_B0->TXBUF = *data++;          //send data
        byteCount--;
    }while(byteCount>0);

    while(UCB0STATW&0x0010);             //wait until done sending
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTP;    //transmit stop
    while((UCB0STATW&0x0010));          //wait until stop is sent

//    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_SWRST;         // Hold EUSCI_B0 module in reset state
//    EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_SWRST;         // Clear SWRST to resume operation
//    EUSCI_B0->CTLW0 &=~ (EUSCI_B_CTLW0_TXSTT|EUSCI_B_CTLW0_TXSTP);

    return 1;
}
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


bool i2c_burstRead(int slaveAddy, int memAddy, int byteCount, unsigned char* data){
    if (byteCount <=0)
        return 0;

    EUSCI_B0->I2CSA = slaveAddy;            //slave adress
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TR;    //transmit mode
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTT; //send start condition
    while((UCB0STATW&0x0010));
    EUSCI_B0->TXBUF = memAddy;              //send address
    while((UCB0STATW&0x0010));     //wait until ready to send
    EUSCI_B0->CTLW0 &=~ EUSCI_B_CTLW0_TR;    //transmit mode
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTT;    //transmit start
//    while((EUSCI_B0->CTLW0 & BIT1));

    do{
        if(byteCount==1)
            EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTP;
        while((UCB0STATW&0x0010));     //wait until ready to read
        *data++ = EUSCI_B0->RXBUF;          //read data
        byteCount--;
    }while(byteCount);

    while((UCB0STATW&0x0010));             //wait until done sending

//    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_SWRST;         // Hold EUSCI_B0 module in reset state
//    EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_SWRST;         // Clear SWRST to resume operation
//    EUSCI_B0->CTLW0 &=~ (EUSCI_B_CTLW0_TXSTT|EUSCI_B_CTLW0_TXSTP);


    return 1;
}

