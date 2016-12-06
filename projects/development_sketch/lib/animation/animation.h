#ifndef ANIMATION_H
#define ANIMATION_H

#include "gestureBoardHAL_LED.h"

class Animation
{
    virtual void update(const GestureBoardHalLed& parent, const int count) = 0;
};

#endif
