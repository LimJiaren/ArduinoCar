#include <analogWrite.h>

#define IN1 12
#define IN2 14
#define IN3 27
#define IN4 26
void setup() {
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);

}

void loop() {
//control speed 
  analogWrite(IN3, 255);
  analogWrite(IN1, 255); 
  digitalWrite(IN2, LOW);
  digitalWrite(IN4, LOW);
  
  

}
