/**
 * @file rbcolor.cpp
 */

#include "rbcolor.h"

#define ADDRESS_DEFAULT 0x29
#define ID_REGISTER 0x12
#define ID_TCS34725 0x44

RBColor::RBColor (int8_t sensor_port) : RBSensor(sensor_port)
{
}

RBColor::RBColor (TwoWire &i2c_wire) : RBSensor(i2c_wire)
{
}

bool RBColor::init(void)
{
    startUsing();
    bool success = tcs_.begin(TCS34725_ADDRESS , wire_);
    stopUsing();
    return success;
}

bool RBColor::isConnected(void)
{
    startUsing();

    uint8_t chip_id = 0;
    wire_->beginTransmission(ADDRESS_DEFAULT);
    wire_->write(ID_REGISTER);
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

    return chip_id == ID_TCS34725;
}

void RBColor::getData(void)
{
    startUsing();
    tcs_.getRawData(&red_, &green_, &blue_, &clear_);
    stopUsing();
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