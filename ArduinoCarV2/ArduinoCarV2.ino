#include <analogWrite.h>
#include <analogStick.h>
#include "BluetoothSerial.h"

byte BTData;
String Data ;
int values[2];

BtAnalogStick a1;

BluetoothSerial SerialBT;

void splitData(String str) {
  int index = str.indexOf(",");

  values[0] = (str.substring(0, index)).toInt();
  values[1] = (str.substring(index + 1)).toInt();
}

void setup() {
  Serial.begin(115200);
  SerialBT.begin();
  Serial.println("Bluetooth Started! Ready to pair...");
}

void loop() {
  if (SerialBT.available()){
    char character = SerialBT.read();
    Data.concat(character);
    if (character == '\n') {
      splitData(Data);

      a1.move(values[0] , values[1]);
      Data = "";
    }
  }
}
