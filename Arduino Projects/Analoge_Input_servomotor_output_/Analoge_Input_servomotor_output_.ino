#include<Servo.h>
int servoOutputPin = 10;
int analogINPUT = A5;
int ledRed = 6, ledYellow = 7;
Servo myServo;
void setup() {
  // put your setup code here, to run once:
  myServo.attach(servoOutputPin);
  Serial.begin(9600);
  pinMode(servoOutputPin,OUTPUT);
  pinMode(ledRed,OUTPUT);
  pinMode(ledYellow,OUTPUT);
  pinMode(analogINPUT,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int analodValue=analogRead(analogINPUT);
  int convertedValue = map(analodValue,1023,0,180,0);
  Serial.print("Sensor value = ");
  Serial.println(analodValue);
  Serial.print("Converted value = ");
  Serial.println(convertedValue);
  Serial.println("--------------------");
  
  digitalWrite(ledYellow,HIGH);
  delay(100);
  digitalWrite(ledYellow,LOW);
  myServo.write(convertedValue);
  delay(1500);
  digitalWrite(ledRed,HIGH);
  delay(100);
  digitalWrite(ledRed,LOW);
  myServo.write(0);
  delay(1500);
  
}
