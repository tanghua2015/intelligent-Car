//*****************************************************************************
// pinmux.c
//
// configure the device pins for different peripheral signals
//
// Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/ 
// 
// 
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//    Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the 
//    documentation and/or other materials provided with the   
//    distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

//*****************************************************************************
// Mod Sun Hanqing
// Project
//  14151 Smart Car Controller
// Description
//  pin mux for the car
// Mod Recs
// 20140909
//  * mod PWM pin mux
//*****************************************************************************
#include "pinmux.h"
#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_gpio.h"
#include "pin.h"
#include "rom.h"
#include "rom_map.h"
#include "gpio.h"
#include "prcm.h"

#include "IO.h"
//#define SENCORS_PINS            SenLeftPin|SenMidPin|SenRightPin|SenObsPin

//*****************************************************************************

extern unsigned int g_uiSenLeftPort,
             g_uiSenRightPort,
             g_uiSenMidPort,
             g_uiSenObsPort;
extern unsigned char g_ucSenLeftPin,
              g_ucSenRightPin,
              g_ucSenMidPin,
              g_ucSenObsPin;

void
PinMuxConfig(void)
{
  //for PWM
  MAP_PRCMPeripheralClkEnable(PRCM_TIMERA2, PRCM_RUN_MODE_CLK);
  MAP_PRCMPeripheralClkEnable(PRCM_TIMERA3, PRCM_RUN_MODE_CLK);
  MAP_PRCMPeripheralClkEnable(PRCM_TIMERA1, PRCM_RUN_MODE_CLK);
  //R1
  MAP_PinTypeTimer(PIN_64, PIN_MODE_3);
  //L2
  MAP_PinTypeTimer(PIN_01, PIN_MODE_3);
  //R2
  MAP_PinTypeTimer(PIN_21, PIN_MODE_9);
  //L1
  MAP_PinTypeTimer(PIN_02, PIN_MODE_3);
  
  //sensor
  //Left
  MAP_PinTypeGPIO(PIN_62, PIN_MODE_0, false);
//  MAP_GPIODirModeSet(g_uiSenLeftPort, g_ucSenLeftPin, GPIO_DIR_MODE_IN);
  //Mid
  MAP_PinTypeGPIO(PIN_05, PIN_MODE_0, false);
//  MAP_GPIODirModeSet(g_uiSenMidPort, g_ucSenMidPin, GPIO_DIR_MODE_IN);
  //right
  MAP_PinTypeGPIO(PIN_59, PIN_MODE_0, false);
//  MAP_GPIODirModeSet(g_uiSenRightPort, g_ucSenRightPin, GPIO_DIR_MODE_IN);
  //Obstacle
  MAP_PinTypeGPIO(PIN_61, PIN_MODE_0, false);
//  MAP_GPIODirModeSet(g_uiSenObsPort, g_ucSenObsPin, GPIO_DIR_MODE_IN);
}
