#include "gestureBoardHAL_COM.h"

GestureBoardHalCom::GestureBoardHalCom(long baudRate)
{
  this->_baudRate = baudRate;
  this->_bufferLength = 0;
  this->_newMessage = false;
}
