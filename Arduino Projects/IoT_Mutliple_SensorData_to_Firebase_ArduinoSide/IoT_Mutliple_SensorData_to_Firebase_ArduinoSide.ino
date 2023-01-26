#include <SoftwareSerial.h>
SoftwareSerial nodemcu(2,3); //(rx,tx)
//tx,rx of arduino is for debugging(serial monitor) ai jonno pin2,pin3 ke rx tx hisebe
//dhore nodemcu namok object create korechi

int sensor1 = A0;
int sensor2 = A1; 
//int sensor3 = A2; 

int phSensor = 0; // sensor1 data
int moisSensor = 0; // sensor2 data
//int sdata3 = 0; // sensor3 data

String cdata; // complete data, consisting of sensors values

void setup()
{
Serial.begin(9600); 
nodemcu.begin(9600);
//nodemcu.begin(115200);

pinMode(sensor1, INPUT);
pinMode(sensor2, INPUT);
//pinMode(sensor3, INPUT);
//pinMode(4, OUTPUT); // TO ON/OFF VARIABLE RESISTOR
//digitalWrite(4, HIGH); 

}

void loop()
{
  
    phSensor = analogRead(sensor1);
    moisSensor = analogRead(sensor2);
    //sdata3 = analogRead(sensor3);
   //cdata = cdata + sdata1+","+sdata2+","+sdata3; // comma will be used a delimeter
   cdata = cdata + phSensor+ "," +moisSensor; // comma will be used a delimeter
   Serial.println(cdata); 
   nodemcu.println(cdata); // nodemcr namok software serial e data guli print kore hoyeche
   delay(2000); // 2 seconds
   //delay(100); // 100 milli seconds
   cdata = ""; 

}
