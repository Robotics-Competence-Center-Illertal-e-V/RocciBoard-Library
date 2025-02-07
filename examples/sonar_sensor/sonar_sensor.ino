/**
 * RocciBoard Sonar-Sensor Default Example
 * 
 * AUTHOR: Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>) 
 * COPYRIGHT: Copyright (c) 2023 Robotics Competence Center Illertal e. V.
 * VERSION: 1.0 [09-2023] First release
 * 
 * This example demonstrates the use of the RocciBoard-Sonar-Sensor. (SRF08)
 * The sonar-sensor must be connected to one of the multiplexed sensor-ports of the RocciBoard.
 * Initialization is performed through the RocciBoard with initRBSensor(sonar) which injects the multiplexer in the sensor.
 * All other RBSensors are also compatible with this schema and can be used accordingly.
 */

#include "rocciboard.h"     // Include the RocciBoard Library

RocciBoard rb;

// Define sonar-sensor on sensor-port 0
RBSonar sonar(0);

void setup() {

    Serial.begin(9600);     // Establish Serial Connection with the PC
    rb.init();              // Initialize RocciBoard

    // Initialize sonar-sensor on sensor-port 1
    rb.initRBSensor(sonar);
    
}

void loop() {

    // Print values to the Serial Monitor via Serial Port
    Serial.println("Distance: " + String(sonar.getDistanceCentimeters()) + " cm");

    // Delay to keep values readable
    delay(500);

}