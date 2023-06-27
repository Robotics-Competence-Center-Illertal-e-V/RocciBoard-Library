#include "rocciboard.h"

RocciBoard rb;

void setup() {
    // Initialize RocciBoard and Motor Drivers
    rb.Init();
}

void loop() {
    // Drive forwards. Wait. Drive Backwards. Wait.
    rb.motor[0].Rotate(100);
    rb.motor[1].Rotate(100);
    delay(1000);
    rb.motor[0].Stop(true);
    rb.motor[1].Stop(true);
    delay(1000);
    rb.motor[0].Rotate(-100);
    rb.motor[1].Rotate(-100);
    delay(1000);
    rb.motor[0].Stop(true);
    rb.motor[1].Stop(true);
    delay(1000);
}