#include<ESP8266WiFi.h>
int digiPin6 = 12;
int digiPin7 = 13;
int analogPin = A0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(digiPin6,OUTPUT);
  pinMode(digiPin7,OUTPUT);
  pinMode(analogPin,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Analog input1: ");
  Serial.print(readSensor1());
  Serial.print(" | ");
  Serial.print("Analog input2: ");
  Serial.println(readSensor2());

}

int readSensor1(){
  digitalWrite(digiPin6, HIGH);
  digitalWrite(digiPin7, LOW);
  return analogRead(analogPin);
  }

int readSensor2(){
  digitalWrite(digiPin6, LOW);
  digitalWrite(digiPin7, HIGH);
  return analogRead(analogPin);
  }
