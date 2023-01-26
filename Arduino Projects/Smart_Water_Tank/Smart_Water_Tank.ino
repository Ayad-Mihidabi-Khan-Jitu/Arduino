#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
const int trigPin = 2;
const int echoPin = 3;
int dis=0;
int ledA=13;
int ledB=12;
int ledC=11;
int ledD=10;
double volInLi = 0.0;
int relay = 4;


int max_distance = 200;
void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
pinMode (ledA,OUTPUT);
pinMode (ledB,OUTPUT);
pinMode (ledC,OUTPUT);
pinMode (ledD,OUTPUT);
pinMode (relay,OUTPUT);

pinMode (trigPin,OUTPUT);
pinMode (echoPin,INPUT);

digitalWrite(ledA, LOW);
digitalWrite(ledB, LOW);
digitalWrite(ledC, LOW);
digitalWrite(ledD, LOW);

//lcd.init();                      // initialize the lcd 
//lcd.init(); 
lcd.begin();

// Print a message to the LCD.
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("Smart Water Tank");
//lcd.setCursor(2,1);
//lcd.print("------------");

}
void loop() {
// put your main code here, to run repeatedly:
long duration, inches, cm;
pinMode(trigPin,OUTPUT);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
//cm = ( duration / 29 ) / 2;
//inches = cm * 0.393701;
inches = microsecondsToInches(duration);
cm = microsecondsToCentimeters(duration);

volInLi = (3.1416*4.98*4.99*abs(20-cm))*0.001;

//map(value, fromLow, fromHigh, toLow, toHigh);
//dis = map(cm, 1, 20, 100, 0);
dis = map(cm, 1, 18, 100, 0);
Serial.println(cm);
Serial.println(dis);
Serial.println(volInLi);

if(cm<=2)
digitalWrite(relay,HIGH);
else
digitalWrite(relay,LOW);

if (cm >= 18 && cm <= 20)
{ 
lvlDisplay(volInLi);

ledInde(0,0,0,1);
//digitalWrite(relay,LOW);
delay(100); 
} 
else if(cm >= 13 && cm <= 17)
{
lvlDisplay(volInLi);
//digitalWrite(relay,LOW);
ledInde(0,0,1,1);
delay(100); 
}
else if(cm >= 8 && cm <= 12)
{
lvlDisplay(volInLi);
//digitalWrite(relay,LOW);
ledInde(0,1,1,1);
delay(100); 
}
else if(cm >= 0 && cm <= 7)
{
lvlDisplay(volInLi);

ledInde(1,1,1,1);
//digitalWrite(relay,HIGH);

delay(100); 
}
else
{
lvlDisplay("Rangeout");

ledInde(0,0,0,0);
delay(100); 
}
//digitalWrite (ledA,HIGH); if (inches >=a) {digitalWrite (ledA,HIGH);digitalWrite (ledB,LOW); digitalWrite (ledC,LOW); digitalWrite (ledD,LOW); }
//else if (inches >=b){digitalWrite (ledA,LOW);digitalWrite (ledB,HIGH); digitalWrite (ledC,LOW); }
//else if (inches >=c){digitalWrite (ledA,LOW);digitalWrite (ledB,LOW); digitalWrite (ledC,HIGH); }
//else if (inches >=d){digitalWrite (ledA,LOW);digitalWrite (ledB,LOW); digitalWrite (ledC,LOW);  }
//else {digitalWrite (ledA,HIGH);digitalWrite (ledB,HIGH); digitalWrite (ledC,HIGH); digitalWrite (ledD,HIGH); }




}



long microsecondsToInches(long microseconds) {
// According to Parallax's datasheet for the PING))), there are
// 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
// second). This gives the distance travelled by the ping, outbound
// and return, so we divide by 2 to get the distance of the obstacle.
// See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
return (microseconds / 74) / 2;
}
long microsecondsToCentimeters(long microseconds) {
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
return (microseconds / 29) / 2;
}

void lvlDisplay(double sttus){

lcd.setCursor(0,1);
lcd.print("Status: ");
//lcd.setCursor(8,1);
lcd.print(sttus);
//if(status == 100)
//lcd.setCursor(11,1);
//else lcd.setCursor(10,1);
lcd.print("L       ");
}

void lvlDisplay(String sttus){
lcd.setCursor(0,1);
lcd.print("Status: ");
lcd.setCursor(8,1);
lcd.print(sttus);

}

void ledInde(int A, int B,int C,int D){
digitalWrite (ledA,A);
digitalWrite (ledB,B); 
digitalWrite (ledC,C);
digitalWrite (ledD,D);
}
