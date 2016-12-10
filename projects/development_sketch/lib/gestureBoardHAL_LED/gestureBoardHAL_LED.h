#ifndef GESTURE_BOARD_HAL_LED_H
#define GESTURE_BOARD_HAL_LED_H

#include "Arduino.h"

class GestureBoardHalLed;
class Animation;

class Animation
{
public:
    virtual void update(GestureBoardHalLed& parent, int count) = 0;
};

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
    virtual void update(GestureBoardHalLed& parent, int count);
};

class FiveButtons : public Animation
{
  public:
    FiveButtons();
    virtual void update(GestureBoardHalLed& parent, int count);
};

class ThreeButtons : public Animation
{
  public:
    ThreeButtons();
    virtual void update(GestureBoardHalLed& parent, int count);
};

class TwoButtons : public Animation
{
  public:
    TwoButtons();
    virtual void update(GestureBoardHalLed& parent, int count);
};

class OneButton : public Animation
{
  public:
    OneButton();
    virtual void update(GestureBoardHalLed& parent, int count);
};

class SleepModePulse : public Animation
{
  public:
    SleepModePulse();
    virtual void update(GestureBoardHalLed& parent, int count);
};


class GestureBoardHalLed
{
  //class members
  public:
    struct mapping_bf {
      uint16_t  ring3_0 : 1;
      uint16_t  ring3_120 : 1;
      uint16_t  ring3_60 : 1;
      uint16_t  ring4_0 : 1;
      uint16_t  ring4_120 : 1;
      uint16_t  ring4_60 : 1;
      uint16_t  ring5_0 : 1;
      uint16_t  ring5_120 : 1;

      uint16_t  n_a : 1;
      uint16_t  ring2_60 : 1;
      uint16_t  ring2_120 : 1;
      uint16_t  ring2_0 : 1;
      uint16_t  ring1_60 : 1;
      uint16_t  ring1_120 : 1;
      uint16_t  ring1_0 : 1;
      uint16_t  ring5_60 : 1;
    };

    union mappingLed {
      mapping_bf mappingLed_bit;
      uint16_t mappingLed_byte;
    };
protected:
  Animation* _runningAnimation;
  bool _runningState;
  int _count;
  mappingLed _map;
//GestureBoardHAL methods
public:
  GestureBoardHalLed(Animation* defaultAnim);
  void setMapping(mappingLed new_map);
  uint16_t getMapping();
  //virtual ~GestureBoardHAL();
  void setAnimation(Animation* anim);
  void start();
  void stop();
  void reset();
  //GestureBoardHAL virtual methods version dependent
  virtual void init() = 0;
  virtual void dim(int value) = 0;
  virtual void set() = 0;
  virtual void update() = 0;
  static Animation* tabAnimations[];
  static Animation* getAnimation(int idx);
};

#endif
