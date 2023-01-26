#include<LiquidCrystal.h> // lcd Header
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // pins for LCD Connection
 
#define buzzer 7 // buzzer pin
#define led 13 //led pin
 
const int xInput = A0;
const int yInput = A1;
const int zInput = A2;

int RawMin = 0;
int RawMax = 1023;
int minchang = 30;
 
long start;
int buz=0;
 
/*Macros*/
const int sampleSize = 10;
int xStd = 632;
int yStd = 529;
int zStd = 534;
#define buzTime 5000 // buzzer on time
//x=611 y=495 z=515

 
void setup()
{
lcd.begin(16,2); //initializing lcd
Serial.begin(9600); // initializing serial
delay(1000);
lcd.print("EarthQuake ");
lcd.setCursor(0,1);
lcd.print("Detector ");
delay(2000);
lcd.clear();
analogReference(EXTERNAL);

pinMode(buzzer, OUTPUT);
pinMode(led, OUTPUT);
buz=0;
digitalWrite(buzzer, buz);
digitalWrite(led, buz);
}
 
void loop()
{
//Read raw values
  int xRaw = ReadAxis(xInput);
  int yRaw = ReadAxis(yInput);
  int zRaw = ReadAxis(zInput);

  // Convert raw values to 'milli-Gs"
  long xScaled = map(xRaw, RawMin, RawMax, -3000, 3000);
  long yScaled = map(yRaw, RawMin, RawMax, -3000, 3000);
  long zScaled = map(zRaw, RawMin, RawMax, -3000, 3000);

  // re-scale to fractional Gs
  float xAccel = xScaled / 1000.0;
  float yAccel = yScaled / 1000.0;
  float zAccel = zScaled / 1000.0;

  delay(200);
 
/*displying change in x,y and z axis values over lcd*/
lcd.setCursor(0,1);
lcd.print(xRaw);
lcd.setCursor(6,1);
lcd.print(yRaw);
lcd.setCursor(12,1);
lcd.print(zRaw);
delay(100);

/* 
// comparing change with predefined limits
if(xRaw < minVal || xRaw > maxVal || yRaw < minVal || yRaw > maxVal || zRaw < minVal || zRaw > maxVal)
{
if(buz == 0)
start=millis(); // timer start
buz=1; // buzzer / led flag activated
}
 
else if(buz == 1) // buzzer flag activated then alerting earthquake
{
lcd.setCursor(0,0);
lcd.print("Earthquake Alert ");
if(millis()>= start+buzTime)
buz=0;
}
 
else
{
lcd.clear();
lcd.print(" X Y Z ");
}
*/

if(abs(xRaw-xStd) > minchang || abs(yRaw-yStd) > minchang || abs(zRaw-zStd) > minchang)
{
if(buz == 0)
start=millis(); // timer start
buz=1; // buzzer / led flag activated
}
 
else if(buz == 1) // buzzer flag activated then alerting earthquake
{
lcd.setCursor(0,0);
lcd.print("Earthquake Alert ");
if(millis()>= start+buzTime)
buz=0;
}
 
else
{
lcd.clear();
lcd.print(" X Y Z ");
}
 
digitalWrite(buzzer, buz); // buzzer on and off command
digitalWrite(led, buz); // led on and off command
 
/*sending values to processing for plot over the graph*/
Serial.print("x=");
Serial.println(xRaw);
Serial.print("y=");
Serial.println(yRaw);
Serial.print("z=");
Serial.println(zRaw);
Serial.println(" $");
}


// Take samples and return the average
int ReadAxis(int axisPin)
{
  long reading = 0;
  analogRead(axisPin);
  delay(1);
  for (int i = 0; i < sampleSize; i++)
  {
  reading += analogRead(axisPin);
  }
  return reading/sampleSize;
}
