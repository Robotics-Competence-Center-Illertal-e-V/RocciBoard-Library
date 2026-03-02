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
         * Checks if the sonar sensor is connected by verifying the software revision
         * @return bool: true if sensor is connected and responds with valid revision
         */
        virtual bool isConnected(void);

        /**
         * Reads the current distance that the sonar-sensor measures. Note that this blocks for ca. 100 ms.
         * Use startMeasurement and readResultInCentimeters to use the time for other processing
         * @return int: distance in centimeters
         */
        int getDistanceCentimeters(void);

        /**
         * Writes a new I2C address to the sonar sensor
         * @param addr new address of the sonar sensor
         */
        void writeAddress(uint8_t addr);

        /**
         * Start a measurement. The result needs to be read with readResultInCentimeters when resultReady is true
         */
        void startMeasurement();

        /**
         * Check if the result of startMeasurement is readable
         * @return bool: true if measurement result is ready
         */
        bool resultReady();

        /**
         * Return the result in centimeters
         * @return int: distance measurement in centimeters, or -1 if not ready
         */
        int readResultInCentimeters();

    private:
        /**
         * Helper function to send commands to the SRF08 sensor
         * @param cmd command byte to send to the sensor
         */
        void command(uint8_t cmd);

        /**
         * I2C address of the SRF08 sensor
         */
        int _srf_address;
};

#endif