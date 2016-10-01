/**************************************************************************/
/*!
    @file     GPIOExpanderController.cpp
    @author   AtoM
	@license  MIT
This is a library for the
	@section  HISTORY
	v0.0  - Creating functions:
        readRegister
        readRegisterPair
        writeRegister
        writeRegisterPair
        readInputRegister
        readOutputRegister
*/
/**************************************************************************/

#ifndef GPIO_EXPANDER_H
#define GPIO_EXPANDER_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define GPIO_INPUT_REGISTER_PORT0 0x00
#define GPIO_INPUT_REGISTER_PORT1 0x01
#define GPIO_OUTPUT_REGISTER_PORT0 0x02
#define GPIO_OUTPUT_REGISTER_PORT1 0x03
#define GPIO_POL_INVERSION_REGISTER_PORT0 0x04
#define GPIO_POL_INVERSION_REGISTER_PORT1 0x05
#define GPIO_CONFIGURATION_REGISTER_PORT0 0x06
#define GPIO_CONFIGURATION_REGISTER_PORT1 0x07
#define GPIO_DRIVE_STRENGTH_REGISTER_PORT0_0 0x40
#define GPIO_DRIVE_STRENGTH_REGISTER_PORT0_1 0x41
#define GPIO_DRIVE_STRENGTH_REGISTER_PORT1_0 0x42
#define GPIO_DRIVE_STRENGTH_REGISTER_PORT1_1 0x43
#define GPIO_INPUT_LATCH_REGISTER_PORT0 0x44
#define GPIO_INPUT_LATCH_REGISTER_PORT1 0x45
#define GPIO_PULL_ENABLE_REGISTER_PORT0 0x46
#define GPIO_PULL_ENABLE_REGISTER_PORT1 0x47
#define GPIO_PULL_SELECTION_REGISTER_PORT0 0x48
#define GPIO_PULL_SELECTION_REGISTER_PORT1 0x49
#define GPIO_INT_MASK_REGISTER_PORT0 0x4A
#define GPIO_INT_MASK_REGISTER_PORT1 0x4B
#define GPIO_INT_STATUS_REGISTER_PORT0 0x4C
#define GPIO_INT_STATUS_REGISTER_PORT1 0x4D
#define GPIO_OUTPUT_PORT_CONF_REGISTER 0x4F

class GPIO_EXPANDER
{
  public:
    GPIO_EXPANDER(const byte device_address);

    //general purpose functions
    int8_t readRegister(uint8_t registerAddress);
    int16_t readRegisterPair(uint8_t registerAddress);
    void writeRegister(uint8_t registerAddress, uint8_t value);
    void writeRegisterPair(uint8_t registerAddress, uint16_t value);

    //register dedicated functions
    int8_t readInputRegister(uint8_t port);
    int8_t readOutputRegister(uint8_t port);

  private:
    const byte _device_address;
};

#endif