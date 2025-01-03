/**
 * @file rocciboard.cpp
*/

#include "Arduino.h"
#include "rocciboard.h"

RocciBoard::RocciBoard (void)
{
    motor[0] = RBMotor(5,6);
    motor[1] = RBMotor(7,8);
    motor[2] = RBMotor(9,10);
    motor[3] = RBMotor(11,12);
}

void RocciBoard::init (void)
{
    // Initializing Error-LED
    pinMode(RB_DEBUG_LED, OUTPUT);
    digitalWrite(RB_DEBUG_LED, LOW);
    // Initializing the voltage-reading ADC
    pinMode(RB_BATTERY_ADC, INPUT);
    // Initializing Motor Drivers
    motor[0].init();
    motor[1].init();
    motor[2].init();
    motor[3].init();
    // Initializing I2C-Multiplexer
    pinMode(RB_MUX_RESET, INPUT_PULLUP);
    tca_.begin(Wire);
    tca_.closeAll();
    // Blink debug-LED to signal finished bootup
    blinkDebugLED();
}

void RocciBoard::openSensorPort (uint8_t sensor_port)
{
    tca_.openChannel(sensor_port);
}

void RocciBoard::closeSensorPort (uint8_t sensor_port)
{
    tca_.closeChannel(sensor_port);
}

void RocciBoard::closeAllSensorPorts (void)
{
    tca_.closeAll();
}

void RocciBoard::resetMultiplexer (void)
{
    pinMode(RB_MUX_RESET, OUTPUT);
    digitalWrite(RB_MUX_RESET, LOW);
    delay(500);
    pinMode(RB_MUX_RESET, INPUT_PULLUP);
}

void RocciBoard::initRBSensor (RBSensor &sensor)
{
    sensor.setMultiplexer(&tca_);
    sensor.init();
}

float RocciBoard::getBatteryVoltage (void)
{
    #if defined(ARDUINO_ARCH_AVR)
        return 0.2805f + 0.0191f * (float)analogRead(RB_BATTERY_ADC);
    #elif defined(ARDUINO_ARCH_SAM)
        #warning "RocciBoard::getBatteryVoltage() is not available on Arduino ARM Boards"
        return 0.0f;
    #else
        #warning "RocciBoard::getBatteryVoltage() is not available on this Board"
        return 0.0f;
    #endif
}


uint8_t RocciBoard::getBatteryCharge (void)
{
    uint8_t soc = -592.465f + 58.333f * getBatteryVoltage();
    soc = max(min(soc, 100), 0);
    return soc;
}

void RocciBoard::blinkDebugLED (void)
{
    digitalWrite(RB_DEBUG_LED, HIGH);
    delay(100);
    digitalWrite(RB_DEBUG_LED, LOW);
}