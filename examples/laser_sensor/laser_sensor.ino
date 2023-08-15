#include "rocciboard.h"     // Include the RocciBoard Library

RocciBoard rb;

RBLaser laser(TYPE_VL53L0X);

void setup() {

    Serial.begin(9600);     // Establish Serial Connection with the PC
    rb.init();              // Initialize RocciBoard and Sensors

    // Initialize laser-sensor on sensor-port 1
    rb.initSensor(&laser, 1);
    
}

void loop() {

    // Print values to the Serial Monitor via Serial Port
    Serial.print("Distance: " + laser.getDistanceMillimeters() + " mm");

    // Delay to keep values readable
    delay(500);

}