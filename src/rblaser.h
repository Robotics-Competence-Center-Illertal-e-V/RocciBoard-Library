/**
 * @file rblaser.h
 *
 * Polulu VL53L0X/VL53L1X Library for use with the RocciBoard
 *
 * @author Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>)
 * @version 1.0 [09-2023] First stable release
 */

#ifndef _RB_LASER_H_
#define _RB_LASER_H_

#include "rbsensor.h"

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
         * @param sensor_port port of the sensor
         * @param is_long_range false to select VL53L0X, true to select VL53L1X
         */
        RBLaser(int8_t sensor_port, bool is_long_range);

        /**
         * Creates the RBLaser-object.
         * Sets the sensor-type to either VL53L0X (short-range) or VL53L1X (long-range).
         * @param i2c_wire wire-object of the I²C-bus to use
         * @param is_long_range false to select VL53L0X, true to select VL53L1X
         */
        RBLaser(TwoWire &i2c_wire, bool is_long_range);

        /**
         * Initializes the VL53L0X and VL53L1X compass sensor
        */    
        virtual bool init(void);

        /**
         * Reads the current distance that the laser-sensor measures
         * @param blocking laser should wait for the next reading
         * @return uint16_t: distance in millimeters
         */
        uint16_t getDistanceMillimeters(bool blocking = true);

        /**
         * Reads the current distance that the laser-sensor measures
         * @param blocking laser should wait for the next reading
         * @return uint16_t: distance in centimeters
         */
        float getDistanceCentimeters(bool blocking = true);

        /**
         * Reads the current distance that the laser-sensor measures
         * @param blocking laser should wait for the next reading
         * @return uint16_t: distance in meters
         */
        float getDistanceMeters(bool blocking = true);

        /**
         * Reads the current distance that the laser-sensor measures
         * @param blocking laser should wait for the next reading
         * @return uint16_t: distance in inches
         */
        float getDistanceInches(bool blocking = true);

        /**
         * Reads the current distance that the laser-sensor measures
         * @param blocking laser should wait for the next reading
         * @return uint16_t: distance in feet
         */
        float getDistanceFeet(bool blocking = true);

    private:
        bool long_range_;
        VL53L0X l0x_;
        VL53L1X l1x_;

};

#endif