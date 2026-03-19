#ifndef _RB_ERROR_H_
#define _RB_ERROR_H_

#include <Arduino.h>

enum RBErrorCode {
    RB_ERR_OK = 0,
    RB_ERR_I2C_TX_FAILED,
    RB_ERR_I2C_RX_FAILED,
    RB_ERR_SENSOR_ID_MISMATCH,
    RB_ERR_MUX_PORT_STUCK_SCL,
    RB_ERR_MUX_PORT_STUCK_SDA,
    RB_ERR_MUX_PORT_SHORT_SCL_SDA,
    RB_ERR_MUX_CHANNEL_CONFLICT,
    RB_ERR_MUX_INVALID_CHANNEL,
    RB_ERR_MUX_RESET_FAILED,
    RB_ERR_INIT_FAILED,
    RB_ERR_NOT_CONNECTED,
    RB_ERR_INVALID_ARGUMENT,
    RB_ERR_BATTERY_LOW,
    RB_ERR_NOT_INITIALIZED,
    RB_ERR_UNKNOWN
};

struct RBError {
    RBErrorCode code = RB_ERR_OK;
    const char* module = nullptr;
    const char* function = nullptr;
    int8_t port = -1;
    uint8_t addr = 0;
    int detail = 0;

    bool ok() const { return code == RB_ERR_OK; }
};

static inline void rbSetError(
    RBError* err,
    RBErrorCode code,
    const char* module,
    const char* function,
    int8_t port,
    uint8_t addr,
    int detail = 0)
{
    if (!err) return;
    err->code = code;
    err->module = module;
    err->function = function;
    err->port = port;
    err->addr = addr;
    err->detail = detail;
}

#endif
