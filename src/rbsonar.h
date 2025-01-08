/**
 * @file rbsonar.h
 *
 * SRF08 Library for use with the RocciBoard
 *
 * @author Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>)
 * @version 1.0 [09-2023] First stable release
 */

#ifndef rbsonar_h
#define rbsonar_h

#include "rbsensor.h"

#include <SonarSRF08.h>

/**
 * Class for implementing the SRF08 sensors for easy usage.
 */
class RBSonar : public RBSensor
{

    public:

        /**
         * Creates the RBSonar-object.
         * @param sensor_port port of the sensor
         */
        RBSonar(int8_t sensor_port);

        /**
         * Creates the RBSonar-object.
         * @param i2c_wire wire-object of the I²C-bus to use
         */
        RBSonar(TwoWire &i2c_wire);

        /**
         * Initializes the SRF08 sensor
        */    
        virtual bool init(void);

        /**
         * Reads the current distance that the sonar-sensor measures
         * @return uint16_t: distance in centimeters
         */
        float getDistanceCentimeters(void);
        
        /**
         * writes a new i2c address to the sonar sensor
         * @param addr new addr of the sonar sensor
         */
        void writeAddress(uint8_t addr);

    private:
        SonarSRF08 srf08_;
};

#endif