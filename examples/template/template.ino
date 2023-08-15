/**
 * ## TITLE OR NAME OF THE FILE/PROJECT ##
 * 
 * AUTHOR: ## NAME(S) OF THE AUTHOR(S) ##
 * VERSION: ## VERSION ##
 * 
 * ## DESCRIPTION OR OTHER DETAILS IF NEEDED ##
 */

#include "rocciboard.h"     // Include the RocciBoard Library

// Put global constants here: ( e.g. #define MY_CONSTANT 5 )
/* ## CODE ## */

RocciBoard rb;              // Define the RocciBoard-object

// Put sensor-definitions here: ( e.g. RBLaser compass(0); )
/* ## CODE ## */

void setup() 
{

   
    Serial.begin(9600);     // Establish Serial Connection with the PC
    rb.init();              // Initialize RocciBoard

    // Put code here, that only needs to run once: ( e.g. rb.initSensor(&compass); )
    /* ## CODE ## */

}

void loop() 
{

    // Put code here, that needs to be repeated: ( e.g. int heading = compass.getHeading(); )
    /* ## CODE ## */
    
}