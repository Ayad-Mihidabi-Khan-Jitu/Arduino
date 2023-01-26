#include<Servo.h>

#define ledpin D0
#define analogpin A0

void setup() {
  // put your setup code here, to run once:
  pinMode(ledpin,OUTPUT);
  pinMode(analogpin,INPUT);
  Serial.begin(9600);
  
}

void loop() {

  int poten = analogRead(analogpin);
  int mappedPoten = map(poten,0,1023,0,255);


  // put your main code here, to run repeatedly:
  //Serial.println("Led ON");
  analogWrite(ledpin,mappedPoten);
  delay(100);


}
