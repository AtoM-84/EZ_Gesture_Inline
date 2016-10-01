# EZ_Gesture_Inline
Libraries and sketches for the 5 inline range sensors board based on VL6180X from STMicroelectronics.

## Library



## Sketch Examples

### Functional Board Test (FunctionalTestSketch)

This functional testing program aimed to test the different functions of the EZ Gesture Inline V1 board. This test aims to ensure a correct functional behavior of the device. The libraries EZ_RangeSensor and EZ_LedFeedback are used to test the different functional parts. The following functions are tested:
* 2.8V power supply for the VL6180X and the I2C which are "behind" the level shifter 5V to 2.8V,
* Correct response of each sensors on the I2C bus,
* Correct response of each GPIO expander,
* Correct assignment of I2C addresses,
* Correct functional behavior of all LED pairs following a particular procedure defined in this document. These tests cannot be declared as passed and must be checked by the user.

If all these tests are passed, communication with the ICs and power supply should be OK. Then the LED feedback and the range sensors are instanciated and the registers of each devices are configured in the normal use of the libraries. The functional testing could be launched.
The functional testing will test the response time of the sensors, the ability to detect the range for each sensors and to give a feedback with the leds and the ability to detect simple gesture (swipe and touch buttons).
The functional testing is a list of tests to choose:

* a test that will dim in the circle of LED as the user get closer to the corresponding sensor,
* a test that indicates alternatively a swipe left and a swipe right and pass to the other if the user execute the correct gesture (a double blink happens if the gesture is correct)
* a push button test that toggle the led pairs for each sensors if the user push the contactless button during more than 1 second.

The test sequence will verbose each test running, and, if available, will declare on the serial port the test passed or not. The device needs to be monitored using a serial port terminal at the baudrate of 112500. 

#### Set-Up Tests ("Unit" tests)

##### 2.8V power up test

2.8V is set OFF, then ON during 3 seconds, OFF during 3 seconds and ON.

##### Sensor response on I2C using Chip Enable (CE)

Each VL6180X sensor is disabled while successively one of them is enabled and a request of IC id is send using the default address (0x28) on I2C bus.

##### Sensor response on I2C after registering a new I2C address for each sensor

Each VL6180X sensor is instantiated as a new range sensor and a new address is given to the sensor 2 to 5. A similar request as the previous one is sent using the library function to get the IC id.

##### GPIO expander for VL6180X response on I2C

##### GPIO expander for LED circles response on I2C

##### LED sensor site unit test

For each sensor site the LED test is :
 1. 1 second blink (1second ON then OFF) of the opposite LED @ 0°/180° then @ 60°/240° and finally @ 120°/300°,
 each LED pairs is set ON while the previous one is kept ON running the same previous cycle, until the circle is completed,
 2. A dim out/dim in sequence is operated with all LEDs on 
 3. All LED are turned OFF.

The same sequence repeats for each sensor sites.

##### LED board testing

All LED for each sensor sites are activated simultaneously with the following procedure:
 1. A rotating process of each opposite LED pairs, for each sensor site (0°/180° - 60°/240° - 120°/300°), 3 times at a rate of 3 seconds per turn,
 2. All pairs for all sites activted simultaneously (all LEDs are ON),
 3. Dim out and then dim in for all LED pairs (duration 4 seconds),
 4. All LED pairs are turned OFF 2 seconds,
 5. Successively ON all the LED of each sensor site from 1 to 5 and OFF from 1 to 5, then from 5 to 1 ON and from 5 to 1 OFF (1 per second).

##### Setting up the GPIO expanders and the range sensors


#### Loop Tests (Functional tests)



## Projects