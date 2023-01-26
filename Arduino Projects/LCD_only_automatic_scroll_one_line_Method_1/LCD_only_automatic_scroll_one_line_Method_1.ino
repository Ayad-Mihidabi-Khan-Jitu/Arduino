#include <LiquidCrystal.h> // include the library

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // define the arduino pins
              //rs, en, d4, d5, d6, d7 lcd pins

// Define 20x4 LCD
int screenWidth = 20;
int screenHeight = 4;

String LargeText = " Computer Science and Technology ";
String SmallText = "PSTU";

int LenthOfLtext = LargeText.length(); 

void setup() {
  // put your setup code here, to run once:
  lcd.begin(20,4);
  lcd.setCursor(5,0); lcd.print(SmallText); 
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,1); //PrintLargeText(LargeText);
  for(int i=0; i<=19; i++){
    lcd.print(LargeText[i]);
    }
    lcd.setCursor(0,1);
    delay(200);
    int swap = LargeText[19];
    for(int i=19; i>0; i--){
    LargeText[i] = LargeText[i-1];
    }
    LargeText[0] = swap;
}

void PrintLargeText( String Ltext ){
  for(int i=0; i<=LenthOfLtext-1; i++){
    lcd.print(Ltext[i]);
    }
    lcd.setCursor(0,1);
    delay(100);
    int swap = Ltext[LenthOfLtext-1];
    for(int i=LenthOfLtext-1; i>0; i--){
    Ltext[i] = Ltext[i-1];
    }
    Ltext[0] = swap;  
  }
