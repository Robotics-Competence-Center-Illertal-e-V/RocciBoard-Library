/**
 * RocciBoard IR-Receiver Example (Arduino Due)
 * 
 * AUTHOR: Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>) 
 * COPYRIGHT: Copyright (c) 2023 Robotics Competence Center Illertal e. V.
 * VERSION: 1.0 [01-2025] First release
 * 
 * This example demonstrates the use of IR-Seekers with the RocciBoard. (TSOP)
 * The sensors (max. 17 at once) must be connected to the supported interrupt pins of the RocciBoard. (14, 15, 16, 17, 18, 19, 20, 21, 22, 46, 47, 48, 49, 50, 51, 52, 53)
 * When instantiating, the order that you pass the pins of the sensors is the index you will address them by later.
 */

#include "rocciboard.h"     // Include the RocciBoard Library

// Generate the IR-receivers on pins 50, 51, 52 and 53
RBInfrared infrared(50, 51, 52, 53); 

void setup() 
{
    Serial.begin(9600);     // Establish Serial Connection with the PC

    // Initialize the infrared-sensors
    infrared.init();
}

void loop() 
{
  // Delay to keep values readable
  delay(1000);

  // Read all four values of the IR-receivers
  Serial.print(infrared.getValue(0));
  for(int i = 1; i < 4; i++)
  {
    Serial.print(", ");
    Serial.print(infrared.getValue(i));
  }
  Serial.println();
}