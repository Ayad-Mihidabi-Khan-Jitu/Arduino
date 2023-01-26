#include<LiquidCrystal.h>
int lamp1 = 8, lamp2 = 9,led = 10;
int lamp1state = 1,lamp2state = 1;
String input;
LiquidCrystal myLCD(2,3,4,5,6,7);
void setup() {
  // put your setup code here, to run once:
  myLCD.begin(20,4);
  myLCD.setCursor(0,0);
  Serial.begin(9600);
  pinMode(lamp1,OUTPUT);
  pinMode(lamp2,OUTPUT);
  pinMode(led,OUTPUT); 
}

void loop() {
      myLCD.setCursor(1,0);
      myLCD.println("WelcomeToLampNight");
  if(Serial.available()!=0){
  input = Serial.readString();
  if(input=="L"){
    if(lamp1state) {
      Serial.println("Lamp 1 is ON");
      myLCD.setCursor(3,1);
      myLCD.println("Lamp 1 is ON");
      }
    else {
      Serial.println("Lamp 1 is OFF");
      myLCD.setCursor(3,1);
      myLCD.println("Lamp 1 is OFF");
      }
    digitalWrite(lamp1,lamp1state);
    lamp1state=!lamp1state;
    }
  else if(input=="LL"){
    if(lamp2state) {
      Serial.println("Lamp 2 is ON");
      myLCD.setCursor(3,2);
      myLCD.println("Lamp 2 is ON");
      }
    else {
      Serial.println("Lamp 2 is OFF");
      myLCD.setCursor(3,2);
      myLCD.println("Lamp 2 is OFF");
      }
    digitalWrite(lamp2,lamp2state);
    lamp2state=!lamp2state;
    }
  else{
    Serial.println("Invalid Input");
      }
    }
else {Serial.println("No Input");
      delay(2000);
}
      myLCD.setCursor(3,3);
      String msg = "PSTUCSE JITU";
      for(int i=0;i<msg.length();i++){
      myLCD.print(msg[i]);
      delay(60);
      }
  }
