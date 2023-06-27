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

#include <Arduino.h>
#include <TCA9548A.h>

#include <rbmotors.h>

//! Motor Driver 1
#define M1 0 
//! Motor Driver 2
#define M2 1
//! Motor Driver 3
#define M3 2
//! Motor Driver 4
#define M4 3

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
    bool Init (void);

    /** @defgroup addtitional_features Additional Features and Functions */

    /**
     * Returns the current voltage of the robots battery
     * @ingroup addtitional_features
     * @return float : battery voltage of the robot
    */
    float GetBatteryVoltage (void);

    /**
     * Returns the current state-of-charge of the robots battery \n
     * (WARNING: Does only work with LiPo 3S batteries! Treat values with caution! Use GetBatteryVoltage() for accurate measurement!)
     * @ingroup addtitional_features
     * @return int8_t : state-of-charge of the robots battery (0% -> 100%)
    */
    uint8_t GetBatteryCharge (void);

    /** @defgroup sensors Sensors */

    /**
     * Opens a channel of the TCA9548A-I2C-Multiplexer
     * WARNING: Do not forget to close the channel after use!
     * @ingroup sensors
     * @param index of the channel to open
     */
    void OpenChannel (uint8_t index);

    /**
     * Closes a channel of the TCA9548A-I2C-Multiplexer
     * @ingroup sensors
     * @param index of the channel to close
     */
    void CloseChannel (uint8_t index);

    /**
     * Closes all channels of the TCA9548A-I2C-Multiplexer
     * @ingroup sensors
     */
    void CloseAllChannels (void);

    /**
     * DRV8871 Motor Drivers of the RocciBoard 
     */
    RBMotor motor[4];

private:

    // Signal an internal error using the built-in Error-LED
    void BlinkErrorLED (void);   

    TCA9548A tca_;

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
