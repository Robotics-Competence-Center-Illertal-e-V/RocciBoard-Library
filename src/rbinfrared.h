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
    public:
        RBInfrared(
            int s0=NOT_CONNECTED,
            int s1=NOT_CONNECTED,
            int s2=NOT_CONNECTED,
            int s3=NOT_CONNECTED,
            int s4=NOT_CONNECTED,
            int s5=NOT_CONNECTED,
            int s6=NOT_CONNECTED,
            int s7=NOT_CONNECTED,
            int s8=NOT_CONNECTED,
            int s9=NOT_CONNECTED,
            int s10=NOT_CONNECTED,
            int s11=NOT_CONNECTED,
            int s12=NOT_CONNECTED,
            int s13=NOT_CONNECTED,
            int s14=NOT_CONNECTED,
            int s15=NOT_CONNECTED)
            {
                RBInfrared::_pin_list[0] = s0;
                RBInfrared::_pin_list[1] = s1;
                RBInfrared::_pin_list[2] = s2;
                RBInfrared::_pin_list[3] = s3;
                RBInfrared::_pin_list[4] = s4;
                RBInfrared::_pin_list[5] = s5;
                RBInfrared::_pin_list[6] = s6;
                RBInfrared::_pin_list[7] = s7;
                RBInfrared::_pin_list[8] = s8;
                RBInfrared::_pin_list[9] = s9;
                RBInfrared::_pin_list[10] = s10;
                RBInfrared::_pin_list[11] = s11;
                RBInfrared::_pin_list[12] = s12;
                RBInfrared::_pin_list[13] = s13;
                RBInfrared::_pin_list[14] = s14;
                RBInfrared::_pin_list[15] = s15;
            };
        void init();
        int getValue(int index);

        static void handleInterrupt(int pin);

    private:
        static int _pin_list[MAX_NUMBER_OF_IR_SENSORS];
        static int _timestamps[MAX_NUMBER_OF_IR_SENSORS];
        static int _values[MAX_NUMBER_OF_IR_SENSORS];

        static int getIndexByPin(int pin);
        static int getGlobalIndexByPin(int pin);
};

#endif