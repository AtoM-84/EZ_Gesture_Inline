#include "gestureBoardHAL_Range_V1_1.h"

GestureBoardHalRange_V1_1::GestureBoardHalRange_V1_1():GestureBoardHalRange()
{
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

  this->_delay = 500;
}

void GestureBoardHalRange_V1_1::init()
{
  this->_pGPIO->writeConfigurationPortPair(0xFF00);
  delay(100);
  this->_pGPIO->writeRegisterPair(0x02, 0x0000);
  delay(100);
  this->assignSensorsAddress();
  delay(100);
  this->initSensors();
}

void GestureBoardHalRange_V1_1::assignSensorsAddress()
{
  this->_pGPIO->writeRegister(GPIO_OUTPUT_REGISTER_PORT0, 0x01);
  delay(10);
  this->_pSensor0->writeByte(I2C_SLAVE__DEVICE_ADDRESS, SENSOR_1_ADDRESS);
  delay(10);
  if (0xB4 == this->_pSensor1->readByte(0x00))
      {
            Serial.println("Sensor 1 OK");
      }
  delay(20);
  this->_pGPIO->writeRegister(GPIO_OUTPUT_REGISTER_PORT0, 0x03);
  delay(10);
  this->_pSensor0->writeByte(I2C_SLAVE__DEVICE_ADDRESS, SENSOR_2_ADDRESS);
  delay(10);
  if (0xB4 == this->_pSensor2->readByte(0x00))
      {
            Serial.println("Sensor 2 OK");
      }
  delay(20);
  this->_pGPIO->writeRegister(GPIO_OUTPUT_REGISTER_PORT0, 0x07);
  delay(10);
  this->_pSensor0->writeByte(I2C_SLAVE__DEVICE_ADDRESS, SENSOR_3_ADDRESS);
  delay(10);
  if (0xB4 == this->_pSensor3->readByte(0x00))
      {
            Serial.println("Sensor 3 OK");
      }
  delay(20);
  this->_pGPIO->writeRegister(GPIO_OUTPUT_REGISTER_PORT0, 0x0F);
  delay(10);
  this->_pSensor0->writeByte(I2C_SLAVE__DEVICE_ADDRESS, SENSOR_4_ADDRESS);
  delay(10);
  if (0xB4 == this->_pSensor4->readByte(0x00))
      {
            Serial.println("Sensor 4 OK");
      }
  delay(20);
  this->_pGPIO->writeRegister(GPIO_OUTPUT_REGISTER_PORT0, 0x1F);
  delay(10);
  this->_pSensor0->writeByte(I2C_SLAVE__DEVICE_ADDRESS, SENSOR_5_ADDRESS);
  delay(10);
  if (0xB4 == this->_pSensor5->readByte(0x00))
      {
            Serial.println("Sensor 5 OK");
      }
  delay(20);
}

void GestureBoardHalRange_V1_1::initSensors()
{
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
  /*
  delay(10);
  this->_range1 = this->_pSensor1->getRangeMeasurement();
  delay(10);
  this->_range2 = this->_pSensor2->getRangeMeasurement();
  delay(10);
  this->_range3 = this->_pSensor3->getRangeMeasurement();
  delay(10);
  this->_range4 = this->_pSensor4->getRangeMeasurement();
  delay(10);
  this->_range5 = this->_pSensor5->getRangeMeasurement();
  delay(10);
  Serial.println(this->_range1, DEC);
  Serial.println(this->_range2, DEC);
  Serial.println(this->_range3, DEC);
  Serial.println(this->_range4, DEC);
  Serial.println(this->_range5, DEC);
  */
}

void GestureBoardHalRange_V1_1::rowMeasurement()
{
  this->_pSensor1->startRangeMeasurement();
  delayMicroseconds(this->_delay);
  this->_range5 = this->_pSensor5->getRangeMeasurement();
  this->_pSensor2->startRangeMeasurement();
  delayMicroseconds(this->_delay);
  this->_range1 = this->_pSensor1->getRangeMeasurement();
  this->_pSensor3->startRangeMeasurement();
  delayMicroseconds(this->_delay);
  this->_range2 = this->_pSensor2->getRangeMeasurement();
  this->_pSensor4->startRangeMeasurement();
  delayMicroseconds(this->_delay);
  this->_range3 = this->_pSensor3->getRangeMeasurement();
  this->_pSensor5->startRangeMeasurement();
  delayMicroseconds(this->_delay);
  this->_range4 = this->_pSensor4->getRangeMeasurement();
}
