#include "gestureBoardHAL_COM_V1_1.h"

GestureBoardHalCom_V1_1::GestureBoardHalCom_V1_1(long baudRate):GestureBoardHalCom(baudRate)
{
}

void GestureBoardHalCom_V1_1::open()
{
  Serial.begin(this->_baudRate);
  Serial.println("serial link started");
}

void GestureBoardHalCom_V1_1::close()
{
  Serial.println("serial link will close shortly");
  delay(2000);
  Serial.end();
}

int GestureBoardHalCom_V1_1::onData()
{
  if(Serial.available() > 0)
  {
    return Serial.available();
  }
  else
  {
    return 0;
  }
}

void GestureBoardHalCom_V1_1::readMessage() {
  /*
  static boolean InProgress = false;
  static int ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  if (Serial.available() > 0 && this->_newData == false) {
      rc = Serial.read();

      if (InProgress == true) {
          if (rc != endMarker) {
              this->_bufferIn[ndx] = rc;
              ndx++;
              if (ndx >= this->_numChars) {
                  ndx = this->_numChars - 1;
              }
              Serial.println("I received :" + this->_bufferIn[ndx]);
          }
          else {
              this->_bufferIn[ndx] = '\0'; // terminate the string
              InProgress = false;
              ndx = 0;
              this->_newData = true;
          }
      }

      else if (rc == startMarker) {
          InProgress = true;
      }
  }
  */
  if (Serial.available()) {
  this->_bufferIn = Serial.read();
  Serial.write(this->_bufferIn);
  }

}

void GestureBoardHalCom_V1_1::showNewMessage() {
  if (Serial.available()) {
    Serial.write(this->_bufferIn);
  }
}

void GestureBoardHalCom_V1_1::sendMessage(char* messageOut, int messageLength)
{
  Serial.write(messageOut, messageLength);
}
