#include<LiquidCrystal.h>
int pin = 9;
int RS = 13,EN = 12,D4 = 6,D5 = 5,D6 = 4,D7 = 3;

LiquidCrystal myLCD(RS,EN,D4,D5,D6,D7);
void setup() {
  //put your setup code here, to run once:
    myLCD.begin(16,2);//begin(column,row)
    pinMode(pin,OUTPUT);
    myLCD.cursor();
    
}


int thisChar = 'a';
void loop() {

  /*
   //likha likhe dan e jabe then abar bam e over hobe
   //reverse directions at 'o':
  if (thisChar == 'o') {
   //go right for the next letter
    myLCD.rightToLeft();
  }
  //reverse again at 'w':
  if (thisChar == 'w') {
    // go left for the next letter
    myLCD.leftToRight();
  }
  // reset at 'z':
  if (thisChar > 'z') {
    // go to (0,0):
    myLCD.clear();
    myLCD.home();
    // start again at 0
    thisChar = 'a';
  }
  // print the character
  myLCD.write(thisChar);
  // wait a second:
  delay(250);
  // increment the letter:
  thisChar++;
*/






  
  // put your main code here, to run repeatedly:
 
   myLCD.noBlink(); // Turn off the blinking cursor:
  delay(1000);
  
  myLCD.blink();// Turn on the blinking cursor:
  delay(1000);

  
  myLCD.noCursor();// Turn off the cursor:
  delay(500);
  
  myLCD.cursor();// Turn on the cursor:
  delay(500);
 
  myLCD.noDisplay(); // Turn off the display:
  delay(500);
  
  myLCD.display();// Turn on the display:
  delay(500);
 

 
  myLCD.setCursor(3,0);// setCursor(column,row)
  myLCD.noAutoscroll();
  ///myLCD.print("Hello There"); nicher string ta 100ms delay kore print korbe
  String hw="Hello There";
  for(int s=0;s<12;s++){
    myLCD.print(hw[s]);
    delay(100);
    }

    
    for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position left:
    myLCD.scrollDisplayLeft();
    // wait a bit:
    delay(150);
  }

  for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position left:
    myLCD.scrollDisplayRight();
    // wait a bit:
    delay(150);
  }

  

  
  myLCD.setCursor(16,1);
  myLCD.autoscroll(); // 16,1 mane akdom last box theke scroll hobe
  //myLCD.print("Project No. 1 2 3 4 5"); // nicher string ta 200ms delay kore print korbe
  String pw="Project No.";
  for(int s=0;s<13;s++){
    myLCD.print(pw[s]);
    delay(200);
    }
    
  for(int j=1;j<10;j++){
    myLCD.print(j);
    delay(400);
    }
  for(int j=1;j<6;j++){ 
    myLCD.print(" ");
    delay(400);
  }
  
  for(int i=0;i<=255;i+=10){ // ata disilam mutolo pwm er jonno mane displayr brightness jate ektu ektu kore bare 
  analogWrite(pin,i);         // but simulator e kaj kore na
    delay(100);
  }
  for(int i=255;i<0;i-=10){  // ata disilam mutolo pwm er jonno mane displayr brightness jate ektu ektu kore kome 
  analogWrite(pin,i);        //// but simulator e kaj kore na
   delay(100);
  }
  delay(1900);
  myLCD.clear();
  delay(500);

}
