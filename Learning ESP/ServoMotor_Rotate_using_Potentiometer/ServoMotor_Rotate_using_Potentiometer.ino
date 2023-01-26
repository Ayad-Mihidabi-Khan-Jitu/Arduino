#include<Servo.h>

#define servoPin D4
#define analogpin A0
#define ledpin D1

Servo servo;

void setup() {
  // put your setup code here, to run once:
  servo.attach(servoPin); 
  pinMode(analogpin,INPUT);
  pinMode(ledpin,OUTPUT);
  Serial.begin(9600);
  
}

void loop() {

  int poten = analogRead(analogpin);
  int mappedPoten = map(poten,0,1023,0,180);
  int mappedLed = map(poten,0,1023,0,255);

  // put your main code here, to run repeatedly:
  Serial.println(poten);
  Serial.println(mappedPoten);
  servo.write(mappedPoten);
  analogWrite(ledpin,mappedLed);
  //delay(100);


}
