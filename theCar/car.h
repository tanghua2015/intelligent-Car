//*****************************************************************************
// car.h
//
//
//*****************************************************************************

#ifndef __CAR_H__
#define __CAR_H__

//#include "IO.h"
//wheels
#define MaxSpeed                14000
#define lrRatio                 1.153 //if left, tune it smaller
#define LoopPerRad              30
#define NormalSpeed             7000
#define _turn                   10
#define _turn2                  35        
//movements
#define BRAKE                   65535
#define STOP                    65534
#define FORWARD                 1
#define BACK                    2
#define RIGHT                   8
#define LEFT                    4


//for PWM
// The PWM works based on the following settings:
//     Timer reload interval -> determines the time period of one cycle
//     Timer match value -> determines the duty cycle 
//                          range [0, timer reload interval]
// The computation of the timer reload interval and dutycycle granularity
// is as described below:
// Timer tick frequency = 80 Mhz = 80000000 cycles/sec
// For a time period of 0.5 ms, 
//      Timer reload interval = 80000000/2000 = 40000 cycles
// To support steps of duty cycle update from [0, 255]
//      duty cycle granularity = ceil(40000/255) = 157
// Based on duty cycle granularity,
//      New Timer reload interval = 255*157 = 40035
//      New time period = 0.5004375 ms
//      Timer match value = (update[0, 255] * duty cycle granularity)
//
#define TIMER_INTERVAL_RELOAD   80070 /* =(255*314) */
#define DUTYCYCLE_GRANULARITY   10 //might be useless!!!!!!!!!!!!!!!!!!!!!!!!

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

#endif //  __GPIOIF_H__

