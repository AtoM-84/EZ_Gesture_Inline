#include "GestureBoardLED.h"

//Swipe left methods

SwipeLeft::SwipeLeft()
{
}

void SwipeLeft::update(GestureBoardLED& parent, int count)
{
    switch (count)
    {
    case 1:
        parent._GPIO.writeRegisterPair(0x02, 0x7000);
        break;
    case 2:
        parent._GPIO.writeRegisterPair(0x02, 0x7E00);
        break;
    case 3:
        parent._GPIO.writeRegisterPair(0x02, 0x7E07);
        break;
    case 4:
        parent._GPIO.writeRegisterPair(0x02, 0x7E3F);
        break;
    case 5:
        parent._GPIO.writeRegisterPair(0x02, 0xFEFF);
        break;
    case 6:
        parent._GPIO.writeRegisterPair(0x02, 0x0000);
        parent.reset();
        break;
    }
}

SwipeRight::SwipeRight()
{
}

void SwipeRight::update(GestureBoardLED& parent, int count)
{
    switch (count)
    {
    case 1:
        parent._GPIO.writeRegisterPair(0x02, 0x80C0);
        break;
    case 2:
        parent._GPIO.writeRegisterPair(0x02, 0x80F8);
        break;
    case 3:
        parent._GPIO.writeRegisterPair(0x02, 0x80FF);
        break;
    case 4:
        parent._GPIO.writeRegisterPair(0x02, 0x8EFF);
        break;
    case 5:
        parent._GPIO.writeRegisterPair(0x02, 0xFEFF);
        break;
    case 6:
        parent._GPIO.writeRegisterPair(0x02, 0x0000);
        parent.reset();
        break;
    }
}

FiveButtons::FiveButtons()
{
}

void FiveButtons::update(GestureBoardLED& parent, int count)
{
    switch (count)
    {
    case 1:
        parent._GPIO.writeRegisterPair(0x02, 0x4849);
        break;
    case 2:
        parent._GPIO.writeRegisterPair(0x02, 0x9224);
        break;
    case 3:
        parent._GPIO.writeRegisterPair(0x02, 0x2492);
        parent.reset();
        break;
    }
}

ThreeButtons::ThreeButtons()
{
}

void ThreeButtons::update(GestureBoardLED& parent, int count)
{
    switch (count)
    {
    case 1:
        parent._GPIO.writeRegisterPair(0x02, 0x4041);
        break;
    case 2:
        parent._GPIO.writeRegisterPair(0x02, 0x9004);
        break;
    case 3:
        parent._GPIO.writeRegisterPair(0x02, 0x2082);
        parent.reset();
        break;
    }
}

TwoButtons::TwoButtons()
{
    
}

void TwoButtons::update(GestureBoardLED& parent, int count)
{
    switch (count)
    {
    case 1:
        parent._GPIO.writeRegisterPair(0x02, 0x0808);
        break;
    case 2:
        parent._GPIO.writeRegisterPair(0x02, 0x0220);
        break;
    case 3:
        parent._GPIO.writeRegisterPair(0x02, 0x0410);
        parent.reset();
        break;
    }
}

OneButton::OneButton()
{
}

void OneButton::update(GestureBoardLED& parent, int count)
{
    switch (count)
    {
    case 1:
        parent._GPIO.writeRegisterPair(0x02, 0x0001);
        break;
    case 2:
        parent._GPIO.writeRegisterPair(0x02, 0x0004);
        break;
    case 3:
        parent._GPIO.writeRegisterPair(0x02, 0x0002);
        parent.reset();
        break;
    }
}

SleepModePulse::SleepModePulse()
{
}

void SleepModePulse::update(GestureBoardLED& parent, int count)
{
    
}

//Gesture Board LED methods

Animation* GestureBoardLED::tabAnimations[]={new SwipeLeft(), new SwipeRight(), new FiveButtons(), new ThreeButtons(),new TwoButtons(),new OneButton(),new SleepModePulse()};

GestureBoardLED::GestureBoardLED(GPIO_EXPANDER& gpio, Animation* defaultAnimation, int delay):_GPIO(gpio)
{
    // this->_GPIO = gpio;
    this->_runningAnimation = defaultAnimation;
    this->_runningState = false;
    this->_count = 0;
    this->_lastMillis = millis();
    this->_delay = delay;
}

void GestureBoardLED::init()
{
    this->_GPIO.writeConfigurationPortPair(0x0000);
    delay(1000);
    this->_GPIO.writeRegisterPair(0x02, 0x0000);
    delay(10);
}

void GestureBoardLED::setAnimation(Animation* anim)
{
    this->_runningAnimation = anim;
    this->_count = 0;
}

void GestureBoardLED::update()
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

void GestureBoardLED::start()
{
    this->_runningState = true;
    this->_count = 0;
}

void GestureBoardLED::stop()
{
    this->_runningState = false;
    this->_count = 0;
    this->_GPIO.writeRegisterPair(0x02, 0x0000);
    delay(10);
}

void GestureBoardLED::reset()   
{
    this->_count = 0;
}

Animation* GestureBoardLED::getAnimation(int idx)
{
    return GestureBoardLED::tabAnimations[idx];
}