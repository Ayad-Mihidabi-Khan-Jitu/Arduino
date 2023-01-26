int ledRed = 11;
int ledBlue = 12;
String led = "";
//char led = '\0';
int rstate = 0;
int bstate = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledRed,OUTPUT);
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
    led=Serial.readString();
    //led="blue on";
    //led=Serial.read();
    delay(500);
    Serial.println(led);
    
    if(led=="red on" || rstate>0){
     // if(rstate) Serial.println("Already ON!!");
      //else{
      //digitalWrite(ledRed,HIGH);
      rstate=1;
      for(int i=1;i<=255;i+=4) {
      analogWrite(ledRed,i);
      delay(10);
      }
      for(int i=255;i>=1;i-=4) {
      analogWrite(ledRed,i);
      delay(10);
      }
  
      
      //Serial.println("Red LED Turned ON!!");

      //}
    }
     if(led=="red off"){
      if(rstate){
      digitalWrite(ledRed,LOW);
      //Serial.println("Red LED Turned OFF!!");
      rstate = 0;
      }
      else{
       //Serial.println("Sorry it is OFF");
       
      }
    }
    if(led=="blue on"){
      //Serial.println("HO dhukse");
      if(bstate) {
        //Serial.println("Already ON!!");
        }
      else{
      digitalWrite(ledBlue,HIGH);
      //Serial.println("Blue LED Turned ON!!");
      bstate=1;
      }
    }
    else if(led=="blue off"){
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
