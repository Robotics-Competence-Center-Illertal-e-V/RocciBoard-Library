#include "rocciboard.h"     // Include the RocciBoard Library

RocciBoard rb;

void setup() {

    Serial.begin(9600);     // Establish Serial Connection with the PC
    rb.init();              // Initialize RocciBoard and Sensors
    
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