#include "analogStick.h"
#include "Arduino.h"
#include "analogWrite.h"

#include <iostream>
#include <math.h>

#define PI 3.14159265

using namespace std;

int pinarray[6];
int leftMotor, rightMotor;
int pos;
double double_x, double_y, speed, motor, temp, temp1;

// Map Func
long BtAnalogStick::mapping(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// BtCar Control
int BtAnalogStick::move(int x, int y){
    double_x = double(x - 512);
    double_y = double(y - 512);
    
    // Calculate position and speed for left right motor using (Polar coordinate system) method
    temp1 = atan2 (double_y, double_x) * 180 / PI;
    pos = int(temp1);

    temp = sqrt(pow(double_x, 2) + pow(double_y, 2));
    speed = mapping(temp, 0, 512, 0, 100);

    if(double_y < 0) pos += 360;
    if(double_x == 0 && double_y == 0) pos = 0;

    // Setting left right motor for analogWrite
    if(pos == 90){
        leftMotor = int((speed/100) * 255);
        rightMotor = int((speed/100) * 255);
    }
    if(pos>90 && pos<180){
        motor = mapping(pos, 91, 179, 0, 255);
        leftMotor = int((speed/100) * (255 - motor));
        rightMotor = int((speed/100) * 255);
    }

    if(pos == 180){
        leftMotor = int((speed/100) * 0);
        rightMotor = int((speed/100) * 255);
    }
    if(pos>180 && pos<270){
        motor = mapping(pos, 181, 269, 0, 255);
        leftMotor = int(floor(255 * (speed/100))-((speed/100) * (255 - motor)));
        rightMotor = int((speed/100) * 255);
    }
    
    if(pos == 270){
        leftMotor = int((speed/100) * 255);
        rightMotor = int((speed/100) * 255);
    }
    if(pos>270 && pos<360){
        motor = mapping(pos, 271, 359, 0, 255);
        leftMotor = int((speed/100) * 255);
        rightMotor = int((speed/100) * (255 - motor));
    }

    if(pos == 0 || pos == 360){
        leftMotor = int((speed/100) * 255);
        rightMotor = int((speed/100) * 0);
    }
    if(pos>0 && pos<90){
        motor = mapping(pos, 1, 89, 0, 255);
        leftMotor = int((speed/100) * 255);
        rightMotor = int(floor(255 * (speed/100))-((speed/100) * (255 - motor)));
    }
    
    // Moving Car
    if(double_y == 0 && double_x == 0){
        // Serial.println("stop");
    }
    else if(double_y > 0){
        // Serial.println("move foward");
        analogWrite(pinarray[4], leftMotor);
        digitalWrite(pinarray[2],LOW);
        digitalWrite(pinarray[3],HIGH);

        analogWrite(pinarray[5], rightMotor);
        digitalWrite(pinarray[1],LOW);
        digitalWrite(pinarray[0],HIGH);
        
    }
    else if(double_y < 0){
        // Serial.println("move backward");
        analogWrite(pinarray[4], leftMotor);
        digitalWrite(pinarray[3],LOW);
        digitalWrite(pinarray[2],HIGH);

        analogWrite(pinarray[5], rightMotor);
        digitalWrite(pinarray[0],LOW);
        digitalWrite(pinarray[1],HIGH);
        
    }

}

// Setting up left right motors pin
int BtAnalogStick::motorpin(int pin1, int pin2, int pin3, int pin4, int ena, int enb)
{
	pinarray[0]=pin1;
	pinarray[1]=pin2;
	pinarray[2]=pin3;
	pinarray[3]=pin4;
	pinarray[4]=ena;
	pinarray[5]=enb;
	for(int count=0;count<6;count++)
	{
		pinMode(pinarray[count],OUTPUT);
	}
}