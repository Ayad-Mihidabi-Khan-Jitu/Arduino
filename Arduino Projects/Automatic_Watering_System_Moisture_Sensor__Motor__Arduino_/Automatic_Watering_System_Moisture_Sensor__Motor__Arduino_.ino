///WORKING PRINCIPLE OF SOIL MOISTURE SENSOR///
//1. Working Voltage 5V
//2. Voltage increases according to dryness of the soil
//   The MORE DRY the MORE VOLTAGE supply
//3. Sensor value according to the voltage:
//   (0V-5V)
//   (0-1023) 

///PLAN OF THE PROJECT///
//1. We will map the range of sensor value to (0-100) mois%
//2. When moisture is below 20% we will water the Soil
// Syntex of map funciton: map(value, fromLow, fromHigh, toLow, toHigh)

#include<LiquidCrystal.h>

LiquidCrystal lcd(13,12,11,10,9,8);
int SensorValue; // variabe for storing sensor's value
int mois;        // variabe for storing moisture value in %
int inputPin = A0; // arduino pin number A0 storing as inputPin
int outputPin = 7; // arduino pin number 7 storing as outputPin
int iCursor = 0;//the column number of the cursor where large text will be started

void setup() {
  Serial.begin(9600);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4); //Taking 20 columns and 4 rows for the display
  
  // Print messages which will be permanent to the LCD.
  //A large text is here from col-0,row-0 which is situated in the loop section
  lcd.setCursor(7,1); lcd.print("- BY PSTU CSE"); // this text will be started from col-7,row-1
  lcd.setCursor(2,2); lcd.print("MOISTURE : ");   // this text will be started from col-2,row-2
  lcd.setCursor(18,2); lcd.print("%");            // this text will be started from col-18,row-2
  
  pinMode(inputPin,INPUT);  //declareing the input inputPin as input
  pinMode(outputPin,OUTPUT);//declareing the input outputPin as output
}

void loop() {

  //LargeTextScroll("TEXT", LineNumber);
  LargeTextScroll("AUTOMATIC WATERING SYSTEM  ", 0);
  
  SensorValue = analogRead(inputPin);//Reading moisture sensor value (range 0-1023)
  mois = map(SensorValue, 0, 1023, 0, 100); //Mapping the range 0-1023 to 0-100
  
  Serial.print("MOISTURE : "); Serial.print(mois); Serial.println("%"); 

  lcd.setCursor(14,2); lcd.print(mois); // this text will be started from col-14,row-2 just after the "MOISTURE" text
  
  if(mois<30){ //below 30 means it is dry
    Serial.println("IT IS DRY");
    
    lcd.setCursor(5,3); lcd.print("IT IS DRY  ");
    
    digitalWrite(outputPin,HIGH);
  }
  else{ //above 30 means it is wet
    Serial.println("IT IS HUMID");
    
    lcd.setCursor(5,3); lcd.print("IT IS HUMID");
    
    digitalWrite(outputPin,LOW);
    }
  delay(1000);
  
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
