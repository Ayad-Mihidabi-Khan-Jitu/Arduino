int ledRed = 13;
int ledBlue = 12;
int ledGreen = 11;
String led;
int rstate = 0;
int gstate = 0;
int bstate = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledRed,OUTPUT);
  pinMode(ledBlue,OUTPUT);
  pinMode(ledGreen,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("-----------------------------------------------");
  Serial.println("red on=>ON      | red off=>OFF | green on=>ON ");
  Serial.println("green off=> OFF | blue on=>ON  | blue off=>OFF");
  Serial.println("-----------------------------------------------");
  delay(7000);
  if(Serial.available()!=0){
    led=Serial.readString();
    Serial.println();
    if(led=="red on"){
      if(rstate) Serial.println("Already ON!!");
      else{
      digitalWrite(ledRed,HIGH);
      Serial.println("Red LED Turned ON!!");
       rstate=1;
      }
    }
    else if(led=="red off"){
      if(rstate){
      digitalWrite(ledRed,LOW);
      Serial.println("Red LED Turned OFF!!");
      rstate = 0;
      }
      else{
       Serial.println("Sorry it is OFF");
       
      }
    }
    if(led=="blue on"){
      if(bstate) Serial.println("Already ON!!");
      else{
      digitalWrite(ledBlue,HIGH);
      Serial.println("Blue LED Turned ON!!");
      bstate=1;
      }
    }
    else if(led=="blue off"){
      if(bstate){
      digitalWrite(ledBlue,LOW);
      Serial.println("Blue LED Turned OFF!!");
      bstate = 0;
      }
     else{
       Serial.println("Sorry it is OFF");
       
     }
      }
    if(led=="green on"){
      if(gstate) Serial.println("Already ON!!");
      else{
      digitalWrite(ledGreen,HIGH);
      Serial.println("Green LED Turned ON!!");
       gstate = 1;
      }
    }
    else if(led=="green off"){
      if(gstate){
      digitalWrite(ledGreen,LOW);
      Serial.println("Green LED Turned OFF!!");
      gstate = 0;
      }
      else{
       Serial.println("Sorry it is OFF");
        
      }
      }
  }
}
