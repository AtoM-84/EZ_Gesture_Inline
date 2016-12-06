#ifndef ANIMATION_H
#define ANIMATION_H

#include "gestureBoardHAL_LED.h"

class Animation
{
  public:
    virtual void update(GestureBoardHalLed& parent, int count) = 0;
};

#endif
