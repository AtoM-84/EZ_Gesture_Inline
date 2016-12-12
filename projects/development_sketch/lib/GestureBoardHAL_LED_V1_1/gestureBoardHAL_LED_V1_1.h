#ifndef GESTURE_BOARD_HAL_LED_V1_1_H
#define GESTURE_BOARD_HAL_LED_V1_1_H

#include "GPIOExpanderPCAL6416A.h"

#include "gestureBoardHAL_LED.h"

#define GPIO_EXPANDER_LED_ADDRESS 0x20

class GestureBoardHalLed_V1_1 : public GestureBoardHalLed
{

private:
  GPIO_EXPANDER* _pGPIO;
  int _lastMillis;
  int _delay;

public:
  GestureBoardHalLed_V1_1(Animation* defaultAnim, int delay);
  virtual void init();
  virtual void dim(int value);
  virtual void set();
  virtual void update();
};

#endif
