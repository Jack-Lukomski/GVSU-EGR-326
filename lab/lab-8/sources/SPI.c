#include "SPI.h"

port2GPIO_t s_csPin7Seg;

void vSPI_Initlize(void)
{
    EUSCI_A3->CTLW0 = UCSWRST; // Putting SPI in reset state
    EUSCI_A3->CTLW0 = 0x29C1; // May need to edit to make 10MHz
    EUSCI_A3->MCTLW = 0;

    P9->SEL0 &= ~(BIT5 | BIT7); // CLK and TRX
    P9->SEL1 &= ~(BIT5 | BIT7);

    vpinsInit_GPIO(&s_csPin7Seg, pin4, output, pullup, disableInterrupt); // CS pin for 7Seg

    EUSCI_A3->CTLW0 &= ~0x0001; // enable eUSCI module
    EUSCI_A3->IE    &= ~0x0003; // Disable Interupts

    vSysTick_Init(); // Init systic clk for delays
}

void vSPI_writeByte(uint8_t userData)
{
    vToggle_turnPinLow(s_csPin7Seg); // Turning CS pin low so data can be sent to 7Seg
    vSysTick_mSecDelay(10); // Delay 10ms
    EUSCI_A3->TXBUF = userData; // data out
    vSysTick_mSecDelay(10); // Delay another 10ms
    vToggle_turnPinHigh(s_csPin7Seg); // Close up the cs line
}

