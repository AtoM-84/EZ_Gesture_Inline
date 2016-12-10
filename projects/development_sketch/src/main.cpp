#include "Arduino.h"
#include "GestureBoardHAL_V1_1.h"
#include "GestureBoardHAL_COM_V1_1.h"
#include "GestureBoardHAL_LED_V1_1.h"

GestureBoardHal_V1_1* gestureBoardHAL = new GestureBoardHal_V1_1();
GestureBoardHalLedV1_1 gestureBoardLED(GestureBoardHalLedV1_1::getAnimation(0), 500);
GestureBoardHalCom_V1_1 gestureBoardCOM(9600);

void setup()
{
  gestureBoardHAL->init();
  gestureBoardCOM.open();

  gestureBoardLED.setAnimation(GestureBoardHalLedV1_1::getAnimation(1));
  gestureBoardLED.init();
  gestureBoardLED.start();
  //gestureBoardCOM._bufferOut = "toto\r\n";
}

void loop()
{
  gestureBoardLED.update();
  gestureBoardCOM.readMessage();
  gestureBoardCOM.showNewMessage();
  //gestureBoardCOM.sendMessage((char*)gestureBoardCOM._bufferOut, 6);
}
