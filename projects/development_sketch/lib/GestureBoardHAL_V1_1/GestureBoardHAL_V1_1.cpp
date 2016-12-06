#include "GestureBoardHAL_V1_1.h"


GestureBoardHalLedV1_1::GestureBoardHalLedV1_1(Animation* defaultAnim, int delay):GestureBoardHalLed(defaultAnim)
{
  _pGPIO = new GPIO_EXPANDER(GPIO_EXPANDER_LED_ADDRESS);
  _lastMillis = millis();
  _delay = delay;
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

void GestureBoardHalLedV1_1::set(int mapping[])
{
  uint16_t physicalMapping = 0x0000;
  physicalMapping = physicalMapping + mapping[13];
  physicalMapping << 1;
  physicalMapping = physicalMapping + mapping[0];
  physicalMapping << 1;
  physicalMapping = physicalMapping + mapping[2];
  physicalMapping << 1;
  physicalMapping = physicalMapping + mapping[1];
  physicalMapping << 1;
  physicalMapping = physicalMapping + mapping[3];
  physicalMapping << 1;
  physicalMapping = physicalMapping + mapping[5];
  physicalMapping << 1;
  physicalMapping = physicalMapping + mapping[4];
  physicalMapping << 1;
  physicalMapping << 1;

  physicalMapping = physicalMapping + mapping[14];
  physicalMapping << 1;
  physicalMapping = physicalMapping + mapping[12];
  physicalMapping << 1;
  physicalMapping = physicalMapping + mapping[10];
  physicalMapping << 1;
  physicalMapping = physicalMapping + mapping[11];
  physicalMapping << 1;
  physicalMapping = physicalMapping + mapping[9];
  physicalMapping << 1;
  physicalMapping = physicalMapping + mapping[7];
  physicalMapping << 1;
  physicalMapping = physicalMapping + mapping[8];
  physicalMapping << 1;
  physicalMapping = physicalMapping + mapping[6];
  physicalMapping << 1;

  _pGPIO->writeRegisterPair(02, physicalMapping);
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
