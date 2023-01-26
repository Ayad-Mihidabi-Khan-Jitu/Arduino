char readData;
int LedOutput = 13; 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LedOutput,OUTPUT);
}

void loop() {
  //Serial.print(13); // ESC
  //clearAndHome();
  // put your main code here, to run repeatedly:
  readData = Serial.read();
  if(readData == 'O'){

    digitalWrite(LedOutput,HIGH);
    
    //Serial.write("LED ON");
    Serial.println("LED ON");
  }
  else if(readData == 'F'){
    //clearAndHome();
    //Serial.flush();
    //Serial.write(0x0C);
    //Serial.clear();
    digitalWrite(LedOutput,LOW);
    //Serial.write("LED OFF");
    Serial.println("LED OFF");
  }

}

void clearAndHome()
{
Serial.print(27); // ESC
Serial.print("[2J"); // clear screen
Serial.print(27); // ESC
Serial.print("[H"); // cursor to home
}
