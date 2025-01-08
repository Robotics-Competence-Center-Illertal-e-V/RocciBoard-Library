/**
 * @file rbinfrared.cpp
 */

#include "Arduino.h"
#include "rbinfrared.h"

#define PIN_HANDLER(pin) \
void pin_handler_##pin (void) \
{ \
  RBInfrared::handleInterrupt(pin); \
}

#define G_MAX_NUMBER_OF_IR_SENSORS 35

PIN_HANDLER (14)
PIN_HANDLER (15)
PIN_HANDLER (16)
PIN_HANDLER (17)
PIN_HANDLER (18)
PIN_HANDLER (19)
PIN_HANDLER (20)
PIN_HANDLER (21)
PIN_HANDLER (22)
PIN_HANDLER (46)
PIN_HANDLER (47)
PIN_HANDLER (48)
PIN_HANDLER (49)
PIN_HANDLER (50)
PIN_HANDLER (51)
PIN_HANDLER (52)
PIN_HANDLER (53)
PIN_HANDLER (54)
PIN_HANDLER (55)
PIN_HANDLER (56)
PIN_HANDLER (57)
PIN_HANDLER (58)
PIN_HANDLER (59)
PIN_HANDLER (60)
PIN_HANDLER (61)
PIN_HANDLER (62)
PIN_HANDLER (63)
PIN_HANDLER (64)
PIN_HANDLER (65)
PIN_HANDLER (66)
PIN_HANDLER (67)
PIN_HANDLER (68)
PIN_HANDLER (69)

const int g_pin_list[] = { 
    14, 
    15,
    16,
    17,
    18,
    19,
    20,
    21,
    22,
    46,
    47,
    48,
    49,
    50,
    51,
    52,
    53,
    54,
    55,
    56,
    57,
    58,
    59,
    60,
    61,
    62,
    63,
    64,
    65,
    66,
    67,
    68,
    69
};

void (* const g_pin_handler_table[])(void)  = {
    pin_handler_14,
    pin_handler_15,
    pin_handler_16,
    pin_handler_17,
    pin_handler_18,
    pin_handler_19,
    pin_handler_20,
    pin_handler_21,
    pin_handler_22,
    pin_handler_46,
    pin_handler_47,
    pin_handler_48,
    pin_handler_49,
    pin_handler_50,
    pin_handler_51,
    pin_handler_52,
    pin_handler_53,
    pin_handler_54,
    pin_handler_55,
    pin_handler_56,
    pin_handler_57,
    pin_handler_58,
    pin_handler_59,
    pin_handler_60,
    pin_handler_61,
    pin_handler_62,
    pin_handler_63,
    pin_handler_64,
    pin_handler_65,
    pin_handler_66,
    pin_handler_67,
    pin_handler_68,
    pin_handler_69
};

int RBInfrared::_pin_list[MAX_NUMBER_OF_IR_SENSORS];
int RBInfrared::_timestamps[MAX_NUMBER_OF_IR_SENSORS];
int RBInfrared::_values[MAX_NUMBER_OF_IR_SENSORS];

int RBInfrared::getIndexByPin(int pin){
    for(int i = 0; i < MAX_NUMBER_OF_IR_SENSORS; i++)
    {
        if(pin == _pin_list[i])
            return i;
        if(_pin_list[i] == NOT_CONNECTED)
            return -1;
    }
    return -1;
}

int RBInfrared::getGlobalIndexByPin(int pin){
    for(int i = 0; i < G_MAX_NUMBER_OF_IR_SENSORS; i++)
    {
        if(pin == g_pin_list[i])
            return i;
    }
    return -1;
}

void RBInfrared::init()
{
    for(int i = 0; i < MAX_NUMBER_OF_IR_SENSORS; i++)
    {
        if(_pin_list[i] != NOT_CONNECTED)
        {
            int pin = _pin_list[i];
            int index = getGlobalIndexByPin(pin);
            if(index == -1)
            {
                Serial.println("ERROR: unsupported pin defined for rbinfrared");
                continue;
            }
            pinMode(pin, INPUT_PULLUP);
            attachInterrupt(pin, g_pin_handler_table[index], CHANGE);
            _values[i] = 0;
            _timestamps[i] = 0;
        }
        else
        {
            return;
        }
    }    
}

void RBInfrared::handleInterrupt(int pin)
{
   int index = getIndexByPin(pin);
   if(index == -1)
   {
        return;
   }
   if(digitalRead(pin)) //rising
   {
        _timestamps[index] = micros();
   }
   else //falling
   {
        _values[index] = micros() - _timestamps[index];
        if(_values[index] > 1000)
            _values[index] = 0;
   }
}

int RBInfrared::getValue(int index)
{
    int tmp = _values[index];
    _values[index] = 0;
    return tmp;
}