#include<Servo.h>
int servoPin =6  ;
int ledPin = 7;
Servo myServo ; // Servo er object. atar kono perameter nai
void setup() {
  // put your setup code here, to run once:
  myServo.attach(6);       // ata begin er moto but pin number attach krote hoy
  pinMode(servoPin,OUTPUT);// pin ta obbossoi PWM pin hote hobe
  pinMode(ledPin,OUTPUT);  // pin 1 = vin | pin 2 = output | pin 3 = GND
}

void loop() {
  myServo.write(90);
  digitalWrite(ledPin,HIGH);
  delay(500);
  digitalWrite(ledPin,LOW);
  delay(500);
  myServo.write(0);
  digitalWrite(ledPin,HIGH);
  delay(500);
  digitalWrite(ledPin,LOW);

  for(int i=1;i<=180;i++){
    myServo.write(i);
    delay(100);   
    }
  
}
