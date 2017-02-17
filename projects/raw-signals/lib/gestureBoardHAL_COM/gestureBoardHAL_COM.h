#ifndef GESTURE_BOARD_HAL_COM_H
#define GESTURE_BOARD_HAL_COM_H

#include "Arduino.h"

class GestureBoardHalCom
{
public:
  byte _bufferIn[32];
  char* _bufferOut;
  int _bufferLength;
  bool _newMessage;

protected:
  long _baudRate;

public:
  GestureBoardHalCom(long baudRate);
  virtual void open() = 0;
  virtual void close() = 0;
  virtual void readMessage() = 0;
  virtual void showLastMessage() = 0;
  virtual void sendMessage(char* messageOut, int messageLength) = 0;
};

#endif
