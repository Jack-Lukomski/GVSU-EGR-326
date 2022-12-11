#include "stepperMotorSam.h"
#include "systick.h"
#include "msp.h"

#define MOTOR_PORT1 P5
#define MOTOR_PORT2 P3
#define PIN1 BIT0
#define PIN2 BIT1
#define PIN3 BIT6
#define PIN4 BIT7


uint64_t currentStep = 0;

typedef void(*stepCounterFunction_ptr)(void);

static const stepCounterFunction_ptr stepNumber_t[4] =
{
 stepOne,
 stepTwo,
 stepThree,
 stepFour,
};

void stepperInit(void)
{
    MOTOR_PORT1->SEL0 &=~ PIN1;
    MOTOR_PORT1->SEL0 &=~ PIN2;
    MOTOR_PORT2->SEL0 &=~ PIN3;
    MOTOR_PORT2->SEL0 &=~ PIN4;
    MOTOR_PORT1->SEL1 &=~ PIN1;
    MOTOR_PORT1->SEL1 &=~ PIN2;
    MOTOR_PORT2->SEL1 &=~ PIN3;
    MOTOR_PORT2->SEL1 &=~ PIN4;

    MOTOR_PORT1->DIR |= PIN1;
    MOTOR_PORT1->DIR |= PIN2;
    MOTOR_PORT2->DIR |= PIN3;
    MOTOR_PORT2->DIR |= PIN4;

    MOTOR_PORT1->OUT &=~ PIN1;
    MOTOR_PORT1->OUT &=~ PIN2;
    MOTOR_PORT2->OUT &=~ PIN3;
    MOTOR_PORT2->OUT &=~ PIN4;
}

void vStepperMotor_turnDeg(uint16_t numberSteps, uint16_t direction, uint32_t delayTime)
{
    if(direction == 1)
    {
        stepperMotorCW(numberSteps, delayTime);
    }
    else if(direction == 0)
    {
        stepperMotorCCW(numberSteps, delayTime);
    }
}

static void stepperMotorCW(uint16_t numberSteps, uint32_t delay)
{
    int i = 0;
    int j = 0;
    int k = 0;
    for(j = 0; j < numberSteps; j++)
    {
       for(i = 0; i < 4; i++)
        {
            stepNumber_t[i]();
//            vSysTick_mSecDelay(delay);
            for(k = 0; k < delay; k++)
            {
                __delay_cycles(48000);          //delay ms for 48mHz
            }

        }
    }
}

static void stepperMotorCCW(uint16_t numberSteps, uint32_t delay)
{
    int i = 3;
    int j = 0;
    int k = 0;
    for(j = 0; j < numberSteps; j++)
    {
        for(i = 3; i >= 0; i--)
        {
            stepNumber_t[i]();
            for(k = 0; k < delay; k++)
            {
                __delay_cycles(48000);          //delay ms for 48mHz
            }
        }
    }
}

static void stepOne(void)
{
//    vToggle_turnPinHigh(s_userPorts_ptr[3]);
//    vToggle_turnPinHigh(s_userPorts_ptr[2]);
//    vToggle_turnPinHigh(s_userPorts_ptr[1]);
//    vToggle_turnPinLow(s_userPorts_ptr[0]);
    MOTOR_PORT1->OUT &=~ PIN1;
    MOTOR_PORT1->OUT |= PIN2;
    MOTOR_PORT2->OUT |= PIN3;
    MOTOR_PORT2->OUT |= PIN4;
}

static void stepTwo(void)
{
//    vToggle_turnPinHigh(s_userPorts_ptr[3]);
//    vToggle_turnPinHigh(s_userPorts_ptr[2]);
//    vToggle_turnPinHigh(s_userPorts_ptr[0]);
//    vToggle_turnPinLow(s_userPorts_ptr[1]);
    MOTOR_PORT1->OUT |= PIN1;
    MOTOR_PORT1->OUT &=~ PIN2;
    MOTOR_PORT2->OUT |= PIN3;
    MOTOR_PORT2->OUT |= PIN4;
}

static void stepThree(void)
{
//    vToggle_turnPinHigh(s_userPorts_ptr[3]);
//    vToggle_turnPinHigh(s_userPorts_ptr[1]);
//    vToggle_turnPinHigh(s_userPorts_ptr[0]);
//    vToggle_turnPinLow(s_userPorts_ptr[2]);
    MOTOR_PORT1->OUT |= PIN1;
    MOTOR_PORT1->OUT |= PIN2;
    MOTOR_PORT2->OUT &=~ PIN3;
    MOTOR_PORT2->OUT |= PIN4;
}

static void stepFour(void)
{
//    vToggle_turnPinHigh(s_userPorts_ptr[0]);
//    vToggle_turnPinHigh(s_userPorts_ptr[2]);
//    vToggle_turnPinHigh(s_userPorts_ptr[1]);
//    vToggle_turnPinLow(s_userPorts_ptr[3]);
    MOTOR_PORT1->OUT |= PIN1;
    MOTOR_PORT1->OUT |= PIN2;
    MOTOR_PORT2->OUT |= PIN3;
    MOTOR_PORT2->OUT &=~ PIN4;
}
