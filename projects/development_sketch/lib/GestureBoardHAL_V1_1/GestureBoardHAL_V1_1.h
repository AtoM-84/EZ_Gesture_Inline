#ifndef GESTURE_BOARD_HAL_V1_1_H
#define GESTURE_BOARD_HAL_V1_1_H

#include "Arduino.h"
#include "Wire.h"
#include "GPIOExpanderPCAL6416A.h"
#include "RangeSensorVL6180X.h"

#define GPIO_LED_RESET 4
#define GPIO_RANGE_SENSORS_RESET 5
#define LED_PWM_PIN 6
#define CHIP_ENABLE_2_8V 7

#define SENSOR_0_ADDRESS 0x29
#define SENSOR_1_ADDRESS 0x31
#define SENSOR_2_ADDRESS 0x32
#define SENSOR_3_ADDRESS 0x33
#define SENSOR_4_ADDRESS 0x34
#define SENSOR_5_ADDRESS 0x35

class GestureBoardHal_V1_1
{
public:
  GestureBoardHal_V1_1();
  void init();
};

#endif
