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
        RBSonar(int8_t sensor_port, uint8_t addr = 0x70);

        /**
         * Creates the RBSonar-object.
         * @param i2c_wire wire-object of the I²C-bus to use
         */
        RBSonar(TwoWire &i2c_wire, uint8_t addr = 0x70);

        /**
         * Initializes the SRF08 sensor
        */    
        virtual bool init(void);

        /**
         * Reads the current distance that the sonar-sensor. Note that this blocks for ca. 100 ms. 
         * Use startMeasurement and readResultInCentimeters to use the time for other processing
         * @return int: distance in centimeters
         */
        int getDistanceCentimeters(void);
        
        /**
         * writes a new i2c address to the sonar sensor
         * @param addr new addr of the sonar sensor
         */
        void writeAddress(uint8_t addr);


        /**
         * start a measurement. The result needs to be read with readResultInCentimeters when resultReady is true
         */
        void startMeasurement();

        /**
         * @brief check if the result of startMeasurement is readable
         * 
         * @return true 
         * @return false 
         */
        bool resultReady();

        /**
         * @brief return the result in centimeters
         * 
         * @return int 
         */
        int readResultInCentimeters();

    private:
        /**
         * @brief helper to send commands to srf08
         * 
         * @param cmd 
         */
        void command(uint8_t cmd);
        
        /**
         * @brief address of the srf08 sensor
         * 
         */
        int _srf_address;
};

#endif