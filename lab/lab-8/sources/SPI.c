#include "SPI.h"

port2GPIO_t s_csPin7Seg;

void vSPI_Initlize(void)
{
    EUSCI_A3->CTLW0 = UCSWRST; // Putting SPI in reset state
    EUSCI_A3->CTLW0 = UCSSEL_1 | UCSYNC | UCMST | UCMSB | UCCKPH; // May need to edit to make 10MHz 0b101010010101 0x29C1
    EUSCI_A3->MCTLW = 0;
    EUSCI_A3->BRW = 3;
    EUSCI_A3->CTLW0 &= ~0x0001; // enable eUSCI module

    P9->SEL0 |= (BIT5 | BIT7); // CLK and TRX
    P9->SEL1 &= ~(BIT5 | BIT7);

    vpinsInit_GPIO(&s_csPin7Seg, pin4, output, pullup, disableInterrupt); // CS pin for 7Seg

    vSysTick_Init(); // Init systic clk for delays
}

void vSPI_writeByte(uint8_t userAddress, uint8_t userData)
{
    vToggle_turnPinHigh(s_csPin7Seg); // Turning CS pin low so data can be sent to 7Seg
    while(!(EUSCI_A3->IFG & 2)); // Delay 10ms
    EUSCI_A3->TXBUF = userAddress; // data out
    while(EUSCI_A3->STATW & 1);// Delay another 10ms
    vToggle_turnPinLow(s_csPin7Seg); // Close up the cs line

    vToggle_turnPinHigh(s_csPin7Seg); // Turning CS pin low so data can be sent to 7Seg
    while(!(EUSCI_A3->IFG & 2)); // Delay 10ms
    EUSCI_A3->TXBUF = userData; // data out
    while(EUSCI_A3->STATW & 1);
    vToggle_turnPinLow(s_csPin7Seg); // Close up the cs line
}

