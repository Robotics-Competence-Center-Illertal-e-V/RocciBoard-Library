/**
 * @file rbsensor.h
 *
 * Interface to unify the construction and implementation of sensors for easy use with the RocciBoard
 *
 * @author Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>)
 * @version 1.0 [09-2023] First stable release
 */

#ifndef rbsensor_h
#define rbsensor_h

#include "Arduino.h"
#include "TCA9548A.h"

#define RB_NO_MULTIPLEXER -2

/**
 * Abstract class to wrap all sensors of the RocciBoard
 */
class RBSensor
{

    public:

        /**
         * Initializes the RBSensor.
         * This function is implemented by the sensor-subclasses.
        */ 
        virtual bool init(void) = 0;

        /**
         * Creates the RBSensor-Object for a Multiplexer setup.
         * @param sensor_port new port of the sensor
         */
        RBSensor(uint8_t sensor_port)
        {
            sensor_port_ = sensor_port;
        }

        /**
         * Sets the I²C-port of the sensor to a given port.
         * @param sensor_port new port of the sensor
         */
        void setSensorPort(uint8_t sensor_port)
        {
            sensor_port_ = sensor_port;
        }

        /**
         * Returns the current I²C-port of the sensor.
         * @return uint8_t: the current I²C-port
         */
        uint8_t getSensorPort(void)
        {
            return sensor_port_;
        }

        /**
         * Sets the TCA9548A-I²C-Multiplexer of the sensor.
         * @param tca pointer to new multiplexer of the sensor
         */
        void setMultiplexer(TCA9548A* tca_mux)
        {
            tca_ = tca_mux;
        }

        /**
         * Returns the TCA9548A-I²C-Multiplexer of the sensor.
         * @return TCA9548A: pointer to the multiplexer
         */
        TCA9548A* getMultiplexer(void)
        {
            return tca_;
        }

    protected:
        uint8_t sensor_port_;
        TCA9548A* tca_;

};

#endif