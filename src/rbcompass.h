/** 
 * @file rbcompass.h
 * 
 * Adafruit BNO055 Library for use with the RocciBoard
 * 
 * @author Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>) 
 * @version 1.0 [09-2023] First stable release
*/

#ifndef rbcompass_h
#define rbcompass_h

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
 * _NoMux: Disables the default I²C-sensor-multiplexing of the RocciBoard so that the sensor can be used on regular I²C.
*/
class RBCompass : public RBSensor {

    public:
        /**
         * Initializes the BNO055 compass sensor
        */    
        virtual bool init (void);
        bool init_NoMux (void);

        /**
         * heading describes the angle of the robot in the horizontal plane 
         * @return int16_t : Heading angle (0° -> 365°)
         */
        int16_t getHeading (void);
        int16_t getHeading_NoMux (void);

        /**
         * Pitch describes the angle of the robot pointing up or down
         * @return int16_t : Pitch angle (-180° -> 180)
         */
        int16_t getPitch (void);
        int16_t getPitch_NoMux (void);

        /**
         * Roll describes the angle of the robot rolling left and right
         * @return int16_t : Roll angle (-180° -> 180)
         */
        int16_t getRoll (void);
        int16_t getRoll_NoMux (void);

        /**
         * Returns the ambient temperature of the compass sensor
         * @return int8_t : temperature in °C
         */
        int8_t getTemperature (void);
        int8_t getTemperature_NoMux (void);

        /**
         * Returns the orientation-vector of the robot
         * @return RBVector : x,y,z-compontens of the orientation euler-angle
         */
        RBVector getVecOrientation (void);
        RBVector getVecOrientation_NoMux (void);

        /**
         * Returns the acceleration of the robot including gravity 
         * @return RBVector : x,y,z-compontens of the accelaration in m/s²
         */
        RBVector getVecAccelerometer (void);
        RBVector getVecAccelerometer_NoMux (void);

        /**
         * Returns the acceleration of the robot excluding gravity 
         * @return RBVector : x,y,z-compontens of the accelaration in m/s²
         */
        RBVector getVecLinearAcceleration (void);
        RBVector getVecLinearAcceleration_NoMux (void);

        /**
         * Returns the angular-velocity-vector of the Robot
         * @return RBVector : x,y,z-compontens of the angular velocity in rad/s
         */
        RBVector getVecGyroscope (void);
        RBVector getVecGyroscope_NoMux (void);

        /**
         * Returns the magnetic-field-vector measured by the compass sensor
         * @return RBVector : x,y,z-compontens of the magnetic field in uT (micro-tesla)
         */
        RBVector getVecMagneticField (void);
        RBVector getVecMagneticField_NoMux (void);
        
        /**
         * Returns the gravitaional acceleration of the robot
         * @return RBVector : x,y,z-compontens of the accelaration in m/s²
         */
        RBVector getVecGravity (void);
        RBVector getVecGravity_NoMux (void);

    private:
        /**
         * Updates the values of the compass-sensor
        */  
        void getData (Adafruit_BNO055::adafruit_vector_type_t event_type);
        void getData_NoMux (Adafruit_BNO055::adafruit_vector_type_t event_type);

        Adafruit_BNO055 bno_ = Adafruit_BNO055(55, 0x28, &Wire);
        sensors_event_t data_;

};

#endif