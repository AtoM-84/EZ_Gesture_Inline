#ifndef GESTURE_BOARD_HAL_LED_V1_1_H
#define GESTURE_BOARD_HAL_LED_V1_1_H

#include "gestureBoardHAL_V1_1.h"
#include "gestureBoardHAL_LED.h"

class GestureBoardHalLedV1_1 : public GestureBoardHalLed
{

private:
  GPIO_EXPANDER* _pGPIO;
  int _lastMillis;
  int _delay;

public:
  GestureBoardHalLedV1_1(Animation* defaultAnim, int delay);
  virtual void init();
  virtual void dim(int value);
  virtual void set();
  virtual void update();
};

#endif
