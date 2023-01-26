#include<Servo.h>

#define S0 D0
#define S1 D1
#define S2 D2
#define S3 D3

#define servoPin D4
#define SIG A0
#define ledpin D5

Servo servo;

void setup() {
  // put your setup code here, to run once:
  servo.attach(servoPin); 
  
  pinMode(S0,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin SO */        
  pinMode(S1,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S1 */  
  pinMode(S2,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S2 */ 
  pinMode(S3,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S3 */  
  pinMode(SIG, INPUT); 
  
  pinMode(ledpin,OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  sensor(0,0,0,0); //Sensor 0
  int sensor0 = analogRead(SIG);
  delay(100);

  sensor(1,0,0,0); //Sensor 1
  int sensor1 = analogRead(SIG);
  delay(100);
 
  sensor(0,1,0,0); //Sensor 2
  int sensor2 = analogRead(SIG);
  delay(100);

  Serial.print("sensor0: ");
  Serial.println(sensor0);
  
  Serial.print("sensor1: ");
  Serial.println(sensor1);
  
  Serial.print("sensor2: ");
  Serial.println(sensor2);

  delay(2000);


  int mappedPoten = map(SIG,0,1023,0,180);
  int mappedLed = map(SIG,0,1023,0,255);

  // put your main code here, to run repeatedly:
  //Serial.println(poten);
  //Serial.println(mappedPoten);
  //servo.write(mappedPoten);
  //analogWrite(ledpin,mappedLed);
  //delay(100);


}

void sensor(int s0,int s1,int s2,int s3){
  digitalWrite(S0,s0);
  digitalWrite(S1,s1);
  digitalWrite(S2,s2);
  digitalWrite(S3,s3);
}
