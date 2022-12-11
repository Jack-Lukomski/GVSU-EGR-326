#include "msp.h"
#include <stdio.h>

#define SLAVE_ADDRESS 0x48

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    P2->SEL0 &= ~BIT(1);
    P2->SEL1 &= ~BIT(1);
    P2->DIR |= BIT(1);
    P2->OUT &= ~BIT(1);

    P1->SEL0 |= BIT6 | BIT7; // P1.6 and P1.7 as UCB0SDA and UCB0SCL

    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_SWRST; // Hold EUSCI_B0 module in reset state
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_MODE_3|EUSCI_B_CTLW0_SYNC;
    EUSCI_B0->I2COA0 = SLAVE_ADDRESS | EUSCI_B_I2COA0_OAEN;
    EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_SWRST; // Clear SWRST to resume operation
    EUSCI_B0->IFG &= ~EUSCI_B_IFG_RXIFG0; // Clear EUSCI_B0 RX interrupt flag
    EUSCI_B0->IE |= EUSCI_B_IE_RXIE0; // Enable EUSCI_B0 RX interrupt
    NVIC->ISER[0] = 0x00100000; // EUSCI_B0 interrupt is enabled in NVIC
    __enable_irq(); // All interrupts are enabled
    SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk; // Sleep on exit
    __sleep(); // enter LPM0
}

void EUSCIB0_IRQHandler(void)
{
    uint8_t MasterRecieveBuf;
    uint32_t status = EUSCI_B0->IFG; // Get EUSCI_B0 interrupt flag
    EUSCI_B0->IFG &=~ EUSCI_B_IFG_RXIFG0; // Clear EUSCI_B0 RX interrupt flag

    if(status & EUSCI_B_IFG_RXIFG0) // Check if receive interrupt occurs
    {
        MasterRecieveBuf = EUSCI_B0->RXBUF; // Load current RXData value to transmit buffer
    }
    if(MasterRecieveBuf == 'B')
    {
        P2->OUT |= BIT(1);
    }
}
