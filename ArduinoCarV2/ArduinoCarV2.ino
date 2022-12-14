#include <analogWrite.h>
#include <analogStick.h>
#include "BluetoothSerial.h"

byte BTData;
String Data ;
int values[2];

int IN1 = 12;
int IN2 = 14;
int IN3 = 27;
int IN4 = 26;
int ENA = 25;
int ENB = 33;
int left_light = 2;
int right_light = 4;
int back_light = 5;
int trig_pin = 32;
int echo_pin = 35;
int buzzer = 18;

BtAnalogStick car;

BluetoothSerial SerialBT;

void splitData(String str) {
  int index = str.indexOf(",");

  values[0] = (str.substring(0, index)).toInt();
  values[1] = (str.substring(index + 1)).toInt();
}

void setup() {
  Serial.begin(115200);
  car.motorpin(IN1, IN2, IN3, IN4, ENA, ENB, left_light, right_light, back_light, buzzer);
  car.UltraSonicPin(trig_pin, echo_pin);
  SerialBT.begin("AnalogBtCar");
  Serial.println("Bluetooth Started! Ready to pair...");
}

void loop() {
  if (SerialBT.available()) {
    char character = SerialBT.read();
    Data.concat(character);
    if (character == '\n') {
      splitData(Data);
      car.move(values[0] , values[1]);
      Data = "";
    }
  }
}
