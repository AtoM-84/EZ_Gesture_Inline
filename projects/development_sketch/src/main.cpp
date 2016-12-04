//EEE parts libraries
//#include "GPIOExpanderPCAL6416A.h"
//#include "RangeSensorVL6180X.h"
//#include "RangeSensorVL53L0.h"

//Hardware libraries
#include "Wire.h"
#include "GestureBoardHAL_V1_1.h"

GPIO_EXPANDER* pledExpander = new GPIO_EXPANDER(0x20);
GPIO_EXPANDER* psensorExpander = new GPIO_EXPANDER(0x21);

RANGE_SENSOR* psensor0 = new RANGE_SENSOR(SENSOR_0_ADDRESS);
RANGE_SENSOR sensor1(SENSOR_1_ADDRESS);
RANGE_SENSOR sensor2(SENSOR_2_ADDRESS);
RANGE_SENSOR sensor3(SENSOR_3_ADDRESS);
RANGE_SENSOR sensor4(SENSOR_4_ADDRESS);
RANGE_SENSOR sensor5(SENSOR_5_ADDRESS);

GESTURE_BOARD_HAL* gestureBoardHAL = new GESTURE_BOARD_HAL();

//Functional libraries
#include "GestureBoardLED.h"
//#include "GestureBoardMotionSensing.h"

GestureBoardLED leds(*pledExpander, GestureBoardLED::getAnimation(0), 150);

void setup()
{
  gestureBoardHAL->init();

  leds.init();
  leds.start();

  delay(10);
  leds.setAnimation(GestureBoardLED::getAnimation(1));

  // ces fontions à intégrer dans l'init du détecteur de mouvement
  delay(10);
  psensorExpander->writeConfigurationPortPair(0xFF00);
  psensorExpander->writeRegisterPair(0x02, 0x0000);
  delay(10);

  gestureBoardHAL->assignSensorsAddress(*psensorExpander, *psensor0, SENSOR_1_ADDRESS, SENSOR_2_ADDRESS, SENSOR_3_ADDRESS, SENSOR_4_ADDRESS, SENSOR_5_ADDRESS);

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
