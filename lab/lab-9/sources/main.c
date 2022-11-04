#include <stdio.h>
#include "msp.h"
#include "stepperMotor.h"
#include "ST7735.h"

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

void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    vpinsInit_GPIO(&motor_ap, pin7, output, pullup, disableInterrupt);
    vpinsInit_GPIO(&motor_a, pin6, output, pullup, disableInterrupt);
    vpinsInit_GPIO(&motor_bp, pin5, output, pullup, disableInterrupt);
    vpinsInit_GPIO(&motor_b, pin4, output, pullup, disableInterrupt);

//    ST7735_InitR(INITR_BLACKTAB);
//    ST7735_FillScreen(ST7735_WHITE);
//
//    ST7735_DrawString(6, 6, "O P E N", ST7735_BLACK);
//    __delay_cycles(30000000);
//    ST7735_FillScreen(ST7735_WHITE);
//    ST7735_DrawString(4, 6, "C L O S E D", ST7735_BLACK);

    while(1)
    {
        vStepperMotor_turnDeg(motorPortPins, 100, counterclockwise);
        vStepperMotor_turnDeg(motorPortPins, 100, clockwise);
    }
}
