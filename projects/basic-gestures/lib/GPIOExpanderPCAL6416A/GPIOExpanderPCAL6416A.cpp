/**************************************************************************/
/*!
	@file     GPIOExpanderPCAL6416A.cpp
	@author   AtoM
	@license  MIT

This is a library for the PCAL6416A GPIO expander.

	@section  HISTORY
	v0.0  - Creating functions:
        readRegister
        readRegisterPair
        writeRegister
        writeRegisterPair
        readInputRegister
        readInputRegisterPair
        readOutputRegister
        readOutputRegisterPair
        writeConfigurationPort
*/
/**************************************************************************/

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>
#include <GPIOExpanderPCAL6416A.h>

/**************************************************************************/
/*! GPIO_EXPANDER(const byte device_address)
	@brief  Instantiates a new GPIO_EXPANDER
	@param  device_address	I2C device_address (7 bits SA)
*/
/**************************************************************************/

GPIO_EXPANDER::GPIO_EXPANDER(const byte device_address) : _device_address(device_address)
{
}

/**************************************************************************/
/*! readRegister(uint8_t registerAddress)
	@brief reads a register value and returns it as a 8 bits integer
	@param registerAddress Internal GPIO register address
*/
/**************************************************************************/
/*
int8_t GPIO_EXPANDER::readRegister(uint8_t registerAddress)
{
        Wire.beginTransmission(_device_address);
        Wire.write(registerAddress);
        Wire.endTransmission();
        Wire.beginTransmission(_device_address);
        Wire.requestFrom(_device_address, 1, true);
        int8_t value = Wire.read();
        if(value != -1)
        {
            return value;
        }
        else
        {
            return -1;
        }
}
*/
/**************************************************************************/
/*! readRegisterPair(uint8_t registerAddress)
	@brief read a register pairs values and returns them as a 16 bits integer (This function works for all pairs except output drive strength).
	@param registerAddress address of the first register of the pair
*/
/**************************************************************************/
/*
int16_t GPIO_EXPANDER::readRegisterPair(uint8_t registerAddress)
{
    Wire.beginTransmission(_device_address);
    Wire.write(registerAddress);
    Wire.endTransmission();
    Wire.beginTransmission(_device_address);
    Wire.requestFrom(_device_address, 2, true);
    int16_t first_byte = Wire.read();
    if(first_byte != -1)
        {
        uint16_t values = ((uint16_t)first_byte << 8) + Wire.read();
         return values;
        }
        else
        {
        return -1;
        }    
}
*/
/**************************************************************************/
/*! writeRegister(uint8_t registerAddress, uint8_t value)
	@brief writes the one byte value inside the selected register
	@param registerAddress address of the register
	@param value 8 bits value to write
*/
/**************************************************************************/

void GPIO_EXPANDER::writeRegister(uint8_t registerAddress, uint8_t value)
{
    Wire.beginTransmission(_device_address);
    Wire.write(registerAddress);
    Wire.write(value);
    Wire.endTransmission(true);
}

/**************************************************************************/
/*! writeRegisterPair(uint8_t registerAddress, uint16_t value)
	@brief writes inside a pair of registers the sixteen bits value cutting it into two bytes and writing it in FIFO mode (the selected register will receive the lower byte, the paired one the higher byte). This function works for all pairs except output drive strength.
	@param registerAddress first address of the register pair
	@param value 16 bits value to write
*/
/**************************************************************************/

void GPIO_EXPANDER::writeRegisterPair(uint8_t registerAddress, uint16_t value)
{
    uint8_t low_byte = value;
    uint8_t high_byte = (value >> 8);

    Wire.beginTransmission(_device_address);
    Wire.write(registerAddress);
    Wire.write(low_byte);
    Wire.write(high_byte);
    Wire.endTransmission(true);
}

/**************************************************************************/
/*! readInputRegister(uint8_t port)
	@brief reads the INPUT register of the selected port
	@param port selected port (0 or 1)
*/
/**************************************************************************/
/*
int8_t GPIO_EXPANDER::readInputRegister(uint8_t port)
{
    if(port == 0)
    {
        return readRegister(GPIO_INPUT_REGISTER_PORT0);
    }
    else if(port == 1)
    {
        return readRegister(GPIO_INPUT_REGISTER_PORT1);
    }
    else
    {
        return -1;
    }
}
*/
/**************************************************************************/
/*! readInputRegisterPair()
	@brief reads the INPUT register pair beginning with port 0
	@param
*/
/**************************************************************************/
/*
int16_t GPIO_EXPANDER::readInputRegisterPair()
{
        return readRegister(GPIO_INPUT_REGISTER_PORT0);
}
*/
/**************************************************************************/
/*! readOutputRegister(uint8_t port)
	@brief reads the OUTPUT register of the selected port
	@param port  selected port (0 or 1) 
*/
/**************************************************************************/
/*
int8_t GPIO_EXPANDER::readOutputRegister(uint8_t port)
{
        if(port == 0)
    {
        return readRegister(GPIO_OUTPUT_REGISTER_PORT0);
    }
    else if(port == 1)
    {
        return readRegister(GPIO_OUTPUT_REGISTER_PORT1);
    }
    else
    {
        return -1;
    }
}
*/
/**************************************************************************/
/*! readOutputRegisterPair()
	@brief reads the OUTPUT register pair beginning with port 0
	@param
*/
/**************************************************************************/
/*
int16_t GPIO_EXPANDER::readOutputRegisterPair()
{
        return readRegister(GPIO_OUTPUT_REGISTER_PORT0);
}
*/
/**************************************************************************/
/*! writeConfigurationPort(uint8_t port, uint8_t port)
	@brief configures Input/Output direction of the selected port
	@param port  selected port (0 or 1)
    @param configuration the 1 byte configuration to applied to the port
*/
/**************************************************************************/

void GPIO_EXPANDER::writeConfigurationPort(uint8_t port, uint8_t configuration)
{
    if(port == 0)
    {
        writeRegister(GPIO_CONFIGURATION_REGISTER_PORT0, configuration);
    }
    else if(port == 1)
    {
        writeRegister(GPIO_CONFIGURATION_REGISTER_PORT1, configuration);
    }
}

/**************************************************************************/
/*! writeConfigurationPort(uint16_t configuration)
	@brief configures Input/Output direction of the selected port
	@param configuration the 2 byte configuration to applied to the expander
*/
/**************************************************************************/

void GPIO_EXPANDER::writeConfigurationPortPair(uint16_t configuration)
{
        writeRegisterPair(GPIO_CONFIGURATION_REGISTER_PORT0, configuration);
}