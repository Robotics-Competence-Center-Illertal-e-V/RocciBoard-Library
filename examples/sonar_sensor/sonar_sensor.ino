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
#include "rocciboard.h"

//Ultraschall an Rocciboard Port 0
RBSonar sonar(0);

// der Multiplexer muss auf einer anderen Addresse konfiguriert werden wie die SRF08 (default = 0x70). 
// Dazu müssen die Lötbrücken A0,A1 und A2 auf VDD für zB 0x77
RocciBoard rb(0x77); 

void setup() {
  Serial.begin(9600);
  rb.init();
  rb.initRBSensor(sonar);
}

void loop() {
    int distance = sonar.getDistanceCentimeters();
    Serial.print("Entfernung: ");
    Serial.print(distance);
    Serial.println(" cm");
}

