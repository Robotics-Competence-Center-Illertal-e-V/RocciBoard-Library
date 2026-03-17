/**
 * @file rbsonar.cpp
 */

#include "rbsonar.h"


// Read
#define SOFTWARE_REVISION 0x00
#define LIGHT_SENSOR      0x01
// Write
#define COMMAND_REGISTER  0x00
#define MAX_GAIN_REGISTER 0x01
#define RANGE_REGISTER    0x02
// Units
#define INCHES            0x50
#define CENTIMETERS       0x51
#define MICROSECONDS      0x52


RBSonar::RBSonar (int8_t sensor_port, uint8_t addr) : RBSensor(sensor_port) 
{
    _srf_address = addr;
}

RBSonar::RBSonar (TwoWire &i2c_wire, uint8_t addr) : RBSensor(i2c_wire)
{
    _srf_address = addr;
}

bool RBSonar::init(void)
{
    return true;
}

bool RBSonar::isConnected(void)
{
    startUsing();

    wire_->beginTransmission(_srf_address);
    wire_->write(SOFTWARE_REVISION);
    if (wire_->endTransmission() != 0)
    {
        stopUsing();
        return false;
    }

    if (wire_->requestFrom(_srf_address, 1) != 1)
    {
        stopUsing();
        return false;
    }

    uint8_t revision = wire_->read();
    stopUsing();

    // SRF08 returns a non-zero software revision value
    return revision != 0;
}

int RBSonar::getDistanceCentimeters(void)
{
    startUsing();
    startMeasurement();
    while( ! resultReady())
    {
        delay(1);
    }
    int measurement = readResultInCentimeters();
    stopUsing();
    return measurement;
}

void RBSonar::writeAddress(uint8_t newAddress)
{
    if(newAddress < 0x70 || newAddress > 0x7F)
    {
        Serial.println("RBSonar::writeAddress address out of range [0x70,0x7F]");
        return;
    }
    startUsing();
    command(0xA0);
    delay(60);
    command(0xAA);
    delay(60);
    command(0xA5);
    delay(60);
    command(newAddress << 1);
    stopUsing();
}

void RBSonar::startMeasurement()
{
    startUsing();
    command(CENTIMETERS); 
    stopUsing();
}

bool RBSonar::resultReady()
{
    startUsing();
    if (readResultInCentimeters() == -1)
    {
        stopUsing();
        return false;
    }
    else
    {
        stopUsing();
        return true;
    }
}

int RBSonar::readResultInCentimeters()
{
    startUsing();
    wire_->beginTransmission(_srf_address);
    wire_->write(RANGE_REGISTER);
    wire_->endTransmission();
    wire_->requestFrom(_srf_address, 2);
    if (wire_->available() >= 2) {
        int highByte = wire_->read();
        int lowByte = wire_->read();
        stopUsing();
        return (highByte << 8) + lowByte;
    }
    stopUsing();
    return -1;
}

void RBSonar::command(uint8_t cmd)
{
    wire_->beginTransmission(_srf_address);
    wire_->write(COMMAND_REGISTER);
    wire_->write(cmd);
    wire_->endTransmission();
}
