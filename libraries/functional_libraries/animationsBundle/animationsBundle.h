#ifndef ANIMATIONS_BUNDLE_H
#define ANIMATIONS_BUNDLE_H

#include "animation.h"

class SwipeLeft : public Animation
{
  public:
    SwipeLeft();
    virtual void update(GestureBoardHalLed& parent, int count);
};

class SwipeRight : public Animation
{
  public:
    SwipeRight();
    virtual void update(GestureBoardHalLed &parent, int count);
};

class FiveButtons : public Animation
{
  public:
    FiveButtons();
    virtual void update(GestureBoardHalLed &parent, int count);
};

class ThreeButtons : public Animation
{
  public:
    ThreeButtons();
    virtual void update(GestureBoardHalLed &parent, int count);
};

class TwoButtons : public Animation
{
  public:
    TwoButtons();
    virtual void update(GestureBoardHalLed &parent, int count);
};

class OneButton : public Animation
{
  public:
    OneButton();
    virtual void update(GestureBoardHalLed &parent, int count);
};

class SleepModePulse : public Animation
{
  public:
    SleepModePulse();
    virtual void update(GestureBoardHalLed &parent, int count);
};

#endif
