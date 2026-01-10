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
         * returns the name of the Sensor
         */
        virtual String getName(void) = 0;

        /**
         * Creates the RBSensor-Object for a Multiplexer setup.
         * @param sensor_port port of the sensor
         */
        RBSensor(int8_t sensor_port, int8_t i2c_address)
        {
            sensor_port_ = sensor_port;
            i2c_adress_ = i2c_address;
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

        /**
         * performs ACK check on the i2c adress defined in the constructor.
         */
        bool checkForAck(void)
        {
            if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->openChannel(sensor_port_);
            Wire.beginTransmission(i2c_adress_);
            int error = Wire.endTransmission();
            if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->closeChannel(sensor_port_);
            if (error)
            {
                Serial.println("Sensor Fehler an Port: "+String(sensor_port_));
                return false;
            }
            else
            {
                return true;
            }
        }

    protected:
        int8_t sensor_port_;
        uint8_t i2c_adress_;
        TCA9548A* tca_;
        TwoWire* wire_;

};

#endif