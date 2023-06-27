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
    motor[0].Init();
    motor[1].Init();
    motor[2].Init();
    motor[3].Init();
}