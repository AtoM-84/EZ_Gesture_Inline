//Library EEE parts
#include "GPIOExpanderPCAL6416A.h"
#include "RangeSensorVL6180X.h"
//#include "RangeSensorVL53L0.h"

//Library hardware
#include "Wire.h"
//#include "GestureBoardHAL.h"

//Library LED bar
#include "GestureBoardLED.h"
//#include "GestureBoardMotionSensing.h"

//A integrer class GestureBoard (integre les define liés à la board

#define GPIO_LED_RESET 4
#define GPIO_RANGE_SENSORS_RESET 5
#define LED_PWM_PIN 6
#define CHIP_ENABLE_2_8V 7

#define SENSOR_0_ADDRESS 0x29
#define SENSOR_1_ADDRESS 0x31
#define SENSOR_2_ADDRESS 0x32
#define SENSOR_3_ADDRESS 0x33
#define SENSOR_4_ADDRESS 0x34
#define SENSOR_5_ADDRESS 0x35

//Led Expander instantiate
GPIO_EXPANDER* pledExpander = new GPIO_EXPANDER(0x20);
GPIO_EXPANDER sensorExpander(0x21);

void assignSensorsAddress(uint8_t address1, uint8_t address2, uint8_t address3, uint8_t address4, uint8_t address5);

GestureBoardLED leds(*pledExpander, GestureBoardLED::getAnimation(0), 150);

// Fin du gestureboard

RANGE_SENSOR sensor0(SENSOR_0_ADDRESS);
RANGE_SENSOR sensor1(SENSOR_1_ADDRESS);
RANGE_SENSOR sensor2(SENSOR_2_ADDRESS);
RANGE_SENSOR sensor3(SENSOR_3_ADDRESS);
RANGE_SENSOR sensor4(SENSOR_4_ADDRESS);
RANGE_SENSOR sensor5(SENSOR_5_ADDRESS);

void setup()
{
  //A integrer dans gesture board
  pinMode(CHIP_ENABLE_2_8V, OUTPUT);
  pinMode(GPIO_LED_RESET, OUTPUT);
  pinMode(GPIO_RANGE_SENSORS_RESET,OUTPUT);
  pinMode(LED_PWM_PIN, OUTPUT);

  digitalWrite(CHIP_ENABLE_2_8V, 1);
  delay(1000);

  digitalWrite(GPIO_LED_RESET, 1);
  digitalWrite(GPIO_RANGE_SENSORS_RESET, 1);

  Wire.begin();
  Serial.println("I2C link started");

  Serial.begin(115200);
  Serial.println("serial link started");

  leds.init();
  leds.start();

  delay(10);
  leds.setAnimation(GestureBoardLED::getAnimation(1));

  delay(10);
  sensorExpander.writeConfigurationPortPair(0xFF00);
  sensorExpander.writeRegisterPair(0x02, 0x0000);
  Serial.println("Expanders configured!");
  delay(10);

  assignSensorsAddress(SENSOR_1_ADDRESS, SENSOR_2_ADDRESS, SENSOR_3_ADDRESS, SENSOR_4_ADDRESS, SENSOR_5_ADDRESS);

  sensor1.setPrivateRegisters();
  sensor2.setPrivateRegisters();
  sensor3.setPrivateRegisters();
  sensor4.setPrivateRegisters();
  sensor5.setPrivateRegisters();

  sensor1.setRangeConvergenceTime(0x1F);
  sensor2.setRangeConvergenceTime(0x1F);
  sensor3.setRangeConvergenceTime(0x1F);
  sensor4.setRangeConvergenceTime(0x1F);
  sensor5.setRangeConvergenceTime(0x1F);

}

void loop()
{

//Range measurement pipeline

  sensor1.startRangeMeasurement();
  delayMicroseconds(500);
  uint8_t range5 = sensor5.getRangeMeasurement();
  //uint8_t range5 = ((sensor5.getRangeMeasurement() <= 200) ? 1 : 0);
  sensor2.startRangeMeasurement();
  delayMicroseconds(500);
  uint8_t range1 = sensor1.getRangeMeasurement();
  //uint8_t range1 = ((sensor1.getRangeMeasurement() <= 200) ? 1 : 0);
  sensor3.startRangeMeasurement();
  delayMicroseconds(500);
  uint8_t range2 = sensor2.getRangeMeasurement();
  //uint8_t range2 = ((sensor2.getRangeMeasurement() <= 200) ? 1 : 0);
  sensor4.startRangeMeasurement();
  delayMicroseconds(500);
  uint8_t range3 = sensor3.getRangeMeasurement();
  //uint8_t range3 = ((sensor3.getRangeMeasurement() <= 200) ? 1 : 0);
  sensor5.startRangeMeasurement();
  delayMicroseconds(500);
  uint8_t range4 = sensor4.getRangeMeasurement();
  //uint8_t range4 = ((sensor4.getRangeMeasurement() <= 200) ? 1 : 0);

/*
  if(range1>50 && togglesup50 == false)
  {
    leds.stop();
    leds.setAnimation(GestureBoardLED::getAnimation(4));
    leds.start();
    togglesup50 = true;
    }
    else if (range1<50 && togglesup50 == true)
    {
    leds.stop();
    leds.setAnimation(GestureBoardLED::getAnimation(1));
    leds.start();
    togglesup50 = false;
    }
*/

//print loop range measurement results

  Serial.print(range1);
  Serial.print(" | ");
  Serial.print(range2);
  Serial.print(" | ");
  Serial.print(range3);
  Serial.print(" | ");
  Serial.print(range4);
  Serial.print(" | ");
  Serial.print(range5);
  Serial.print(" | ");
  Serial.println();
  /*
  uint8_t sumMeasurements = range1 + range2 + range3 + range4 + range5;
  uint8_t byteMeasurements;

  if (sumMeasurements > 1)
  {
    byteMeasurements = range1 + (range2 << 1) + (range3 << 2) + (range4 << 3) + (range5 << 4);
    byteMeasurements >> 1;
  }
  else if (sumMeasurements == 1)
  {
    byteMeasurements = range1 + (range2 << 1) + (range3 << 2) + (range4 << 3) + (range5 << 4);
  }
  else
  {
    byteMeasurements = 0;
  }
  Serial.println(sumMeasurements);
  Serial.println(byteMeasurements);
  */
  leds.update();

}


void assignSensorsAddress(uint8_t address1, uint8_t address2, uint8_t address3, uint8_t address4, uint8_t address5)
{
  sensorExpander.writeRegister(GPIO_OUTPUT_REGISTER_PORT0, 0x01);
  delay(10);
  sensor0.writeByte(I2C_SLAVE__DEVICE_ADDRESS, address1);
  Serial.println("1st address changed");
  sensorExpander.writeRegister(GPIO_OUTPUT_REGISTER_PORT0, 0x03);
  delay(10);
  sensor0.writeByte(I2C_SLAVE__DEVICE_ADDRESS, address2);
  Serial.println("2nd address changed");
  sensorExpander.writeRegister(GPIO_OUTPUT_REGISTER_PORT0, 0x07);
  delay(10);
  sensor0.writeByte(I2C_SLAVE__DEVICE_ADDRESS, address3);
  Serial.println("3rd address changed");
  sensorExpander.writeRegister(GPIO_OUTPUT_REGISTER_PORT0, 0x0F);
  delay(10);
  sensor0.writeByte(I2C_SLAVE__DEVICE_ADDRESS, address4);
  Serial.println("4th address changed");
  sensorExpander.writeRegister(GPIO_OUTPUT_REGISTER_PORT0, 0x1F);
  delay(10);
  sensor0.writeByte(I2C_SLAVE__DEVICE_ADDRESS, address5);
  Serial.println("5th address changed");
}
