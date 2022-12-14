#include <analogStick.h>
#include <SoftwareSerial.h> //include SoftwareSerial Library
SoftwareSerial BT(11, 12); //TX, RX
byte BTData;
String Data ;
int values[2];

int IN1 = 3;
int IN2 = 5;
int IN3 = 6;
int IN4 = 9;
int ENA = A1;
int ENB = A1;
int left_light = 4;
int right_light = 7;
int back_light = 2;
int trig_pin = 10;
int echo_pin = 8;
int buzzer = A0;

BtAnalogStick car;
void splitData(String str) {
  int index = str.indexOf(",");

  values[0] = (str.substring(0, index)).toInt();
  values[1] = (str.substring(index + 1)).toInt();
}

void setup() {
  Serial.begin(9600);
  Serial.println("BT is ready!");
  BT.begin(9600);
  
  car.motorpin(IN1, IN2, IN3, IN4, ENA, ENB, left_light, right_light, back_light, buzzer);
  car.UltraSonicPin(trig_pin, echo_pin);
  Serial.println("Bluetooth Started! Ready to pair...");
  
}

void loop() {
  if (BT.available()> 0) {
    char character = BT.read();
    Data.concat(character);
    if (character == '\n') {
      splitData(Data);
      car.move(values[0] , values[1]);
      Data = "";
    }
  }
}
