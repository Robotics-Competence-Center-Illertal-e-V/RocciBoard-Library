/**
 * @file rblaser.cpp
 */

#include "rblaser.h"

RBLaser::RBLaser (int8_t sensor_port, bool is_long_range) : RBSensor(sensor_port)
{
    long_range_ = is_long_range;
}

RBLaser::RBLaser (TwoWire &i2c_wire, bool is_long_range) : RBSensor(i2c_wire)
{
    long_range_ = is_long_range;
}

bool RBLaser::init(void)
{
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->openChannel(sensor_port_);
    if (long_range_)
    {
        if(!l1x_.init(wire_)) return false;
        l1x_.setTimeout(500);
        l1x_.startContinuous(33);
        l1x_.setMeasurementTimingBudget(33000);
    }
    else
    {
        if(!l0x_.init(wire_)) return false;
        l0x_.setTimeout(500);
        l0x_.startContinuous(33);
        l0x_.setMeasurementTimingBudget(33000);
    }
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->closeChannel(sensor_port_);
    return true;
}

uint16_t RBLaser::getDistanceMillimeters(void)
{
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->openChannel(sensor_port_);
    uint16_t measurement = long_range_ ? l1x_.readRangeContinuousMillimeters() : l0x_.readRangeContinuousMillimeters();
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->closeChannel(sensor_port_);
    return measurement;
}

float RBLaser::getDistanceCentimeters(void)
{
    return (float)getDistanceMillimeters() / 10.0f;
}

float RBLaser::getDistanceMeters(void)
{
    return (float)getDistanceMillimeters() / 1000.0f;
}

float RBLaser::getDistanceInches(void)
{
    return (float)getDistanceMillimeters() / 25.4f;
}

float RBLaser::getDistanceFeet(void)
{
    return (float)getDistanceMillimeters() / 304.8f;
}