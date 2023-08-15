#include "rocciboard.h"     // Include the RocciBoard Library

RocciBoard rb;

RBCompass compass;

void setup() {

    Serial.begin(9600);     // Establish Serial Connection with the PC
    rb.init();              // Initialize RocciBoard and Sensors

    // Initialize compass-sensor on sensor-port 0
    rb.initSensor(&compass, 0);
    
}

void loop() {

    // Print values to the Serial Monitor via Serial Port
    Serial.print(" Heading: " + compass.getHeading());
    Serial.print(" Pitch: " + compass.getPitch());
    Serial.print(" Roll: " + compass.getRoll());

    RBVector magneticField = compass.getVecMagneticField();
    Serial.print(" Magnetic field: ");
    Serial.println("( " + magneticField.x + " , " + magneticField.y + " , " + magneticField.z + " )");

    // Delay to keep values readable
    delay(500);

}