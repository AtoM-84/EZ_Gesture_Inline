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

  static boolean InProgress = false;
  static int ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  byte rc;
  byte message[32];

  while (Serial.available()) {
  rc = Serial.read();

  if (InProgress == true) {
      if (rc != endMarker) {
        message[ndx] = rc;
        ndx++;
      }
      else {
          message[ndx] = '\0';
          InProgress = false;
          this->_bufferLength = ndx +1;
          for(int i=0; i<this->_bufferLength; i++)
          {
            this->_bufferIn[i] = message[i];
          }
          ndx = 0;
          this->_newMessage = true;
      }
  }
  else if (rc == startMarker) {
      InProgress = true;
  }
}
}

void GestureBoardHalCom_V1_1::showLastMessage() {
  if (this->_newMessage)
  {
    for(int i=0; i<this->_bufferLength; i++)
    {
      Serial.write(this->_bufferIn[i]);
    }
  }
  this->_newMessage = false;
}


void GestureBoardHalCom_V1_1::sendMessage(char* messageOut, int messageLength)
{
  Serial.write(messageOut, messageLength);
}
