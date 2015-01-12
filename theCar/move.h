//
//*****************************************************************************

#ifndef __MOVE_H__
#define __MOVE_H__

extern void run(const int LeftSpeed, const int RightSpeed);
extern void moveForward(int speed);
extern void moveBack(int speed);
extern void turnRight(int rad);
extern void turnLeft(int rad);
extern void stop();
extern void brake();

#endif //  __MOVE_H__
