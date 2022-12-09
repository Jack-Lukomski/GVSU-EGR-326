#include "spi.h"
#include "stdint.h"

void spi_init(void)
{
    SSPORT->SEL0 &=~ SSPIN;
    SSPORT->SEL1 &=~ SSPIN;
    SSPORT->DIR |= SSPIN;
    SSPORT->OUT |= SSPIN;

    SPIPORT->SEL0 |= CLK | MOSI;
    SPIPORT->SEL1 &=~ (CLK | MOSI);
    EUSCI_B2->CTLW0 = 0X0001;
    EUSCI_B2->CTLW0 = 0XE9C1;
    EUSCI_B2->BRW = 30;
//    EUSCI_B2->IE |= 0X02;
    EUSCI_B2->CTLW0 &=~ 0X0001;
}

void spi_write(uint8_t addy, uint8_t data)
{
    SSPORT->OUT &=~ SSPIN;
//    x = EUSCI_B2->RXBUF;
    while (!(EUSCI_B2->IFG & 2));       //wait for transmit buffer clear
    EUSCI_B2->TXBUF = addy;
    while (!(EUSCI_B2->IFG & 2));       //wait for transmit buffer clear
    while (EUSCI_B2->STATW & 1);        //wait for busy to be cleared
//    __delay_cycles(30000);
//    x = EUSCI_B2->RXBUF;
    EUSCI_B2->TXBUF = data;
//    while (!(EUSCI_B2->IFG & 2));       //wait for transmit buffer clear
    while (EUSCI_B2->STATW & 1);        //wait for busy to be cleared
    SSPORT->OUT |= SSPIN;
    __delay_cycles(300000);
//    x = EUSCI_B2->RXBUF;
}