#include "Arduino.h"
#include "GestureBoardHAL_ArduinoUNO_V1_1.h"
#include "GestureBoardHAL_COM_V1_1.h"
#include "GestureBoardHAL_LED_V1_1.h"
#include "GestureBoardHAL_Range_V1_1.h"

GestureBoardHal_ArduinoUNO_V1_1* gestureBoardHAL = new GestureBoardHal_ArduinoUNO_V1_1();
GestureBoardHalCom_V1_1* gestureBoardCOM = new GestureBoardHalCom_V1_1(115200);
GestureBoardHalLed_V1_1* gestureBoardLED = new GestureBoardHalLed_V1_1(GestureBoardHalLed_V1_1::getAnimation(0), 150);
GestureBoardHalRange_V1_1* gestureBoardRange = new GestureBoardHalRange_V1_1();


void setup()
{
  gestureBoardHAL->init();
  gestureBoardCOM->open();
  gestureBoardLED->init();
  gestureBoardRange->init();
  gestureBoardLED->setAnimation(GestureBoardHalLed_V1_1::getAnimation(2));
  gestureBoardLED->start();
  //gestureBoardCOM._bufferOut = "toto\r\n";
}

void loop()
{
  gestureBoardLED->update();
    gestureBoardCOM->readMessage();
    if(gestureBoardCOM->_newMessage){
      gestureBoardCOM->showLastMessage();
      //Serial.println(gestureBoardCOM->_bufferIn[5]);
    switch(gestureBoardCOM->_bufferIn[5])
      {
        case 48:
        gestureBoardLED->stop();
        gestureBoardLED->setAnimation(GestureBoardHalLed_V1_1::getAnimation(0));
        gestureBoardLED->start();
        break;
        case 49:
        gestureBoardLED->stop();
        gestureBoardLED->setAnimation(GestureBoardHalLed_V1_1::getAnimation(1));
        gestureBoardLED->start();
        break;
        case 50:
        gestureBoardLED->stop();
        gestureBoardLED->setAnimation(GestureBoardHalLed_V1_1::getAnimation(2));
        gestureBoardLED->start();
        break;
        case 51:
        gestureBoardLED->stop();
        gestureBoardLED->setAnimation(GestureBoardHalLed_V1_1::getAnimation(3));
        gestureBoardLED->start();
        break;
        case 52:
        gestureBoardLED->stop();
        gestureBoardLED->setAnimation(GestureBoardHalLed_V1_1::getAnimation(3));
        gestureBoardLED->start();
        break;
        case 53:
        gestureBoardLED->stop();
        gestureBoardLED->setAnimation(GestureBoardHalLed_V1_1::getAnimation(4));
        gestureBoardLED->start();
        break;
      }

  }
  gestureBoardRange->rowMeasurement();
  Serial.print(gestureBoardRange->_range1,DEC);
  Serial.print(" | ");
  Serial.print(gestureBoardRange->_range2,DEC);
  Serial.print(" | ");
  Serial.print(gestureBoardRange->_range3,DEC);
  Serial.print(" | ");
  Serial.print(gestureBoardRange->_range4,DEC);
  Serial.print(" | ");
  Serial.println(gestureBoardRange->_range5,DEC);
  //gestureBoardCOM.showLastMessage();
  //gestureBoardCOM.sendMessage((char*)gestureBoardCOM._bufferOut, 6);
}
