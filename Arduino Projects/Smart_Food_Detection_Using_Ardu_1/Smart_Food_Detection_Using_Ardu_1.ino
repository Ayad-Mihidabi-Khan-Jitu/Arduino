#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial nodemcu(2, 3);

int pinRedLed = 12;
int pinGreenLed = 11;
int pinSensor = A0;
int THRESHOLD = 90;
int buzzer = 10;

 

int rdata = 0; 
String mystring; 
void setup()
{
Serial.begin(9600); 
nodemcu.begin(9600); 

lcd.begin();
lcd.setCursor(0, 0);
// Turn on the blacklight and print a message.
lcd.backlight();
lcd.print("--Food Status--");


pinMode(buzzer, OUTPUT);
pinMode(pinRedLed, OUTPUT);
pinMode(pinGreenLed, OUTPUT);
pinMode(pinSensor, INPUT);



}

void loop()
{

// put your main code here, to run repeatedly:
lcd.setCursor(0, 1);
int rdata  =  analogRead(pinSensor);


Serial.print("Methane Range: ");
Serial.println(rdata);

if(rdata >= THRESHOLD)
  {
   digitalWrite(pinRedLed, HIGH);
   digitalWrite(pinGreenLed, LOW);
   digitalWrite(buzzer, HIGH);  
   lcd.print("Rotten      ");
   delay(50);
 
  }
else
  {
    digitalWrite(pinRedLed, LOW);
    digitalWrite(pinGreenLed, HIGH);
    digitalWrite(buzzer, LOW);
    lcd.print("Well State       ");
  }
  
  if (nodemcu.available() > 0)
  {
  char data; 
  data = nodemcu.read(); 
  Serial.println(data); 
  }
  if(rdata < THRESHOLD){
  mystring = mystring + "Methane Range: " + rdata; 
  nodemcu.println(mystring);
  Serial.println(mystring); 
  
  }else
{
    mystring = "Food Spoiled";
    nodemcu.println(mystring);
    Serial.println(mystring); 
  
  }

 mystring = ""; 
delay(1000); 
 
}
