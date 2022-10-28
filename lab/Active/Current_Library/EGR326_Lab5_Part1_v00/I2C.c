/*********************************************************************************
* Name:             Samuel DeJong
* Course:           EGR 326 -
* Project:          Lab 05 -
* File:             EGR326_Lab5_Part1.c
* Description:      Code taken from Mazidi and Valvano
* ********************************************************************************/
#include "msp.h"
#include "I2C.h"



void i2c_init(void){
      // initialize eUSCI
      UCB0CTLW0 = 0x0001;                // hold the eUSCI module in reset mode
      // configure UCB0CTLW0 for:
      // bit15      UCA10 = 0; own address is 7-bit address
      // bit14      UCSLA10 = 0; address slave with 7-bit address
      // bit13      UCMM = 0; single master environment
      // bit12      reserved
      // bit11      UCMST = 1; master mode
      // bits10-9   UCMODEx = 3; I2C mode
      // bit8       UCSYNC = 1; synchronous mode
      // bits7-6    UCSSELx = 2; eUSCI clock SMCLK
      // bit5       UCTXACK = X; transmit ACK condition in slave mode
      // bit4       UCTR = X; transmitter/receiver
      // bit3       UCTXNACK = X; transmit negative acknowledge in slave mode
      // bit2       UCTXSTP = X; transmit stop condition in master mode
      // bit1       UCTXSTT = X; transmit start condition in master mode
      // bit0       UCSWRST = 1; reset enabled
      UCB0CTLW0 = 0x0F81;
      // configure UCB0CTLW1 for:
      // bits15-9   reserved
      // bit8       UCETXINT = X; early UCTXIFG0 in slave mode
      // bits7-6    UCCLTO = 3; timeout clock low after 165,000 SYSCLK cycles
      // bit5       UCSTPNACK = 0; send negative acknowledge before stop condition in master receiver mode
      // bit4       UCSWACK = 0; slave address acknowledge controlled by hardware
      // bits3-2    UCASTPx = 2; generate stop condition automatically after UCB0TBCNT bytes
      // bits1-0    UCGLITx = 0 deglitch time of 50 ns
      UCB0CTLW1 = 0x00C8;
      UCB0TBCNT = 2;                     // generate stop condition after this many bytes
      // set the baud rate for the eUSCI which gets its clock from SMCLK
      // Clock_Init48MHz() from ClockSystem.c sets SMCLK = HFXTCLK/4 = 12 MHz
      // if the SMCLK is set to 12 MHz, divide by 120 for 100 kHz baud clock
      UCB0BRW = 30;
      P1SEL0 |= 0xC0;
      P1SEL1 &= ~0xC0;                   // configure P1.7 and P1.6 as primary module function
      UCB0CTLW0 &= ~0x0007;              // enable eUSCI module
      UCB0IE = 0x0000;                   // disable interrupts
}

uint16_t I2C_Send1(int8_t slave, uint8_t data1){
  uint16_t status;                   // save status register here in case of error
  while(UCB0STATW&0x0010){};         // wait for I2C ready
  UCB0CTLW0 |= 0x0001;               // hold the eUSCI module in reset mode
  UCB0CTLW0 &= ~0x0001;              // enable eUSCI module
  UCB0I2CSA = slave;                 // I2CCSA[6:0] is slave address
  UCB0CTLW0 = ((UCB0CTLW0&~0x0004)   // clear bit2 (UCTXSTP) for no transmit stop condition
                                     // set bit1 (UCTXSTT) for transmit start condition
                | 0x0012);           // set bit4 (UCTR) for transmit mode
  while(UCB0CTLW0&0x0002){};         // wait for slave address sent
  UCB0TXBUF = data1&0xFF;            // TXBUF[7:0] is data
  UCB0CTLW0 |= 0x0004;               // send stop
  while(UCB0STATW&0x0010){           // wait for I2C idle
    if(UCB0IFG&0x0030){              // bit5 set on not-acknowledge; bit4 set on arbitration lost
      status = UCB0IFG;              // snapshot flag register for calling program
      i2c_init();                    // reset to known state
      return status;
    }
  }
  return 0;
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

    while(UCB0STATW&0x0010){};         // wait for I2C ready
    EUSCI_B0->I2CSA = slaveAddy;            //slave adress
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TR;    //transmit mode
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTT; //send start condition
    while(!(EUSCI_B0->CTLW0 & BIT1));
    EUSCI_B0->TXBUF = memAddy;              //send address
    while((EUSCI_B0->IFG & BIT2));     //wait until ready to send
    EUSCI_B0->CTLW0 &=~ EUSCI_B_CTLW0_TR;    //transmit mode
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTT;    //transmit start
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


    return 1;
}

uint16_t I2C_Send2(int8_t slave, uint8_t data1, uint8_t data2){
  uint16_t status;                   // save status register here in case of error
  while(UCB0STATW&0x0010){};         // wait for I2C ready
  UCB0CTLW0 |= 0x0001;               // hold the eUSCI module in reset mode
  UCB0TBCNT = 2;                     // generate stop condition after this many bytes
  UCB0CTLW0 &= ~0x0001;              // enable eUSCI module
  UCB0I2CSA = slave;                 // I2CCSA[6:0] is slave address
  UCB0CTLW0 = ((UCB0CTLW0&~0x0004)   // clear bit2 (UCTXSTP) for no transmit stop condition
                                     // set bit1 (UCTXSTT) for transmit start condition
                | 0x0012);           // set bit4 (UCTR) for transmit mode
  while(UCB0CTLW0&0x0002){};         // wait for slave address sent
  UCB0TXBUF = data1;            // TXBUF[7:0] is data
  while((UCB0IFG&0x0002) == 0){      // wait for first data sent
    if(UCB0IFG&0x0030){              // bit5 set on not-acknowledge; bit4 set on arbitration lost
      status = UCB0IFG;              // snapshot flag register for calling program
      i2c_init();                    // reset to known state
      return status;
    }
  }
  UCB0TXBUF = data2;            // TXBUF[7:0] is data
  while(UCB0STATW&0x0010){           // wait for I2C idle
    if(UCB0IFG&0x0030){              // bit5 set on not-acknowledge; bit4 set on arbitration lost
      status = UCB0IFG;              // snapshot flag register for calling program
      i2c_init();                    // reset to known state
      return status;
    }
  }
  return 0;
}

uint8_t I2C_Recv(int8_t slave){
  int8_t data1;
  while(UCB0STATW&0x0010){};         // wait for I2C ready
  UCB0CTLW0 |= 0x0001;               // hold the eUSCI module in reset mode
  UCB0CTLW0 &= ~0x0001;              // enable eUSCI module
  UCB0I2CSA = slave;                 // I2CCSA[6:0] is slave address
  UCB0CTLW0 = ((UCB0CTLW0&~0x0014)   // clear bit4 (UCTR) for receive mode
                                     // clear bit2 (UCTXSTP) for no transmit stop condition
                | 0x0002);           // set bit1 (UCTXSTT) for transmit start condition
  while((UCB0IFG&0x0001) == 0){      // wait for complete character received
      UCB0CTLW0 |= 0x0004;              // enable eUSCI module
    if(UCB0IFG&0x0030){              // bit5 set on not-acknowledge; bit4 set on arbitration lost
        i2c_init();                    // reset to known state
      return 0xFF;
    }
  }
  data1 = UCB0RXBUF;            // get the reply
  return data1;
}

uint16_t I2C_Recv2(int8_t slave, uint8_t data1){
  uint8_t data2;
  uint16_t status;
  while(UCB0STATW&0x0010){};         // wait for I2C ready
  UCB0CTLW0 |= 0x0001;               // hold the eUSCI module in reset mode
  UCB0TBCNT = 2;                     // generate stop condition after this many bytes
  UCB0CTLW0 &= ~0x0001;              // enable eUSCI module
  UCB0I2CSA = slave;                 // I2CCSA[6:0] is slave address
  UCB0CTLW0 = ((UCB0CTLW0&~0x0004)   // clear bit2 (UCTXSTP) for no transmit stop condition
                                     // set bit1 (UCTXSTT) for transmit start condition
                | 0x0012);           // set bit4 (UCTR) for transmit mode
  while(UCB0CTLW0&0x0002){};         // wait for slave address sent
  UCB0TXBUF = data1&0xFF;            // TXBUF[7:0] is data
  while((UCB0IFG&0x0002) == 0){      // wait for first data sent
    if(UCB0IFG&0x0030){              // bit5 set on not-acknowledge; bit4 set on arbitration lost
      status = UCB0IFG;              // snapshot flag register for calling program
      i2c_init();                    // reset to known state
      return 0;
    }
  }
  data1 = UCB0RXBUF&0xFF;            // get the reply
  while((UCB0IFG&0x0001) == 0){      // wait for complete character received
    if(UCB0IFG&0x0030){              // bit5 set on not-acknowledge; bit4 set on arbitration lost
        i2c_init();                    // reset to known state
      return 0xFFFF;
    }
  }
  data2 = UCB0RXBUF&0xFF;            // get the reply
  return data2;
}

