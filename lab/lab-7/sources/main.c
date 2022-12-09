#include <stdio.h>
#include <stdlib.h>
#include "msp.h"
#include "pinsInint.h"
#include "Toggle.h"
#include "stepperMotor.h"
#include "readInputs.h"

#define PARTONE 0

#if PARTONE
uint8_t buttonCount = 0;

port2GPIO_t motor_a;
port2GPIO_t motor_b;
port2GPIO_t motor_ap;
port2GPIO_t motor_bp;
port2GPIO_t button;

void vMain_InitMainPorts(void);

static const port2GPIO_t motorPortPins[4] =
{
 {.e_GPIOType = pullup, .e_IO = output, .e_IOpinNumber = pin6, .e_Interrupt = disableInterrupt}, // A
 {.e_GPIOType = pullup, .e_IO = output, .e_IOpinNumber = pin4, .e_Interrupt = disableInterrupt}, // B
 {.e_GPIOType = pullup, .e_IO = output, .e_IOpinNumber = pin7, .e_Interrupt = disableInterrupt}, // Ap
 {.e_GPIOType = pullup, .e_IO = output, .e_IOpinNumber = pin5, .e_Interrupt = disableInterrupt}, // Bp
};

void main(void)
 {
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	vMain_InitMainPorts();

	while(1)
	{
	    if(!xReadInputs_read(button) && buttonCount == 0)
	    {
	        vStepperMotor_turnDeg(motorPortPins, 100, clockwise);
	        buttonCount++;
	    }
        if(!xReadInputs_read(button) && buttonCount == 1)
        {
            vStepperMotor_turnDeg(motorPortPins, 100, counterclockwise);
            buttonCount = 0;
        }
	}
}

void vMain_InitMainPorts(void)
{
    vpinsInit_GPIO(&motor_ap, pin7, output, pullup, disableInterrupt);
    vpinsInit_GPIO(&motor_a, pin6, output, pullup, disableInterrupt);
    vpinsInit_GPIO(&motor_bp, pin5, output, pullup, disableInterrupt);
    vpinsInit_GPIO(&motor_b, pin4, output, pullup, disableInterrupt);
    vpinsInit_GPIO(&button, pin3, input, pullup, disableInterrupt);
}
#endif

#if !PARTONE

#include "msp.h"
#include <stdbool.h>
#include "ST7735.h"

#define SLAVE_ADDRESS 0x48

char TXData;

uint16_t size = 4;
int16_t textColor = ST7735_WHITE;

uint16_t color = 0b0000000000011111;

int display = -1;

int num = -1;



void SysTick_Initialize();               //prototype functions

void SysTick_Delay_ms(uint16_t delayms);

int Read_Keypad (void);

void EUSCIB0_IRQHandler(void);

//void PORT4_IRQHandler(void);





void main(void)

{

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
    // Master init
    P1->SEL0 |= BIT6 | BIT7;                // P1.6 and P1.7 as UCB0SDA and UCB0SCL

    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_SWRST; // Hold EUSCI_B1 module in reset state
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_MODE_3 | EUSCI_B_CTLW0_MST | EUSCI_B_CTLW0_SYNC;
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_UCSSEL_2; // Select SMCLK as EUSCI_B1 clock
    EUSCI_B0->BRW = 0x001E;                    // Set BITCLK = BRCLK / (UCBRx+1) = 3 MHz / 30 = 100 kHz
    EUSCI_B0->I2CSA = SLAVE_ADDRESS;
    EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_SWRST;        // Clear SWRST to resume operation
    while (EUSCI_B0->CTLW0 & EUSCI_B_CTLW0_TXSTP);

    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TR | EUSCI_B_CTLW0_TXSTT;

    NVIC_EnableIRQ(EUSCIB0_IRQn);
    __enable_irq();                                 // All interrupts are enabled

      while(1)
      {
          EUSCI_B0->IE |= EUSCI_B_IE_TXIE0;
          __delay_cycles(1000000);
      }
}



void EUSCIB0_IRQHandler(void)
{
    uint32_t status = EUSCI_B0->IFG; // Get EUSCI_B0 interrupt flag
    EUSCI_B0->IFG &= ~EUSCI_B_IFG_TXIFG0; // Clear EUSCI_B0 TX interrupt flag

    if (status & EUSCI_B_IFG_TXIFG0)
    {
            EUSCI_B0->TXBUF = 'B';
            EUSCI_B0->IE &= ~EUSCI_B_IE_TXIE0;
    } // Disable EUSCI_B0 TX interrupt
    else
    {
        EUSCI_B0->TXBUF = TXData; // Load current TXData value to transmit buffer
        EUSCI_B0->IE &= ~EUSCI_B_IE_TXIE0;
    }
}
#endif
