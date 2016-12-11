#include "gestureBoardHAL_ArduinoUNO_V1_1.h"

GestureBoardHal_ArduinoUNO_V1_1::GestureBoardHal_ArduinoUNO_V1_1()
{
  pinMode(CHIP_ENABLE_2_8V, OUTPUT);
  pinMode(GPIO_LED_RESET, OUTPUT);
  pinMode(GPIO_RANGE_SENSORS_RESET,OUTPUT);
  pinMode(LED_PWM_PIN, OUTPUT);
}

void GestureBoardHal_ArduinoUNO_V1_1::init()
{
  digitalWrite(CHIP_ENABLE_2_8V, 1);
  delay(1000);

  digitalWrite(GPIO_LED_RESET, 1);
  digitalWrite(GPIO_RANGE_SENSORS_RESET, 1);

  Wire.begin();
}
