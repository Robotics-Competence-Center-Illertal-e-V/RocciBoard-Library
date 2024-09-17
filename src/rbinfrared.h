/** 
 * @file rbinfrared.h
 * 
 * library for detecting soccer balls with remote control ir detector RocciBoard
 * 
 * @author Alexander Ulbrich (<alexander.ulbrich@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>) 
 * @version 1.0 [9-2024] First stable release
*/

#ifndef _RB_INFRARED_H_
#define _RB_INFRARED_H_


#define MAX_NUMBER_OF_IR_SENSORS 16
#define NOT_CONNECTED -1

class RBInfrared{
    private:
    static int _pin_list[MAX_NUMBER_OF_IR_SENSORS];
    static int _timestamps[MAX_NUMBER_OF_IR_SENSORS];
    static int _values[MAX_NUMBER_OF_IR_SENSORS];

    static int getIndexByPin(int pin);
    static int getGlobalIndexByPin(int pin);

    public:
    static void handleInterrupt(int pin);

    RBInfrared(
        int s0=NOT_CONNECTED,
        int s1=NOT_CONNECTED,
        int s2=NOT_CONNECTED)
        {
            _pin_list[0] = s0;
            _pin_list[1] = s1;
            _pin_list[2] = s2;
        };
    void init();
    int getValue(int index);
};

#endif