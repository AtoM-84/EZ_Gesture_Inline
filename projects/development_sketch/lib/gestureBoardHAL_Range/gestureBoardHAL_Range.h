#ifndef GESTURE_BOARD_HAL_RANGE_H
#define GESTURE_BOARD_HAL_RANGE_H

#include "Arduino.h"

class GestureBoardHalRange
{
protected:
  int _timeOut;
  int _delay;
  uint8_t _convergenceTime;

public:
  GestureBoardHalRange();
  virtual void init() = 0;
  virtual void initSensors() = 0;
  virtual void assignSensorsAddress() = 0;
  virtual void rowMeasurement() = 0;
};

#endif
