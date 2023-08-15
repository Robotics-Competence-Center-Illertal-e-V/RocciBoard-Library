/**
 * @file rblaser.cpp
 */

#include "rblaser.h"

RBLaser::RBLaser (bool is_long_range)
{
    long_range_ = is_long_range;
}

bool RBLaser::init(void)
{
    tca_->openChannel(sensor_port_);
    if (long_range_)
    {
        if(!l1x_.init()) return false;
        l1x_.setTimeout(500);
        l1x_.startContinuous(33);
        l1x_.setMeasurementTimingBudget(33000);
    }
    else
    {
        if(!l0x_.init()) return false;
        l0x_.setTimeout(500);
        l0x_.startContinuous(33);
        l0x_.setMeasurementTimingBudget(33000);
    }
    tca_->closeChannel(sensor_port_);
    return true;
}
bool RBLaser::init_NoMux(void)
{
    if (long_range_)
    {
        if(!l1x_.init()) return false;
        l1x_.setTimeout(500);
        l1x_.startContinuous(33);
        l1x_.setMeasurementTimingBudget(33000);
    }
    else
    {
        if(!l0x_.init()) return false;
        l0x_.setTimeout(500);
        l0x_.startContinuous(33);
        l0x_.setMeasurementTimingBudget(33000);
    }
    return true;
}

uint16_t RBLaser::getDistanceMillimeters(void)
{
    tca_->openChannel(sensor_port_);
    uint16_t measurement = long_range_ ? l1x_.readRangeContinuousMillimeters() : l0x_.readRangeContinuousMillimeters();
    tca_->closeChannel(sensor_port_);
    return measurement;
}
uint16_t RBLaser::getDistanceMillimeters_NoMux(void)
{
    return long_range_ ? l1x_.readRangeContinuousMillimeters() : l0x_.readRangeContinuousMillimeters();
}