#ifndef GESTURE_BOARD_HAL_ARDUINOUNO_V1_1_H
#define GESTURE_BOARD_HAL_ARDUINOUNO_V1_1_H

#include "Arduino.h"
#include "Wire.h"

#define GPIO_LED_RESET 4
#define GPIO_RANGE_SENSORS_RESET 5
#define LED_PWM_PIN 6
#define CHIP_ENABLE_2_8V 7

class GestureBoardHal_ArduinoUNO_V1_1 {
public:
  GestureBoardHal_ArduinoUNO_V1_1();
  void init();
};

#endif
