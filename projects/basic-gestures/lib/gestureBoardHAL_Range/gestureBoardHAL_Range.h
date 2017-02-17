#ifndef GESTURE_BOARD_HAL_RANGE_H
#define GESTURE_BOARD_HAL_RANGE_H

#include "Arduino.h"

class GestureBoardHalRange {
protected:
  int _delay;
  uint8_t _convergenceTime;

public:
  unsigned long _timeOut;
  GestureBoardHalRange();
  virtual void setTimeOut(unsigned long timeOut) = 0;
  virtual void init() = 0;
  virtual void initSensors() = 0;
  virtual void assignSensorsAddress() = 0;
  virtual void rowMeasurement() = 0;
};

#endif
