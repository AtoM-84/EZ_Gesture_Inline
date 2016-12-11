C++ libraries for Gesture Board Inline

All libraries prefixed with gestureBoardHAL are related to an abstraction layer of the hardware. When not suffixed, the library is hardware agnostic and exposed the function that will be used by upper level embedded code. When suffixed with the electronic board version (for instance V1_1 for board V1.1), the library is hardware dependant.
By construction, gestureBoardHAL_xxx are based on parent classes that are mainly composed by methods overloaded in the corresponding gestureBoardHAL_xxx_Vy dependant on the version. No code specific to the hardware should be in the gestureBoardHAL_xxx with the exception of a link to Arduino.h library needed for the definition of types related to the embedded device (unint8_t, bytes and so on...). I did not have neither the need nor the time to develop a specific library to define these types.
If everything is OK, the libraries gestureBoardHAL_xxx would not evolve with no major changes (especially new added methods), and the prefixed version will evolve with the board version and the hardware. If new methods are added by the new board version, the programs (main.cpp) will be specified to work only with a specific version. Otherwise, the links to libraries will only need to be correctly adressed in the header of main.cpp file.

The HAL libraries are :
* HAL_ArduinoUNO : abstraction layer for the ATMEGA328 MCU in Arduino context, with I2C and correct pin config.
* HAL_COM : communication through COM port based on Serial library.
* HAL_LED : providing LED feedback mainly based on PCAL6416A GPIO expander library.
* HAL_Range : configuring FlightSense range sensors and getting the range measurements from sensors.

There are two other families of libraries.

Libraries related to specific components, used in Object Oriented Programming styles that are the GPIOExpanderPCAL6416A from NXP and the RangeSensorVL6180X from STMicroelectronis. They will be completed in a closed future with the library RangeSensorVL53L0X from STMicroelectronics to enable the management of the V2 board, dedicated to long range interactions.

The last family are the embedded software providing upper abstraction level and detection the motion (motionDetection library), and the LED animation (animation and animationsBundle libraries).

Libraries HAL "hardware agnostic"
|--lib
|  |--gestureBoardHAL_COM
|  |--gestureBoardHAL_LED
|  |--gestureBoardHAL_Range

Libraries HAL "hardware specific" (for V1.1 i.e. for VL6180X sensors)
|--lib
|  |--gestureBoardHAL_ArduinoUNO_V1_1
|  |--gestureBoardHAL_COM_V1_1
|  |--gestureBoardHAL_LED_V1_1
|  |--gestureBoardHAL_Range_V1_1

Component libraries
|--lib
|  |--GPIOExpanderPCAL6416A
|  |--RangeSensorVL6180X
|  |--RangeSensorVL53L0X (to come for V2 support)

Embedded software libraries
|--lib
|  |--animation
|  |--animationsBundle


This directory is intended for the project specific (private) libraries.
PlatformIO will compile them to static libraries and link to executable file.

More information about PlatformIO Library Dependency Finder
- http://docs.platformio.org/en/stable/librarymanager/ldf.html
