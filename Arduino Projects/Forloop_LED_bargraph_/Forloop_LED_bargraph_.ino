int ledout;
int swtch = 12;

void setup() {
  // put your setup code here, to run once:
    //pinMode(swtch,INPUT);
  for(ledout=0;ledout<=9;ledout++){
    pinMode(ledout,OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(swtch)){
  for(ledout=0;ledout<=9;ledout++){
    digitalWrite(ledout,HIGH);
    delay(150);
    digitalWrite(ledout,LOW);
    delay(150);
  }
}
}
