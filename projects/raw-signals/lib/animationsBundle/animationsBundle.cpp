
#include "animationsBundle.h"

SwipeLeft::SwipeLeft()
{
}

void SwipeLeft::update(GestureBoardHalLed& parent, int count)
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

void SwipeRight::update(GestureBoardHalLed& parent, int count)
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

void FiveButtons::update(GestureBoardHalLed& parent, int count)
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

void ThreeButtons::update(GestureBoardHalLed& parent, int count)
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

void TwoButtons::update(GestureBoardHalLed& parent, int count)
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

void OneButton::update(GestureBoardHalLed& parent, int count)
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

void SleepModePulse::update(GestureBoardHalLed& parent, int count)
{

}
