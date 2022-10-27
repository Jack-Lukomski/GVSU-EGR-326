#include <stdio.h>
#include <stdlib.h>
#include "msp.h"
#include "pinsInint.h"
#include "Toggle.h"
#include "stepperMotor.h"
#include "readInputs.h"

#define PARTONE 1

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



    ST7735_InitR(INITR_BLACKTAB);

    ST7735_FillScreen(ST7735_BLACK);



    P5->SEL0 &= ~(BIT4|BIT5|BIT6);  //set GPIO

    P5->SEL1 &= ~(BIT4|BIT5|BIT6);  //set GPIO

    P5->DIR  &= ~(BIT4|BIT5|BIT6); //set as input

    P5->REN |= (BIT4|BIT5|BIT6); //enable resistors

    P5->OUT |= (BIT4|BIT5|BIT6);



    P4->SEL0 &= ~(BIT4|BIT5|BIT6|BIT7);  //set GPIO

    P4->SEL1 &= ~(BIT4|BIT5|BIT6|BIT7);  //set GPIO

    P4->DIR  &= ~(BIT4|BIT5|BIT6|BIT7); //set as input

    P4->REN |= (BIT4|BIT5|BIT6|BIT7); //enable resistors

    P4->OUT |= (BIT4|BIT5|BIT6|BIT7);

   // P4->IE |= (BIT4|BIT5|BIT6|BIT7);

    //P4->IES |= (BIT4|BIT5|BIT6|BIT7);

    //P4->IFG = 0x00;



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

    //NVIC_EnableIRQ(PORT4_IRQn);

    NVIC_EnableIRQ(EUSCIB0_IRQn);



    __enable_irq();                                 // All interrupts are enabled

    SysTick_Initialize();



  while(1)

  {

      Read_Keypad();



      if (num == 12)

      {

          EUSCI_B0->IE |= EUSCI_B_IE_TXIE0; // Enable EUSCI_A0 TX interrupt

      }

      else if(num == 10){

          TXData = 'B';

          EUSCI_B0->IE |= EUSCI_B_IE_TXIE0; // Enable EUSCI_A0 TX interrupt

      }

      else if(num > 0 && num < 10)

      {

          if(num == 1)TXData = '1';

          else if(num ==2) TXData = '2';

          else if(num ==3) TXData = '3';

          else if(num ==4) TXData = '4';

          else if(num ==5) TXData = '5';

          else if(num ==6) TXData = '6';

          else if(num ==7) TXData = '7';

          else if(num ==8) TXData = '8';

          else if(num ==9) TXData = '9';

          display = num + 48;

          ST7735_DrawCharS(54, 68, display, textColor, color, size);

      }

  }
}



void EUSCIB0_IRQHandler(void)

{

    uint32_t status = EUSCI_B0->IFG; // Get EUSCI_B0 interrupt flag



    EUSCI_B0->IFG &= ~EUSCI_B_IFG_TXIFG0; // Clear EUSCI_B0 TX interrupt flag



    if (status & EUSCI_B_IFG_TXIFG0)

    { // Check if transmit interrupt occurs

        if (num == 10)

        {

            EUSCI_B0->TXBUF = 'B';

            EUSCI_B0->IE &= ~EUSCI_B_IE_TXIE0;

        }

        else

        {

            EUSCI_B0->TXBUF = TXData; // Load current TXData value to transmit buffer

            EUSCI_B0->IE &= ~EUSCI_B_IE_TXIE0;

        }





    } // Disable EUSCI_B0 TX interrupt

}



int Read_Keypad (void)

{

    int h=0, j=0; //counter variables

    int returnVal = -1; //return value variable



    for(h=4; h<=6; h++) //column pins 5.4-5.6

    {

        P5->OUT &= ~(BIT(h));

        P5->DIR |= (BIT(h));



        for(j=4; j<=7; j++)//row pins 4.4-4.7

        {

            if(!(P4->IN & (BIT(j))))

            {

                SysTick_Delay_ms(5);

               if(!(P4->IN & (BIT(j))))

               {

               while(!(P4->IN & (BIT(j))));



               if(j==4)

                   returnVal = h-3;

               if(j==5)

                   returnVal = h;

               if(j==6)

                   returnVal = h+3;

               if(j==7)

                   returnVal = h+6;

               }

            }

        }

        P5->DIR &= ~(BIT(h));

        P5->OUT|= (BIT(h));

    }

if(returnVal==11)

    returnVal=0;



num = returnVal;



return returnVal;

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
#endif
