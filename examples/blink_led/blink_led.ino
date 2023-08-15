#include "rocciboard.h"     // Include the RocciBoard Library

RocciBoard rb;

void setup() 
{
   
    Serial.begin(9600);     // Establish Serial Connection with the PC
    rb.init();              // Initialize RocciBoard and Sensors

}

void loop() 
{

    // Blinks the internal Debug-LED of the RocciBoard
    digitalWrite(RB_DEBUG_LED, HIGH);
    delay(500);
    digitalWrite(RB_DEBUG_LED, LOW);
    delay(500);
    
}