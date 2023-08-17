/**
 * @file rblaser.h
 *
 * Polulu VL53L0X/VL53L1X Library for use with the RocciBoard
 *
 * @author Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>)
 * @version 1.0 [09-2023] First stable release
 */

#ifndef rblaser_h
#define rblaser_h

#include "rbsensor.h"

#include "Arduino.h"
#include "VL53L0X.h"
#include "VL53L1X.h"

#define TYPE_VL53L0X false
#define TYPE_SHORTRANGE false
#define TYPE_VL53L1X true
#define TYPE_LONGRANGE true

/**
 * Class for implementing the VL53L0X and VL53L1X laser-sensors for easy usage.
 */
class RBLaser : public RBSensor
{

    public:

        /**
         * Creates the RBLaser-object.
         * Sets the sensor-type to either VL53L0X (short-range) or VL53L1X (long-range).
         * @param is_long_range false to select VL53L0X, true to select VL53L1X
         */
        RBLaser(uint8_t sensor_port, bool is_long_range) : RBSensor(sensor_port);

        /**
         * Initializes the VL53L0X and VL53L1X compass sensor
        */    
        virtual bool init(void);

        /**
         * Reads the current distance that the laser-sensor measures
         * @return uint16_t: distance in millimeters
         */
        uint16_t getDistanceMillimeters(void);

        /**
         * Reads the current distance that the laser-sensor measures
         * @return uint16_t: distance in centimeters
         */
        float getDistanceCentimeters(void);

        /**
         * Reads the current distance that the laser-sensor measures
         * @return uint16_t: distance in meters
         */
        float getDistanceMeters(void);

        /**
         * Reads the current distance that the laser-sensor measures
         * @return uint16_t: distance in inches
         */
        float getDistanceInches(void);

        /**
         * Reads the current distance that the laser-sensor measures
         * @return uint16_t: distance in feet
         */
        float getDistanceFeet(void);

    private:
        bool long_range_;
        VL53L0X l0x_;
        VL53L1X l1x_;

};

#endif