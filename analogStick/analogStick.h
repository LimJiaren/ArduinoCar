#ifndef analogStick
#define analogStick
#include <iostream>
#include <string>
#include "string.h"

using namespace std;
class BtAnalogStick{
    public:
        int motorpin(int pin1,int pin2,int pin3,int pin4, int ena, int enb, int left_light, int right_light, int back_light, int buzzer);
        int move(int x, int y);
        long mapping(long x, long in_min, long in_max, long out_min, long out_max);
        int UltraSonicPin(int trig,int echo);
        void range();

};

#endif