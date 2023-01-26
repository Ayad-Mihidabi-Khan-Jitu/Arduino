int pir = 3;
int led = 2;
int state;


void setup() {
  Serial.begin(9600);
 pinMode(pir,INPUT);
 pinMode(led,OUTPUT);
}

void loop() {
  state =  digitalRead(pir);
  digitalWrite(led,state);
  //delay(1000);
  if(state)
  Serial.print("Motion Detected \n");
  else
   Serial.print("No Motion \n");

}
