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
#include "Wire.h"
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
         * @param sensor_port port of the sensor
         */
        RBSensor(uint8_t sensor_port)
        {
            sensor_port_ = sensor_port;
            wire_ = &Wire;
        }

        /**
         * Creates the RBSensor-Object for a No-Multiplexer setup.
         * @param i2c_wire Wire-object of the I²C-bus to use
         */
        RBSensor(Wire &i2c_wire)
        {
            sensor_port_ = RB_NO_MULTIPLEXER;
            wire_ = &i2c_bus;
        }

        /**
         * Returns the current I²C-port of the sensor.
         * @return uint8_t: the I²C-mux-port of the sensor
         */
        uint8_t getSensorPort(void)
        {
            return sensor_port_;
        }

        /**
         * Returns the Wire-object of the sensor.
         * @return Wire: Wire-object of the sensor
         */
        Wire* getWire(void)
        {
            return wire_;
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
        Wire* wire_;

};

#endif