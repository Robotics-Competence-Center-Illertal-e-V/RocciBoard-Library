/** 
 * @file rbinfrared.h
 * 
 * Library for detecting active-infrared soccer balls with TSOP-IR-receivers using the RocciBoard
 * 
 * @author Alexander Ulbrich (<alexander.ulbrich@rocci.net>) for the Robotics Competence Center Illertal e. V. (<https://rocci.net>) 
 * @version 1.0 [9-2024] First stable release
 *          1.1 [01-2025] Adapted to RBSensor-Interface
*/

#ifndef _RB_INFRARED_H_
#define _RB_INFRARED_H_

#define MAX_NUMBER_OF_IR_SENSORS 16
#define NOT_CONNECTED -1

/**
 * Class for implementing the TSOP-IR-receivers for easy usage.
*/
class RBInfrared{

    public:

        /**
         * Creates the RBInfrared-object.
         * Selects the used pins for IR-interrupts.
         * @param sX s0...s15 pins to use for IR-interrupts
         */
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
            int s15=NOT_CONNECTED,
            int s16=NOT_CONNECTED,
            int s17=NOT_CONNECTED,
            int s18=NOT_CONNECTED,
            int s19=NOT_CONNECTED,
            int s20=NOT_CONNECTED,
            int s21=NOT_CONNECTED,
            int s22=NOT_CONNECTED,
            int s23=NOT_CONNECTED,
            int s24=NOT_CONNECTED,
            int s25=NOT_CONNECTED,
            int s26=NOT_CONNECTED,
            int s27=NOT_CONNECTED,
            int s28=NOT_CONNECTED,
            int s29=NOT_CONNECTED,
            int s30=NOT_CONNECTED,
            int s31=NOT_CONNECTED)
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
                RBInfrared::_pin_list[16] = s16;
                RBInfrared::_pin_list[17] = s17;
                RBInfrared::_pin_list[18] = s18;
                RBInfrared::_pin_list[19] = s19;
                RBInfrared::_pin_list[20] = s20;
                RBInfrared::_pin_list[21] = s21;
                RBInfrared::_pin_list[22] = s22;
                RBInfrared::_pin_list[23] = s23;
                RBInfrared::_pin_list[24] = s24;
                RBInfrared::_pin_list[25] = s25;
                RBInfrared::_pin_list[26] = s26;
                RBInfrared::_pin_list[27] = s27;
                RBInfrared::_pin_list[28] = s28;
                RBInfrared::_pin_list[29] = s29;
                RBInfrared::_pin_list[30] = s30;
                RBInfrared::_pin_list[31] = s31;
            };

         /**
         * Initializes the TSOP-IR-Receivers
        */   
        void init(void);

        /**
         * Reads the current value of the receiver with the given
         * @param index index of receiver to read value from
         * @return int: distance in millimeters
         */
        int getValue(int index);

        /**
         * Internal static function for interrupt handling of IR-signals
         * @param pin pin of receiver to handle interrupt
         */
        static void handleInterrupt(int pin);

        void reset(void);

    private:

        static int _pin_list[MAX_NUMBER_OF_IR_SENSORS];
        static int _timestamps[MAX_NUMBER_OF_IR_SENSORS];
        static int _values[MAX_NUMBER_OF_IR_SENSORS];

        static int getIndexByPin(int pin);
        static int getGlobalIndexByPin(int pin);
};

#endif