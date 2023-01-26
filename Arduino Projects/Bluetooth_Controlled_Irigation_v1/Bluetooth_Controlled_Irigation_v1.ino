#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
int soilMoistureValue = 0;
int soilMoistureValue1 = 0;
int percentage=0;
int percentage1=0;
int switchPin = 7;
int pushed = 0;
char bt;
char au = 'a';
void setup() {  
  // initialize the LCD
  //lcd.begin();
  lcd.init();                      // initialize the lcd 
  lcd.init();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("Welcome!");                              
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  digitalWrite(3, HIGH);    
  digitalWrite(4, HIGH);    
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  Serial.begin(9600);
  bt = au;
  
}
void loop() {
soilMoistureValue = analogRead(A0);
//soilMoistureValue1 = analogRead(A1);
int switchState = digitalRead(switchPin);

//percentage = map(soilMoistureValue, 0, 1023, 0, 100);
percentage = map(soilMoistureValue, 0, 1023, 100, 0);
//percentage1 = map(soilMoistureValue1, 0, 1023, 100, 0);
//percentage = 9;
Serial.print("Moisture-1: ");
Serial.println(percentage);
//Serial.print("Moisture-2: ");
//Serial.println(percentage1);
//if(percentage<10) 
lcd.setCursor(0,0); 
lcd.print("Moisture:"); 
//lcd.print((percentage+percentage1)/2); 
lcd.print(percentage); 
lcd.print(" % "); 


if(Serial.available())
{
bt=Serial.read();
delay(500);
}
else if(!Serial.available()){
  bt = bt;
}
Serial.println("Pump Auto Mode");

if(bt == 'a')
{
  au = bt;
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

if((bt == 'o'))  
{
   bt = 'n';
   lcd.setCursor(0,1); 
   lcd.print("Pump on "); 
   Serial.println(" pump on ");
   digitalWrite(3,LOW);
   delay(2000);
}
if((bt == 'f') )
{ 
  //bt = 'a';
  Serial.println("Pump off");
  lcd.setCursor(0,1); 
  lcd.print("Pump off"); 
  digitalWrite(3,HIGH);
  delay(2000);
}

}
