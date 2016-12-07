#include "gestureBoardHAL_LED.h"

GestureBoardHalLed::GestureBoardHalLed(Animation* defaultAnim):_runningAnimation(defaultAnim)
{
  this->_count = 0;
  this->_runningState = false;
  this->_map.mappingLed_byte = 0;
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
  mappingLed zero;
  zero.mappingLed_byte = 0;
  this->setMapping(zero);
  this->_count = 0;
}

uint16_t GestureBoardHalLed::getMapping()
{
  return this->_map.mappingLed_byte;
}

void GestureBoardHalLed::setMapping(mappingLed new_map)
{
  this->_map = new_map;
}


Animation* GestureBoardHalLed::getAnimation(int idx)
{
    return GestureBoardHalLed::tabAnimations[idx];
}

Animation* GestureBoardHalLed::tabAnimations[]={new SwipeLeft(), new SwipeRight(), new FiveButtons(), new ThreeButtons(),new TwoButtons(),new OneButton(),new SleepModePulse()};



SwipeLeft::SwipeLeft()
{
}

void SwipeLeft::update(GestureBoardHalLed& parent, int count)
{
  GestureBoardHalLed::mappingLed current_mapping;
  current_mapping.mappingLed_byte = parent.getMapping();
    switch (count)
    {
    case 1:
      current_mapping.mappingLed_bit.ring1_0 = 1;
      current_mapping.mappingLed_bit.ring1_60 = 1;
      current_mapping.mappingLed_bit.ring1_120 = 1;
      parent.setMapping(current_mapping);
      break;
    case 2:
      current_mapping.mappingLed_bit.ring2_0 = 1;
      current_mapping.mappingLed_bit.ring2_60 = 1;
      current_mapping.mappingLed_bit.ring2_120 = 1;
      parent.setMapping(current_mapping);
      break;
    case 3:
      current_mapping.mappingLed_bit.ring3_0 = 1;
      current_mapping.mappingLed_bit.ring3_60 = 1;
      current_mapping.mappingLed_bit.ring3_120 = 1;
      parent.setMapping(current_mapping);
      break;
    case 4:
      current_mapping.mappingLed_bit.ring4_0 = 1;
      current_mapping.mappingLed_bit.ring4_60 = 1;
      current_mapping.mappingLed_bit.ring4_120 = 1;
      parent.setMapping(current_mapping);
      break;
    case 5:
      current_mapping.mappingLed_bit.ring5_0 = 1;
      current_mapping.mappingLed_bit.ring5_60 = 1;
      current_mapping.mappingLed_bit.ring5_120 = 1;
      parent.setMapping(current_mapping);
      break;
    case 6:
      current_mapping.mappingLed_byte = 0;
      parent.setMapping(current_mapping);
      parent.reset();
      break;
    }
    parent.set();
}

SwipeRight::SwipeRight()
{
}

void SwipeRight::update(GestureBoardHalLed& parent, int count)
{
  GestureBoardHalLed::mappingLed current_mapping;
  current_mapping.mappingLed_byte = parent.getMapping();
    switch (count)
    {
    case 1:
      current_mapping.mappingLed_bit.ring5_0 = 1;
      current_mapping.mappingLed_bit.ring5_60 = 1;
      current_mapping.mappingLed_bit.ring5_120 = 1;
      parent.setMapping(current_mapping);
      break;
    case 2:
      current_mapping.mappingLed_bit.ring4_0 = 1;
      current_mapping.mappingLed_bit.ring4_60 = 1;
      current_mapping.mappingLed_bit.ring4_120 = 1;
      parent.setMapping(current_mapping);
      break;
    case 3:
      current_mapping.mappingLed_bit.ring3_0 = 1;
      current_mapping.mappingLed_bit.ring3_60 = 1;
      current_mapping.mappingLed_bit.ring3_120 = 1;
      parent.setMapping(current_mapping);
      break;
    case 4:
      current_mapping.mappingLed_bit.ring2_0 = 1;
      current_mapping.mappingLed_bit.ring2_60 = 1;
      current_mapping.mappingLed_bit.ring2_120 = 1;
      parent.setMapping(current_mapping);
      break;
    case 5:
      current_mapping.mappingLed_bit.ring1_0 = 1;
      current_mapping.mappingLed_bit.ring1_60 = 1;
      current_mapping.mappingLed_bit.ring1_120 = 1;
      parent.setMapping(current_mapping);
      break;
    case 6:
      current_mapping.mappingLed_byte = 0;
      parent.setMapping(current_mapping);
      parent.reset();
      break;
    }
    parent.set();
}

FiveButtons::FiveButtons()
{
}

void FiveButtons::update(GestureBoardHalLed& parent, int count)
{
  GestureBoardHalLed::mappingLed current_mapping;
  current_mapping.mappingLed_byte = parent.getMapping();
    switch (count)
    {
    case 1:
        current_mapping.mappingLed_bit.ring1_0 = 1;
        current_mapping.mappingLed_bit.ring2_0 = 1;
        current_mapping.mappingLed_bit.ring3_0 = 1;
        current_mapping.mappingLed_bit.ring4_0 = 1;
        current_mapping.mappingLed_bit.ring5_0 = 1;
        break;
    case 2:
        current_mapping.mappingLed_bit.ring1_60 = 1;
        current_mapping.mappingLed_bit.ring2_60 = 1;
        current_mapping.mappingLed_bit.ring3_60 = 1;
        current_mapping.mappingLed_bit.ring4_60 = 1;
        current_mapping.mappingLed_bit.ring5_60 = 1;
        break;
    case 3:
        current_mapping.mappingLed_bit.ring1_120 = 1;
        current_mapping.mappingLed_bit.ring2_120 = 1;
        current_mapping.mappingLed_bit.ring3_120 = 1;
        current_mapping.mappingLed_bit.ring4_120 = 1;
        current_mapping.mappingLed_bit.ring5_120 = 1;
        parent.reset();
        break;
    }
    parent.set();
}

ThreeButtons::ThreeButtons()
{
}

void ThreeButtons::update(GestureBoardHalLed& parent, int count)
{
  GestureBoardHalLed::mappingLed current_mapping;
  current_mapping.mappingLed_byte = parent.getMapping();
    switch (count)
    {
    case 1:
        current_mapping.mappingLed_bit.ring1_0 = 1;
        current_mapping.mappingLed_bit.ring3_0 = 1;
        current_mapping.mappingLed_bit.ring5_0 = 1;
        break;
    case 2:
        current_mapping.mappingLed_bit.ring1_60 = 1;
        current_mapping.mappingLed_bit.ring3_60 = 1;
        current_mapping.mappingLed_bit.ring5_60 = 1;
        break;
    case 3:
        current_mapping.mappingLed_bit.ring1_120 = 1;
        current_mapping.mappingLed_bit.ring3_120 = 1;
        current_mapping.mappingLed_bit.ring5_120 = 1;
        parent.reset();
        break;
    }
    parent.set();
}

TwoButtons::TwoButtons()
{

}

void TwoButtons::update(GestureBoardHalLed& parent, int count)
{
  GestureBoardHalLed::mappingLed current_mapping;
  current_mapping.mappingLed_byte = parent.getMapping();
    switch (count)
    {
    case 1:
        current_mapping.mappingLed_bit.ring2_0 = 1;
        current_mapping.mappingLed_bit.ring4_0 = 1;
        break;
    case 2:
        current_mapping.mappingLed_bit.ring2_60 = 1;
        current_mapping.mappingLed_bit.ring4_60 = 1;
        break;
    case 3:
        current_mapping.mappingLed_bit.ring2_120 = 1;
        current_mapping.mappingLed_bit.ring4_120 = 1;
        parent.reset();
        break;
    }
    parent.set();
}

OneButton::OneButton()
{
}

void OneButton::update(GestureBoardHalLed& parent, int count)
{
  GestureBoardHalLed::mappingLed current_mapping;
  current_mapping.mappingLed_byte = parent.getMapping();
    switch (count)
    {
    case 1:
        current_mapping.mappingLed_bit.ring3_0 = 1;
        break;
    case 2:
        current_mapping.mappingLed_bit.ring3_60 = 1;
        break;
    case 3:
        current_mapping.mappingLed_bit.ring3_120 = 1;
        parent.reset();
        break;
    }
    parent.set();
}

SleepModePulse::SleepModePulse()
{
}

void SleepModePulse::update(GestureBoardHalLed& parent, int count)
{

}
