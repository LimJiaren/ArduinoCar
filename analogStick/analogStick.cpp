#include "analogStick.h"
#include "Arduino.h"
#include <math.h>

#define PI 3.14159265

using namespace std;

int pinarray[10];
int leftMotor, rightMotor, trigpin, echopin;
int pos;
int echo=0, trig=0;

double double_x, double_y, speed, motor, temp, temp1;
long duration;
float ultraSonicDistance;

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
    speed = mapping(temp, 0, 512, 40, 100);

    if(double_y < 0) pos += 360;
    if(double_x == 0 && double_y == 0) pos = 0;
    digitalWrite(pinarray[9], LOW);
    // Setting left right motor for analogWrite
    if(pos == 90){
        leftMotor = int((speed/100) * 255);
        rightMotor = int((speed/100) * 255);
    }
    if(pos>90 && pos<180){
        motor = mapping(pos, 91, 179, 0, 255);
        leftMotor = int((speed/100) * (255 - motor));
        rightMotor = int((speed/100) * 255);
        digitalWrite(pinarray[6], HIGH);
        digitalWrite(pinarray[7], LOW);
    }

    if(pos == 180){
        leftMotor = int((speed/100) * 0);
        rightMotor = int((speed/100) * 255);
        digitalWrite(pinarray[6], HIGH);
        digitalWrite(pinarray[7], LOW);
    }
    if(pos>180 && pos<270){
        motor = mapping(pos, 181, 269, 0, 255);
        leftMotor = int(floor(255 * (speed/100))-((speed/100) * (255 - motor)));
        rightMotor = int((speed/100) * 255);
        digitalWrite(pinarray[6], HIGH);
        digitalWrite(pinarray[7], LOW);
    }
    
    if(pos == 270){
        leftMotor = int((speed/100) * 255);
        rightMotor = int((speed/100) * 255);
    }
    if(pos>270 && pos<360){
        motor = mapping(pos, 271, 359, 0, 255);
        leftMotor = int((speed/100) * 255);
        rightMotor = int((speed/100) * (255 - motor));
        digitalWrite(pinarray[7], HIGH);
        digitalWrite(pinarray[6], LOW);
    }

    if(pos == 0 || pos == 360){
        leftMotor = int((speed/100) * 255);
        rightMotor = int((speed/100) * 0);
        digitalWrite(pinarray[7], HIGH);
        digitalWrite(pinarray[6], LOW);
    }
    if(pos>0 && pos<90){
        motor = mapping(pos, 1, 89, 0, 255);
        leftMotor = int((speed/100) * 255);
        rightMotor = int(floor(255 * (speed/100))-((speed/100) * (255 - motor)));
        digitalWrite(pinarray[7], HIGH);
        digitalWrite(pinarray[6], LOW);
    }

    // Moving Car
    if(double_y == 0 && double_x == 0){
        digitalWrite(pinarray[2],LOW);
        digitalWrite(pinarray[3],LOW); 
        digitalWrite(pinarray[1],LOW);
        digitalWrite(pinarray[0],LOW);
        digitalWrite(pinarray[6], LOW);
        digitalWrite(pinarray[7], LOW);
        digitalWrite(pinarray[8], LOW);
        
    }
    else if(double_y > 0){
        digitalWrite(pinarray[8], LOW);
        range();
        if(ultraSonicDistance <= 5){
            digitalWrite(pinarray[9], HIGH);
            Serial.println("!Danger!");
        }  
        else{
            digitalWrite(pinarray[9], LOW);

            digitalWrite(pinarray[2],LOW);
            analogWrite(pinarray[3],leftMotor);

            analogWrite(pinarray[0], rightMotor);
            digitalWrite(pinarray[1],LOW);

        }
    }
    else if(double_y < 0){
        
        digitalWrite(pinarray[8], HIGH);

        analogWrite(pinarray[2], leftMotor);
        digitalWrite(pinarray[3],LOW);

        analogWrite(pinarray[1], rightMotor);
        digitalWrite(pinarray[0],LOW);    
    }

}

// Setting up left right motors pin
int BtAnalogStick::motorpin(int pin1, int pin2, int pin3, int pin4, int ena, int enb, int left_light, int right_light, int back_light, int buzzer)
{
	pinarray[0] = pin1;
	pinarray[1] = pin2;
	pinarray[2] = pin3;
	pinarray[3] = pin4;
	pinarray[4] = ena;
	pinarray[5] = enb;
    pinarray[6] = left_light;
    pinarray[7] = right_light;
    pinarray[8] = back_light;
    pinarray[9] = buzzer;
	for(int count=0;count<10;count++)
	{
		pinMode(pinarray[count],OUTPUT);
	}
}

void BtAnalogStick::range(){
	digitalWrite(trigpin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigpin, LOW);
    duration = pulseIn (echopin, HIGH);
    // Serial.println(duration);
    ultraSonicDistance = duration * 0.034 / 2;
    Serial.println(ultraSonicDistance);
    
}

int BtAnalogStick::UltraSonicPin(int trig,int echo)
{
	trigpin=trig;
	echopin=echo;
	pinMode(trig,OUTPUT);
	pinMode(echo,INPUT);
}