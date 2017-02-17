#ifndef GESTURE_BOARD_HAL_COM_V1_1_H
#define GESTURE_BOARD_HAL_COM_V1_1_H

#include "gestureBoardHAL_COM.h"

class GestureBoardHalCom_V1_1 : public GestureBoardHalCom
{
  public:
    GestureBoardHalCom_V1_1(long baudRate);
    virtual void open();
    virtual void close();
    virtual int onData();
    virtual void readMessage();
    virtual void showLastMessage();
    virtual void sendMessage(char* messageOut, int messageLength);
};

#endif
