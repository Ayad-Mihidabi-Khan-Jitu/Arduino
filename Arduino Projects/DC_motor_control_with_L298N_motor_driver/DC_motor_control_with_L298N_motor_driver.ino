int motorA_ENA = 3; //~PWM
int motorA_IN1 = 4;
int motorA_IN2 = 5;

int motorB_ENB = 6; //~PWM
int motorB_IN3 = 7;
int motorB_IN4 = 8;

int forwardLED  = 9;
int rightLED    = 10;
int leftLED     = 11;
int backwardLED = 12;
int carSpeed    = 10;
char drive;


void setup() {
  Serial.begin(9600);
  pinMode(motorA_ENA,OUTPUT);
  pinMode(motorA_IN1,OUTPUT);
  pinMode(motorA_IN2,OUTPUT);
  pinMode(motorB_ENB,OUTPUT);
  pinMode(motorB_IN3,OUTPUT);
  pinMode(motorB_IN4,OUTPUT);
  
  pinMode(forwardLED,OUTPUT);
  pinMode(rightLED,OUTPUT);
  pinMode(leftLED,OUTPUT);
  pinMode(backwardLED,OUTPUT); 
}

/*
    EN    IN1   IN2      OUTPUT
    ---------------     --------
    1     0      0         0
          1      1         0
          1      0      clockwise
          0      1      anti-clockwise
#if and only if EN is 1 then IN1 IN2 can be operated 
#that is if i want to switch off a motor simply make IN1 IN2 both (0 or 1) OTHOBA EN -> 0 
*/

void loop() {
  
  if(Serial.available()!=0){
    drive = Serial.read();
      (drive=='1') ? carSpeed = 50,Serial.println("Slower"):0;
      (drive=='2') ? carSpeed = 100,Serial.println("Slow"):0;
      (drive=='3') ? carSpeed = 150,Serial.println("Fast"):0;
      (drive=='4') ? carSpeed = 200,Serial.println("Faster"):0;
      (drive=='5') ? carSpeed = 255,Serial.println("Fastest"):0;
      (drive=='0') ? carSpeed = 0,Serial.println("Car Stoped!!!!"):0;

    //Speed control of motorA  
    analogWrite(motorA_ENA,carSpeed);

    //Speed control of motor
    analogWrite(motorB_ENB,carSpeed);
    
    if(drive == 'i'){
      goForward();
      headLight(); 
      }
      
    if(drive == 'l'){
       goRight(); 
       rightIndicator(); 
      }
      
    if(drive == 'j'){    
       goLeft(); 
       leftIndicator(); 
      } 
      
    if(drive == 'k'){
       goBackward(); 
       backLight(); 
      }
    if(drive!='k'&&drive!='l'&&drive!='j'&&drive!='i'&&
       drive!='0'&&drive!='1'&&drive!='2'&&drive!='3'&&
       drive!='4'&&drive!='5')
        {
         Serial.println("Press i => move forward");
         Serial.println("Press k => move backward");
         Serial.println("Press l => move right");
         Serial.println("Press i => move left");
         delay(1000);
        }
      
    }
    
   else{
        Serial.println("HOLD ON CONTROL!!!");    
      } 

}

void goForward(){
  Serial.println("Moving Forward!!");
  digitalWrite(motorA_IN1,HIGH);
  digitalWrite(motorA_IN2,LOW);
  digitalWrite(motorB_IN3,HIGH);
  digitalWrite(motorB_IN4,LOW); 
  }
  void goRight(){
  Serial.println("Moving Right!!");
  digitalWrite(motorA_IN1,HIGH);
  digitalWrite(motorA_IN2,LOW);
  digitalWrite(motorB_IN3,LOW);
  digitalWrite(motorB_IN4,LOW);
  }
  void goLeft(){
  Serial.println("Moving Left!!");
  digitalWrite(motorA_IN1,LOW);
  digitalWrite(motorA_IN2,LOW);
  digitalWrite(motorB_IN3,HIGH);
  digitalWrite(motorB_IN4,LOW); 
  }
  void goBackward(){
  Serial.println("Moving Back!!");
  digitalWrite(motorA_IN1,LOW);
  digitalWrite(motorA_IN2,HIGH);
  digitalWrite(motorB_IN3,LOW);
  digitalWrite(motorB_IN4,HIGH); 
  }
  void headLight(){
      digitalWrite(forwardLED,HIGH);
      delay(25);
      digitalWrite(forwardLED,LOW);
      delay(25);}
  void rightIndicator(){
       digitalWrite(rightLED,HIGH);
       delay(25);
       digitalWrite(rightLED,LOW);
       delay(25);}
 void leftIndicator(){
       digitalWrite(leftLED,HIGH);
       delay(25);
       digitalWrite(leftLED,LOW);
       delay(25);}
 void backLight(){
       digitalWrite(backwardLED,HIGH);
       delay(25);
       digitalWrite(backwardLED,LOW);
       delay(25);}
