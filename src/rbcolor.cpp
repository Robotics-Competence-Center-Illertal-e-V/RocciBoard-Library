/**
 * @file rbcolor.cpp
 */

#include "rbcolor.h"

#define ADDRESS_DEFAULT 0x29
#define ID_REGISTER 0x12
#define ID_REGISTER_VALUE 0x0

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
    return true;
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