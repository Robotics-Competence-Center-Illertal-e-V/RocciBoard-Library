/**
 * RocciBoard Driving Example
 * 
 * AUTHOR: Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>) 
 * COPYRIGHT: Copyright (c) 2023 Robotics Competence Center Illertal e. V.
 * VERSION: 1.0 [09-2023] First release
 * 
 * This example demonstrates the use of the RocciBoard-Motor-Functions.
 * After initialization the motors are conteolled on a timed basis.
 * The example uses a custom defined function stopAllMotors(bool brake) to stop all motors,
 * which shows the adaptability of the library to your own functions.
 */

#include "rocciboard.h"     // Include the RocciBoard Library

RocciBoard rb;

void setup() {

    Serial.begin(9600);     // Establish Serial Connection with the PC
    rb.init();              // Initialize RocciBoard
    
}

void loop() {

    // Drive forwards. Wait. Drive Backwards. Wait.
    rb.motor[0].rotate(100);
    rb.motor[1].rotate(100);
    delay(1000);

    stopAllMotors(true);
    delay(1000);

    rb.motor[0].rotate(-100);
    rb.motor[1].rotate(-100);
    delay(1000);

    stopAllMotors(true);
    delay(1000);

}

// Custom function to stop all motors
void stopAllMotors (bool brake) 
{
    rb.motor[0].stop(brake);
    rb.motor[1].stop(brake);
}