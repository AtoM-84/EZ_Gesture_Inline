#ifndef GESTURE_BOARD_HAL_LED_H
#define GESTURE_BOARD_HAL_LED_H

#include "animation.h"

class GestureBoardHalLed
{
public:
  GestureBoardHalLed(Animation* defaultAnim);
  //virtual ~GestureBoardHAL();

  //class members
protected:
  Animation* _runningAnimation;
  bool _runningState;
  int _count;
public:
  //GestureBoardHAL methods
  void setAnimation(Animation* anim);
  void start();
  void stop();
  void reset();
  //GestureBoardHAL virtual methods version dependent
  virtual void init() = 0;
  virtual void dim(int value) = 0;
  virtual void set(bool mapping[]) = 0;
  virtual void update() = 0;
};

#endif
