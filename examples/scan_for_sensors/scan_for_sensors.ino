/**
 * RocciBoard Sonar-Sensor Default Example
 * 
 * AUTHOR: Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>) 
 * COPYRIGHT: Copyright (c) 2023 Robotics Competence Center Illertal e. V.
 * VERSION: 1.0 [09-2023] First release
 * 
 * This example demonstrates the i2c scan and sensor scan functions of the RocciBoard.
 * The functions can be used to identify connected sensors and their addresses for debugging purposes.
 */
#include "rocciboard.h"     // Include the RocciBoard Library

RocciBoard rb;             

void setup() 
{
    rb.init();              // Initialize RocciBoard
    rb.scanI2C();
    rb.scanSensors();
}

void loop() 
{
}