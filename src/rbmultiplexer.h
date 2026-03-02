/**
 * @file        rbmultiplexer.h
 *
 * @brief       Wrapper class for the TCA9548A I2C multiplexer used
 *              on the RocciBoard Shield.
 *
 * This class provides simplified access to the hardware I2C multiplexer.
 * It allows opening and closing individual I2C channels (0–7)
 * so multiple identical sensors can be used without address conflicts.
 *
 * WARNING:
 * Only create ONE instance of RBMultiplexer in your program!
 */

#ifndef _RB_MULTIPLEXER_H_
#define _RB_MULTIPLEXER_H_

#include <Arduino.h>
#include <Wire.h>
#include <TCA9548A.h>


typedef enum {
    PORT_STATUS_OPEN,
    PORT_STATUS_CLOSED,
    PORT_STATUS_DEFEKT
} PortStatus_t;

/**
 * @class RBMultiplexer
 * @brief Controls the TCA9548A I2C multiplexer.
 */
class RBMultiplexer {

  public:
    /**
     * @brief Constructor
     *
     * @param addr       I2C address of the TCA9548A (default: 0x70)
     * @param reset_pin  GPIO pin connected to the reset pin
     */
    RBMultiplexer(TwoWire &wire, uint8_t addr = 0x70, uint8_t reset_pin = 4);

    void begin();

    bool selfTest();

    bool portCycleTest();

    bool testI2CPort();
    /**
     * @brief Enables a specific channel (0–7).
     */
    void openChannel(uint8_t id);

    /**
     * @brief Disables a specific channel (0–7).
     */
    void closeChannel(uint8_t id);
    
    /**
     * @brief Disable all channels
     */
    void closeAll();

    /**
     * @brief Activates exactly one channel and disables all others.
     */
    void clockOutI2C();

    /**
     * @brief Performs a hardware reset of the multiplexer.
     */
    void resetMultiplexer();

  private:
    TwoWire* wire_;
    TCA9548A tca_;        ///< Instance of the TCA9548A library
    uint8_t tca_addr_;     ///< I2C address
    uint8_t reset_pin_;   ///< Reset GPIO pin
    PortStatus_t current_port_status_[8];
};

#endif