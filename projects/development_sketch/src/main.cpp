#include "Arduino.h"
#include "GestureBoardHAL_LED_V1_1.h"
#include "GestureBoardHAL_V1_1.h"

GestureBoardHal_V1_1* gestureBoardHAL = new GestureBoardHal_V1_1();
GestureBoardHalLedV1_1 gestureBoardLED(GestureBoardHalLedV1_1::getAnimation(0), 500);

void setup()
{
  gestureBoardHAL->init();

  gestureBoardLED.setAnimation(GestureBoardHalLedV1_1::getAnimation(1));
  gestureBoardLED.init();
  gestureBoardLED.start();
}

void loop()
{
  gestureBoardLED.update();
}
