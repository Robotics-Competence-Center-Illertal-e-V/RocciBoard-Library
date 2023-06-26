/** 
 * @file motors.h
 * 
 * DRV8871 motor driver library for the RocciBoard
 * 
 * @author Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>) 
 * @version 1.0 [09-2023] First stable release
*/

#ifndef rbmotors_h
#define rbmotors_h

#include "Arduino.h"

/**
 * Helper class for implementing motors for easy usage. Instances are created automatically when initializing the RocciBoard!
*/
class RBMotor {
  public:

    /**
     * Initializes the motor
    */
    void Init (void);
    
    /**
     * Turns the motor off
    */
    void Off (void);

    /**
     * Controls the DRV8871 motor driver to use a DC-motor
     * @param speed that the motor should be set to (-255 -> 255)
    */
    void SetSpeed (int16_t speed);

    /**
     * Returns the current set-speed of the motor
     * @ingroup motor_drivers
     * @return int16_t : set-speed of the motor (-255 -> 255)
    */
    int16_t GetSpeed (uint8_t index);

  private:

    uint8_t index_;
    int16_t speed_;

}

#endif