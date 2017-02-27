/**************************************************************************/
/*!
        @file     RangeSensorVL6180X.cpp
        @author   AtoM
        @license  MIT

This is a library for the VL6180X range sensor from STMicroelectronics.

    @section  HISTORY
        v0.0  - Creating functions:
    readByte
    writeByte
    setRangeConvergenceTime
    setPrivateRegisters
*/
/**************************************************************************/

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <RangeSensorVL6180X.h>
#include <Wire.h>

#define IDENTIFICATION__MODEL_ID 0x0000
#define IDENTIFICATION__MODEL_REV_MAJOR 0x0001
#define IDENTIFICATION__MODEL_REV_MINOR 0x0002
#define IDENTIFICATION__MODULE_REV_MAJOR 0x0003
#define IDENTIFICATION__MODULE_REV_MINOR 0x0004
#define IDENTIFICATION__DATE_HI 0x0006
#define IDENTIFICATION__DATE_LO 0x0007
#define IDENTIFICATION__TIME_1 0x0008
#define IDENTIFICATION__TIME_2 0x0009
#define SYSTEM__MODE_GPIO0 0x0010
#define SYSTEM__MODE_GPIO1 0x0011
#define SYSTEM__HISTORY_CTRL 0x0012
#define SYSTEM__INTERRUPT_CONFIG_GPIO 0x0014
#define SYSTEM__INTERRUPT_CLEAR 0x0015
#define SYSTEM__FRESH_OUT_OF_RESET 0x0016
#define SYSTEM__GROUPED_PARAMETER_HOLD 0x0017
#define SYSRANGE__START 0x0018
#define SYSRANGE__THRESH_HIGH 0x0019
#define SYSRANGE__THRESH_LOW 0x001A
#define SYSRANGE__INTERMEASUREMENT_PERIOD 0x001B
#define SYSRANGE__MAX_CONVERGENCE_TIME 0x001C
#define SYSRANGE__CROSSTALK_COMPENSATION_RATE 0x001E
#define SYSRANGE__CROSSTALK_VALID_HEIGHT 0x0021
#define SYSRANGE__EARLY_CONVERGENCE_ESTIMATE 0x0022
#define SYSRANGE__PART_TO_PART_RANGE_OFFSET 0x0024
#define SYSRANGE__RANGE_IGNORE_VALID_HEIGHT 0x0025
#define SYSRANGE__RANGE_IGNORE_THRESHOLD 0x0026
#define SYSRANGE__MAX_AMBIENT_LEVEL_MULT 0x002C
#define SYSRANGE__RANGE_CHECK_ENABLES 0x002D
#define SYSRANGE__VHV_RECALIBRATE 0x002E
#define SYSRANGE__VHV_REPEAT_RATE 0x0031
#define SYSALS__START 0x0038
#define SYSALS__THRESH_HIGH 0x003A
#define SYSALS__THRESH_LOW 0x003C
#define SYSALS__INTERMEASUREMENT_PERIOD 0x003E
#define SYSALS__ANALOGUE_GAIN 0x003F
#define SYSALS__INTEGRATION_PERIOD 0x0040
#define RESULT__RANGE_STATUS 0x004D
#define RESULT__ALS_STATUS 0x004E
#define RESULT__INTERRUPT_STATUS_GPIO 0x004F
#define RESULT__ALS_VAL 0x0050
#define RESULT__HISTORY_BUFFER 0x0052
#define RESULT__RANGE_VAL 0x0062
#define RESULT__RANGE_RAW 0x0064
#define RESULT__RANGE_RETURN_RATE 0x0066
#define RESULT__RANGE_REFERENCE_RATE 0x0068
#define RESULT__RANGE_RETURN_SIGNAL_COUNT 0x006C
#define RESULT__RANGE_REFERENCE_SIGNAL_COUNT 0x0070
#define RESULT__RANGE_RETURN_AMB_COUNT 0x0074
#define RESULT__RANGE_REFERENCE_AMB_COUNT 0x0078
#define RESULT__RANGE_RETURN_CONV_TIME 0x007C
#define RESULT__RANGE_REFERENCE_CONV_TIME 0x0080
#define READOUT__AVERAGING_SAMPLE_PERIOD 0x010A
#define FIRMWARE__BOOTUP 0x0119
#define FIRMWARE__RESULT_SCALER 0x0120
#define I2C_SLAVE__DEVICE_ADDRESS 0x0212
#define INTERLEAVED_MODE__ENABLE 0x02A3

/**************************************************************************/
/*! RANGE_SENSOR (const byte device_address)
        @brief  Instantiates a new RANGE_SENSOR
        @param  device_address	I2C device_address (7 bits SA)
*/
/**************************************************************************/

RANGE_SENSOR::RANGE_SENSOR(const byte device_address)
    : _device_address(device_address) {}

/**************************************************************************/
/*! readByte (uint16_t subAddress)
    @brief read one byte of the adressed VL6180X using the Wire (I2C) library
    @param subAddress : address of the addressed register (coded on two bytes)
*/
/**************************************************************************/

uint8_t RANGE_SENSOR::readByte(uint16_t subAddress) {
  Wire.beginTransmission(_device_address);
  Wire.write((subAddress >> 8) & 0xFF);
  Wire.write(subAddress & 0xFF);
  Wire.endTransmission(true);
  Wire.requestFrom(_device_address, 1);
  return Wire.read();
}

/**************************************************************************/
/*! writeByte (uint16_t subAddress, uint8_t data)
    @brief read one byte of the adressed VL6180X using the Wire (I2C) library
    @param subAddress : address of the written register (coded on two bytes)
    @param data : data content to be written
*/
/**************************************************************************/

void RANGE_SENSOR::writeByte(uint16_t subAddress, uint8_t data) {
  Wire.beginTransmission(_device_address);
  Wire.write((subAddress >> 8) & 0xFF);
  Wire.write(subAddress & 0xFF);
  Wire.write(data);
  Wire.endTransmission(true);
}

/**************************************************************************/
/*! writeTwoBytes (uint16_t subAddress, uint16_t data)
    @brief read one byte of the adressed VL6180X using the Wire (I2C) library
    @param subAddress : address of the written register (coded on two bytes)
    @param data : data content to be written
*/
/**************************************************************************/

void RANGE_SENSOR::writeTwoBytes(uint16_t subAddress, uint16_t data) {
  Wire.beginTransmission(_device_address);
  Wire.write((subAddress >> 8) & 0xFF);
  Wire.write(subAddress & 0xFF);
  Wire.write((data >> 8) & 0xFF);
  Wire.endTransmission(true);

  Wire.beginTransmission(_device_address);
  Wire.write(((subAddress + 0x01) >> 8) & 0xFF);
  Wire.write((subAddress + 0x01) & 0xFF);
  Wire.write(data & 0xFF);
  Wire.endTransmission(true);
}

/**************************************************************************/
/*! setRangeConvergenceTime (uint8_t value)
    @brief This function sets the range convergence time in order to limit the
   range to be measured if it is not needed to measure a long range. This will
   reduce power consumption.
    Reset value is 0x31. See datasheet p.60.
    @param value : value between 1 and 63 (0x3F)
*/
/**************************************************************************/

void RANGE_SENSOR::setRangeConvergenceTime(uint8_t value) {
  writeByte(SYSRANGE__MAX_CONVERGENCE_TIME, value);
}

/**************************************************************************/
/*! setPrivateRegisters ()
    @brief This set the registers for the range sensors after powering up.
*/
/**************************************************************************/

void RANGE_SENSOR::setPrivateRegisters() {
  if (!readByte(0x0016))
    return;
  // This first instruction checks that the component was not already
  // initialized by checking the register 0x0016 to be at 0 (fresh out of
  // reset).
  // If set to 0 the component is initialized and the function is stopped there.
  // Set up private registers
  writeByte(0x0207, 0x01);
  writeByte(0x0208, 0x01);
  writeByte(0x0096, 0x00);
  writeByte(0x0097, 0xfd);
  writeByte(0x00e3, 0x00);
  writeByte(0x00e4, 0x04);
  writeByte(0x00e5, 0x02);
  writeByte(0x00e6, 0x01);
  writeByte(0x00e7, 0x03);
  writeByte(0x00f5, 0x02);
  writeByte(0x00d9, 0x05);
  writeByte(0x00db, 0xce);
  writeByte(0x00dc, 0x03);
  writeByte(0x00dd, 0xf8);
  writeByte(0x009f, 0x00);
  writeByte(0x00a3, 0x3c);
  writeByte(0x00b7, 0x00);
  writeByte(0x00bb, 0x3c);
  writeByte(0x00b2, 0x09);
  writeByte(0x00ca, 0x09);
  writeByte(0x0198, 0x01);
  writeByte(0x01b0, 0x17);
  writeByte(0x01ad, 0x00);
  writeByte(0x00ff, 0x05);
  writeByte(0x0100, 0x05);
  writeByte(0x0199, 0x05);
  writeByte(0x01a6, 0x1b);
  writeByte(0x01ac, 0x3e);
  writeByte(0x01a7, 0x1f);
  writeByte(0x0030, 0x00);
  // Recommended register setup
  writeByte(SYSTEM__MODE_GPIO1, 0x10);
  writeByte(READOUT__AVERAGING_SAMPLE_PERIOD, 0x30);
  writeByte(SYSALS__ANALOGUE_GAIN, 0x46);
  writeByte(SYSRANGE__VHV_REPEAT_RATE, 0xFF);
  writeByte(SYSALS__INTEGRATION_PERIOD, 0x63);
  writeByte(SYSRANGE__VHV_RECALIBRATE, 0x01);
  // Optional registers
  writeByte(SYSRANGE__INTERMEASUREMENT_PERIOD, 0x09);
  writeByte(SYSALS__INTERMEASUREMENT_PERIOD, 0x31);
  writeByte(SYSTEM__INTERRUPT_CONFIG_GPIO, 0x24);
  // Change fresh out of set status to 0 to indicate if the component was
  // already configured after reset
  writeByte(SYSTEM__FRESH_OUT_OF_RESET, 0x00);
}

/**************************************************************************/
/*! singleRange ()
    @brief perform one range measurement (not time efficient with multiple
   sensors)
*/
/**************************************************************************/

int RANGE_SENSOR::singleRange() {
  writeByte(SYSRANGE__START, 0x01);
  while ((readByte(RESULT__INTERRUPT_STATUS_GPIO) & 0x07) != 4) {
    delay(1);
  }
  int rangeValue = readByte(RESULT__RANGE_VAL);
  writeByte(SYSTEM__INTERRUPT_CLEAR, 0x07);
  return rangeValue;
}

/**************************************************************************/
/*! singleRawRange ()
    @brief perform one raw range measurement (not time efficient with multiple
   sensors) and
*/
/**************************************************************************/

void RANGE_SENSOR::singleRawRangeAndReturnRate(int rawRange,
                                               int rangeReturnRate) {
  writeByte(SYSRANGE__START, 0x01);
  while ((readByte(RESULT__INTERRUPT_STATUS_GPIO) & 0x07) != 4) {
    delay(1);
  }
  rawRange = readByte(RESULT__RANGE_RAW);
  rangeReturnRate = readByte(RESULT__RANGE_RETURN_RATE);
  writeByte(SYSTEM__INTERRUPT_CLEAR, 0x07);
}

/**************************************************************************/
/*! startRangeMeasurement ()
    @brief start a range measurement in the VL6180X
*/
/**************************************************************************/

void RANGE_SENSOR::startRangeMeasurement() { writeByte(SYSRANGE__START, 0x01); }

/**************************************************************************/
/*! getRangeMeasurement ()
    @brief get the last range measurement in the register
*/
/**************************************************************************/

int RANGE_SENSOR::getRangeMeasurement() {
  int rangeValue = readByte(RESULT__RANGE_VAL);
  writeByte(SYSTEM__INTERRUPT_CLEAR, 0x07);
  return rangeValue;
}

/**************************************************************************/
/*! performCrossTalkCompensation ()
    @brief execute the cross-talk compensation on the part
*/
/**************************************************************************/

int RANGE_SENSOR::setCrossTalkCompensation() {
  int crossTalkCompensationRate;
  int rawRangeTable[10];
  int rawRangeReturnRate[10];

  for (int i = 0; i < 10; i++) {
    singleRawRangeAndReturnRate(rawRangeTable[i], rawRangeReturnRate[i]);
    delay(100);
    Serial.print("raw range ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(rawRangeTable[i]);
    Serial.print("return rate ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(rawRangeReturnRate[i]);
  }

  int averageRawRange = (rawRangeTable[0] + rawRangeTable[1] + rawRangeTable[2] + rawRangeTable[3] + rawRangeTable[4] + rawRangeTable[5] + rawRangeTable[6] + rawRangeTable[7] + rawRangeTable[8] + rawRangeTable[9]) / 10;

  int averageReturnRate = ((rawRangeReturnRate[0] + rawRangeReturnRate[1] + rawRangeReturnRate[2] + rawRangeReturnRate[3] + rawRangeReturnRate[4] + rawRangeReturnRate[5] + rawRangeReturnRate[6] + rawRangeReturnRate[7] + rawRangeReturnRate[8] + rawRangeReturnRate[9]) / 128) / 10;

  crossTalkCompensationRate = averageReturnRate * ((1 - averageRawRange)/100);

  writeTwoBytes(SYSRANGE__CROSSTALK_COMPENSATION_RATE, crossTalkCompensationRate);

  return crossTalkCompensationRate;
}
