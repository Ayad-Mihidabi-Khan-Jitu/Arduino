
#include <LiquidCrystal.h> // include the library

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // define the arduino pins
              //rs, en, d4, d5, d6, d7 lcd pins

// Define 20x4 LCD
int screenWidth = 20;
int screenHeight = 4;

// To move ONLY one line needs to move one character at a time

char * largeText = "Automatic Scrolling A Line  ";

int iLineNumber = 1; //Line number to show your staring
int iCursor = 0;


void setup() {
  lcd.begin(screenWidth, screenHeight);
  lcd.setCursor(7,0); lcd.print("Welcome");
}

void loop() 
{
  UpdateLCDDisplay();
  delay(500);
}

void UpdateLCDDisplay(){
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
