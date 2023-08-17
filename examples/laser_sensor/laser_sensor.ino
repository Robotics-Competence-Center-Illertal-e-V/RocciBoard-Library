/**
 * RocciBoard Laser-Sensor Default Example
 * 
 * AUTHOR: Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>) 
 * COPYRIGHT: Copyright (c) 2023 Robotics Competence Center Illertal e. V.
 * VERSION: 1.0 [09-2023] First release
 * 
 * This example demonstrates the use of the RocciBoard-Laser-Sensor. (VL53L0X or VL53L1X)
 * The laser-sensor must be connected to one of the multiplexed sensor-ports of the RocciBoard.
 * Initialization is performed through the RocciBoard with initRBSensor(&laser) which injects the multiplexer in the sensor.
 * All other RBSensors are also compatible with this schema and can be used accordingly.
 */

#include "rocciboard.h"     // Include the RocciBoard Library

RocciBoard rb;

// Define laser-sensor on sensor-port 0
RBLaser laser(TYPE_VL53L0X);

void setup() {

    Serial.begin(9600);     // Establish Serial Connection with the PC
    rb.init();              // Initialize RocciBoard

    // Initialize laser-sensor on sensor-port 1
    rb.initSensor(laser, 1);
    
}

void loop() {

    // Print values to the Serial Monitor via Serial Port
    Serial.print("Distance: " + laser.getDistanceMillimeters() + " mm");

    // Delay to keep values readable
    delay(500);

}