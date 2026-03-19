/**
 * RocciBoard Sensor Auto-Detect Example
 *
 * AUTHOR: Robotics Competence Center Illertal e. V.
 * VERSION: 1.0 [03-2026]
 *
 * This example scans all 8 multiplexer ports by using each sensor class'
 * isConnected() function and then reads values from detected sensors in loop().
 */

#include "rocciboard.h"

RocciBoard rb;

enum DetectedSensorType {
    SENSOR_NONE = 0,
    SENSOR_SONAR,
    SENSOR_COLOR,
    SENSOR_COMPASS,
    SENSOR_LASER_SHORT,
    SENSOR_LASER_LONG
};

DetectedSensorType detected_sensor[8];
uint8_t detected_sonar_address[8];
RBSensor* detected_instance[8] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

void printDetectedSensor(uint8_t port, DetectedSensorType type, uint8_t sonar_addr)
{
    Serial.print("Port ");
    Serial.print(port);
    Serial.print(": ");

    switch(type)
    {
        case SENSOR_SONAR:
            Serial.print("Sonar (SRF08), Adresse 0x");
            Serial.println(sonar_addr, HEX);
            break;
        case SENSOR_COLOR:
            Serial.println("Farb-Sensor (TCS34725)");
            break;
        case SENSOR_COMPASS:
            Serial.println("Kompass (BNO055)");
            break;
        case SENSOR_LASER_SHORT:
            Serial.println("Laser Short Range (VL53L0X)");
            break;
        case SENSOR_LASER_LONG:
            Serial.println("Laser Long Range (VL53L1X)");
            break;
        default:
            Serial.println("Kein Sensor erkannt");
            break;
    }
}

void detectAndInitPort(uint8_t port)
{
    detected_sensor[port] = SENSOR_NONE;
    detected_sonar_address[port] = 0x00;
    detected_instance[port] = nullptr;

    // Sonar: scan all supported SRF08 addresses (0x70 to 0x7F).
    for(uint8_t addr = 0x70; addr <= 0x7F; addr++)
    {
        RBSonar* sonar_candidate = new RBSonar(port, addr);
        if(rb.initRBSensor(*sonar_candidate))
        {
            detected_sensor[port] = SENSOR_SONAR;
            detected_sonar_address[port] = addr;
            detected_instance[port] = sonar_candidate;
            printDetectedSensor(port, detected_sensor[port], detected_sonar_address[port]);
            return;
        }
        delete sonar_candidate;
    }

    RBColor* color = new RBColor(port);
    if(rb.initRBSensor(*color))
    {
        detected_sensor[port] = SENSOR_COLOR;
        detected_instance[port] = color;
        printDetectedSensor(port, detected_sensor[port], detected_sonar_address[port]);
        return;
    }
    delete color;

    RBCompass* compass = new RBCompass(port);
    if(rb.initRBSensor(*compass))
    {
        detected_sensor[port] = SENSOR_COMPASS;
        detected_instance[port] = compass;
        printDetectedSensor(port, detected_sensor[port], detected_sonar_address[port]);
        return;
    }
    delete compass;

    RBLaser* laser_short = new RBLaser(port, TYPE_VL53L0X);
    if(rb.initRBSensor(*laser_short))
    {
        detected_sensor[port] = SENSOR_LASER_SHORT;
        detected_instance[port] = laser_short;
        printDetectedSensor(port, detected_sensor[port], detected_sonar_address[port]);
        return;
    }
    delete laser_short;

    RBLaser* laser_long = new RBLaser(port, TYPE_VL53L1X);
    if(rb.initRBSensor(*laser_long))
    {
        detected_sensor[port] = SENSOR_LASER_LONG;
        detected_instance[port] = laser_long;
        printDetectedSensor(port, detected_sensor[port], detected_sonar_address[port]);
        return;
    }
    delete laser_long;
}

void setup()
{
    if(!rb.init(false))
    {
        Serial.println("RocciBoard init fehlgeschlagen.");
        while(1) { delay(1000); }
    }
    rb.disableErrorPrint();

    Serial.println("=== Sensor Auto-Detect gestartet ===");
    for(uint8_t port = 0; port < 8; port++)
    {
        detectAndInitPort(port);
    }
    Serial.println("=== Auto-Detect abgeschlossen ===");
}

void loop()
{
    for(uint8_t port = 0; port < 8; port++)
    {
        if(detected_sensor[port] == SENSOR_NONE)
            continue;

        Serial.print("Port ");
        Serial.print(port);
        Serial.print(": ");

        switch(detected_sensor[port])
        {
            case SENSOR_SONAR:
            {
                RBSonar* sonar = static_cast<RBSonar*>(detected_instance[port]);
                Serial.print("Distanz=");
                Serial.print(sonar->getDistanceCentimeters());
                Serial.println(" cm");
                break;
            }
            case SENSOR_COLOR:
            {
                RBColor* color = static_cast<RBColor*>(detected_instance[port]);
                Serial.print("R=");
                Serial.print(color->getRed());
                Serial.print(" G=");
                Serial.print(color->getGreen());
                Serial.print(" B=");
                Serial.print(color->getBlue());
                Serial.print(" C=");
                Serial.println(color->getClear());
                break;
            }
            case SENSOR_COMPASS:
            {
                RBCompass* compass = static_cast<RBCompass*>(detected_instance[port]);
                Serial.print("Heading=");
                Serial.print(compass->getHeading());
                Serial.print(" Pitch=");
                Serial.print(compass->getPitch());
                Serial.print(" Roll=");
                Serial.println(compass->getRoll());
                break;
            }
            case SENSOR_LASER_SHORT:
            {
                RBLaser* laser_short = static_cast<RBLaser*>(detected_instance[port]);
                Serial.print("Distanz=");
                Serial.print(laser_short->getDistanceMillimeters());
                Serial.println(" mm");
                break;
            }
            case SENSOR_LASER_LONG:
            {
                RBLaser* laser_long = static_cast<RBLaser*>(detected_instance[port]);
                Serial.print("Distanz=");
                Serial.print(laser_long->getDistanceMillimeters());
                Serial.println(" mm");
                break;
            }
            default:
                Serial.println("Unbekannter Sensortyp");
                break;
        }
    }

    Serial.println("---");
    delay(500);
}
