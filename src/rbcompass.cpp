/**
 * @file rbcompass.cpp
 */

#include "rbcompass.h"

#define ADDRESS_DEFAULT 0x28
#define ID_REGISTER 0x0
#define ID_REGISTER_VALUE 0xA0

RBCompass::RBCompass (int8_t sensor_port) : RBSensor(sensor_port)
{
}

RBCompass::RBCompass (TwoWire &i2c_wire) : RBSensor(i2c_wire)
{
}

bool RBCompass::init(RBError* err)
{
    startUsing();
    bool success = bno_.begin(); // Muss mit Adafruit I2C-Device gelöst
    stopUsing();
    if(!success)
    {
        rbSetError(err, RB_ERR_INIT_FAILED, "RBCompass", "init", sensor_port_, ADDRESS_DEFAULT);
    }
    return success;
}

bool RBCompass::isConnected(RBError* err)
{
    startUsing();
    wire_->beginTransmission(ADDRESS_DEFAULT);
    wire_->write(ID_REGISTER);  // set register for read
    int error = wire_->endTransmission(false);// false to not release the line
    if(error == 0) //continue
    {   
        wire_->requestFrom(ADDRESS_DEFAULT, 1); // request 1 byte from register XY
        if(wire_->available() < 1)
        {
            stopUsing();
            rbSetError(err, RB_ERR_I2C_RX_FAILED, "RBCompass", "isConnected", sensor_port_, ADDRESS_DEFAULT);
            return false;
        }
        uint8_t read_sensor_id = 0;   
        wire_->readBytes(&read_sensor_id, 1); 
        if(read_sensor_id == ID_REGISTER_VALUE)
        {
            error = 0;
        }
        else
        {
            error = 1;
        }
    }
    else
    {
        rbSetError(err, RB_ERR_I2C_TX_FAILED, "RBCompass", "isConnected", sensor_port_, ADDRESS_DEFAULT, error);
    }
    stopUsing();
    if(error == 0)
        return true;
    else
    {
        rbSetError(err, RB_ERR_SENSOR_ID_MISMATCH, "RBCompass", "isConnected", sensor_port_, ADDRESS_DEFAULT);
        return false;
    }
}

void RBCompass::getData(Adafruit_BNO055::adafruit_vector_type_t event_type)
{
    startUsing();
    bno_.getEvent(&data_, event_type);
    stopUsing();
}

int16_t RBCompass::getHeading(void)
{
    getData(Adafruit_BNO055::VECTOR_EULER);
    return data_.orientation.x;
}

int16_t RBCompass::getPitch(void)
{
    getData(Adafruit_BNO055::VECTOR_EULER);
    return data_.orientation.y;
}

int16_t RBCompass::getRoll(void)
{
    getData(Adafruit_BNO055::VECTOR_EULER);
    return data_.orientation.z;
}

int8_t RBCompass::getTemperatureCelsius(void)
{
    startUsing();
    int8_t temp = bno_.getTemp();
    stopUsing();
    return temp;
}

RBVector RBCompass::getVecOrientation(void)
{
    getData(Adafruit_BNO055::VECTOR_EULER);
    return RBVector{data_.orientation.x, data_.orientation.y, data_.orientation.z};
}

RBVector RBCompass::getVecAccelerometer(void)
{
    getData(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    return RBVector{data_.acceleration.x, data_.acceleration.y, data_.acceleration.z};
}

RBVector RBCompass::getVecLinearAcceleration(void)
{
    getData(Adafruit_BNO055::VECTOR_LINEARACCEL);
    return RBVector{data_.acceleration.x, data_.acceleration.y, data_.acceleration.z};
}

RBVector RBCompass::getVecGyroscope(void)
{
    getData(Adafruit_BNO055::VECTOR_GYROSCOPE);
    return RBVector{data_.gyro.x, data_.gyro.y, data_.gyro.z};
}

RBVector RBCompass::getVecMagneticField(void)
{
    getData(Adafruit_BNO055::VECTOR_MAGNETOMETER);
    return RBVector{data_.magnetic.x, data_.magnetic.y, data_.magnetic.z};
}

RBVector RBCompass::getVecGravity(void)
{
    getData(Adafruit_BNO055::VECTOR_GRAVITY);
    return RBVector{data_.acceleration.x, data_.acceleration.y, data_.acceleration.z};
}