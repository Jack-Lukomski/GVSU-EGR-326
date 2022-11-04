#include <stdint.h>
#include <stdbool.h>
#include <msp.h>
#include <stdio.h>
#include "stepperMotor.h"
#include "ST7735.h"
#include "clk48MHz.h"
#include "GPIO_Interrupt.h"
#include "timer32.h"

port2GPIO_t motor_a;
port2GPIO_t motor_b;
port2GPIO_t motor_ap;
port2GPIO_t motor_bp;

static const port2GPIO_t motorPortPins[4] =
{
 {.e_GPIOType = pullup, .e_IO = output, .e_IOpinNumber = pin4, .e_Interrupt = disableInterrupt}, // A
 {.e_GPIOType = pullup, .e_IO = output, .e_IOpinNumber = pin5, .e_Interrupt = disableInterrupt}, // B
 {.e_GPIOType = pullup, .e_IO = output, .e_IOpinNumber = pin6, .e_Interrupt = disableInterrupt}, // Ap
 {.e_GPIOType = pullup, .e_IO = output, .e_IOpinNumber = pin7, .e_Interrupt = disableInterrupt}, // Bp
};


uint32_t time;
int key;
bool hall;
double rpm;

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    vpinsInit_GPIO(&motor_ap, pin7, output, pullup, disableInterrupt);
    vpinsInit_GPIO(&motor_a, pin6, output, pullup, disableInterrupt);
    vpinsInit_GPIO(&motor_bp, pin5, output, pullup, disableInterrupt);
    vpinsInit_GPIO(&motor_b, pin4, output, pullup, disableInterrupt);


    vSysTick_Init();
    vHall_effect_pinsInit();
    vMain_Initlize48MHz();
    vTimer32_init();
    NVIC->ISER[1] = 1 << ((PORT5_IRQn) & 31);
    __enable_interrupt();

//    ST7735_InitR(INITR_BLACKTAB);
//    ST7735_FillScreen(ST7735_WHITE);
//
//    ST7735_DrawString(6, 6, "O P E N", ST7735_BLACK);
//    __delay_cycles(30000000);
//    ST7735_FillScreen(ST7735_WHITE);
//    ST7735_DrawString(4, 6, "C L O S E D", ST7735_BLACK);
//
    puts("\nEnter a number 0 through 5 \n");
//    scanf("%d", &key);

    while(1)
    {
        scanf("%d", key);
        if(key==5)
            time = 50;
        else
            time = 500 - key*100;
        vStepperMotor_turnDeg(motorPortPins, 1, clockwise, time);
    }
}


void PORT5_IRQHandler(void){
    if(P5->IFG & BIT6){
//        if(~(P5->IN & BIT6))
//        {
            hall ^= 1;
            rpm = 60.0 / ((0xffffffff - (TIMER32_1 -> VALUE))/ 48000000.0);
            TIMER32_1 -> LOAD = 0XFFFFFFFF;
//        }
//        }
    }
    P5->IFG &= ~(BIT6);
}
