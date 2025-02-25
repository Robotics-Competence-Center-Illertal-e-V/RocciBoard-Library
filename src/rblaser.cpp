/**
 * @file rblaser.cpp
 */

#include "rblaser.h"

#define ADDRESS_DEFAULT 0b0101001 // same for VL53L0X and VL53L1X 

RBLaser::RBLaser (int8_t sensor_port, bool is_long_range) : RBSensor(sensor_port, ADDRESS_DEFAULT)
{
    long_range_ = is_long_range;
}

RBLaser::RBLaser (TwoWire &i2c_wire, bool is_long_range) : RBSensor(i2c_wire, ADDRESS_DEFAULT)
{
    long_range_ = is_long_range;
}

bool RBLaser::init(void)
{
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->openChannel(sensor_port_);
    if (long_range_)
    {
        l1x_.setBus(wire_);
        if(!l1x_.init()) return false;
        l1x_.setTimeout(500);
        l1x_.startContinuous(33);
        l1x_.setMeasurementTimingBudget(33000);
    }
    else
    {
        l0x_.setBus(wire_);
        if(!l0x_.init()) return false;
        l0x_.setTimeout(500);
        l0x_.startContinuous(33);
        l0x_.setMeasurementTimingBudget(33000);
    }
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->closeChannel(sensor_port_);
    return true;
}

uint16_t RBLaser::getDistanceMillimeters(bool blocking)
{
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->openChannel(sensor_port_);
    uint16_t measurement = long_range_ ? l1x_.readRangeContinuousMillimeters(blocking) : l0x_.readRangeContinuousMillimeters();
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->closeChannel(sensor_port_);
    return measurement;
}

float RBLaser::getDistanceCentimeters(bool blocking)
{
    return (float)getDistanceMillimeters(blocking) / 10.0f;
}

float RBLaser::getDistanceMeters(bool blocking)
{
    return (float)getDistanceMillimeters(blocking) / 1000.0f;
}

float RBLaser::getDistanceInches(bool blocking)
{
    return (float)getDistanceMillimeters(blocking) / 25.4f;
}

float RBLaser::getDistanceFeet(bool blocking)
{
    return (float)getDistanceMillimeters(blocking) / 304.8f;
}