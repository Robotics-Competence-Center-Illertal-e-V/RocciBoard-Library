#include "rocciboard.h"

RocciBoard rb;
RBCompass compass;

void setup() {

    // Initialize RocciBoard
    rb.init();

    // Initialize compass-sensor on sensor-port 1
    compass = rb.initCompassSensor(1);
    
}

void loop() {

    Serial.print(" Heading: " + compass.getHeading());
    Serial.print(" Pitch: " + compass.getPitch());
    Serial.print(" Roll: " + compass.getRoll());

    RBVector magneticField = compass.getVecMagneticField();
    Serial.print(" Magnetic field: ");
    Serial.println("( " + magneticField.x + " , " + magneticField.y + " , " + magneticField.z + " )");

    delay(500);

}