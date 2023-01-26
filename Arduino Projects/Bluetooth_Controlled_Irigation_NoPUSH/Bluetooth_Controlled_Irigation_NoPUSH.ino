#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
int soilMoistureValue = 0;
int percentage=0;
char bt;
char au = 'a';
String btt = "auto";
void setup() {  
  // initialize the LCD
  lcd.init();                      // initialize the lcd 
  lcd.init();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("Welcome!"); 
                                 
  digitalWrite(3, HIGH);    
  pinMode(3,OUTPUT);
  pinMode(A0,INPUT);
  Serial.begin(9600);
  bt = au;
}
void loop() {
soilMoistureValue = analogRead(A0);

//percentage = map(soilMoistureValue, 0, 1023, 0, 100);
percentage = map(soilMoistureValue, 0, 1023, 100, 0);
//percentage = 9;
Serial.print("Soil Moisture: ");
Serial.print(percentage);
Serial.println(" %");

//if(percentage<10) 
lcd.setCursor(0,0); 
lcd.print("Moisture:"); 
lcd.print(percentage); 
lcd.print(" % "); 

if(!Serial.available()==0)
{
//bt=Serial.read();
//delay(3000);
btt=Serial.readString();
//Serial.print("Entered into Serial ava:");
//Serial.print(btt);
//Serial.print("###");
//Serial.println();
}


//Serial.println(bt);

if(btt == "auto")
{
  Serial.println("Smart Mode");
  if( percentage < 10)  
  {
   lcd.setCursor(0,1); 
   lcd.print("Pump ON "); 
   Serial.println("Pump on ");
   digitalWrite(3,LOW);
   delay(2000);
 }
 if(percentage >60)
 { 
  Serial.println("Pump off");
  lcd.setCursor(0,1); 
  lcd.print("Pump OFF"); 
  digitalWrite(3,HIGH);
  delay(2000);
 }
}

if(btt == "on")  
{
   lcd.setCursor(0,1); 
   lcd.print("Pump ON "); 
   Serial.println("Pump on ");
   digitalWrite(3,LOW);
   delay(2000);
}
if(btt == "off")
{ 
  Serial.println("Pump off");
  lcd.setCursor(0,1); 
  lcd.print("Pump OFF"); 
  digitalWrite(3,HIGH);
  delay(2000);
}

delay(1000);

}
