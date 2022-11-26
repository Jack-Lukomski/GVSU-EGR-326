
// P5.5 -> A0
// using mem[0] and MCTL[0]



#include "msp.h"
#include "stdio.h"
#include "ADC.h"
#include "SysTickTimer.h"
#include "stdint.h"
#include "clk48MHz.h"
//#include "ST7735.h"

#define PWM_Period 60000
#define resetSet 0xE0
#define SMCLK 0x200
#define countUp 0x10
#define timerAClear 0x4

    float ADCvoltage;
    uint16_t ADCval;
    int lightVal;

    void PWM_set(int duty);
    void PWM_init(void);

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watch dog timer
    vMain_Initlize48MHz();
    ADC_port_init();
    ADC_init();
    SysTick_init();
    PWM_init();

//    volatile uint16_t dutyperiod = dutyCycle * PWM_Period;

//    ST7735_InitR(INITR_GREENTAB);
//    ST7735_FillScreen(ST7735_WHITE);

//    char c = '1';
//
//    ST7735_DrawCharS(6, 6, c, ST7735_BLACK, ST7735_WHITE, 2);




    while(1){
        ADC14->CTL0 |= ADC14_CTL0_SC;        //start conversation   auto-reset
        while ( !ADC14->IFGR0 & BIT0 );     //wait for conversation to complete
        ADCval = ADC14->MEM[0];              // get the value from the ADC using A0
        ADCvoltage = (ADCval * 3.3) / 16384;
        lightVal =  (ADCvoltage-0.5) * (10/3)  ;
        printf("14 bit value is: %d \n\t ADC voltage: %f \n\t", ADCval, ADCvoltage );
//        ST7735_DrawString(7, 6, "L C D", ST7735_BLACK);
        SysTickTimer_ms(100);                  // SysTick delay for 2 seconds
        PWM_set(lightVal*10);

    }


}

void PWM_init(void){

    P2->SEL0 |=  BIT7;
    P2->SEL1 &=~ BIT7;
    P2->DIR  |=  BIT7;
    TIMER_A0->CCR[0] = PWM_Period;
    TIMER_A0->CCTL[4] = resetSet;
    TIMER_A0->CTL = (SMCLK | countUp | timerAClear);
    TIMER_A0->CTL |= 0x80;
}

void PWM_set(int duty){
    volatile uint16_t dutyperiod = duty * PWM_Period/100;
    TIMER_A0->CCR[4] = dutyperiod;
}
