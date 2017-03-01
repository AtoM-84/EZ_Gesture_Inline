#include "Arduino.h"
#include "GestureBoardHAL_ArduinoUNO_V1_1.h"
#include "GestureBoardHAL_COM_V1_1.h"
#include "GestureBoardHAL_LED_V1_1.h"
#include "GestureBoardHAL_Range_V1_1.h"

GestureBoardHal_ArduinoUNO_V1_1 *gestureBoardHAL =
    new GestureBoardHal_ArduinoUNO_V1_1();
GestureBoardHalCom_V1_1 *gestureBoardCOM = new GestureBoardHalCom_V1_1(115200);
GestureBoardHalLed_V1_1 *gestureBoardLED =
    new GestureBoardHalLed_V1_1(GestureBoardHalLed_V1_1::getAnimation(0), 100);
GestureBoardHalRange_V1_1 *gestureBoardRange = new GestureBoardHalRange_V1_1();


// click button variables
unsigned long pwmValue;
unsigned long timeElapsed;
bool overOffDone = false;
int overValue;

// swipe variables
bool swipeRightOn = false;
int swipeRightCounter = 0;
int swipeRightTimer = millis();
int swipeRightArray[5];

// swipe variables
bool swipeLeftOn = false;
int swipeLeftCounter = 0;
int swipeLeftTimer = millis();
int swipeLeftArray[5];

void setup() {
  gestureBoardHAL->init();
  gestureBoardCOM->open();
  gestureBoardLED->init();
  gestureBoardRange->init();
  gestureBoardLED->setAnimation(GestureBoardHalLed_V1_1::getAnimation(2));
  gestureBoardLED->start();
  gestureBoardRange->setTimeOut(600);
}

void loop() {
  gestureBoardLED->update();
  gestureBoardCOM->readMessage();
  if (gestureBoardCOM->_newMessage) {
    gestureBoardCOM->showLastMessage();
    switch (gestureBoardCOM->_bufferIn[5]) {
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
      gestureBoardLED->setAnimation(GestureBoardHalLed_V1_1::getAnimation(4));
      gestureBoardLED->start();
      break;
    case 53:
      gestureBoardLED->stop();
      gestureBoardLED->setAnimation(GestureBoardHalLed_V1_1::getAnimation(5));
      gestureBoardLED->start();
      break;
    }
  }
  gestureBoardRange->rowMeasurement(150);

  if (swipeRightOn == true)
  {
    int swipeRightTimerElapsed = millis() - swipeRightTimer;
    if (swipeRightTimerElapsed > 250)
    {
      swipeRightOn = false;
      swipeRightCounter = 0;
      Serial.println("restart swipe timer");
    }
    else if ((swipeRightTimerElapsed < 250) && (swipeRightCounter >= 2))
    {
      if((swipeRightArray[0] < swipeRightArray[1]) && (swipeRightArray[1] < swipeRightArray[2]) && (!gestureBoardRange->_flag1 && !gestureBoardRange->_flag2 &&
          !gestureBoardRange->_flag3 && !gestureBoardRange->_flag4 && !gestureBoardRange->_flag5))
      {
        swipeRightOn = false;
        swipeRightCounter = 0;
        gestureBoardCOM->sendMessage("<swipe_right>", 13);
        Serial.print("[");
        Serial.print(swipeRightArray[0]);
        Serial.print(",");
        Serial.print(swipeRightArray[1]);
        Serial.print(",");
        Serial.print(swipeRightArray[2]);
        Serial.println("]");
        gestureBoardLED->stop();
        gestureBoardLED->setAnimation(GestureBoardHalLed_V1_1::getAnimation(0));
        gestureBoardLED->start();
      }
    }
  }

  if (swipeLeftOn == true)
  {
    int swipeLeftTimerElapsed = millis() - swipeLeftTimer;
    if (swipeLeftTimerElapsed > 250)
    {
      swipeLeftOn = false;
      swipeLeftCounter = 0;
      Serial.println("restart swipe timer");
    }
    else if ((swipeLeftTimerElapsed < 250) && (swipeLeftCounter >= 2))
    {
      if((swipeLeftArray[0] > swipeLeftArray[1]) && (swipeLeftArray[1] > swipeLeftArray[2]) && (!gestureBoardRange->_flag1 && !gestureBoardRange->_flag2 &&
          !gestureBoardRange->_flag3 && !gestureBoardRange->_flag4 && !gestureBoardRange->_flag5))
      {
        swipeLeftOn = false;
        swipeLeftCounter = 0;
        gestureBoardCOM->sendMessage("<swipe_left>", 12);
        Serial.print("[");
        Serial.print(swipeLeftArray[0]);
        Serial.print(",");
        Serial.print(swipeLeftArray[1]);
        Serial.print(",");
        Serial.print(swipeLeftArray[2]);
        Serial.println("]");
        gestureBoardLED->stop();
        gestureBoardLED->setAnimation(GestureBoardHalLed_V1_1::getAnimation(1));
        gestureBoardLED->start();
      }
    }
  }

  // nouvelle partie du code
  if (gestureBoardRange->_motionDetected) {
    if (gestureBoardRange->_flag1 && !gestureBoardRange->_flag2 &&
        !gestureBoardRange->_flag3 && !gestureBoardRange->_flag4 &&
        !gestureBoardRange->_flag5) { // hover sensor 1
      if (!gestureBoardRange->_alreadyFired) {
        if (gestureBoardRange->_timeStamp == 0) {
          GestureBoardHalLed_V1_1::mappingLed mapping1;
          mapping1.mappingLed_byte = 0;
          mapping1.mappingLed_bit.ring1_0 = 1;
          mapping1.mappingLed_bit.ring1_60 = 1;
          mapping1.mappingLed_bit.ring1_120 = 1;

          gestureBoardLED->stop();
          gestureBoardLED->reset();
          gestureBoardLED->setMapping(mapping1);
          gestureBoardLED->set();
          gestureBoardLED->dim(255);

          gestureBoardCOM->sendMessage("<overOn_1>", 10);
          overValue = 1;
          gestureBoardRange->_timeStamp = millis();

          if (swipeRightOn == false)
          {
            swipeRightOn = true;
            swipeRightCounter = 0;
            swipeRightTimer = millis();
            swipeRightArray[swipeRightCounter] = overValue;
            Serial.print("swipe start :");
            Serial.println(swipeRightArray[swipeRightCounter]);
          }

          if (swipeLeftOn == true)
          {
            swipeLeftCounter +=1;
            swipeLeftArray[swipeLeftCounter] = overValue;
            swipeLeftTimer = millis();
            Serial.print("swipe continue :");
            Serial.println(swipeLeftArray[swipeLeftCounter]);
          }

        } else {
          timeElapsed = millis() - gestureBoardRange->_timeStamp;
          if (timeElapsed > gestureBoardRange->_timeOut) {
            gestureBoardCOM->sendMessage("<click_1>", 9);
            gestureBoardRange->_alreadyFired = true;
            gestureBoardLED->blinker(100);
          } else {
            pwmValue =
                255 *
                (1 - ((float)timeElapsed / (float)gestureBoardRange->_timeOut));
            gestureBoardLED->dim((int)pwmValue);
          }
        }
      } else {
        gestureBoardLED->stop();
        gestureBoardLED->setAnimation(GestureBoardHalLed_V1_1::getAnimation(2));
      }
    } else if (!gestureBoardRange->_flag1 && gestureBoardRange->_flag2 &&
               !gestureBoardRange->_flag3 && !gestureBoardRange->_flag4 &&
               !gestureBoardRange->_flag5) { // hover sensor 2
      if (!gestureBoardRange->_alreadyFired) {
        if (gestureBoardRange->_timeStamp == 0) {
          GestureBoardHalLed_V1_1::mappingLed mapping2;
          mapping2.mappingLed_byte = 0;
          mapping2.mappingLed_bit.ring2_0 = 1;
          mapping2.mappingLed_bit.ring2_60 = 1;
          mapping2.mappingLed_bit.ring2_120 = 1;

          gestureBoardLED->stop();
          gestureBoardLED->reset();
          gestureBoardLED->setMapping(mapping2);
          gestureBoardLED->set();
          gestureBoardLED->dim(255);

          gestureBoardCOM->sendMessage("<overOn_2>", 10);
          overValue = 2;

          if (swipeRightOn == true)
          {
            swipeRightCounter +=1;
            swipeRightArray[swipeRightCounter] = overValue;
            swipeRightTimer = millis();
            Serial.print("swipe continue :");
            Serial.println(swipeRightArray[swipeRightCounter]);
          }
          else if (swipeRightOn == false)
          {
            swipeRightOn = true;
            swipeRightCounter = 0;
            swipeRightTimer = millis();
            swipeRightArray[swipeRightCounter] = overValue;
            Serial.print("swipe start :");
            Serial.println(swipeRightArray[swipeRightCounter]);
          }

          if (swipeLeftOn == true)
          {
            swipeLeftCounter +=1;
            swipeLeftArray[swipeLeftCounter] = overValue;
            swipeLeftTimer = millis();
            Serial.print("swipe continue :");
            Serial.println(swipeLeftArray[swipeLeftCounter]);
          }

          gestureBoardRange->_timeStamp = millis();

        } else {
          timeElapsed = millis() - gestureBoardRange->_timeStamp;
          if (timeElapsed > gestureBoardRange->_timeOut) {
            gestureBoardCOM->sendMessage("<click_2>", 9);
            gestureBoardRange->_alreadyFired = true;
            gestureBoardLED->blinker(100);
          } else {
            pwmValue =
                255 *
                (1 - ((float)timeElapsed / (float)gestureBoardRange->_timeOut));
            gestureBoardLED->dim((int)pwmValue);
          }
        }
      } else {
        gestureBoardLED->stop();
        gestureBoardLED->setAnimation(GestureBoardHalLed_V1_1::getAnimation(2));
      }
    } else if (!gestureBoardRange->_flag1 && !gestureBoardRange->_flag2 &&
               gestureBoardRange->_flag3 && !gestureBoardRange->_flag4 &&
               !gestureBoardRange->_flag5) {
      // hover sensor 3
      if (!gestureBoardRange->_alreadyFired) {
        if (gestureBoardRange->_timeStamp == 0) {
          GestureBoardHalLed_V1_1::mappingLed mapping3;
          mapping3.mappingLed_byte = 0;
          mapping3.mappingLed_bit.ring3_0 = 1;
          mapping3.mappingLed_bit.ring3_60 = 1;
          mapping3.mappingLed_bit.ring3_120 = 1;

          gestureBoardLED->stop();
          gestureBoardLED->reset();
          gestureBoardLED->setMapping(mapping3);
          gestureBoardLED->set();
          gestureBoardLED->dim(255);

          gestureBoardCOM->sendMessage("<overOn_3>", 10);
          overValue = 3;

          if (swipeRightOn == true)
          {
            swipeRightCounter +=1;
            swipeRightArray[swipeRightCounter] = overValue;
            swipeRightTimer = millis();
            Serial.print("swipe continue :");
            Serial.println(swipeRightArray[swipeRightCounter]);
          }

          if (swipeLeftOn == true)
          {
            swipeLeftCounter +=1;
            swipeLeftArray[swipeLeftCounter] = overValue;
            swipeLeftTimer = millis();
            Serial.print("swipe continue :");
            Serial.println(swipeLeftArray[swipeLeftCounter]);
          }

          gestureBoardRange->_timeStamp = millis();
        } else {
          timeElapsed = millis() - gestureBoardRange->_timeStamp;
          if (timeElapsed > gestureBoardRange->_timeOut) {
            gestureBoardCOM->sendMessage("<click_3>", 9);
            gestureBoardRange->_alreadyFired = true;
            gestureBoardLED->blinker(100);
          } else {
            pwmValue =
                255 *
                (1 - ((float)timeElapsed / (float)gestureBoardRange->_timeOut));
            gestureBoardLED->dim((int)pwmValue);
          }
        }
      } else {
        gestureBoardLED->stop();
        gestureBoardLED->setAnimation(GestureBoardHalLed_V1_1::getAnimation(2));
      }
    } else if (!gestureBoardRange->_flag1 && !gestureBoardRange->_flag2 &&
               !gestureBoardRange->_flag3 && gestureBoardRange->_flag4 &&
               !gestureBoardRange->_flag5) {
      // hover sensor 3
      if (!gestureBoardRange->_alreadyFired) {
        if (gestureBoardRange->_timeStamp == 0) {
          GestureBoardHalLed_V1_1::mappingLed mapping4;
          mapping4.mappingLed_byte = 0;
          mapping4.mappingLed_bit.ring4_0 = 1;
          mapping4.mappingLed_bit.ring4_60 = 1;
          mapping4.mappingLed_bit.ring4_120 = 1;

          gestureBoardLED->stop();
          gestureBoardLED->reset();
          gestureBoardLED->setMapping(mapping4);
          gestureBoardLED->set();
          gestureBoardLED->dim(255);

          gestureBoardCOM->sendMessage("<overOn_4>", 10);
          overValue = 4;

          if (swipeRightOn == true)
          {
            swipeRightCounter +=1;
            swipeRightArray[swipeRightCounter] = overValue;
            swipeRightTimer = millis();
            Serial.print("swipe continue :");
            Serial.println(swipeRightArray[swipeRightCounter]);
          }

          if (swipeLeftOn == true)
          {
            swipeLeftCounter +=1;
            swipeLeftArray[swipeLeftCounter] = overValue;
            swipeLeftTimer = millis();
            Serial.print("swipe continue :");
            Serial.println(swipeLeftArray[swipeLeftCounter]);
          }
          else if (swipeLeftOn == false)
          {
            swipeLeftOn = true;
            swipeLeftCounter = 0;
            swipeLeftTimer = millis();
            swipeLeftArray[swipeLeftCounter] = overValue;
            Serial.print("swipe start :");
            Serial.println(swipeLeftArray[swipeLeftCounter]);
          }

          gestureBoardRange->_timeStamp = millis();
        } else {
          timeElapsed = millis() - gestureBoardRange->_timeStamp;
          if (timeElapsed > gestureBoardRange->_timeOut) {
            gestureBoardCOM->sendMessage("<click_4>", 9);
            gestureBoardRange->_alreadyFired = true;
            gestureBoardLED->blinker(100);
          } else {
            pwmValue =
                255 *
                (1 - ((float)timeElapsed / (float)gestureBoardRange->_timeOut));
            gestureBoardLED->dim((int)pwmValue);
          }
        }
      } else {
        gestureBoardLED->stop();
        gestureBoardLED->setAnimation(GestureBoardHalLed_V1_1::getAnimation(2));
      }
    } else if (!gestureBoardRange->_flag1 && !gestureBoardRange->_flag2 &&
               !gestureBoardRange->_flag3 && !gestureBoardRange->_flag4 &&
               gestureBoardRange->_flag5) {
      // not already finished detection condition
      if (!gestureBoardRange->_alreadyFired) {
        // starting detection condition ==> hover action
        if (gestureBoardRange->_timeStamp == 0) {
          // hover sensor 5
          GestureBoardHalLed_V1_1::mappingLed mapping5;
          mapping5.mappingLed_byte = 0;
          mapping5.mappingLed_bit.ring5_0 = 1;
          mapping5.mappingLed_bit.ring5_60 = 1;
          mapping5.mappingLed_bit.ring5_120 = 1;

          gestureBoardLED->stop();
          gestureBoardLED->reset();
          gestureBoardLED->setMapping(mapping5);
          gestureBoardLED->set();
          gestureBoardLED->dim(255);

          gestureBoardCOM->sendMessage("<overOn_5>", 10);
          overValue = 5;

          if (swipeRightOn == true)
          {
            swipeRightCounter +=1;
            swipeRightArray[swipeRightCounter] = overValue;
            swipeRightTimer = millis();
            Serial.print("swipe continue :");
            Serial.println(swipeRightArray[swipeRightCounter]);
          }

          if (swipeLeftOn == false)
          {
            swipeLeftOn = true;
            swipeLeftCounter = 0;
            swipeLeftTimer = millis();
            swipeLeftArray[swipeLeftCounter] = overValue;
            Serial.print("swipe start :");
            Serial.println(swipeLeftArray[swipeLeftCounter]);
          }

          gestureBoardRange->_timeStamp = millis();
        } else {
          // ending detection condition ==> click action
          timeElapsed = millis() - gestureBoardRange->_timeStamp;

          if (timeElapsed > gestureBoardRange->_timeOut) {
            gestureBoardCOM->sendMessage("<click_5>", 9);
            gestureBoardRange->_alreadyFired = true;
            gestureBoardLED->blinker(100);
          } else {
            // running detection condition ==> dimming action
            pwmValue =
                255 *
                (1 - ((float)timeElapsed / (float)gestureBoardRange->_timeOut));
            gestureBoardLED->dim((int)pwmValue);
          }
        }
      } else {
        // finished detection ==> back to animation
        gestureBoardLED->stop();
        gestureBoardLED->setAnimation(GestureBoardHalLed_V1_1::getAnimation(2));
      }
    } else {
      // reset push button actions parameters
      gestureBoardRange->_motionDetected = false;
      gestureBoardRange->_timeStamp = 0;
      if (!overOffDone) {
        overOffDone = true;
        switch (overValue) {
        case 1:
          gestureBoardCOM->sendMessage("<overOff_1>", 11);
          break;
        case 2:
          gestureBoardCOM->sendMessage("<overOff_2>", 11);
          break;
        case 3:
          gestureBoardCOM->sendMessage("<overOff_3>", 11);
          break;
        case 4:
          gestureBoardCOM->sendMessage("<overOff_4>", 11);
          break;
        case 5:
          gestureBoardCOM->sendMessage("<overOff_5>", 11);
          break;
        }
      }
      gestureBoardLED->dim(0);
      gestureBoardLED->start();
    }
  } else if (!gestureBoardRange->_motionDetected &&
             ((gestureBoardRange->_flag1 && !gestureBoardRange->_flag2 &&
               !gestureBoardRange->_flag3 && !gestureBoardRange->_flag4 &&
               !gestureBoardRange->_flag5) ||
              (!gestureBoardRange->_flag1 && gestureBoardRange->_flag2 &&
               !gestureBoardRange->_flag3 && !gestureBoardRange->_flag4 &&
               !gestureBoardRange->_flag5) ||
              (!gestureBoardRange->_flag1 && !gestureBoardRange->_flag2 &&
               gestureBoardRange->_flag3 && !gestureBoardRange->_flag4 &&
               !gestureBoardRange->_flag5) ||
              (!gestureBoardRange->_flag1 && !gestureBoardRange->_flag2 &&
               !gestureBoardRange->_flag3 && gestureBoardRange->_flag4 &&
               !gestureBoardRange->_flag5) ||
              (!gestureBoardRange->_flag1 && !gestureBoardRange->_flag2 &&
               !gestureBoardRange->_flag3 && !gestureBoardRange->_flag4 &&
               gestureBoardRange->_flag5))) {
    gestureBoardRange->_motionDetected = true;
    overOffDone = false;
  } else {
    gestureBoardRange->_alreadyFired = false;
    overOffDone = false;
  }
}
