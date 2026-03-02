/** 
 * @file rbcompass.h
 * 
 * Adafruit BNO055 Library for use with the RocciBoard
 * 
 * @author Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>) 
 * @version 1.0 [09-2023] First stable release
*/

#ifndef _RB_COMPASS_H_
#define _RB_COMPASS_H_

#include "rbsensor.h"

#include "Adafruit_BNO055.h"

/**
 * Stores a three-dimensional vector with float values
*/
typedef struct {
    float x;
    float y;
    float z;
} RBVector;

/**
 * Class for implementing the BNO055 compass sensor for easy usage.
*/
class RBCompass : public RBSensor {

    public:
        /**
         * Creates the RBCompass-object.
         * @param sensor_port port of the sensor (for multiplexer setup)
         */
        RBCompass (int8_t sensor_port);

        /**
         * Creates the RBCompass-object.
         * @param i2c_wire wire-object of the I²C-bus to use
         */
        RBCompass (TwoWire &i2c_wire);
        /**
         * Initializes the BNO055 compass sensor
         */
        virtual bool init(void);

        /**
         * Checks if the compass sensor is connected by verifying the chip ID
         * @return bool: true if sensor is connected and responds with correct chip ID
         */
        virtual bool isConnected(void);
        /**
         * heading describes the angle of the robot in the horizontal plane
         * @return int16_t : Heading angle (0° -> 360°)
         */
        int16_t getHeading(void);

        /**
         * Pitch describes the angle of the robot pointing up or down
         * @return int16_t : Pitch angle (-90° -> 90°)
         */
        int16_t getPitch(void);

        /**
         * Roll describes the angle of the robot rolling left and right
         * @return int16_t : Roll angle (-180° -> 180°)
         */
        int16_t getRoll(void);

        /**
         * Returns the ambient temperature of the compass sensor
         * @return int8_t : temperature in °C
         */
        int8_t getTemperatureCelsius(void);

        /**
         * Returns the orientation-vector of the robot
         * @return RBVector : x,y,z-components of the orientation euler-angle
         */
        RBVector getVecOrientation(void);

        /**
         * Returns the acceleration of the robot including gravity
         * @return RBVector : x,y,z-components of the acceleration in m/s²
         */
        RBVector getVecAccelerometer(void);

        /**
         * Returns the acceleration of the robot excluding gravity
         * @return RBVector : x,y,z-components of the acceleration in m/s²
         */
        RBVector getVecLinearAcceleration(void);

        /**
         * Returns the angular-velocity-vector of the robot
         * @return RBVector : x,y,z-components of the angular velocity in rad/s
         */
        RBVector getVecGyroscope(void);

        /**
         * Returns the magnetic-field-vector measured by the compass sensor
         * @return RBVector : x,y,z-components of the magnetic field in µT (micro-tesla)
         */
        RBVector getVecMagneticField(void);

        /**
         * Returns the gravitational acceleration of the robot
         * @return RBVector : x,y,z-components of the acceleration in m/s²
         */
        RBVector getVecGravity(void);

    private:
        /**
         * Updates the cached sensor data by reading from the BNO055 sensor
         * @param event_type the type of vector/event data to read
         */
        void getData(Adafruit_BNO055::adafruit_vector_type_t event_type);

        Adafruit_BNO055 bno_ = Adafruit_BNO055(55, 0x28, &Wire); /**< BNO055 compass sensor instance */
        sensors_event_t data_;                                    /**< Cached sensor event data */

};

#endif