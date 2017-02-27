#ifndef GESTURE_BOARD_HAL_RANGE_V1_1_H
#define GESTURE_BOARD_HAL_RANGE_V1_1_H

#include "GPIOExpanderPCAL6416A.h"
#include "RangeSensorVL6180X.h"

#include "gestureBoardHAL_Range.h"

class GestureBoardHalRange;

#define GPIO_EXPANDER_SENSORS_ADDRESS 0x21

#define SENSOR_0_ADDRESS 0x29
#define SENSOR_1_ADDRESS 0x31
#define SENSOR_2_ADDRESS 0x32
#define SENSOR_3_ADDRESS 0x33
#define SENSOR_4_ADDRESS 0x34
#define SENSOR_5_ADDRESS 0x35

class GestureBoardHalRange_V1_1 : public GestureBoardHalRange {
private:
  GPIO_EXPANDER *_pGPIO;
  RANGE_SENSOR *_pSensor0;
  RANGE_SENSOR *_pSensor1;
  RANGE_SENSOR *_pSensor2;
  RANGE_SENSOR *_pSensor3;
  RANGE_SENSOR *_pSensor4;
  RANGE_SENSOR *_pSensor5;

public:
  uint8_t _range1;
  uint8_t _range2;
  uint8_t _range3;
  uint8_t _range4;
  uint8_t _range5;
  bool _flag1;
  bool _flag2;
  bool _flag3;
  bool _flag4;
  bool _flag5;
  bool _motionDetected;
  bool _alreadyFired;
  unsigned long _timeStamp;

public:
  GestureBoardHalRange_V1_1();
  virtual void setTimeOut(unsigned long timeOut);
  virtual void init();
  virtual void initSensors();
  virtual int* setSensorsXtalkCompensation();
  virtual void assignSensorsAddress();
  virtual void rowMeasurement(int threshold);
  virtual int getMinRangeUnderThreshold(int threshold);
};

#endif
