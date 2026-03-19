/**
 * @file rocciboard.cpp
*/

#include "Arduino.h"
#include "rocciboard.h"

RocciBoard::RocciBoard (uint8_t tca_addr) : tca_(Wire, tca_addr, RB_MUX_RESET)
{
    tca_addr_ = tca_addr;
    motor[0] = RBMotor(5,6);
    motor[1] = RBMotor(7,8);
    motor[2] = RBMotor(9,10);
    motor[3] = RBMotor(11,12);
}

bool RocciBoard::init (bool block_on_failure)
{
    is_initialized_ = false;
    block_on_failure_ = block_on_failure;
    Serial.begin(9600);
    // Initializing Error-LED
    pinMode(RB_DEBUG_LED, OUTPUT);
    digitalWrite(RB_DEBUG_LED, LOW);
    // Initializing the voltage-reading ADC
    pinMode(RB_BATTERY_ADC, INPUT);

    
    #if defined(__AVR_ATmega2560__)
    float u_bat = getBatteryVoltage();
    if(u_bat < 6.0)
    {
        RBError err;
        rbSetError(&err, RB_ERR_BATTERY_LOW, "RocciBoard", "init", -1, 0, (int)(u_bat * 100.0f));
        printError(err);
        return false;
    }
    #endif

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

    Wire.begin();

    RBError err;


     // test i2c port
    if( tca_.testI2CPort(&err) == false)
    {
        printError(err);
        return false;
    }

    // test tca multiplexer
    if( tca_.selfTest(&err) == false)
    {
        printError(err);
        return false;
    }

    tca_.begin();

    is_initialized_ = true;

    // test if there is a broken sensor at any of the ports
    if( tca_.portCycleTest(&err) == false)
    {
        printError(err);
        return false;
    }

    // Blink debug-LED to signal finished bootup
    blinkDebugLED();
    return true;
}

bool RocciBoard::init_fast (void)
{
    is_initialized_ = false;
    block_on_failure_ = false;
    Serial.begin(9600);

    // Initializing Error-LED
    pinMode(RB_DEBUG_LED, OUTPUT);
    digitalWrite(RB_DEBUG_LED, LOW);

    // Initializing the voltage-reading ADC
    pinMode(RB_BATTERY_ADC, INPUT);

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

    // Initialize I2C and multiplexer without diagnostic tests
    Wire.begin();
    tca_.begin();

    is_initialized_ = true;

    return true;
}

void RocciBoard::openSensorPort (uint8_t sensor_port)
{
    if(!ensureInitialized("openSensorPort")) return;
    tca_.openChannel(sensor_port, nullptr);
}

void RocciBoard::closeSensorPort (uint8_t sensor_port)
{
    if(!ensureInitialized("closeSensorPort")) return;
    tca_.closeChannel(sensor_port, nullptr);
}

void RocciBoard::closeAllSensorPorts (void)
{
    if(!ensureInitialized("closeAllSensorPorts")) return;
    tca_.closeAll();
}

void RocciBoard::resetMultiplexer (void)
{
    if(!ensureInitialized("resetMultiplexer")) return;
    tca_.resetMultiplexer();
}

bool RocciBoard::initRBSensor (RBSensor &sensor, RBError* err)
{
    if(!ensureInitialized("initRBSensor")) return false;
    sensor.setMultiplexer(&tca_);
    RBError local_err;
    RBError* used_err = (err != nullptr) ? err : &local_err;
    if( ! sensor.isConnected(used_err))
    {
        printError(*used_err);
        return false;
    }
    if( ! sensor.init(used_err))
    {
        printError(*used_err);
        return false;
    }
    else
    {
        return true;
    }
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
    if(!ensureInitialized("getBatteryCharge")) return 0;
    uint8_t soc = -592.465f + 58.333f * getBatteryVoltage();
    soc = max(min(soc, 100), 0);
    return soc;
}

void RocciBoard::blinkDebugLED (void)
{
    if(!ensureInitialized("blinkDebugLED")) return;
    digitalWrite(RB_DEBUG_LED, HIGH);
    delay(100);
    digitalWrite(RB_DEBUG_LED, LOW);
}

void RocciBoard::disableErrorPrint (void)
{
    print_errors_ = false;
}

void RocciBoard::scanSensors(void)
{
    if(!ensureInitialized("scanSensors")) return;
    Serial.println("Start Sensor Scan");
    for(uint8_t port = 0; port < 8; port++)
    {
        for(int addr = 0x70; addr < 0x80; addr++)
        {
            RBSonar sonar(port, addr);
            sonar.setMultiplexer(&tca_);
            if(sonar.isConnected()) {
                Serial.println("Port "+String(port)+": Ultraschall (SRF08) mit Adresse "+String(addr, HEX));
            }
        }

        RBColor color(port);
        color.setMultiplexer(&tca_);
        if(color.isConnected()) {
            Serial.println("Port "+String(port)+": Farb-Sensor (TCS34725)");
        }

        RBCompass compass(port);
        compass.setMultiplexer(&tca_);
        if(compass.isConnected()) {
            Serial.println("Port "+String(port)+": Kompass (BNO055)");
        }

        RBLaser laser_short(port, TYPE_VL53L0X);
        laser_short.setMultiplexer(&tca_);
        if(laser_short.isConnected()) {
            Serial.println("Port "+String(port)+": Laser Short Range (VL53L0X)");
        }

        RBLaser laser_long(port, TYPE_VL53L1X);
        laser_long.setMultiplexer(&tca_);
        if(laser_long.isConnected()) {
            Serial.println("Port "+String(port)+": Laser Long Range (VL53L1X)");
        }
    }
    Serial.println("Ende");
}

void RocciBoard::scanI2C(void)
{
    if(!ensureInitialized("scanI2C")) return;
    Serial.println("Start I2C Scan");
    for(int sensor_port = 0; sensor_port < 8; sensor_port++)
    {
        openSensorPort(sensor_port); 
        for(int i2c_addr = 1; i2c_addr < 128; i2c_addr++)
        {            
            Wire.beginTransmission(i2c_addr);
            int error = Wire.endTransmission();
            if(i2c_addr == tca_addr_) //skip multiplexer
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

void RocciBoard::printError(const RBError& err, Print& out)
{
    if( ! print_errors_)
    {
        return;
    }
    // Error code string (ERR0 … ERRn)
    out.print("[RB] ERR");
    out.print((int)err.code);
    out.print(" - ");

    // Short German description per error code
    switch(err.code)
    {
        case RB_ERR_OK:
            out.print("Kein Fehler");
            break;
        case RB_ERR_I2C_TX_FAILED:
            out.print("I2C Senden fehlgeschlagen");
            break;
        case RB_ERR_I2C_RX_FAILED:
            out.print("I2C Empfangen fehlgeschlagen");
            break;
        case RB_ERR_SENSOR_ID_MISMATCH:
            out.print("Sensor-ID stimmt nicht ueberein (falscher Sensor oder Typ?)");
            break;
        case RB_ERR_MUX_PORT_STUCK_SCL:
            out.print("SCL-Leitung haengt auf GND");
            if(err.port == -1)
            {
                block_on_failure_ = true;
            }
            break;
        case RB_ERR_MUX_PORT_STUCK_SDA:
            out.print("SDA-Leitung haengt auf GND");
            if(err.port == -1)
            {
                block_on_failure_ = true;
            }
            break;
        case RB_ERR_MUX_PORT_SHORT_SCL_SDA:
            out.print("SCL und SDA sind kurzgeschlossen");
            if(err.port == -1)
            {
                block_on_failure_ = true;
            }
            break;
        case RB_ERR_MUX_CHANNEL_CONFLICT:
            out.print("Multiplexer-Kanal bereits geoeffnet");
            block_on_failure_ = true;
            break;
        case RB_ERR_MUX_INVALID_CHANNEL:
            out.print("Ungueltige Multiplexer-Kanal-Nummer");
            break;
        case RB_ERR_MUX_RESET_FAILED:
            out.print("Multiplexer-Reset fehlgeschlagen");
            block_on_failure_ = true;
            break;
        case RB_ERR_INIT_FAILED:
            out.print("Sensor konnte nicht initialisiert werden");
            break;
        case RB_ERR_NOT_CONNECTED:
            out.print("Kein Sensor an diesem Port angeschlossen");
            break;
        case RB_ERR_INVALID_ARGUMENT:
            out.print("Ungueltiges Argument");
            break;
        case RB_ERR_BATTERY_LOW:
            out.print("Batteriespannung zu niedrig");
            break;
        case RB_ERR_NOT_INITIALIZED:
            out.print("RocciBoard nicht initialisiert (init() oder init_fast() fehlt)");
            block_on_failure_ = true;
            break;
        default:
            out.print("Unbekannter Fehler");
            break;
    }

    // Context: module, port, address, detail
    if(err.module)
    {
        out.print(" [");
        out.print(err.module);
        if(err.function) { out.print("::"); out.print(err.function); }
        out.print("]");
    }
    if(err.port >= 0)
    {
        out.print(" Port=");
        out.print(err.port);
    }
    if(err.addr != 0)
    {
        out.print(" Addr=0x");
        out.print(err.addr, HEX);
    }
    if(err.detail != 0)
    {
        out.print(" Detail=");
        out.print(err.detail);
    }
    out.println();

    if (block_on_failure_)
    {
        pinMode(RB_DEBUG_LED, OUTPUT);
        while(1)
        {
            digitalWrite(RB_DEBUG_LED, HIGH);
            delay(100);
            digitalWrite(RB_DEBUG_LED, LOW);
            delay(1000);
        }
    }
}

bool RocciBoard::ensureInitialized(const char* function_name)
{
    if(is_initialized_) return true;

    RBError err;
    rbSetError(&err, RB_ERR_NOT_INITIALIZED, "RocciBoard", function_name, -1, tca_addr_);
    printError(err);
    return false;
}