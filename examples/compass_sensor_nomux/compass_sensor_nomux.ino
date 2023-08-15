/**
 * RocciBoard Compass-Sensor NoMux Example
 * 
 * AUTHOR: Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>) 
 * COPYRIGHT: Copyright (c) 2023 Robotics Competence Center Illertal e. V.
 * VERSION: 1.0 [09-2023] First release
 * 
 * This example demonstrates the use of the RocciBoard-Compass-Sensor without the built-in I²C-multiplexer.
 * The compass-sensor must be connected directly to the I²C-1 of the Arduino.
 * Initialization is performed not on the RocciBoard object, but instead directly on the sensor with init().
 * All other RBSensors are also compatible with this schema and can be used accordingly.
 */

#include "rocciboard.h"     // Include the RocciBoard Library

RocciBoard rb;

// Define laser-sensor without using the I²C-multiplexer
RBCompass compass(RB_NO_MULTIPLEXER);

void setup() {

    Serial.begin(9600);     // Establish Serial Connection with the PC
    rb.init();              // Initialize RocciBoard

    // Initialize compass-sensor without the I²C-multiplexer
    compass.init();   
    
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