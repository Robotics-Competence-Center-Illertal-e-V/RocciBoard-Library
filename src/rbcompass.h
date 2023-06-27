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

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

/**
 * Stores a three-dimensional vector with float values
*/
typedef struct {
    float x;
    float y;
    float z;
} Vector;

/**
 * Class for implementing the BNO055 compass sensor for easy usage.
*/
class RBCompass {

public:

    /**
     * Initializes the BNO055 compass sensor
    */    
    void Init (void);

    /**
     * Heading describes the angle of the robot in the horizontal plane 
     * @return int16_t : Heading angle (0° -> 365°)
     */
    int16_t Heading (void);

    /**
     * Pitch describes the angle of the robot pointing up or down
     * @return int16_t : Pitch angle (-180° -> 180)
     */
    int16_t Pitch (void);

    /**
     * Roll describes the angle of the robot rolling left and right
     * @return int16_t : Roll angle (-180° -> 180)
     */
    int16_t Roll (void);

    /**
     * Returns the ambient temperature of the compass sensor
     * @return int8_t : temperature in °C
     */
    int8_t Temperature (void);

    /**
     * Returns the orientation-vector of the robot
     * @return Vector : x,y,z-compontens of the orientation euler-angle
     */
    Vector Orientation (void);

    /**
     * Returns the acceleration of the robot including gravity 
     * @return Vector : x,y,z-compontens of the accelaration in m/s²
     */
    Vector Accelerometer (void);

    /**
     * Returns the acceleration of the robot excluding gravity 
     * @return Vector : x,y,z-compontens of the accelaration in m/s²
     */
    Vector LinearAcceleration (void);

    /**
     * Returns the angular-velocity-vector of the Robot
     * @return Vector : x,y,z-compontens of the angular velocity in rad/s
     */
    Vector Gyroscope (void);

    /**
     * Returns the magnetic-field-vector measured by the compass sensor
     * @return Vector : x,y,z-compontens of the magnetic field in uT (micro-tesla)
     */
    Vector MagneticField (void);
    
    /**
     * Returns the gravitaional acceleration of the robot
     * @return Vector : x,y,z-compontens of the accelaration in m/s²
     */
    Vector Gravity (void);

private:

    void GetData (Adafruit_BNO055::adafruit_vector_type_t event_type);

    Adafruit_BNO055 bno_ = Adafruit_BNO055(55, 0x28, &Wire);
    sensors_event_t data_;

};

#endif