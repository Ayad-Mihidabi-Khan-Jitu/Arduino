#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
int soilMoistureValue = 0;
int percentage=0;
int switchPin = 7;
int pushed = 0;
char bt;
char au = 'a';
void setup() {  
  // initialize the LCD
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("Welcome!"); 
  pinMode(switchPin,INPUT);                              
  digitalWrite(3, HIGH);    
  pinMode(3,OUTPUT);
  pinMode(A0,INPUT);
  Serial.begin(9600);
  bt = au;
  
}
void loop() {
soilMoistureValue = analogRead(A0);
int switchState = digitalRead(switchPin);

//working with push mode
if(switchState == 1) {
  //switchState = 0;
  pushed = 1 - pushed;
  }

  Serial.println(switchState);
  Serial.println(pushed);

//percentage = map(soilMoistureValue, 0, 1023, 0, 100);
percentage = map(soilMoistureValue, 0, 1023, 100, 0);
//percentage = 9;
Serial.println(percentage);
//if(percentage<10) 
lcd.setCursor(0,0); 
lcd.print("Moisture:"); 
lcd.print(percentage); 
lcd.print(" % "); 

if(Serial.available())
{
bt=Serial.read();
delay(500);

}
Serial.println(bt);

if(bt == 'a')
{
  if( percentage < 10)  
  {
   lcd.setCursor(0,1); 
   lcd.print("Pump on "); 
   Serial.println(" pump on ");
   digitalWrite(3,LOW);
   delay(2000);
 }
 if(percentage >60)
 { 
  Serial.println("Pump off");
  lcd.setCursor(0,1); 
  lcd.print("Pump off"); 
  digitalWrite(3,HIGH);
  delay(2000);
 }
}

if((bt == 'o') || (pushed == 1))  
{
   bt = 'n';
   lcd.setCursor(0,1); 
   lcd.print("Pump on "); 
   Serial.println(" pump on ");
   digitalWrite(3,LOW);
   delay(2000);
}
if((bt == 'f') || (pushed == 0 && bt != 'a'))
{ 
  //bt = 'a';
  Serial.println("Pump off");
  lcd.setCursor(0,1); 
  lcd.print("Pump off"); 
  digitalWrite(3,HIGH);
  delay(2000);
}

}
