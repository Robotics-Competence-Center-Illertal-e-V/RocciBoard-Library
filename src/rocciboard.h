/** 
 * @file        rocciboard.h
 *
 * @mainpage    RocciBoard Library
 * This library was developed by the AK-Entwicklung of the RoCCI e. V. junior robotics association in 2023 together with its hardware complement, 
 * the RocciBoard-Shield for the Arduino Mega/Giga, to provide students an easy-to-learn platform and a first entry into the world of microcontrollers and C++ programming.
 * Because it is meant for young students, this library may not provide all functions and possibilies of the underlying hardware, 
 * but rather the fundamentals needed when starting off with robotics.
 *
 * If you have questions or notice bugs, please feel free to contact the author using the contact details below!
 *
 * @section     Author
 * Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>)
 *
 * @section     Copyright
 * Copyright (c) 2023 Robotics Competence Center Illertal e. V.
 * 
 * @section     History
 * 0.0 [06-2023] Started development
 * 1.0 [09-2023] First stable release
*/

#ifndef _RB_ROCCIBOARD_H_
#define _RB_ROCCIBOARD_H_

#include "rbsensor.h"
#include "rbmotor.h"
#include "rbcompass.h"
#include "rblaser.h"
#include "rbcolor.h"
#include "rbinfrared.h"
#include "rbsonar.h"
#include "rbmultiplexer.h"

#define RB_DEBUG_LED 13
#define RB_BATTERY_ADC A0
#define RB_MUX_RESET 4
#define RB_I2C_SCL 21
#define RB_I2C_SDA 20

/**
 * Hardware specific class that implements the functions of the RocciBoard-Shield. \n
 * WARNING: Only use it once in your program!
*/
class RocciBoard {

  public:
    /**
     * Creates the RocciBoard-Object
     * @param addr is the I2C multiplexer address
    */
    RocciBoard (uint8_t addr=0x70);

    /**
     * Initializes the RocciBoard
     * @param block_on_failure if true, the board will halt on initialization failure
     * @return bool : Initialization successful
    */
    bool init (bool block_on_failure = true);

    /**
     * Fast initialization without any startup tests.
     * Skips battery, I2C and multiplexer port diagnostics.
     * @return bool : Initialization successful
    */
    bool init_fast (void);


    /**
     * Opens a sensor-channel on the I²C-Multiplexer. \n 
     * (WARNING: Be sure to always close the channel after use!)
     * @param sensor_port port/channel of the sensor
    */
    void openSensorPort (uint8_t sensor_port);
    
    /**
     * Closes a sensor-channel on the I²C-Multiplexer.
     * @param sensor_port port/channel of the sensor
    */
    void closeSensorPort (uint8_t sensor_port);

    /**
     * Closes all sensor-channels on the I²C-Multiplexer.
    */
    void closeAllSensorPorts (void);

    /**
     * Resets the I²C-multiplexer by using its reset-pin.
    */
    void resetMultiplexer (void);

    /**
     * Initializes a RocciBoard-Sensor on a given sensor port using the Multiplexer.
     * The TCA9548A-object is injected into the sensor.
     * @param sensor pointer to the object of the sensor (e.g. &compass)
     * @param sensor_port I2C-port of the sensor to initialize
     * @return bool : Initialization successful
    */
    bool initRBSensor (RBSensor &sensor, RBError* err = nullptr);

    /**
     * Returns the current voltage of the robots battery
     * @return float : battery voltage of the robot
    */
    float getBatteryVoltage (void);

    /**
     * Returns the current state-of-charge of the robots battery \n
     * (WARNING: Does only work with LiPo 3S batteries! Treat values with caution! Use getBatteryVoltage() for accurate measurement!)
     * @return int8_t : state-of-charge of the battery in percent (0-100)
    */
    uint8_t getBatteryCharge (void);

    /**
     * Signal something using the built-in Debug-LED.
     * Activates the Debug-LED for 100 milliseconds.
    */ 
    void blinkDebugLED (void); 

    /**
     * Rough i2c address scan for debugging purposes. \n
     * The function tries to access each possible I2C address and prints the results to the
     */
    void scanI2C(void);

    /**
     * Scans the sensor ports for connected sensors and prints the results to the serial monitor. \n
     * The function tries to identify the type of sensor connected to each port and prints the result
     */
    void scanSensors(void);

    RBMotor motor[4];

  private:
    void printError(const RBError& err, Print& out = Serial);
    RBMultiplexer tca_;   
    uint8_t tca_addr_;
    bool block_on_failure_ = true;

};

#endif

/*
#if defined(ARDUINO_ARCH_AVR)
  // AVR-specific code
#elif defined(ARDUINO_ARCH_SAM)
  // SAM-specific code
#else
  #error "This library only supports boards with an AVR or SAM processor."
#endif
*/
