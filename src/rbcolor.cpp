/**
 * @file rbcolor.cpp
 */

#include "rbcolor.h"

#define ADDRESS_DEFAULT 0x29
#define ID_REGISTER 0xB2 //Register 0x12 + Command Bit + Auto-Increment Bit [10100000 | 00010010]
#define ID_TCS34725 0x44 //TCS34721 and TCS34725
#define ID_TCS34723 0x4D //TCS34723 and TCS34727

RBColor::RBColor (int8_t sensor_port) : RBSensor(sensor_port)
{
}

RBColor::RBColor (TwoWire &i2c_wire) : RBSensor(i2c_wire)
{
}

bool RBColor::init(RBError* err)
{
    startUsing();
    bool success = tcs_.begin(TCS34725_ADDRESS , wire_);
    stopUsing();
    if(!success)
    {
        rbSetError(err, RB_ERR_INIT_FAILED, "RBColor", "init", sensor_port_, ADDRESS_DEFAULT);
    }
    return success;
}

bool RBColor::isConnected(RBError* err)
{
    startUsing();

    uint8_t chip_id = 0;
    wire_->beginTransmission(ADDRESS_DEFAULT);
    wire_->write(ID_REGISTER);
    if (wire_->endTransmission(false) != 0)
    {
        stopUsing();
        rbSetError(err, RB_ERR_I2C_TX_FAILED, "RBColor", "isConnected", sensor_port_, ADDRESS_DEFAULT);
        return false;
    }
    if (wire_->requestFrom(ADDRESS_DEFAULT, 1) != 1)
    {
        stopUsing();
        rbSetError(err, RB_ERR_I2C_RX_FAILED, "RBColor", "isConnected", sensor_port_, ADDRESS_DEFAULT);
        return false;
    }

    chip_id = wire_->read();
    if(chip_id == ID_TCS34725 || chip_id == ID_TCS34723)
    {
        stopUsing();
        return true;
    }
    else    
    {
        stopUsing();
        rbSetError(err, RB_ERR_SENSOR_ID_MISMATCH, "RBColor", "isConnected", sensor_port_, ADDRESS_DEFAULT, chip_id);
        return false;
    }
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