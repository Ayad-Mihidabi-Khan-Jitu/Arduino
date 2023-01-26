#include<LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int LED = 8;
int SignalPin = A0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SignalPin,INPUT);
  pinMode(LED,OUTPUT);
  lcd.begin(16,2);
  lcd.cursor();
  lcd.setCursor(0,0);
  lcd.print("Cell Detector");
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(SignalPin);
  Serial.println(value);
  if(value>500){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cell Detect");
    digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED,LOW);
    delay(500);
    digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED,LOW);
    
    //delay(2000);
    lcd.clear();
    lcd.print("jitu");
    }
}
