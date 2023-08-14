/** 
 * @file        rocciboard.h
 *
 * @mainpage    RocciBoard Library
 * This library was developed by the AK-Entwicklung of the RoCCI e. V. junior robotics association in 2023 together with its hardware complement, 
 * the RocciBoard-Shield for Arduino Mega/Giga, to provide students an easy to learn platform and a first entry into the world of microcontrollers and C++ programming.
 * Because it is meant for young students, this library may not provide all functions and possibilies of the underlying hardware, 
 * but rather the fundamentals needed when starting off with robotics.
 *
 * If you have questions or notice bugs, please feel free to contact the author using the contact details below!
 *
 * @section     Author
 * Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>)
 *
 * @section     License
 * MIT License
 * Copyright (c) 2023 Robotics Competence Center Illertal e. V.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * @section     History
 * 0.0 [06-2023] Started development
 * 1.0 [09-2023] First stable release
*/

#ifndef rocciboard_h
#define rocciboard_h

#include "Arduino.h"

#include "rbmotors.h"
#include "rbcompass.h"

/**
 * Hardware specific class that implements the functions of the RocciBoard-Shield. \n
 * WARNING: Only use it once in your program!
*/
class RocciBoard {
  public:

    /**
     * Creates the RocciBoard-Object
    */
    RocciBoard (void);

    /** @defgroup general_functions General Functions */

    /**
     * Initializes the RocciBoard
     * @ingroup general_functions
     * @return bool : Initialization successful
    */
    bool init (void);

    /** @defgroup sensor_functions Sensors and their functions */

    /**
     * Opens a sensor-channel on the I²C-Multiplexer. \n 
     * (WARNING: Be sure to always close the channel after use!)
     * @param sensor_port port/channel of the sensor
     * @ingroup sensor_functions
    */
    void openSensorChannel (uint8_t sensor_port);
    
    /**
     * Closes a sensor-channel on the I²C-Multiplexer.
     * @param sensor_port port/channel of the sensor
     * @ingroup sensor_functions
    */
    void closeSensorChannel (uint8_t sensor_port);

    /**
     * Closes all sensor-channels on the I²C-Multiplexer.
     * @ingroup sensor_functions
    */
    void closeAllSensorChannels (void);

    /**
     * Initializes a BNO055 compass-sensor on a given sensor port.
     * @param sensor_port port/channel of the sensor
     * @return RBCompass : compass-object of the connected compass-sensor
     * @ingroup sensor_functions
    */
    RBCompass initCompassSensor (uint8_t sensor_port);

    /** @defgroup addtitional_features Additional Features and Functions */

    /**
     * Returns the current voltage of the robots battery
     * @return float : battery voltage of the robot
     * @ingroup addtitional_features
    */
    float getBatteryVoltage (void);

    /**
     * Returns the current state-of-charge of the robots battery \n
     * (WARNING: Does only work with LiPo 3S batteries! Treat values with caution! Use getBatteryVoltage() for accurate measurement!)
     * @return int16_t : set-speed of the motor (-255 -> 255)
     * @ingroup addtitional_features
    */
    uint8_t getBatteryCharge (void);

    RBMotor motor[4];

  private:

    /**
     * Signal an internal error using the built-in Error-LED
    */ 
    void blinkErrorLED (void); 

    TCA9548A tca_;   
    RBCompass compass_sensor_;

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
