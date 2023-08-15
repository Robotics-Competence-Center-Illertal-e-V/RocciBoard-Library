/**
 * RocciBoard Blinking LED Example
 * 
 * AUTHOR: Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>) 
 * COPYRIGHT: Copyright (c) 2023 Robotics Competence Center Illertal e. V.
 * VERSION: 1.0 [09-2023] First release
 * 
 * This example demonstrates the most simple program on the RocciBoard: Blinking a LED.
 * It is just as simple as it sounds: The RB_DEBUG_LED is turned on and off with a delay
 * using the default Arduino pinMode-function.
 */

#include "rocciboard.h"     // Include the RocciBoard Library

RocciBoard rb;

void setup() 
{
   
    Serial.begin(9600);     // Establish Serial Connection with the PC
    rb.init();              // Initialize RocciBoard

}

void loop() 
{

    // Blinks the internal Debug-LED of the RocciBoard
    digitalWrite(RB_DEBUG_LED, HIGH);
    delay(500);
    digitalWrite(RB_DEBUG_LED, LOW);
    delay(500);
    
}