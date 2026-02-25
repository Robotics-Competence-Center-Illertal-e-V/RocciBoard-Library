#include "rbmultiplexer.h"

#define RB_I2C_SCL 21
#define RB_I2C_SDA 20

/**
 * @brief Constructor
 */
RBMultiplexer::RBMultiplexer(TwoWire &wire, uint8_t addr, uint8_t reset_pin)
    : tca_(addr)
{
    wire_ = &wire;
    reset_pin_ = reset_pin;
    tca_addr_ = addr;
    for(int i = 0; i < 8; i++)
        current_port_status_[i] = PORT_STATUS_CLOSED;
}

void RBMultiplexer::begin()
{
    pinMode(reset_pin_, OUTPUT);
    digitalWrite(reset_pin_, HIGH);

    // Initialize multiplexer
    tca_.begin();
}

bool RBMultiplexer::selfTest()
{
    //verify TCA is connected with correct address
    Wire.beginTransmission(tca_addr_);
    int error = Wire.endTransmission();
    if(error)
    {
        Serial.println("Multiplexer Addresse ist Falsch. Suche Alternative...");
        for(int i2c_addr = 112; i2c_addr < 120; i2c_addr++)
        {            
            Wire.beginTransmission(i2c_addr);
            int error = Wire.endTransmission();
            if (error == 0)
            {
                Serial.println("verwende: RocciBoard rb("+String(i2c_addr)+")");
                return false;
            }
        }
        Serial.println("RocciBoard Defekt!");
        return false;
    }
    return true;
}


bool RBMultiplexer::portCycleTest()
{
    closeAll();
    //test multiplexer i2c ports
    for(int sensor_port = 0; sensor_port < 8; sensor_port++)
    {
        openChannel(sensor_port); 
        if( ! testI2CPort() )
        {
            Serial.println("try clocking Out...");
            Serial.flush();
            clockOutI2C();
            if( ! testI2CPort() )
            {
                Serial.println(" am I2C Port "+String(sensor_port)+". Kabel oder Sensor defekt?");
                current_port_status_[sensor_port] = PORT_STATUS_DEFEKT;
                Serial.println("versuche Multiplexer Reset");
                Serial.flush();
                resetMultiplexer(); // reset instead of close to avoid stuck at
                if( ! testI2CPort() )
                {
                    return false;
                }
                else
                {
                    Serial.println("Port "+String(sensor_port)+" als Defekt vermerkt");
                }
            }
            else
            {
                Serial.println("gelöst");
            }
        }
            
        Serial.flush();
        closeChannel(sensor_port);
    }

    closeAll();
    return true;
}


bool RBMultiplexer::testI2CPort()
{
    bool result = true;
    Wire.end();
    pinMode(RB_I2C_SCL, INPUT);
    pinMode(RB_I2C_SDA, INPUT);
    delayMicroseconds(5);
    //test scl stuck at gnd
    if(digitalRead(RB_I2C_SCL) == 0) 
    {
        Serial.println("SCL Low Fehler");
        result = false;
    }
    //test sda stuck at gnd
    if(digitalRead(RB_I2C_SDA) == 0)
    {
        Serial.println("SDA Low Fehler");
        result = false;
    } 
    //teste scl and sda short
    pinMode(RB_I2C_SCL, OUTPUT);
    digitalWrite(RB_I2C_SCL, LOW);
    delayMicroseconds(1);
    if(digitalRead(RB_I2C_SDA) == 0)
    {
        Serial.println("Kurzschluss zwischen SDA und SCL");
        result = false;
    }
    digitalWrite(RB_I2C_SCL, HIGH);
    pinMode(RB_I2C_SDA, INPUT);
    Wire.begin();
    return result;
}

/**
 * @brief Enable a channel without disabling others
 */
void RBMultiplexer::openChannel(uint8_t id)
{
    if (id > 7) return;
    if (current_port_status_[id] == PORT_STATUS_DEFEKT) return;
    tca_.openChannel(id);
    current_port_status_[id] = PORT_STATUS_OPEN;
}


/**
 * @brief Disable a channel
 */
void RBMultiplexer::closeChannel(uint8_t id)
{
    if (id > 7) return;
    if (current_port_status_[id] == PORT_STATUS_DEFEKT) return;

    tca_.closeChannel(id);
    current_port_status_[id] = PORT_STATUS_CLOSED;
}

/**
 * @brief Disable all channels
 */
void RBMultiplexer::closeAll()
{
    tca_.closeAll();
    
    for(int i = 0; i < 8; i++)
        if(current_port_status_[i] != PORT_STATUS_DEFEKT)
            current_port_status_[i] = PORT_STATUS_CLOSED;
}


/**
 * @brief toggle scl so the bus is released by the sensor
 */
void RBMultiplexer::clockOutI2C()
{
    Wire.end();
    pinMode(RB_I2C_SCL, OUTPUT);
    for(int i = 0; i < 8; i++)
    {
        digitalWrite(RB_I2C_SCL, LOW);
        delayMicroseconds(5);
        digitalWrite(RB_I2C_SCL, HIGH);
        delayMicroseconds(5);
    }
    
    Wire.begin();
}


/**
 * @brief Verify device presence on I2C bus
 */
bool RBMultiplexer::verifyPortStatus()
{
    #warning Hier fehlt noch was
    return true;
}


/**
 * @brief Hardware reset using reset pin
 */
void RBMultiplexer::resetMultiplexer()
{
    digitalWrite(reset_pin_, LOW);
    delay(1);
    digitalWrite(reset_pin_, HIGH);
    delay(1);

    tca_.closeAll();
}