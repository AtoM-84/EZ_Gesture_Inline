
#include "gestureBoardHAL_LED.h"

GestureBoardHalLed::GestureBoardHalLed(Animation* defaultAnim):_runningAnimation(defaultAnim)
{
  this->_count = 0;
  this->_runningState = false;
}

void GestureBoardHalLed::setAnimation(Animation* anim)
{
  this->_runningAnimation = anim;
  this->_count = 0;
}

void GestureBoardHalLed::start()
{
  this->_runningState = true;
  this->_count = 0;
}

void GestureBoardHalLed::stop()
{
  this->_runningState = false;
  this->_count = 0;
  this->reset();
  //delay(10);
}

void GestureBoardHalLed::reset()
{
  bool zeroMapping[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  this->set(zeroMapping);
}
