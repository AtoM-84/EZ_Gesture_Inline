#include "gestureBoardHAL_Range_V1_1.h"

GestureBoardHalRange_V1_1::GestureBoardHalRange_V1_1()
    : GestureBoardHalRange() {
  this->_pGPIO = new GPIO_EXPANDER(GPIO_EXPANDER_SENSORS_ADDRESS);
  this->_pSensor0 = new RANGE_SENSOR(SENSOR_0_ADDRESS);
  this->_pSensor1 = new RANGE_SENSOR(SENSOR_1_ADDRESS);
  this->_pSensor2 = new RANGE_SENSOR(SENSOR_2_ADDRESS);
  this->_pSensor3 = new RANGE_SENSOR(SENSOR_3_ADDRESS);
  this->_pSensor4 = new RANGE_SENSOR(SENSOR_4_ADDRESS);
  this->_pSensor5 = new RANGE_SENSOR(SENSOR_5_ADDRESS);

  this->_range1 = 0;
  this->_range2 = 0;
  this->_range3 = 0;
  this->_range4 = 0;
  this->_range5 = 0;

  this->_flag1 = false;
  this->_flag2 = false;
  this->_flag3 = false;
  this->_flag4 = false;
  this->_flag5 = false;

  this->_timeStamp = 0;

  this->_motionDetected = false;
  this->_alreadyFired = false;

  this->_delay = 500;
}

void GestureBoardHalRange_V1_1::init() {
  this->_pGPIO->writeConfigurationPortPair(0xFF00);
  delay(100);
  this->_pGPIO->writeRegisterPair(0x02, 0x0000);
  delay(100);
  this->assignSensorsAddress();
  delay(100);
  this->initSensors();
}

void GestureBoardHalRange_V1_1::assignSensorsAddress() {
  this->_pGPIO->writeRegister(GPIO_OUTPUT_REGISTER_PORT0, 0x01);
  delay(10);
  this->_pSensor0->writeByte(I2C_SLAVE__DEVICE_ADDRESS, SENSOR_1_ADDRESS);
  delay(10);
  this->_pGPIO->writeRegister(GPIO_OUTPUT_REGISTER_PORT0, 0x03);
  delay(10);
  this->_pSensor0->writeByte(I2C_SLAVE__DEVICE_ADDRESS, SENSOR_2_ADDRESS);
  delay(10);
  this->_pGPIO->writeRegister(GPIO_OUTPUT_REGISTER_PORT0, 0x07);
  delay(10);
  this->_pSensor0->writeByte(I2C_SLAVE__DEVICE_ADDRESS, SENSOR_3_ADDRESS);
  delay(10);
  this->_pGPIO->writeRegister(GPIO_OUTPUT_REGISTER_PORT0, 0x0F);
  delay(10);
  this->_pSensor0->writeByte(I2C_SLAVE__DEVICE_ADDRESS, SENSOR_4_ADDRESS);
  delay(10);
  this->_pGPIO->writeRegister(GPIO_OUTPUT_REGISTER_PORT0, 0x1F);
  delay(10);
  this->_pSensor0->writeByte(I2C_SLAVE__DEVICE_ADDRESS, SENSOR_5_ADDRESS);
  delay(10);
}

void GestureBoardHalRange_V1_1::initSensors() {
  this->_pSensor1->setPrivateRegisters();
  this->_pSensor2->setPrivateRegisters();
  this->_pSensor3->setPrivateRegisters();
  this->_pSensor4->setPrivateRegisters();
  this->_pSensor5->setPrivateRegisters();
  delay(10);
  this->_pSensor1->setRangeConvergenceTime(this->_convergenceTime);
  this->_pSensor2->setRangeConvergenceTime(this->_convergenceTime);
  this->_pSensor3->setRangeConvergenceTime(this->_convergenceTime);
  this->_pSensor4->setRangeConvergenceTime(this->_convergenceTime);
  this->_pSensor5->setRangeConvergenceTime(this->_convergenceTime);
  delay(10);
  this->_pSensor1->startRangeMeasurement();
  this->_pSensor2->startRangeMeasurement();
  this->_pSensor3->startRangeMeasurement();
  this->_pSensor4->startRangeMeasurement();
  this->_pSensor5->startRangeMeasurement();
}

void GestureBoardHalRange_V1_1::rowMeasurement() {
  this->_pSensor1->startRangeMeasurement();
  delayMicroseconds(this->_delay);
  this->_range5 = 255 - this->_pSensor5->getRangeMeasurement();
  if (this->_range5 > 80) {
    this->_flag5 = true;
  } else {
    this->_flag5 = false;
  }
  this->_pSensor2->startRangeMeasurement();
  delayMicroseconds(this->_delay);
  this->_range1 = 255 - this->_pSensor1->getRangeMeasurement();
  if (this->_range1 > 80) {
    this->_flag1 = true;
  } else {
    this->_flag1 = false;
  }
  this->_pSensor3->startRangeMeasurement();
  delayMicroseconds(this->_delay);
  this->_range2 = 255 - this->_pSensor2->getRangeMeasurement();
  if (this->_range2 > 80) {
    this->_flag2 = true;
  } else {
    this->_flag2 = false;
  }
  this->_pSensor4->startRangeMeasurement();
  delayMicroseconds(this->_delay);
  this->_range3 = 255 - this->_pSensor3->getRangeMeasurement();
  if (this->_range3 > 80) {
    this->_flag3 = true;
  } else {
    this->_flag3 = false;
  }
  this->_pSensor5->startRangeMeasurement();
  delayMicroseconds(this->_delay);
  this->_range4 = 255 - this->_pSensor4->getRangeMeasurement();
  if (this->_range4 > 80) {
    this->_flag4 = true;
  } else {
    this->_flag4 = false;
  }
}

void GestureBoardHalRange_V1_1::setTimeOut(unsigned long timeOut) {
  this->_timeOut = timeOut;
}
