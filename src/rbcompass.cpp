/**
 * @file rbcompass.cpp
*/

#include <rbcompass.h>

void RBCompass::Init (void)
{
    bno_.begin();
}

void RBCompass::GetData (Adafruit_BNO055::adafruit_vector_type_t event_type)
{
    bno_.getEvent(&data_, event_type);
}

int16_t RBCompass::Heading (void)
{
    GetData(Adafruit_BNO055::VECTOR_EULER);
    return data_.orientation.x;
}

int16_t RBCompass::Pitch (void)
{
    GetData(Adafruit_BNO055::VECTOR_EULER);
    return data_.orientation.y;
}

int16_t RBCompass::Roll (void)
{
    GetData(Adafruit_BNO055::VECTOR_EULER);
    return data_.orientation.z;
}

int8_t RBCompass::Temperature (void)
{
    return bno_.getTemp();
}

Vector RBCompass::Orientation (void)
{
    GetData(Adafruit_BNO055::VECTOR_EULER);
    return Vector{data_.orientation.x, data_.orientation.y, data_.orientation.z};
}

Vector RBCompass::Accelerometer (void)
{
    GetData(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    return Vector{data_.acceleration.x, data_.acceleration.y, data_.acceleration.z};
}

Vector RBCompass::LinearAcceleration (void)
{
    GetData(Adafruit_BNO055::VECTOR_LINEARACCEL);
    return Vector{data_.acceleration.x, data_.acceleration.y, data_.acceleration.z};
}

Vector RBCompass::Gyroscope (void)
{
    GetData(Adafruit_BNO055::VECTOR_GYROSCOPE);
    return Vector{data_.gyro.x, data_.gyro.y, data_.gyro.z};
}

Vector RBCompass::MagneticField (void)
{
    GetData(Adafruit_BNO055::VECTOR_MAGNETOMETER);
    return Vector{data_.magnetic.x, data_.magnetic.y, data_.magnetic.z};
}
    
Vector RBCompass::Gravity (void)
{
    GetData(Adafruit_BNO055::VECTOR_GRAVITY);
    return Vector{data_.acceleration.x, data_.acceleration.y, data_.acceleration.z};
}