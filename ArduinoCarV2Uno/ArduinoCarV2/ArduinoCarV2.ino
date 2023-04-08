#include <analogStick.h>
#include <SoftwareSerial.h>  //include SoftwareSerial Library
SoftwareSerial BT(11, 12);   //TX, RX
byte BTData;
String Data;
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
unsigned long long previousTime1 = 0;
bool buzzerBool = false;

BtAnalogStick car;
void splitData(String str) {
  int index = str.indexOf(",");

  values[0] = (str.substring(0, index)).toInt();
  values[1] = (str.substring(index + 1)).toInt();
  if (values[0] < 0 || values[0] > 1024) {
    values[0] = 512;
  }
  if (values[1] < 0 || values[1] > 1024) {
    values[1] = 512;
  }
//   Serial.print("value 1: ");
//   Serial.print(values[0]);
  // Serial.print(" values 2: ");
  // Serial.println(values[1]);
}

void setup() {
  Serial.begin(9600);
  Serial.println("BT is ready!");
  BT.begin(9600);

  car.motorpin(IN1, IN2, IN3, IN4, ENA, ENB, left_light, right_light, back_light, buzzer);
  car.UltraSonicPin(trig_pin, echo_pin);
  previousTime1 = millis();
  Serial.println("Bluetooth Started! Ready to pair...");
}

void loop() {
  if (BT.available() > 0) {
    char character = BT.read();
    Data.concat(character);
    if (character == '\n') {
      splitData(Data);
      if (values[1] > 512) {
        car.range();
        if (car.getDistance() > 5) {
          car.move(values[0], values[1]);
        } else {
          buzzerBool = true;
          car.move(512, 512);
          Data = "";
        }
      } else {
        car.move(values[0], values[1]);
        Data = "";
      }
    }
  }
  if (buzzerBool){
    if(millis() - previousTime1 >= 100){
      previousTime1 = millis();
      buzzerBool = false;
    }
    analogWrite(buzzer, 255);
  }
}
