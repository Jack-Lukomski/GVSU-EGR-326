#include "stepperMotor.h"
#include "systick.h"

uint64_t currentStep = 0;

typedef void(*stepCounterFunction_ptr)(port2GPIO_t * s_userPorts_ptr);

static const stepCounterFunction_ptr stepNumber_t[4] =
{
 stepOne,
 stepTwo,
 stepThree,
 stepFour,
};

void vStepperMotor_turnDeg(port2GPIO_t * s_userPorts_ptr, uint16_t numberSteps, stepperMotorDirection_t e_motorDirection, uint32_t delayTime)
{
    if(e_motorDirection == clockwise)
    {
        stepperMotorCW(s_userPorts_ptr, numberSteps, delayTime);
    }
    else if(e_motorDirection == counterclockwise)
    {
        stepperMotorCCW(s_userPorts_ptr, numberSteps);
    }
}

static void stepperMotorCW(port2GPIO_t * s_userPorts_ptr, uint16_t numberSteps, uint32_t delay)
{
    int i = 0;
    int j = 0;
    int k = 0;
    for(j = 0; j < numberSteps; j++)
    {
       for(i = 0; i < 4; i++)
        {
            stepNumber_t[i](s_userPorts_ptr);
//            vSysTick_mSecDelay(delay);
            for(k = 0; k < delay; k++)
            {
                __delay_cycles(48000);          //delay ms for 48mHz
            }

        }
    }
}

static void stepperMotorCCW(port2GPIO_t * s_userPorts_ptr, uint16_t numberSteps)
{
    int i = 3;
    int j = 0;
    for(j = 0; j < numberSteps; j++)
    {
        for(i = 3; i >= 0; i--)
        {
            stepNumber_t[i](s_userPorts_ptr);
            __delay_cycles(40000);
        }
    }
}

static void stepOne(port2GPIO_t * s_userPorts_ptr)
{
    vToggle_turnPinHigh(s_userPorts_ptr[3]);
    vToggle_turnPinHigh(s_userPorts_ptr[2]);
    vToggle_turnPinHigh(s_userPorts_ptr[1]);
    vToggle_turnPinLow(s_userPorts_ptr[0]);
}

static void stepTwo(port2GPIO_t * s_userPorts_ptr)
{
    vToggle_turnPinHigh(s_userPorts_ptr[3]);
    vToggle_turnPinHigh(s_userPorts_ptr[2]);
    vToggle_turnPinHigh(s_userPorts_ptr[0]);
    vToggle_turnPinLow(s_userPorts_ptr[1]);
}

static void stepThree(port2GPIO_t * s_userPorts_ptr)
{
    vToggle_turnPinHigh(s_userPorts_ptr[3]);
    vToggle_turnPinHigh(s_userPorts_ptr[1]);
    vToggle_turnPinHigh(s_userPorts_ptr[0]);
    vToggle_turnPinLow(s_userPorts_ptr[2]);
}

static void stepFour(port2GPIO_t * s_userPorts_ptr)
{
    vToggle_turnPinHigh(s_userPorts_ptr[0]);
    vToggle_turnPinHigh(s_userPorts_ptr[2]);
    vToggle_turnPinHigh(s_userPorts_ptr[1]);
    vToggle_turnPinLow(s_userPorts_ptr[3]);
}

