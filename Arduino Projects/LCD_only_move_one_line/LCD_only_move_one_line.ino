
#include <LiquidCrystal.h> // include the library

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // define the arduino pins
              //rs, en, d4, d5, d6, d7 lcd pins

// Define 20x4 LCD
int screenWidth = 20;
int screenHeight = 4;

// To move ONLY one line needs to move one character at a time

// Define two line

String line1 = " LCD ep3: "; // stationary 
String line2 = " This is a one line scrolling tutorial! "; // scroll this line

int stringStart, stringEnd = 0;
int scrollCursor = screenWidth; 

void setup() {
  lcd.begin(screenWidth, screenHeight);
}

void loop() {

  lcd.setCursor(0, 0); // Seting the cursor on first row 
  lcd.print(line1); // To print line1 message
  lcd.setCursor(0, 1); // Seting the cursor on first row and (scrolling from left end to right)
  lcd.print(line2.substring(stringStart,stringEnd)); // To print line1 first character "T"

  delay(500);
  
  //lcd.clear(); // clear message
  
  if(stringStart == 0 && scrollCursor > 0){
    scrollCursor--; // Moving cursor from 20 to 0
    stringEnd++; // Character T, H, I, S ...
                 // it will print out character from 0 to 23 the whole length of the screen
  }
  else if (stringStart == stringEnd){ // start all over again
    stringStart = stringEnd = 0;
    scrollCursor = screenWidth;
  } 
  else if (stringEnd == line1.length() && scrollCursor == 0) { // if reach to the end character
    stringStart++;
  } 
  else { // it will print out character from (1 to 16) to end character (this case it's !))
    stringStart++;
    stringEnd++;
  }
}
