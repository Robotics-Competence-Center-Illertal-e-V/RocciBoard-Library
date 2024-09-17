#include "Arduino.h"
#include "rbinfrared.h"


#define PIN_HANDLER(pin) \
const int ir_pin_##pin = pin;\
void pin_handler_##pin (void) \
{ \
  RBInfrared::handleInterrupt(pin); \
}

#define G_MAX_NUMBER_OF_IR_SENSORS 2

PIN_HANDLER (0)
PIN_HANDLER (1)


const int g_pin_list[] = { 
    0, 
    1
};

void (* const g_pin_handler_table[])(void)  = {
    pin_handler_0,
    pin_handler_1,
};

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
   if(digitalRead(pin)) //rising
   {
        _timestamps[index] = millis();
   }
   else //falling
   {
        _values[index] = millis() - _timestamps[index];
   }
}

int RBInfrared::getValue(int index)
{
    return _values[index];
}