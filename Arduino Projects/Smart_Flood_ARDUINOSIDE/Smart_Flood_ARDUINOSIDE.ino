#include <LiquidCrystal.h>
#include <DHT.h>
#include <SoftwareSerial.h>
SoftwareSerial nodemcu(2,3); //(rx,tx)

#define DHTPIN 4
#define trigger 6
#define echo 7
#define DHTTYPE DHT11   // DHT 11

float time = 0, distance = 0;
DHT dht(DHTPIN, DHTTYPE); // Create a DHT object

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
String cdata = "";

void setup() {
  Serial.begin(9600);
  nodemcu.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  dht.begin();
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {


  digitalWrite(trigger,LOW); // jodi age theke pin ta on thake
  //delay(2);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  time=pulseIn(echo,HIGH);
  //int timeInsec = timeInmicro/1000000;
  //distenceInmeter = (340*timeInsec);
  //double distenceIncentimeter = distenceInmeter/100;
  int distance = (time*0.034)/2;

  //Serial.print(distance);
  //Serial.println(" cm");

  lcd.setCursor(0, 0);
  float humidity = dht.readHumidity();
  lcd.print(String(humidity) + " H");
  lcd.setCursor(8, 0);
  //lcd.print(String(dht.readTemperature()) + " T");
  int tempCel = dht.readTemperature();
  lcd.setCursor(0, 1);

  //Serial.println(humidity);
  //Serial.println(tempCel);


  if(distance<30)
  {
      lcd.print(String(distance) + "% HIG");
      //Serial.println("HIGH");
      nodemcu.println("HIGH");

  }
  else if(distance<70)
  {
      lcd.print(String(distance) + "% MID");
      //Serial.println("MID");
      nodemcu.println("MID");
  }
  else
  {
    lcd.print(String(distance) + "% LOW");
    //Serial.println("LOW");
    nodemcu.println("LOW");
  }
   //Serial.println(distance); 
   //Serial.println(tempCel); 
   delay(1000);

   //cdata = cdata + distance+ "," +tempCel; // comma will be used a delimeter
   //Serial.println(cdata); 
   //nodemcu.println(cdata); // nodemcr namok software serial e data guli print kore hoyeche
   //delay(2000); // 2 seconds
   //delay(100); // 100 milli seconds
   //cdata = ""; 


}
