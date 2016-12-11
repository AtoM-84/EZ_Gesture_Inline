#include "Arduino.h"
#include "GestureBoardHAL_V1_1.h"
#include "GestureBoardHAL_COM_V1_1.h"
#include "GestureBoardHAL_LED_V1_1.h"

GestureBoardHal_V1_1* gestureBoardHAL = new GestureBoardHal_V1_1();
GestureBoardHalLedV1_1 gestureBoardLED(GestureBoardHalLedV1_1::getAnimation(0), 200);
GestureBoardHalCom_V1_1 gestureBoardCOM(9600);

void setup()
{
  gestureBoardHAL->init();
  gestureBoardCOM.open();
  gestureBoardLED.init();
  gestureBoardLED.setAnimation(GestureBoardHalLedV1_1::getAnimation(2));
    gestureBoardLED.start();
  //gestureBoardCOM._bufferOut = "toto\r\n";
}

void loop()
{
  gestureBoardLED.update();
    gestureBoardCOM.readMessage();
    if(gestureBoardCOM._newMessage){
      gestureBoardCOM.showLastMessage();
      Serial.println(gestureBoardCOM._bufferIn[5]);
      switch(gestureBoardCOM._bufferIn[5])
      {
        case 48:
        gestureBoardLED.stop();
        gestureBoardLED.setAnimation(GestureBoardHalLedV1_1::getAnimation(0));
        gestureBoardLED.start();
        break;
        case 49:
        gestureBoardLED.stop();
        gestureBoardLED.setAnimation(GestureBoardHalLedV1_1::getAnimation(1));
        gestureBoardLED.start();
        break;
        case 50:
        gestureBoardLED.stop();
        gestureBoardLED.setAnimation(GestureBoardHalLedV1_1::getAnimation(2));
        gestureBoardLED.start();
        break;
        case 51:
        gestureBoardLED.stop();
        gestureBoardLED.setAnimation(GestureBoardHalLedV1_1::getAnimation(3));
        gestureBoardLED.start();
        break;
        case 52:
        gestureBoardLED.stop();
        gestureBoardLED.setAnimation(GestureBoardHalLedV1_1::getAnimation(3));
        gestureBoardLED.start();
        break;
        case 53:
        gestureBoardLED.stop();
        gestureBoardLED.setAnimation(GestureBoardHalLedV1_1::getAnimation(4));
        gestureBoardLED.start();
        break;
      }

  }
  //gestureBoardCOM.showLastMessage();
  //gestureBoardCOM.sendMessage((char*)gestureBoardCOM._bufferOut, 6);
}
