
#ifndef GESTURE_BOARD_LED_H
#define GESTURE_BOARD_LED_H

#include "GPIOExpanderPCAL6416A.h"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class GestureBoardLED;
class Animation;
class SwipeLeft;

class Animation
{
  public:
    virtual void update(GestureBoardLED& parent, int count);
};

class SwipeLeft : public Animation
{
  public:
    SwipeLeft();
    virtual void update(GestureBoardLED& parent, int count);
};

class SwipeRight : public Animation
{
  public:
    SwipeRight();
    virtual void update(GestureBoardLED &parent, int count);
};

class FiveButtons : public Animation
{
  public:
    FiveButtons();
    virtual void update(GestureBoardLED &parent, int count);
};

class ThreeButtons : public Animation
{
  public:
    ThreeButtons();
    virtual void update(GestureBoardLED &parent, int count);
};

class TwoButtons : public Animation
{
  public:
    TwoButtons();
    virtual void update(GestureBoardLED &parent, int count);
};

class OneButton : public Animation
{
  public:
    OneButton();
    virtual void update(GestureBoardLED &parent, int count);
};

class SleepModePulse : public Animation
{
  public:
    SleepModePulse();
    virtual void update(GestureBoardLED &parent, int count);
};

class GestureBoardLED
{
  private:
  static Animation* tabAnimations[];
  public:
    //class members
    GPIO_EXPANDER& _GPIO;
    Animation* _runningAnimation;
    bool _runningState;
    int _count;
    int _lastMillis;
    int _delay;


    //constructor
    GestureBoardLED(GPIO_EXPANDER& gpio, Animation* defaultAnimation, int delay);
    //methods
    void init();
    void setAnimation(Animation* anim);
    void update();
    void start();
    void stop();
    void reset();
    static Animation* getAnimation(int idx);
};

#endif