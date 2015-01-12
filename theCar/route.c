//*****************************************************************************
// Author Sun Hanqing
// Project
//  14151 Smart Car Controller
// Description
//  find her way with sensors' help
// Mod Recs
// 20140909
//  * init
// 20140910
//  * 
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

#include "car.h"
#include "IO.h"
#include "route.h"
#include "move.h"

extern unsigned int  g_uiSenLeftPort,
                     g_uiSenRightPort,
                     g_uiSenMidPort,
                     g_uiSenObsPort;
extern unsigned char g_ucSenLeftPin,
                     g_ucSenRightPin,
                     g_ucSenMidPin,
                     g_ucSenObsPin;

typedef struct PosStatus
{
  unsigned char Left;
  unsigned char Mid;
  unsigned char Right;
  unsigned char Obs;
}PosStatus;

int lastStatus;

int isOnLeft(PosStatus status){if((status.Left == OnRoute) && (status.Mid!=OnRoute) && (status.Right!=OnRoute))return 1;else return 0;}
int isOnRight(PosStatus status){if((status.Left != OnRoute) && (status.Mid!=OnRoute) && (status.Right==OnRoute))return 1;else return 0;}
int isOnLeft2(PosStatus status){if((status.Left == OnRoute) && (status.Mid==OnRoute) && (status.Right!=OnRoute))return 1;else return 0;}
int isOnRight2(PosStatus status){if((status.Left != OnRoute) && (status.Mid==OnRoute) && (status.Right==OnRoute))return 1;else return 0;}
int isOnRoute(PosStatus status){if((status.Left != OnRoute) && (status.Mid==OnRoute) && (status.Right!=OnRoute))return 1;else return 0;}
int isOnEnd(PosStatus status){if((status.Left == OnRoute) && (status.Right==OnRoute))return 1;else return 0;}

void route( )
{
//  if(GPIOPinRead(SenBase,SenObstaclePin))return;
//  int status;
//  status=GPIOPinRead(SenBase,SenLeftPin|SenMidPin|SenRightPin);
  PosStatus status;
  status.Left=GPIO_IF_Get(SenLeftGPIO, g_uiSenLeftPort, g_ucSenLeftPin);
  status.Mid=GPIO_IF_Get(SenMidGPIO, g_uiSenMidPort, g_ucSenMidPin);
  status.Right=GPIO_IF_Get(SenRightGPIO, g_uiSenRightPort, g_ucSenRightPin);
  status.Obs=GPIO_IF_Get(SenObsGPIO, g_uiSenObsPort, g_ucSenObsPin);
//debug
//  if(status.Left == OnRoute){moveForward(9000);return;}
//  else{moveBack(9000);return;}
  int allStatus = 0x01;
  if(isOnLeft(status)) 
    allStatus=_onLeft;
  if( isOnRight(status) ) 
    allStatus=_onRight;
  if(isOnLeft2(status))
    allStatus=_onLeft2;
  if(isOnRight2(status))
    allStatus=_onRight2;
  if(isOnEnd(status)) 
    allStatus=_onEnd;
  if(isOnRoute(status))
    allStatus=_onRoute;
  switch (allStatus)
  {
  case _onLeft:
    turnLeft(_turn);
//    moveForward(NormalSpeed);
    lastStatus = allStatus;
    break;
  case _onLeft2:
    lastStatus = allStatus;
    turnLeft(_turn2);
//    moveForward(NormalSpeed);
    break;
  case _onRight:
    turnRight(_turn);
    lastStatus = allStatus;
//    moveForward(NormalSpeed);
    break;
  case _onRight2:
    turnRight(_turn2);
    lastStatus = allStatus;
//    moveForward(NormalSpeed);
    break;
  case _onEnd:
    brake();
    lastStatus = allStatus;
    break;
  case _onRoute:
    moveForward(NormalSpeed);
    break;
  default:
//    switch(lastStatus)
//    {
//    case _onLeft:
//      turnRight(_turn);
////      moveForward(NormalSpeed);
//      break;
//    case _onRight:
//      turnLeft(_turn);
////      moveForward(NormalSpeed);
//      break;
//    case _onLeft2:
//      turnRight(_turn2);
////      moveForward(NormalSpeed);
//      break;
//    case _onRight2:
//      turnLeft(_turn2);
////      moveForward(NormalSpeed);
//      break;
//    case _onEnd:
//      brake();
//      break;
//    default:
//      moveBack(NormalSpeed);
//      break;
//    }
//    MAP_UtilsDelay(1000000);
    break;
  }  
}