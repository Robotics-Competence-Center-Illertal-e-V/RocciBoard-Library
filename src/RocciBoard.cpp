/**
 * @file rocciboard.cpp
*/

#include "RocciBoard.h"

RocciBoard::RocciBoard (void)
{
    motor[0] = RBMotor(5,6);
    motor[1] = RBMotor(7,8);
    motor[2] = RBMotor(9,10);
    motor[3] = RBMotor(11,12);
}

bool RocciBoard::Init (void)
{
    // Initializing Error-LED
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    // Initializing Motor Drivers
    motor[0].Init();
    motor[1].Init();
    motor[2].Init();
    motor[3].Init();
    // Initializing I2C-Multiplexer
    tca_.begin(Wire);
    tca_.closeAll();
}

void RocciBoard::OpenChannel (uint8_t index)
{
    tca_.openChannel(index);
}

void RocciBoard::CloseChannel (uint8_t index)
{
    tca_.closeChannel(index);
}

void RocciBoard::CloseAllChannels (void)
{
    tca_.closeAll();
}