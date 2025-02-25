/**
 * @file rbcolor.cpp
 */

#include "rbcolor.h"

#define ADDRESS_DEFAULT 0x29

RBColor::RBColor (int8_t sensor_port) : RBSensor(sensor_port, ADDRESS_DEFAULT)
{
}

RBColor::RBColor (TwoWire &i2c_wire) : RBSensor(i2c_wire, ADDRESS_DEFAULT)
{
}

bool RBColor::init(void)
{
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->openChannel(sensor_port_);
    bool success = tcs_.begin(TCS34725_ADDRESS , wire_);
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->closeChannel(sensor_port_);
    return success;
}

void RBColor::getData(void)
{
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->openChannel(sensor_port_);
    tcs_.getRawData(&red_, &green_, &blue_, &clear_);
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->closeChannel(sensor_port_);
}

uint16_t RBColor::getRed(void)
{
    getData();
    return red_;
}

uint16_t RBColor::getGreen(void)
{
    getData();
    return green_;
}

uint16_t RBColor::getBlue(void)
{
    getData();
    return blue_;
}

uint16_t RBColor::getClear(void)
{
    getData();
    return clear_;
}

uint16_t RBColor::getColorTemperature(void)
{
    getData();
    return tcs_.calculateColorTemperature(red_, green_, blue_);
}

uint16_t RBColor::getLux(void)
{
    getData();
    return tcs_.calculateLux(red_, green_, blue_);
}