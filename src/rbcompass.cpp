/**
 * @file rbcompass.cpp
 */

#include "rbcompass.h"

bool RBCompass::init(void)
{
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->openChannel(sensor_port_);
    bool success = bno_.begin(); // Muss mit Adafruit I2C-Device gelöst
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->closeChannel(sensor_port_);
    return success;
}

void RBCompass::getData(Adafruit_BNO055::adafruit_vector_type_t event_type)
{
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->openChannel(sensor_port_);
    bno_.getEvent(&data_, event_type);
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->closeChannel(sensor_port_);
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
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->openChannel(sensor_port_);
    int8_t temp = bno_.getTemp();
    if(sensor_port_ != RB_NO_MULTIPLEXER) tca_->closeChannel(sensor_port_);
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