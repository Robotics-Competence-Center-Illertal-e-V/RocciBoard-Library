/**
 * RocciBoard Blinking LED Example
 * 
 * AUTHOR: Jonas Biener (<jonas.biener@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>) 
 * COPYRIGHT: Copyright (c) 2023 Robotics Competence Center Illertal e. V.
 * VERSION: 1.0 [09-2023] First release
 * 
 * This example demonstrates the ir library
 */

#include "rocciboard.h"     // Include the RocciBoard Library

RBInfrared infrared(50,51,52,53); //generate ir detector on pins 50,51,52 and 53

void setup() 
{
    Serial.begin(9600);     // Establish Serial Connection with the PC
    infrared.init();
}

void loop() 
{
  //read all 4 values of the ir detector
  delay(1000);
  Serial.print(infrared.getValue(0));
  for(int i = 1; i < 4; i++)
  {
    Serial.print(", ");
    Serial.print(infrared.getValue(i));
  }
  Serial.println();
}