#include<LiquidCrystal.h>
int pinLCD[6]={2,3,4,5,6,7};
int ultraEcho= 2;
int ultraTrig= 3;
int ledPin=11;
long timeInmicro;
double distenceInmeter;

LiquidCrystal myLCD(pinLCD[0],pinLCD[1],pinLCD[2],pinLCD[3],pinLCD[4],pinLCD[5]);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myLCD.begin(20,4);
  myLCD.setCursor(0,0);
  pinMode(ultraTrig,OUTPUT);
  pinMode(ultraEcho,INPUT);
  pinMode(ledPin,OUTPUT);
}
/*
Ultrasonic Sensor er KriaKoushol
--------------------------------
# Hange holo 2cm-400cm
# Trigpin takes 10 micro second 5 volts
  to create 8 cycle ultrasonic wave and transmit
  by the transmiter ar jokhon e transmiter diye 
  signal ber hoy tokhon e echo pin high hoye jay.
  Kono object e signal badha peye fire ele jokhon receiver 
  ta receive  kore tokhon echo pin low hoye jay. 
  echo pin ta jotokkhon high thake seta e signal er travers time
  in microseconds(jehetu pulseIn(PIN,STATUS) function microsecond output dey)
  akhon s=vt diye distence ber korte hobe here v=430ms-1, s=2d
  ||
  .'. t (in second) = t/1000000 // akhane t ke 1000000 diye vag kora jabe na 
  s (in meter) =(340*t)/2;      // karon 340 meter kokhono cross korbe na cz
  s (in centimeter) =s/100;     // atar range 340 er kom 
  ||
  #taile hisab ta hobe: 
  1000000      microsec  e   jay      34000         centimeter 
  1               =      =    =     34000/1000000        =
  timeInmicro     =      =    =    (34000/1000000)*timeInmicro  =

  1000000 microsec e je distence jay seta send kora and received er distence
  .'. distenceIncentimeter = ((34000/1000000)*timeInmicro)/2
  
  
*/

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ultraTrig,LOW); // jodi age theke pin ta on thake
  //delay(2);
  delayMicroseconds(2);
  digitalWrite(ultraTrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(ultraTrig,LOW);
  timeInmicro=pulseIn(ultraEcho,HIGH);
  //int timeInsec = timeInmicro/1000000;
  //distenceInmeter = (340*timeInsec);
  //double distenceIncentimeter = distenceInmeter/100;
  double distenceIncentimeter = (timeInmicro*0.034)/2;
  
  
  distenceInmeter = (distenceIncentimeter/100);
  myLCD.setCursor(3,0);
  myLCD.println("Distence Meter");
  myLCD.setCursor(4,1);
  myLCD.print(distenceIncentimeter);
  myLCD.print(" C.Meters");
  myLCD.setCursor(4,2);
  myLCD.print(distenceInmeter);
  myLCD.print(" Meters");

  Serial.print("Distance : "); Serial.print(distenceIncentimeter); Serial.println(" cm"); 
  
  if(distenceIncentimeter>400){
    digitalWrite(ledPin,HIGH);
    delay(1000);
     myLCD.setCursor(0,3);
     myLCD.print("In Range-PSTUCSECLUB");
     
    }
    else{
  digitalWrite(ledPin,LOW);
  myLCD.setCursor(4,3);
  myLCD.print(timeInmicro);
  myLCD.print(" micros");
    }
  delay(1000);
  myLCD.clear();
  
}
