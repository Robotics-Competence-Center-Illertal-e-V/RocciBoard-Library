/** 
 * @file rbmotors.h
 * 
 * DRV8871 motor driver library for the RocciBoard
 * 
 * @author Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>) 
 * @version 1.0 [09-2023] First stable release
*/

#ifndef rbmotors_h
#define rbmotors_h

#include <Arduino.h>

/**
 * Helper class for implementing motors for easy usage. \n
 * WARNING: Instances are created automatically when initializing the RocciBoard!
*/
class RBMotor {

public:

    /**
     * Creates the RBMotor-Object and assigns digital pins
     * @param pin_1 first digital pin of the DRV8871
     * @param pin_2 second digital pin of the DRV8871
    */
    RBMotor (uint8_t pin_1, uint8_t pin_2);
    RBMotor (void) {}

    /**
     * Initializes the motor
    */
    void init (void);
    
    /**
     * Turns the motor off either with or without braking (braking=true is default)
     * @param brake True: stopping the motor electrically, False: letting the motor stop through friction
    */
    void stop (bool brake);
    void stop (void) { stop(true); };

    /**
     * Sets the speed of the motor to a specific value
     * @param speed that the motor should be set to (-255 -> 255)
    */
    void rotate (int16_t speed);

    /**
     * Returns the current set-speed of the motor
     * @return int16_t : set-speed of the motor (-255 -> 255)
    */
    int16_t getSpeed (void);

private:

    uint8_t pin_1_ = 0;
    uint8_t pin_2_ = 0;
    int16_t speed_ = 0;

};

#endif