#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
SoftwareSerial nodemcu(2, 3);


// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

int pinRedLed = 12;
int pinGreenLed = 11;

int pinSensor = A0;
int THRESHOLD = 90;
int buzzer = 10;

 

int rdata = 0; 
String mystring; 
void setup()
{
  // initialize the LCD
 lcd.begin();
 lcd.setCursor(0, 0);
  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("--Food Status--");

  //for debug
  Serial.begin(9600); 
  //for node
  nodemcu.begin(9600); 



pinMode(buzzer, OUTPUT);
pinMode(pinRedLed, OUTPUT);
pinMode(pinGreenLed, OUTPUT);
pinMode(pinSensor, INPUT);


}

void loop()
{

   // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);

    // put your main code here, to run repeatedly:

int rdata  =  analogRead(pinSensor);


//Serial.print("Methane Range: ");
//Serial.println(rdata);

if(rdata >= THRESHOLD){
   digitalWrite(pinRedLed, HIGH);
   digitalWrite(pinGreenLed, LOW);
   digitalWrite(buzzer, HIGH);  
   lcd.print("Rotten      ");
   Serial.println("Rotten");

  if (nodemcu.available() > 0)
  {
    nodemcu.println("Rotten");
  }
   
   delay(50);
 
}else
  {
    digitalWrite(pinRedLed, LOW);
    digitalWrite(pinGreenLed, HIGH);
    digitalWrite(buzzer, LOW);
    lcd.print("Well State       ");
    Serial.println("Well State");

  if (nodemcu.available() > 0)
  {
    nodemcu.println("Well State");
  }
  
  }
  
  /*
 if (nodemcu.available() > 0)
  {
  char data; 
  data = nodemcu.read(); 
  Serial.println(data); 
  }
  if(rdata < 200){
  mystring = mystring + "Methane Range: " + rdata; 
  nodemcu.println(mystring);
  Serial.println(mystring); 
  
  }else
{
    mystring = "Food Spoiled";
    nodemcu.println(mystring);
    Serial.println(mystring); 
  
  }
*/
 //mystring = ""; 
delay(1000); 
 
}
