//int motorA_ENA = 6; //~PWM
int motorA_IN1 = 7;
int motorA_IN2 = 8;

//int carSpeed    = 10;
//char drive;


void setup() {
  Serial.begin(9600);
  //pinMode(motorA_ENA,OUTPUT);
  pinMode(motorA_IN1,OUTPUT);
  pinMode(motorA_IN2,OUTPUT);
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

    //Speed control of motorA  
    //analogWrite(motorA_ENA,HIGH);


      goForward();
     


}

void goForward(){
  Serial.println("Moving Forward!!");
  digitalWrite(motorA_IN1,HIGH);
  digitalWrite(motorA_IN2,LOW);
  }
