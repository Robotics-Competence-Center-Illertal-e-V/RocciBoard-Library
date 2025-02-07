/**
 * @file rbsonar.cpp
 */

#include "rbsonar.h"


#define MAIN_08_ADDRESS (0xF8 >> 1)

// Setup Analogue Gain
// http://www.robot-electronics.co.uk/htm/srf08tech.html section "Analogue Gain"
#define GAIN_REGISTER 0x09
// Setup Range Location
// http://www.robot-electronics.co.uk/htm/srf08tech.html section "Changing the Range"
#define LOCATION_REGISTER 0x8C


RBSonar::RBSonar (int8_t sensor_port, uint8_t addr) : RBSensor(sensor_port), srf08_(MAIN_08_ADDRESS+addr, GAIN_REGISTER, LOCATION_REGISTER)
{
}

RBSonar::RBSonar (TwoWire &i2c_wire, uint8_t addr) : RBSensor(i2c_wire), srf08_(MAIN_08_ADDRESS+addr, GAIN_REGISTER, LOCATION_REGISTER)
{
}

bool RBSonar::init(void)
{
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->openChannel(sensor_port_);
    srf08_.begin();
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->closeChannel(sensor_port_);
    return true;
}

float RBSonar::getDistanceCentimeters(void)
{
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->openChannel(sensor_port_);
    float measurement = (float)srf08_.readRange('c');
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->closeChannel(sensor_port_);
    return measurement;
}

void RBSonar::writeAddress(uint8_t addr)
{
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->openChannel(sensor_port_);
    srf08_.writeAddress(addr);
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->closeChannel(sensor_port_);
}