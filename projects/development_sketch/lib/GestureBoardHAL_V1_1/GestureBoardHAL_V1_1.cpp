#include "GestureBoardHAL_V1_1.h"

GESTURE_BOARD_HAL::GESTURE_BOARD_HAL()
{
  pinMode(CHIP_ENABLE_2_8V, OUTPUT);
  pinMode(GPIO_LED_RESET, OUTPUT);
  pinMode(GPIO_RANGE_SENSORS_RESET,OUTPUT);
  pinMode(LED_PWM_PIN, OUTPUT);
}

void GESTURE_BOARD_HAL::init()
{
  digitalWrite(CHIP_ENABLE_2_8V, 1);
  delay(1000);

  digitalWrite(GPIO_LED_RESET, 1);
  digitalWrite(GPIO_RANGE_SENSORS_RESET, 1);

  Wire.begin();
  Serial.println("I2C link started");

  Serial.begin(115200);
  Serial.println("serial link started");
}

void GESTURE_BOARD_HAL::assignSensorsAddress(GPIO_EXPANDER& sensorExpander, RANGE_SENSOR& sensorDefault, uint8_t address1, uint8_t address2, uint8_t address3, uint8_t address4, uint8_t address5)
{
  sensorExpander.writeRegister(GPIO_OUTPUT_REGISTER_PORT0, 0x01);
  delay(10);
  sensorDefault.writeByte(I2C_SLAVE__DEVICE_ADDRESS, address1);
  Serial.println("1st address changed");
  sensorExpander.writeRegister(GPIO_OUTPUT_REGISTER_PORT0, 0x03);
  delay(10);
  sensorDefault.writeByte(I2C_SLAVE__DEVICE_ADDRESS, address2);
  Serial.println("2nd address changed");
  sensorExpander.writeRegister(GPIO_OUTPUT_REGISTER_PORT0, 0x07);
  delay(10);
  sensorDefault.writeByte(I2C_SLAVE__DEVICE_ADDRESS, address3);
  Serial.println("3rd address changed");
  sensorExpander.writeRegister(GPIO_OUTPUT_REGISTER_PORT0, 0x0F);
  delay(10);
  sensorDefault.writeByte(I2C_SLAVE__DEVICE_ADDRESS, address4);
  Serial.println("4th address changed");
  sensorExpander.writeRegister(GPIO_OUTPUT_REGISTER_PORT0, 0x1F);
  delay(10);
  sensorDefault.writeByte(I2C_SLAVE__DEVICE_ADDRESS, address5);
  Serial.println("5th address changed");
}
