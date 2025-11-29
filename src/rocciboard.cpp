/**
 * @file rocciboard.cpp
*/

#include "Arduino.h"
#include "rocciboard.h"

RocciBoard::RocciBoard (uint8_t addr) : tca_(addr)
{
    tca_addr = addr;
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
    float u_bat = getBatteryVoltage();
    if(u_bat < 6.0)
    {
        Serial.println("Batteriespannung "+String(u_bat)+"V. Muss über 6V sein");
        while(1);
    }

    // Changing motor PWM frequency
    #if defined(__AVR_ATmega2560__)
        // Arduino Mega: set PWM frequency to 31372.55 Hz
        TCCR1B = (TCCR1B & B11111000) | B00000001;
        TCCR2B = (TCCR2B & B11111000) | B00000001;
        TCCR3B = (TCCR3B & B11111000) | B00000001;
        TCCR4B = (TCCR4B & B11111000) | B00000001;
    #endif
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
        // Arduino Mega
        return 0.2805f + 0.0191f * (float)analogRead(RB_BATTERY_ADC);
    #elif defined(ARDUINO_ARCH_SAM)
        // Arduino Due
        #warning "RocciBoard::getBatteryVoltage() is not available on Arduino ARM Boards"
        return 0.0f;
    #else
        // other boards
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

void RocciBoard::scanI2C(void)
{
    Serial.println("Start I2C Scan");
    for(int sensor_port = 0; sensor_port < 8; sensor_port++)
    {
        openSensorPort(sensor_port); 
        for(int i2c_addr = 1; i2c_addr < 128; i2c_addr++)
        {            
            Wire.beginTransmission(i2c_addr);
            int error = Wire.endTransmission();
            if(i2c_addr == tca_addr) //skip multiplexer
            {
                continue;
            }
            if (error == 0)
            {
                Serial.println("Port:"+String(sensor_port)+" Addresse:"+String(i2c_addr));
            }
        }
        closeSensorPort(sensor_port);
    }
    Serial.println("Ende");
}