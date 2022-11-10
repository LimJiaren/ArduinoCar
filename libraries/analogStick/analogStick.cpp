#include "analogStick.h"
#include "Arduino.h"
#include "analogWrite.h"

#include <iostream>
#include <math.h>

#define PI 3.14159265

using namespace std;

int pinarray[4];
int leftMotor, rightMotor;
int pos;
double double_x, double_y, speed, motor, temp, temp1;

long BtAnalogStick::mapping(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int BtAnalogStick::move(int x, int y){
    double_x = double(x - 512);
    double_y = double(y - 512);

    temp1 = atan2 (double_y, double_x) * 180 / PI;
    pos = int(temp1);

    if(double_y < 0) pos += 360;
    if(double_x == 0 && double_y == 0) pos = 0;

    temp = sqrt(pow(double_x, 2) + pow(double_y, 2));
    speed = mapping(temp, 0, 512, 0, 100);

    
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
    

    Serial.print(leftMotor);
    Serial.print(" , ");
    Serial.println(rightMotor);

    if(double_y == 0 && double_x == 0){
        Serial.println("stop");
    }
    else if(double_y > 0){
        Serial.println("move foward");
        digitalWrite(pinarray[2],LOW);
        analogWrite(pinarray[3],leftMotor);

        digitalWrite(pinarray[1],LOW);
         analogWrite(pinarray[0],rightMotor);
        
    }
    else if(double_y < 0){
        Serial.println("move backward");
        digitalWrite(pinarray[3],LOW);
        analogWrite(pinarray[2],leftMotor);
        
        digitalWrite(pinarray[0],LOW);
        analogWrite(pinarray[1],rightMotor);
        
    }

}



int BtAnalogStick::motorpin(int pin1,int pin2,int pin3,int pin4)
{
	pinarray[0]=pin1;
	pinarray[1]=pin2;
	pinarray[2]=pin3;
	pinarray[3]=pin4;
	for(int count=0;count<4;count++)
	{
		pinMode(pinarray[count],OUTPUT);
	}
}