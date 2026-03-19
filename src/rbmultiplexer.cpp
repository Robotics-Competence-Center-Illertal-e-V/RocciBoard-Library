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

bool RBMultiplexer::selfTest(RBError* err)
{
    //verify TCA is connected with correct address
    Wire.beginTransmission(tca_addr_);
    int tx_error = Wire.endTransmission();
    if(tx_error)
    {
        for(int i2c_addr = 112; i2c_addr < 120; i2c_addr++)
        {            
            Wire.beginTransmission(i2c_addr);
            int probe_error = Wire.endTransmission();
            if (probe_error == 0)
            {
                rbSetError(err, RB_ERR_I2C_TX_FAILED, "RBMultiplexer", "selfTest", -1, tca_addr_, i2c_addr);
                return false;
            }
        }
        rbSetError(err, RB_ERR_I2C_TX_FAILED, "RBMultiplexer", "selfTest", -1, tca_addr_, tx_error);
        return false;
    }
    return true;
}


bool RBMultiplexer::portCycleTest(RBError* err)
{
    closeAll();
    //test multiplexer i2c ports
    for(int sensor_port = 0; sensor_port < 8; sensor_port++)
    {
        if(!openChannel(sensor_port, err))
        {
            return false;
        }

        if( ! testI2CPort(err, sensor_port) )
        {
            clockOutI2C();
            if( ! testI2CPort(err, sensor_port) )
            {
                current_port_status_[sensor_port] = PORT_STATUS_DEFEKT;
                resetMultiplexer(); // reset instead of close to avoid stuck at
                if( ! testI2CPort(err, sensor_port) )
                {
                    rbSetError(err, RB_ERR_MUX_RESET_FAILED, "RBMultiplexer", "portCycleTest", sensor_port, tca_addr_);
                    return false;
                }
                else
                {
                    return false;
                }
            }
        }
            
        closeChannel(sensor_port, nullptr);
    }

    closeAll();
    return true;
}


bool RBMultiplexer::testI2CPort(RBError* err, int8_t port)
{
    bool result = true;
    Wire.end();
    pinMode(RB_I2C_SCL, INPUT_PULLUP);
    pinMode(RB_I2C_SDA, INPUT_PULLUP);
    delayMicroseconds(5);

    bool scl_low = (digitalRead(RB_I2C_SCL) == 0);
    bool sda_low = (digitalRead(RB_I2C_SDA) == 0);

    //test scl stuck at gnd
    if(scl_low)
    {
        result = false;
    }
    //test sda stuck at gnd
    if(sda_low)
    {
        result = false;
    }

    // Prefer reporting SDA low if both are low to avoid masking SDA faults.
    if(sda_low)
    {
        rbSetError(err, RB_ERR_MUX_PORT_STUCK_SDA, "RBMultiplexer", "testI2CPort", port, tca_addr_);
    }
    else if(scl_low)
    {
        rbSetError(err, RB_ERR_MUX_PORT_STUCK_SCL, "RBMultiplexer", "testI2CPort", port, tca_addr_);
    }

    //teste scl and sda short
    pinMode(RB_I2C_SCL, OUTPUT);
    digitalWrite(RB_I2C_SCL, LOW);
    delayMicroseconds(1);
    if(digitalRead(RB_I2C_SDA) == 0 && result == true)
    {
        rbSetError(err, RB_ERR_MUX_PORT_SHORT_SCL_SDA, "RBMultiplexer", "testI2CPort", port, tca_addr_);
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
bool RBMultiplexer::openChannel(uint8_t id, RBError* err)
{
    if (id > 7)
    {
        rbSetError(err, RB_ERR_MUX_INVALID_CHANNEL, "RBMultiplexer", "openChannel", id, tca_addr_);
        return false;
    }
    if (current_port_status_[id] == PORT_STATUS_DEFEKT)
    {
        rbSetError(err, RB_ERR_NOT_CONNECTED, "RBMultiplexer", "openChannel", id, tca_addr_);
        return false;
    }
    for(int i = 0; i < 8; i++)
    {
        if(i != id && current_port_status_[i] == PORT_STATUS_OPEN)
        {
            rbSetError(err, RB_ERR_MUX_CHANNEL_CONFLICT, "RBMultiplexer", "openChannel", id, tca_addr_, i);
            return false;
        }
    }
    tca_.openChannel(id);
    current_port_status_[id] = PORT_STATUS_OPEN;
    return true;
}


/**
 * @brief Disable a channel
 */
bool RBMultiplexer::closeChannel(uint8_t id, RBError* err)
{
    if (id > 7)
    {
        rbSetError(err, RB_ERR_MUX_INVALID_CHANNEL, "RBMultiplexer", "closeChannel", id, tca_addr_);
        return false;
    }
    if (current_port_status_[id] == PORT_STATUS_DEFEKT)
    {
        rbSetError(err, RB_ERR_NOT_CONNECTED, "RBMultiplexer", "closeChannel", id, tca_addr_);
        return false;
    }

    tca_.closeChannel(id);
    current_port_status_[id] = PORT_STATUS_CLOSED;
    return true;
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