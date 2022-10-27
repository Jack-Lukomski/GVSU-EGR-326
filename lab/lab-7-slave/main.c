#include "msp.h"

#define LED2_RED BIT0

#define LED2_GREEN BIT1

#define LED2_BLUE BIT2

#define SLAVE_ADDRESS 0x48

char RXData;

char RXData2, RXData3;

int degree = 0;

int total = 0;

int j = 0;



void EUSCIB0_IRQHandler(void);

void SysTick_Initialize();

void SysTick_Delay_ms(uint16_t delayms);



void main(void){

WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;



P2->SEL0 &= ~(BIT4|BIT5|BIT6|BIT7);

P2->SEL1 &= ~(BIT4|BIT5|BIT6|BIT7);  // sets pin 2.0 2.1 and 2.2 to GPIO

P2->DIR  |= (BIT4|BIT5|BIT6|BIT7);// p2.0 p2.1 p2.2 as an output

P2->REN |= (BIT4|BIT5|BIT6|BIT7); //resistor enabled

P2->OUT &= ~(BIT4|BIT5|BIT6|BIT7);  // default state of 1

SysTick_Initialize(); // calls the system timer initializing function



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

void EUSCIB0_IRQHandler(void){

uint32_t status = EUSCI_B0->IFG; // Get EUSCI_B0 interrupt flag

EUSCI_B0->IFG &=~ EUSCI_B_IFG_RXIFG0; // Clear EUSCI_B0 RX interrupt flag

if(status & EUSCI_B_IFG_RXIFG0){ // Check if receive interrupt occurs

RXData = EUSCI_B0->RXBUF; // Load current RXData value to transmit buffer

if(RXData != 'B')

{

    if(RXData == '1') degree = (1*20)/2;

    else if(RXData == '2') degree = (2*20)/2;

    else if(RXData == '3') degree = (3*20)/2;

    else if(RXData == '4') degree = (4*20)/2;

    else if(RXData == '5') degree = (5*20)/2;

    else if(RXData == '6') degree = (6*20)/2;

    else if(RXData == '7') degree = (7*20)/2;

    else if(RXData == '8') degree = (8*20)/2;

    else if(RXData == '9') degree = (9*20)/2;

    total = total + degree;

    for(j=0;j<=degree;j++)

        {

        P2->OUT |= BIT5;

        P2->OUT |= BIT6;

        SysTick_Delay_ms(10);

        P2->OUT &= ~BIT5;

        P2->OUT |= BIT4;

        SysTick_Delay_ms(10);

        P2->OUT &= ~BIT6;

        P2->OUT |= BIT7;

        SysTick_Delay_ms(10);

        P2->OUT &= ~BIT4;

        P2->OUT |= BIT5;

        SysTick_Delay_ms(10);

        P2->OUT &= ~BIT7;

        }

    RXData = 0;

    RXData2 = 0;

    RXData3 = 0;

}

else if(RXData == 'B')

{

    for(j=0;j<=total;j++)

    {

    P2->OUT |= BIT7;

    P2->OUT |= BIT4;

    SysTick_Delay_ms(10);

    P2->OUT &= ~BIT7;

    P2->OUT |= BIT6;

    SysTick_Delay_ms(10);

    P2->OUT &= ~BIT4;

    P2->OUT |= BIT5;

    SysTick_Delay_ms(10);

    P2->OUT &= ~BIT6;

    P2->OUT |= BIT7;

    SysTick_Delay_ms(10);

    P2->OUT &= ~BIT5;



    }

    total = 0;

    RXData = 0;

    RXData2 = 0;

    RXData3 = 0;

}

}

}



void SysTick_Initialize() // these two functions were taken from examples from Prof. Kandalafts Registers_Summary_and_Vectors report

{

    SysTick->CTRL = 0; // clears the control register

    SysTick->LOAD = 0x00FFFFFF; // sets the timer to near the maximum count of 5 seconds

    SysTick->VAL = 0; // clears the value register writing anything to it clears it

    SysTick->CTRL = 0x00000005; // sets up the timer for 3Mhz with no interrupts

}

/*

*  This function is the functions that generates the delay using the system timer. Each time this function is called it takes in a value

*   of the number of milliseconds the delay is going to be set for this is accomplished by multiplying the number passed to the function by 3000

*   and then subtracting that total by 1 for the value and then the function waits for bt 16 of the control register to fkip meaning the timer is done

*   and when its done the program continues.

*/

void SysTick_Delay_ms(uint16_t delayms)

{

    SysTick->LOAD = ((delayms*3000)-1); // sets the timer to the desired value

    SysTick->VAL = 0;   // sets the value register to 0 again

    while((SysTick->CTRL & 0x00010000)==0); // waits for the timer to be done counting

}
