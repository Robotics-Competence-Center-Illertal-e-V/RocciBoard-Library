/**
 * @file rblaser.cpp
 */

#include "rblaser.h"

#define ADDRESS_DEFAULT 0x29 // same for VL53L0X and VL53L1X
#define ID_VL53L0X_REGISTER 0xc0
#define ID_VL53L1X_REGISTER 0x010F
#define ID_VL53L0X 0xEE
#define ID_VL53L1X 0xEA


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
    startUsing();
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
    stopUsing();
    return true;
}

bool RBLaser::isConnected(void)
{
    startUsing();

    uint8_t chip_id = 0;
    wire_->beginTransmission(ADDRESS_DEFAULT);
    if(long_range_)
    {
        wire_->write(ID_VL53L1X_REGISTER >> 8);
        wire_->write(ID_VL53L1X_REGISTER & 0xFF);
    }
    else
    {
         wire_->write(ID_VL53L0X_REGISTER);
    }
    
    if (wire_->endTransmission() != 0)
    {
        stopUsing();
        return false;
    }

    if (wire_->requestFrom(ADDRESS_DEFAULT, 1) != 1)
    {
        stopUsing();
        return false;
    }

    chip_id = wire_->read();
    stopUsing();
    
    // Verify chip ID matches the expected sensor type
    if (long_range_)
    {
        if(chip_id != ID_VL53L1X)
        {
            Serial.println("Laser Chip ID falsch war: "+String(chip_id, HEX));
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        if(chip_id != ID_VL53L0X)
        {
            Serial.println("Laser Chip ID falsch war: "+String(chip_id, HEX));
            return false;
        }
        else
        {
            return true;
        }
    }
}

uint16_t RBLaser::getDistanceMillimeters(bool blocking)
{
    startUsing();
    uint16_t measurement;
    if (long_range_) {
        measurement = l1x_.readRangeContinuousMillimeters(blocking);
    } else {
        // VL53L0X API does not support blocking parameter
        measurement = l0x_.readRangeContinuousMillimeters();
    }
    stopUsing();
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