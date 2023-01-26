#include<LiquidCrystal.h>

int RS =2, E=3, D4=4, D5=5, D6=6, D7 =7;
int ledPin =9 ;
int IRSensorPin = 11;
int state=0;
LiquidCrystal myLCD(RS,E,D4,D5,D6,D7);

void setup() {
  // put your setup code here, to run once:
 myLCD.begin(24,4);
 myLCD.setCursor(0,0);
 pinMode(IRSensorPin,INPUT);       
}

void loop() {
  myLCD.setCursor(0,0);
  myLCD.println("Welcome to IR Sensor");
  delay(100);
  myLCD.clear();
  delay(100);
  state=digitalRead(IRSensorPin);
  if(state){for(int i=0;i<255;i+=5){analogWrite(ledPin,i);
                                    delay(100);
                                    }
            for(int i=255;i>0;i-=5){analogWrite(ledPin,i); 
                                    delay(100); 
                                    }
  }
  else{digitalWrite(ledPin,LOW);}
 
  
  // put your main code here, to run repeatedly:

}
