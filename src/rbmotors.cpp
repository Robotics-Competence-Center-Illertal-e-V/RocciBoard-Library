/**
 * @file rbmotors.cpp
*/

#include <rbmotors.h>

RBMotor::RBMotor (uint8_t pin_1, uint8_t pin_2)
{
    pin_1_ = pin_1;
    pin_2_ = pin_2;
}

void RBMotor::Init (void)
{
    pinMode(pin_1_, OUTPUT);
    pinMode(pin_2_, OUTPUT);
    Stop(false);
}

void RBMotor::Stop () { Stop(true); }
void RBMotor::Stop (bool brake)
{
    // 1-1: Using the slow-current-decay brake mode of the DRV8871
    // 0-0: Using the fast-current-decay coast mode of the DRV8871
    analogWrite(pin_1_, brake ? 255 : 0);
    analogWrite(pin_2_, brake ? 255 : 0);
    speed_ = 0;
}

void RBMotor::Rotate (int16_t speed)
{
    // PWM should switch between braking and powering according to the DRV8871 datasheet (-> inverse PWM value)
    analogWrite(pin_1_, speed < 0 ? 255 : 255 - speed);
    analogWrite(pin_2_, speed < 0 ? 255 + speed : 255);
    speed_ = speed;
}

int16_t RBMotor::GetSpeed (void)
{
    return speed_;
}