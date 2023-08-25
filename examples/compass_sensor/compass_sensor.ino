/**
 * RocciBoard Compass-Sensor Default Example
 * 
 * AUTHOR: Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>) 
 * COPYRIGHT: Copyright (c) 2023 Robotics Competence Center Illertal e. V.
 * VERSION: 1.0 [09-2023] First release
 * 
 * This example demonstrates the use of the RocciBoard-Compass-Sensor. (BNO055)
 * The compass-sensor must be connected to one of the multiplexed sensor-ports of the RocciBoard.
 * Initialization is performed through the RocciBoard with initRBSensor(&compass) which injects the multiplexer in the sensor.
 * All other RBSensors are also compatible with this schema and can be used accordingly.
 */

#include "rocciboard.h"     // Include the RocciBoard Library

RocciBoard rb;

// Define compass-sensor on sensor-port 0
RBCompass compass(0);

void setup() {

    Serial.begin(9600);     // Establish Serial Connection with the PC
    rb.init();              // Initialize RocciBoard

    // Initialize compass-sensor through the RocciBoard
    rb.initRBSensor(compass);
    
}

void loop() {

    // Print values to the Serial Monitor via Serial Port
    Serial.print(" Heading: " + String(compass.getHeading()));
    Serial.print(" Pitch: " + String(compass.getPitch()));
    Serial.print(" Roll: " + String(compass.getRoll()));

    RBVector magneticField = compass.getVecMagneticField();
    Serial.print(" Magnetic field: ");
    Serial.println("( " + String(magneticField.x) + " , " + String(magneticField.y) + " , " + String(magneticField.z) + " )");

    // Delay to keep values readable
    delay(500);

}