#include "rocciboard.h"     // Include the RocciBoard Library

// Put global constants here: ( e.g. #define MY_CONSTANT 5 )
/* YOUR CODE HERE */

RocciBoard rb;

// Put sensor-definitions here: ( e.g. RBCompass compass; )
/* YOUR CODE HERE */

void setup() 
{

   
    Serial.begin(9600);     // Establish Serial Connection with the PC
    rb.init();              // Initialize RocciBoard and Sensors

    // Put code here, that only needs to run once: ( e.g. rb.initSensor(&compass, 0); )
    /* YOUR CODE HERE */

}

void loop() 
{

    // Put code here, that needs to be repeated: ( e.g. int16_t heading = compass.getHeading(); )
    /* YOUR CODE HERE */
    
}