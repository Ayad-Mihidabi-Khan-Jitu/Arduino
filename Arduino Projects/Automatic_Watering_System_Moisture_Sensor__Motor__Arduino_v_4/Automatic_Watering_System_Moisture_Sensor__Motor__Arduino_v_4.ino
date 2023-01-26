///IN THIS PROJECT WE WILL USE 
//1. SOIL MOISTURE SENSOR
//2. PUMP MOTOR
//3. 20*4 DISPLAY
//#Wiring
//VCC -> 5v DC
//GND -> GND
//SDA (Signal Data) -> A4
//SCL (Signal Clock) -> A5

///WORKING PRINCIPLE OF SOIL MOISTURE SENSOR///
//i.  Working Voltage 5V
//ii. Voltage increases according to dryness of the soil
//    The MORE DRY the MORE VOLTAGE supply
//iii. Sensor value according to the voltage:
//     (0V-5V)
//     (0-1023) 



///PLAN OF THE PROJECT///
//1. We will take the INPUT as SOIL MOISTURE SENSOR  
//   We will map the range of sensor value to (0-100) mois%
//   Syntex of map funciton: map(value, fromLow, fromHigh, toLow, toHigh)
//2. When moisture is below 20% we will start watering the soil gradually
//   for this we have to control the PUMP MOTOR according to the moisture value 


//#include<LiquidCrystal.h>
//LiquidCrystal lcd(13,12,11,10,9,8);
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);
int SensorValue; // variabe for storing sensor's value
int mois;        // variabe for storing moisture value in %
int sensorOutputPWM;
int inputPinSoil = A0; // arduino pin number A0 storing as inputPin 
int echoPin = 2; // attach pin D2 Arduino to pin Echo of HC-SR04
int trigPin = 3; //attach pin D3 Arduino to pin Trig of HC-SR04
int DISTANCE = 0;

int relayIn = 4;
int ledlowPin = 5;
int ledmidPin = 6;
int ledfullPin = 7;


int iCursor = 0;//the column number of the cursor where large text will be started

void setup() {
  Serial.begin(9600);
  
  // set up the LCD's number of columns and rows:
  //lcd.begin(20, 4); //Taking 20 columns and 4 rows for the display
  //lcd.init();
  lcd.begin();
  // Print messages which will be permanent to the LCD.
  //A large text is here from col-0,row-0 which is situated in the loop section
  lcd.setCursor(1,1); lcd.print("Automatic Irrigation"); // this text will be started from col-7,row-1
  lcd.setCursor(2,2); lcd.print("MOISTURE : ");   // this text will be started from col-2,row-2
  lcd.setCursor(18,2); lcd.print("%");            // this text will be started from col-18,row-2
  
  pinMode(inputPinSoil,INPUT);  //declareing the input inputPin as input
  pinMode(relayIn,OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(ledlowPin, OUTPUT);
  pinMode(ledmidPin, OUTPUT);
  pinMode(ledfullPin, OUTPUT);

}

void loop() {

   //Serial.print("Distance: ");
   //Serial.println(" cm");
   DISTANCE = distance();

  //LargeTextScroll("TEXT", LineNumber);
  LargeTextScroll("AUTOMATIC WATERING SYSTEM  ", 0);
  
  SensorValue = analogRead(inputPinSoil);//Reading moisture sensor value (range 0-1023)
  //Serial.print("SensorValue : "); Serial.print(SensorValue);
  mois = map(SensorValue, 0, 1023, 100, 0); //Mapping the range 0-1023 to 0-100

  sensorOutputPWM = map(SensorValue, 0, 1023, 0, 255); //Mapping the range 0-1023 to 0-255
  //sensorOutputPWM = map(SensorValue, 0, 1023, 255, 0); //Mapping the range 0-1023 to 0-255
  
  
  Serial.print("MOISTURE : "); Serial.print(mois); Serial.println("%"); 

  lcd.setCursor(14,2); lcd.print(mois); // this text will be started from col-14,row-2 just after the "MOISTURE" text
  
  if(mois<30){ //below 30 means it is dry
    //Serial.println("IT IS DRY");
    
    lcd.setCursor(5,3); lcd.print("IT IS DRY  ");
    digitalWrite(relayIn, HIGH);

  }
  else{ //above 30 means it is wet
    //Serial.println("IT IS HUMID");
    
    lcd.setCursor(5,3); lcd.print("IT IS HUMID");
    digitalWrite(relayIn, LOW);
  }

   if(DISTANCE <=5){
      Serial.println(" fullllllllllllllll");
      Serial.print(DISTANCE);
      LEDs(0, 0, 1);
   }
   else if(DISTANCE >=7 && DISTANCE <= 14){
       Serial.println(" Middddddddd");
       Serial.print(DISTANCE);
       LEDs(0, 1, 0);
   }
   else{
     Serial.println("LOWWWWWW");
     Serial.print(DISTANCE);
     LEDs(1, 0, 0);
   }
    
  delay(1000);
  //lcd.clear();
  
}

//this function is used for large text
//this function takes the parameter "Text" and iLineNumber
void LargeTextScroll(char * largeText, int iLineNumber){
  int iLenthOfLargeText = strlen(largeText); //calculate the length of string
  if(iCursor == iLenthOfLargeText-1){ //Reset variable for rollover effct
    
    iCursor = 0;
    }
    
    lcd.setCursor(0,iLineNumber);
    if(iCursor<iLenthOfLargeText-20){//this loop excute for normal 24 character
      for(int iChar = iCursor; iChar < iCursor+20; iChar++){
        lcd.print(largeText[iChar]);//print a message to the LCD
        }
        
      }
      
     else{
      
      for(int iChar = iCursor; iChar < (iLenthOfLargeText-1); iChar++){
        //This code takes care of printing characters fo current string
        lcd.print(largeText[iChar]);//print a message to the LCD
        }
       for(int iChar = 0; iChar <= 20-(iLenthOfLargeText-iCursor); iChar++) {
        //This code takes care of printing characters fo current string
        lcd.print(largeText[iChar]);//print a message to the LCD
        }
  
      }
      iCursor++;
  }

  int distance (){
     // Clears the trigPin condition
  int duration,distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  //delay(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  //Serial.print("Distance: ");
  //Serial.print(distance);
  //Serial.println(" cm");
  //delay(1000);
  //Serial.println(distance);
  return distance;
    }

    void LEDs(int l, int m, int f){
    digitalWrite(ledlowPin, l);
    digitalWrite(ledmidPin, m);
    digitalWrite(ledfullPin, f);
      }
