/**
 * @file rbsensor.h
 *
 * Interface to unify the construction and implementation of sensors for easy use with the RocciBoard
 *
 * @author Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>)
 * @version 1.0 [09-2023] First stable release
 */

#ifndef _RB_SENSOR_H_
#define _RB_SENSOR_H_

#include "Arduino.h"
#include "Wire.h"
#include "RBMultiplexer.h"

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
         * Checks if the sensor is connected.
         * This function is implemented by the sensor-subclasses.
         * @return bool: true if sensor is connected, false otherwise
         */
        virtual bool isConnected(void) = 0;
        /**
         * Creates the RBSensor-Object for a Multiplexer setup.
         * @param sensor_port port of the sensor
         */
        RBSensor(int8_t sensor_port)
        {
            sensor_port_ = sensor_port;
            wire_ = &Wire;
        }

        /**
         * Creates the RBSensor-Object for a No-Multiplexer setup.
         * @param i2c_wire Wire-object of the I²C-bus to use
         */
        RBSensor(TwoWire &i2c_wire)
        {
            sensor_port_ = RB_NO_MULTIPLEXER;
            wire_ = &i2c_wire;
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
        TwoWire* getWire(void)
        {
            return wire_;
        }

        /**
         * Sets the RBMultiplexer-I²C-Multiplexer of the sensor.
         * @param tca pointer to new multiplexer of the sensor
         */
        void setMultiplexer(RBMultiplexer* tca_mux)
        {
            tca_ = tca_mux;
        }

        /**
         * Returns the RBMultiplexer-I²C-Multiplexer of the sensor.
         * @return RBMultiplexer: pointer to the multiplexer
         */
        RBMultiplexer* getMultiplexer(void)
        {
            return tca_;
        }
        
    protected:
        int8_t sensor_port_;
        RBMultiplexer* tca_;
        TwoWire* wire_;

        /**
         * Opens the I2C multiplexer channel for this sensor (if using a multiplexer).
         * Must be called before communicating with the sensor through the multiplexer.
         */
        void startUsing(void)
        {
            if(sensor_port_ != RB_NO_MULTIPLEXER)
                tca_->openChannel(sensor_port_);
        }

        /**
         * Closes the I2C multiplexer channel for this sensor (if using a multiplexer).
         * Must be called after communicating with the sensor through the multiplexer.
         */
        void stopUsing(void)
        {
            if(sensor_port_ != RB_NO_MULTIPLEXER)
                tca_->closeChannel(sensor_port_);
        }
};

#endif