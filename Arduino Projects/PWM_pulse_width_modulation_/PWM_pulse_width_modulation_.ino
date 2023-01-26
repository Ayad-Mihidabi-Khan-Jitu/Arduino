/*
# "~" signed pins are PWM digital pin 
# ara digital INPUT/OUTPUT pin holew 0-255 man er analog value dewa jay
# onekta analog er moto kaj kore
*/


int PWMled1 = 10;
int PWMled2 = 11;
int i; 
int brightness = 0,fadeness=1;

void setup() {
    pinMode(PWMled1,OUTPUT);
    pinMode(PWMled2,OUTPUT);
}

void loop() {
  int fadeonoff=0;
 
  //Method 1
  //--------
  for(i=0;i<=255;i++){
    analogWrite(PWMled1,i);
    delay(1);
  }
  for(i=255;i>=0;i--){
    analogWrite(PWMled1,i);
    delay(1);
  }
  digitalWrite(PWMled1,LOW);
  delay(3000);

   //Method 2
   //--------
   /*
   while(fadeonoff<513){
   analogWrite(PWMled2,brightness);
   delay(1);
   brightness = brightness + fadeness;
   if(brightness==0||brightness==255){
    fadeness = -fadeness;
    }
     fadeonoff++;
   }
   digitalWrite(PWMled2,LOW);
   */
}
