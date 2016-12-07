#include "gestureBoardHAL_LED_V1_1.h"

GestureBoardHalLedV1_1::GestureBoardHalLedV1_1(Animation* defaultAnim, int delay):GestureBoardHalLed(defaultAnim)
{
  this->_pGPIO = new GPIO_EXPANDER(GPIO_EXPANDER_LED_ADDRESS);
  this->_lastMillis = millis();
  this->_delay = delay;
}

void GestureBoardHalLedV1_1::init()
{
  _pGPIO->writeConfigurationPortPair(0x0000);
  delay(1000);
  _pGPIO->writeRegisterPair(0x02, 0x0000);
  delay(10);
}

void GestureBoardHalLedV1_1::dim(int value)
{

}

void GestureBoardHalLedV1_1::set()
{
  _pGPIO->writeRegisterPair(02, this->_map.mappingLed_byte);
}

void GestureBoardHalLedV1_1::update()
{
  int newTick = millis();
  if (this->_runningState)
  {
      if(newTick - this->_lastMillis >= this->_delay)
      {
          this->_count++;
          this->_lastMillis = newTick;
      }
      this->_runningAnimation->update(*this, this->_count);
  }
}
