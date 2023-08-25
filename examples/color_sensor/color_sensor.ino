/**
 * RocciBoard Compass-Sensor Default Example
 * 
 * AUTHOR: Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>) 
 * COPYRIGHT: Copyright (c) 2023 Robotics Competence Center Illertal e. V.
 * VERSION: 1.0 [09-2023] First release
 * 
 * This example demonstrates the use of the RocciBoard-Color-Sensor. (BNO055)
 * The color-sensor must be connected to one of the multiplexed sensor-ports of the RocciBoard.
 * Initialization is performed through the RocciBoard with initRBSensor(color) which injects the multiplexer in the sensor.
 * All other RBSensors are also compatible with this schema and can be used accordingly.
 */

#include "rocciboard.h"     // Include the RocciBoard Library

RocciBoard rb;

// Define compass-sensor on sensor-port 0
RBColor color(0);

void setup() {

    Serial.begin(9600);     // Establish Serial Connection with the PC
    rb.init();              // Initialize RocciBoard

    // Initialize compass-sensor through the RocciBoard
    rb.initRBSensor(color);
    
}

void loop() {

    // Print values to the Serial Monitor via Serial Port
    Serial.print(" Red: " + String(color.getRed()));
    Serial.print(" Green: " + String(color.getGreen()));
    Serial.print(" Blue: " + String(color.getBlue()));
    Serial.print(" Clear: " + String(color.getBlue()));

    Serial.print(" Temperature: " + String(color.getColorTemperature()));
    Serial.println(" Lux: " + String(color.getLux()));

    // Delay to keep values readable
    delay(500);

}