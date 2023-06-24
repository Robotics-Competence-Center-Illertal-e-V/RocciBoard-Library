/** 
 * @file rocciboard.h
 *
 * RocciBoard Library
 *
 * This library was developed by the AK-Entwicklung of the RoCCI e. V. junior robotics association in 2023 together with its hardware complement, 
 * the RocciBoard-Shield for Arduino Mega/Giga, to provide students an easy to learn platform and a first entry into the world of microcontrollers and C++ programming.
 * Because it is meant for young students, this library may not provide all functions and possibilies of the underlying hardware, 
 * but rather the fundamentals needed when starting off with robotics.
 *
 * If you have questions or notice bugs, please feel free to contact the author using the contact details below!
 * 
 * @author Jonas Biener <jonas.biener@rocci.net> for the Robotics Competence Center Illertal e. V. <https://rocci.net>
 * @copyright: MIT License - See LICENCE.txt for details!
 * @version: 1.0 (09-2023) 
*/

#ifndef rocciboard_h
#define rocciboard_h

#include "Arduino.h"

/**
 * Hardware specific class that implements the functions of the RocciBoard-Shield
*/
class RocciBoard {
  public:

  private:

}

#if defined(ARDUINO_ARCH_AVR)
  // AVR-specific code
#elif defined(ARDUINO_ARCH_SAM)
  // SAM-specific code
#else
  #error "This library only supports boards with an AVR or SAM processor."
#endif

#endif