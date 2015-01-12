//*****************************************************************************
// Author Sun Hanqing
// Project
//  14151 Smart Car Controller
// Description
//  let PWM drive the car
// Mod Recs
// 20140905
//  * init
//  * add speed calculating, run & move functions
// 20140909
//  * add move.h
//  * add turn & stop functions
// 20140910
//  * add move function
//*****************************************************************************

#include <stdio.h>
#include "hw_types.h"
#include "interrupt.h"
#include "hw_ints.h"
#include "pin.h"
#include "hw_apps_rcm.h"
#include "hw_common_reg.h"
#include "prcm.h"
#include "rom.h"
#include "rom_map.h"
#include "hw_memmap.h"
#include "timer.h"
#include "utils.h"
#include "timer_if.h"
#include "gpio_if.h"

#include "IO.h"
#include "car.h"
#include "move.h"

void calcSpeed(int speed, int dualSpeed[])
{//make the car run straight ahead
  if(lrRatio<=1.0)
  {//left is faster
    if(speed>MaxSpeed)
    {
      speed=MaxSpeed;
    }
    dualSpeed[0]=(int)speed;
    dualSpeed[1]=(int)(lrRatio*speed);
  }
  else
  {//right is faster
    if(speed>MaxSpeed)
    {
      speed=MaxSpeed;
    }
    dualSpeed[0]=(int)(speed/lrRatio);
    dualSpeed[1]=(int)speed;
  }

}

//****************************************************************************
//
//! Update the dutycycle of the PWM timer
//!
//! \param ulBase is the base address of the timer to be configured
//! \param ulTimer is the timer to be setup (TIMER_A or  TIMER_B)
//! \param ucLevel translates to duty cycle settings (0:255)
//! 
//! This function  
//!    1. The specified timer is setup to operate as PWM
//!
//! \return None.
//
//****************************************************************************
void UpdateDutyCycle(unsigned long ulBase,
                     unsigned long ulTimer,
                     unsigned char ucLevel)
{
    //
    // Match value is updated to reflect the new dutycycle settings
    //
    MAP_TimerMatchSet(ulBase,ulTimer,(ucLevel*DUTYCYCLE_GRANULARITY));
}

void _run(unsigned long ulBase1, unsigned long ulTimer1, 
         unsigned long ulBase2, unsigned long ulTimer2,
         int ucLevel)
{
  switch(ucLevel)
  {
  case BRAKE:
    MAP_TimerMatchSet(ulBase1,ulTimer1,MaxSpeed);
    MAP_TimerMatchSet(ulBase2,ulTimer2,MaxSpeed);
    break;
  case STOP:
    MAP_TimerMatchSet(ulBase1,ulTimer1,0);
    MAP_TimerMatchSet(ulBase2,ulTimer2,0);
    break;
  default:
    if(ucLevel>0)
    {
      MAP_TimerMatchSet(ulBase1,ulTimer1,ucLevel);
      MAP_TimerMatchSet(ulBase2,ulTimer2,0);
    }
    else if(ucLevel<0)
    {
      MAP_TimerMatchSet(ulBase1,ulTimer1,0);
      MAP_TimerMatchSet(ulBase2,ulTimer2,-ucLevel);
    }
    else return;
  }
}

void run(const int LeftSpeed, const int RightSpeed)
{
  int dualSpeed[2];
  calcSpeed(MaxSpeed, dualSpeed);
  _run(TimerLeft_Base1, TimerLeft1, TimerLeft_Base2, TimerLeft2, dualSpeed[0]);
  _run(TimerRight_Base1, TimerRight1, TimerRight_Base2, TimerRight2, dualSpeed[1]);  
  MAP_UtilsDelay(50000);
  _run(TimerLeft_Base1, TimerLeft1, TimerLeft_Base2, TimerLeft2, LeftSpeed);
  _run(TimerRight_Base1, TimerRight1, TimerRight_Base2, TimerRight2, RightSpeed);  
}

void moveForward(int speed)
{
  int dualSpeed[2];
  calcSpeed(speed, dualSpeed);
  run(dualSpeed[0], dualSpeed[1]);
//  run(TimerLeft_Base1, TimerLeft1, TimerLeft_Base2, TimerLeft2, dualSpeed[0]);
//  run(TimerRight_Base1, TimerRight1, TimerRight_Base2, TimerRight2, dualSpeed[1]);
}

void moveBack(int speed)
{
  int dualSpeed[2];
  calcSpeed(speed, dualSpeed);
  run(-dualSpeed[0], -dualSpeed[1]);
//  run(TimerLeft_Base1, TimerLeft1, TimerLeft_Base2, TimerLeft2, -dualSpeed[0]);
//  run(TimerRight_Base1, TimerRight1, TimerRight_Base2, TimerRight2, -dualSpeed[1]);
}

void turnLeft(int rad)
{
//  brake();
  int speed;
  speed = NormalSpeed;
  int dualSpeed[2];
  calcSpeed(speed, dualSpeed);
  if(rad>0)
  {
    run(-dualSpeed[0], dualSpeed[1]);
//    run(TimerLeft_Base1, TimerLeft1, TimerLeft_Base2, TimerLeft2, -dualSpeed[0]);
//    run(TimerRight_Base1, TimerRight1, TimerRight_Base2, TimerRight2, dualSpeed[1]);
//    MAP_UtilsDelay((int)(rad*LoopPerRad));
  }
  else if(rad<0)
  {
    run(dualSpeed[0], -dualSpeed[1]);
//    run(TimerLeft_Base1, TimerLeft1, TimerLeft_Base2, TimerLeft2, dualSpeed[0]);
//    run(TimerRight_Base1, TimerRight1, TimerRight_Base2, TimerRight2, -dualSpeed[1]);
//    MAP_UtilsDelay((int)(-rad*LoopPerRad));
  }
//  brake();
}

void turnRight(int rad)
{
  turnLeft(-rad);
}

void brake()
{
  run(BRAKE, BRAKE);
//  run(TimerLeft_Base1, TimerLeft1, TimerLeft_Base2, TimerLeft2, dualSpeed[0]);
//  run(TimerRight_Base1, TimerRight1, TimerRight_Base2, TimerRight2, dualSpeed[1]);  
}

void stop()
{
  run(STOP, STOP);
//  run(TimerLeft_Base1, TimerLeft1, TimerLeft_Base2, TimerLeft2, dualSpeed[0]);
//  run(TimerRight_Base1, TimerRight1, TimerRight_Base2, TimerRight2, dualSpeed[1]);  
}

