/**
 * @file rbcolor.cpp
 */

#include "rbcolor.h"

bool RBColor::init(void)
{
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->openChannel(sensor_port_);
    bool success = tcs_.begin(&wire_);
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->closeChannel(sensor_port_);
    return success;
}

uint16_t RBLaser::getData(void)
{
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->openChannel(sensor_port_);
    tcs.getRawData(&red_, &green_, &blue_, &clear_);
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->closeChannel(sensor_port_);
}

uint16_t RBLaser::getRed(void)
{
    getData();
    return red_;
}

uint16_t RBLaser::getGreen(void)
{
    getData();
    return green_;
}

uint16_t RBLaser::getBlue(void)
{
    getData();
    return blue_;
}

uint16_t RBLaser::getClear(void)
{
    getData();
    return clear_;
}

uint16_t RBLaser::getColorTemperature(void)
{
    getData();
    return tcs_.calculateColorTemperature(uint16_t r, uint16_t g, uint16_t b);
}

uint16_t RBLaser::getLux(void)
{
    getData();
    return tcs_.calculateLux(red_, green_, blue_);
}