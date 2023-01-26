#include<LiquidCrystal.h>
int RS=10, EN=9, D4=8, D5=7, D6=6, D7=5;
int tsensor = A0;
LiquidCrystal myLCD(RS,EN,D4,D5,D6,D7);

char line0[21]; 
//char line1[21]="X";
void updateDisplay() {
   myLCD.setCursor(0,1);
   myLCD.print(line0);
   //myLCD.print(line1);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myLCD.begin(24,4);
  myLCD.setCursor(1,0);
  pinMode(tsensor,INPUT);
}

double sensorValue,temp,mvolt;
void loop() {
   myLCD.print("Digital Tharmometer"); 
   updateDisplay();
  // put your main code here, to run repeatedly:
  sensorValue=analogRead(tsensor);// => 409=analogRead(2000mvolt)
  mvolt=(sensorValue*5000)/1024;  // 1. 10 milivolts = 1'C
  temp=mvolt/10;                  // 2. 5000 milivolts = 1024 bits
                                  // sensor ti milivolts pathay
                                  // arduino seta No.2 unujaye bits e convert kore 
  // ata virtual monitor e dekhabe
  /*
  Serial.print("Sensor value = ");
  Serial.print(tsensor);
  Serial.println(" milivolts");
  Serial.print("Converted Sensor value = ");
  Serial.print(sensorValue);
  Serial.println(" bits");
  Serial.print("Tempature = ");
  Serial.print(temp);
  Serial.print(" ");
  Serial.print(char(39));
  Serial.println(" C");
  Serial.println();
  delay(2000);
*/
  // ata LCD te dekhabe
    myLCD.print("Tempature=");
    myLCD.print(temp);
    myLCD.print(" ");
    myLCD.print("'");
    myLCD.print(" C");
    //delay(1000);
    //myLCD.clear();
    myLCD.setCursor(0,2);
    myLCD.write("Happy Coding");
    myLCD.setCursor(-2,3);
    String msg = "PSTU   CSE   CLUB";
    for(int i=0;i<17;i++){
      myLCD.print(msg[i]);
      delay(50);
      }
      delay(500);
    myLCD.clear();
}
