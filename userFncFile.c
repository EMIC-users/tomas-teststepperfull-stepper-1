#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "inc/userFncFile.h"
#include "inc/systemTimer.h"
#include "inc/led_Led1.h"
#include "inc/led_Led2.h"
#include "inc/timer_api1.h"
#include "inc/StepperDriver_Motor.h"
#include "inc/conversionFunctions.h"
#include "inc/EMICBus.h"

/* User Variables */
uint8_t testStep = 0;

void onReset()
{
    pI2C("STEP\tinit");
    LEDs_Led1_state(1);
    testStep = 0;
    setTime1(5000, 'A');
}


void etOut1()
{
    switch (testStep)
    {
        case 0:
            pI2C("STEP\t0-cfg-eighth-400");
            StepperDriver_Motor_setMicrostep(8);
            StepperDriver_Motor_setSpeed(400);
            testStep = 1;
            break;
        case 1:
            pI2C("STEP\t1-moveCW-400");
            StepperDriver_Motor_move(1, 400);
            testStep = 2;
            break;
        case 2:
            pI2C("STEP\t2-moveCCW-400");
            StepperDriver_Motor_move(0, 400);
            testStep = 3;
            break;
        case 3:
            pI2C("STEP\t3-cfg-full-200");
            StepperDriver_Motor_setMicrostep(1);
            StepperDriver_Motor_setSpeed(200);
            testStep = 4;
            break;
        case 4:
            pI2C("STEP\t4-moveCW-200");
            StepperDriver_Motor_move(1, 200);
            testStep = 5;
            break;
        case 5:
            pI2C("STEP\t5-goHome-CCW");
            StepperDriver_Motor_goHome(0);
            testStep = 6;
            break;
        case 6:
            pI2C("STEP\t6-goTo-100");
            StepperDriver_Motor_goTo(100);
            testStep = 7;
            break;
        case 7:
            pI2C("STEP\t7-sleep-ON");
            StepperDriver_Motor_sleep(1);
            LEDs_Led1_blink(100, 400, 3);
            testStep = 8;
            break;
        case 8:
            pI2C("STEP\t8-wake-done");
            StepperDriver_Motor_sleep(0);
            LEDs_Led2_blink(100, 400, 3);
            testStep = 0;
            break;

    }
}


void StepperDriver_Motor_onLimitSwitch()
{
    pI2C("STEP\tlimit-hit");
    LEDs_Led2_state(2);
}



