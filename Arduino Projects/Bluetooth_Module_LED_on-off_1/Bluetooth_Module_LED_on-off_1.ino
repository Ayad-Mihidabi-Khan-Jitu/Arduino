int ledBlue = 12;
char led = '\0';
int rstate = 0;
int bstate = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledBlue,OUTPUT);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(micros());
  //Serial.println("-----------------------------------------------");
  //Serial.println("red on=>ON      | red off=>OFF ");
  //Serial.println("| blue on=>ON  | blue off=>OFF");
  //Serial.println("-----------------------------------------------");
  //delay(7000);
  if(Serial.available()!=0){
    led=Serial.read();
    delay(500);
    Serial.println(led);

    if(led=='b'){
      Serial.println("HO dhukse");
      if(bstate) {
        //Serial.println("Already ON!!");
        }
      else{
      digitalWrite(ledBlue,HIGH);
      //Serial.println("Blue LED Turned ON!!");
      bstate=1;
      }
    }
    else if(led=='o'){
      if(bstate){
      digitalWrite(ledBlue,LOW);
      //Serial.println("Blue LED Turned OFF!!");
      bstate = 0;
      }
     else{
       //Serial.println("Sorry it is OFF");
       
     }
      }
    
      }
  }
