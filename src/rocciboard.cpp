/**
 * @file rocciboard.cpp
*/

#include "rocciboard.h"

RocciBoard::RocciBoard (void)
{
    motor[0] = RBMotor(5,6);
    motor[1] = RBMotor(7,8);
    motor[2] = RBMotor(9,10);
    motor[3] = RBMotor(11,12);
}

bool RocciBoard::init (void)
{
    // Initializing Error-LED
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    // Initializing Motor Drivers
    motor[0].init();
    motor[1].init();
    motor[2].init();
    motor[3].init();
    // Initializing I2C-Multiplexer
    tca_.begin(Wire);
    tca_.closeAll();
}

void RocciBoard::openSensorChannel (uint8_t sensor_port)
{
    tca_.openChannel(index);
}

void RocciBoard::closeSensorChannel (uint8_t sensor_port)
{
    tca_.closeChannel(index);
}

void RocciBoard::closeAllSensorChannels (void)
{
    tca_.closeAll();
}

RBCompass RocciBoard::initCompassSensor (uint8_t sensor_port)
{
    compass_sensor_.init(tca_, sensor_port);
    return compass_sensor_;
}

void RocciBoard::updateCompassSensor (void)
{
    openSensorChannel(compass_port_);
    compass_sensor.init();
    closeSensorChannel(compass_port_);
}