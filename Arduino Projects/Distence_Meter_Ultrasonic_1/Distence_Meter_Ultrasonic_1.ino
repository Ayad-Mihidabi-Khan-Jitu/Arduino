#include<LiquidCrystal.h> // lcd Header
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // pins for LCD Connection
 
#define led1 6 //led pin
#define led2 7 //led pin
#define led3 8 //led pin
#define led4 9 //led pin
#define echoPin 7
#define trigPin 9

int long duration;
int distance;
 
void setup()
{
lcd.begin(16,2); //initializing lcd
Serial.begin(9600); // initializing serial
lcd.print("Distance ");
lcd.setCursor(0,1);
lcd.print("Meter ");
delay(2000);
lcd.clear();
//analogReference(EXTERNAL);

pinMode(echoPin,INPUT);
pinMode(trigPin,OUTPUT);

pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(led3,OUTPUT);
pinMode(led4,OUTPUT);

}
 
void loop()
{
 
/*displying change in x,y and z axis values over lcd*/
digitalWrite(trigPin,LOW);
delayMicroseconds(2); 
digitalWrite(trigPin,HIGH);
delayMicroseconds(10); 
digitalWrite(trigPin,LOW);
duration=pulseIn(echoPin,HIGH);
distance=(duration*0.034/2);
Serial.println(distance);

lcd.setCursor(1,1);
lcd.print("Distance = ");
lcd.setCursor(12,1);
lcd.print(distance);
  
  if(distance<=2){
digitalWrite(led1,HIGH);
digitalWrite(led2,HIGH);
digitalWrite(led3,HIGH);
digitalWrite(led4,HIGH);

}
else if(distance>2 && distance <= 10){
digitalWrite(led1,HIGH);
digitalWrite(led2,HIGH);
digitalWrite(led3,HIGH);
digitalWrite(led4,LOW);
}
else if(distance>10 && distance <= 20){
digitalWrite(led1,HIGH);
digitalWrite(led2,HIGH);
digitalWrite(led3,LOW);
digitalWrite(led4,LOW);
}
else if(distance>20 && distance <= 30){
digitalWrite(led1,HIGH);
digitalWrite(led2,LOW);
digitalWrite(led3,LOW);
digitalWrite(led4,LOW);
}
else {
digitalWrite(led1,LOW);
digitalWrite(led2,LOW);
digitalWrite(led3,LOW);
digitalWrite(led4,LOW);
}
  //delay(500);

 
}
