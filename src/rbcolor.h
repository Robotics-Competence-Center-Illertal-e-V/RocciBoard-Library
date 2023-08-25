/**
 * @file rblaser.h
 *
 * Adafruit-TCS34725 Library for use with the RocciBoard
 *
 * @author Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>)
 * @version 1.0 [09-2023] First stable release
 */

#ifndef rbcolor_h
#define rbcolor_h

#include "rbsensor.h"

#include "Adafruit_TCS34725.h"

/**
 * Class for implementing the TCS34725 color-sensor for easy usage.
 */
class RBColor : public RBSensor
{

    public:
        using RBSensor::RBSensor;

        /**
         * Initializes the VL53L0X and VL53L1X compass sensor
        */    
        virtual bool init(void);

        /**
         * Reads the current reflectance-value of the color red
         * @return uint16_t: value of color red (0-1024)
         */
        uint16_t getRed(void);

        /**
         * Reads the current reflectance-value of the color green
         * @return uint16_t: value of color green (0-1024)
         */
        uint16_t getGreen(void);
        
        /**
         * Reads the current reflectance-value of the color blue
         * @return uint16_t: value of color blue (0-1024)
         */
        uint16_t getBlue(void);

        /**
         * Reads the current overall reflectance-brightness
         * @return uint16_t: value of the brightness (0-1024)
         */
        uint16_t getClear(void);

        /**
         * Reads the current color temperature
         * @return uint16_t: color temperature in degrees kelvin
         */
        uint16_t getColorTemperature(void);

        /**
         * Reads the current lux-illuminance value
         * @return uint16_t: illumniance ("brightness") in lux
         */
        uint16_t getLux(void);

    private:
        /**
         * Updates the values of the color-sensor
        */  
        void getData (void);

        Adafruit_TCS34725 tcs_;
        uint16_t red_ = 0; 
        uint16_t green_ = 0; 
        uint16_t blue_ = 0; 
        uint16_t clear_ = 0;

};

#endif