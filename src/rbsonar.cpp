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


RBSonar::RBSonar (int8_t sensor_port, uint8_t addr) : RBSensor(sensor_port, addr) 
{
}

RBSonar::RBSonar (TwoWire &i2c_wire, uint8_t addr) : RBSensor(i2c_wire, addr)
{
}

bool RBSonar::init(void)
{
    return true;
}

int RBSonar::getDistanceCentimeters(void)
{
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->openChannel(sensor_port_);
    startMeasurement();
    while( ! resultReady())
    {
        delay(1);
    }
    int measurement = readResultInCentimeters();
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->closeChannel(sensor_port_);
    return measurement;
}

void RBSonar::writeAddress(uint8_t newAddress)
{
    if(newAddress < 0x70 && newAddress > 0x7F)
    {
        Serial.println("RBSonar::writeAddress address out of range [0x70,0x7F]");
        return;
    }
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->openChannel(sensor_port_);
    command(0xA0);
    delay(60);
    command(0xAA);
    delay(60);
    command(0xA5);
    delay(60);
    command(newAddress << 1);
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->closeChannel(sensor_port_);
}

void RBSonar::startMeasurement()
{
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->openChannel(sensor_port_);
    command(CENTIMETERS); 
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->closeChannel(sensor_port_);
}

bool RBSonar::resultReady()
{
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->openChannel(sensor_port_);
    if (readResultInCentimeters() == -1)
    {
        if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->closeChannel(sensor_port_);
        return false;
    }
    else
    {
        if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->closeChannel(sensor_port_);
        return true;
    }
}

int RBSonar::readResultInCentimeters()
{
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->openChannel(sensor_port_);
    Wire.beginTransmission(sensor_i2c_address_);
    Wire.write(RANGE_REGISTER);
    Wire.endTransmission();
    Wire.requestFrom(sensor_i2c_address_, 2);
    if (Wire.available() >= 2) {
        int highByte = Wire.read();
        int lowByte = Wire.read();
        if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->closeChannel(sensor_port_);
        return (highByte << 8) + lowByte;
    }
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->closeChannel(sensor_port_);
    return -1;
}

void RBSonar::command(uint8_t cmd)
{
    Wire.beginTransmission(sensor_i2c_address_);
    Wire.write(COMMAND_REGISTER);
    Wire.write(cmd);
    Wire.endTransmission();
}
