/**
 * @file rbcompass.cpp
*/

#include <rbcompass.h>

void RBCompass::init_NoMux (void)
{
    bno_.begin();
}
void RBCompass::init (TCA9548A tca, uint8_t sensor_port)
{
    tca_ = tca;
    port_ = sensor_port;
    tca_.openChannel(port_);
    bno_.begin();
    tca_.closeChannel(port_);
}

void RBCompass::getData_NoMux (Adafruit_BNO055::adafruit_vector_type_t event_type)
{
    bno_.getEvent(&data_, event_type);
}
void RBCompass::getData (Adafruit_BNO055::adafruit_vector_type_t event_type)
{
    tca_.openChannel(port_);
    bno_.getEvent(&data_, event_type);
    tca_.closeChannel(port_);
}

int16_t RBCompass::getHeading_NoMux (void)
{
    getData_NoMux(Adafruit_BNO055::VECTOR_EULER);
    return data_.orientation.x;
}
int16_t RBCompass::getHeading (void)
{
    getData(Adafruit_BNO055::VECTOR_EULER);
    return data_.orientation.x;
}

int16_t RBCompass::getPitch_NoMux (void)
{
    getData_NoMux(Adafruit_BNO055::VECTOR_EULER);
    return data_.orientation.y;
}
int16_t RBCompass::getPitch (void)
{
    getData(Adafruit_BNO055::VECTOR_EULER);
    return data_.orientation.y;
}

int16_t RBCompass::getRoll_NoMux (void)
{
    getData_NoMux(Adafruit_BNO055::VECTOR_EULER);
    return data_.orientation.z;
}
int16_t RBCompass::getRoll (void)
{
    getData(Adafruit_BNO055::VECTOR_EULER);
    return data_.orientation.z;
}

int8_t RBCompass::getTemperature_NoMux (void)
{
    return bno_.getTemp();
}
int8_t RBCompass::getTemperature (void)
{
    tca_.openChannel(port_);
    int8_t temp = bno_.getTemp();
    tca_.closeChannel(port_);
    return temp;
}

RBVector RBCompass::getVecOrientation_NoMux (void)
{
    getData_NoMux(Adafruit_BNO055::VECTOR_EULER);
    return RBVector{data_.orientation.x, data_.orientation.y, data_.orientation.z};
}
RBVector RBCompass::getVecOrientation (void)
{
    getData(Adafruit_BNO055::VECTOR_EULER);
    return RBVector{data_.orientation.x, data_.orientation.y, data_.orientation.z};
}

RBVector RBCompass::getVecAccelerometer_NoMux (void)
{
    getData_NoMux(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    return RBVector{data_.acceleration.x, data_.acceleration.y, data_.acceleration.z};
}
RBVector RBCompass::getVecAccelerometer (void)
{
    getData(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    return RBVector{data_.acceleration.x, data_.acceleration.y, data_.acceleration.z};
}

RBVector RBCompass::getVecLinearAcceleration_NoMux (void)
{
    getData_NoMux(Adafruit_BNO055::VECTOR_LINEARACCEL);
    return RBVector{data_.acceleration.x, data_.acceleration.y, data_.acceleration.z};
}
RBVector RBCompass::getVecLinearAcceleration (void)
{
    getData(Adafruit_BNO055::VECTOR_LINEARACCEL);
    return RBVector{data_.acceleration.x, data_.acceleration.y, data_.acceleration.z};
}

RBVector RBCompass::getVecGyroscope_NoMux (void)
{
    getData_NoMux(Adafruit_BNO055::VECTOR_GYROSCOPE);
    return RBVector{data_.gyro.x, data_.gyro.y, data_.gyro.z};
}
RBVector RBCompass::getVecGyroscope (void)
{
    getData(Adafruit_BNO055::VECTOR_GYROSCOPE);
    return RBVector{data_.gyro.x, data_.gyro.y, data_.gyro.z};
}

RBVector RBCompass::getVecMagneticField_NoMux (void)
{
    getData_NoMux(Adafruit_BNO055::VECTOR_MAGNETOMETER);
    return RBVector{data_.magnetic.x, data_.magnetic.y, data_.magnetic.z};
}
RBVector RBCompass::getVecMagneticField (void)
{
    getData(Adafruit_BNO055::VECTOR_MAGNETOMETER);
    return RBVector{data_.magnetic.x, data_.magnetic.y, data_.magnetic.z};
}
    
RBVector RBCompass::getVecGravity_NoMux (void)
{
    getData_NoMux(Adafruit_BNO055::VECTOR_GRAVITY);
    return RBVector{data_.acceleration.x, data_.acceleration.y, data_.acceleration.z};
}
RBVector RBCompass::getVecGravity (void)
{
    getData(Adafruit_BNO055::VECTOR_GRAVITY);
    return RBVector{data_.acceleration.x, data_.acceleration.y, data_.acceleration.z};
}