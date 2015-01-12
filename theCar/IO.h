
#ifndef __IO_H__
#define __IO_H__

#include "GPIO.h"
//PWM
#define TimerLeft_Base1         TIMERA3_BASE
#define TimerLeft1              TIMER_B
#define TimerLeft_Base2         TIMERA3_BASE
#define TimerLeft2              TIMER_A
#define TimerRight_Base1        TIMERA2_BASE
#define TimerRight1             TIMER_B
#define TimerRight_Base2        TIMERA1_BASE
#define TimerRight2             TIMER_A
//sensors
#define SenLeftGPIO             7
#define SenMidGPIO              14
#define SenRightGPIO            4
#define OnRoute                 1
#define _onLeft                 0x18
#define _onRight                0x30
#define _onLeft2                0x08
#define _onRight2               0x20
#define _onEnd                  0x00
#define _onRoute                0x28

#define SenObsGPIO              6
#define IsBlocked               1

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif


//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //  __IO_H__

