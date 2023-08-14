#include "rocciboard.h"

RocciBoard rb;

void setup() {

    // Initialize RocciBoard and Motor Drivers
    rb.init();
    
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

void stopAllMotors (bool brake) 
{
    rb.motor[0].stop(brake);
    rb.motor[1].stop(brake);
}