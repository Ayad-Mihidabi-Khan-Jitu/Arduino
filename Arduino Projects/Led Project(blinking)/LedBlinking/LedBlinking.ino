int led_Pin_Out_13=13;
int vol_Pin_input_3=3;
int Input;
void setup() {
  Serial.begin(9600);
   pinMode(led_Pin_Out_13,OUTPUT);
   pinMode(vol_Pin_input_3,INPUT);

}

void loop() {
  Input=digitalRead(vol_Pin_input_3);
  digitalWrite(led_Pin_Out_13,Input);
  if(Input){
  Serial.print("Light is on!!\n");
  digitalWrite(led_Pin_Out_13,HIGH);
  delay(500);

  Serial.print("Light is off!!\n");
  digitalWrite(led_Pin_Out_13,LOW);
  delay(1000);
  }
  

}
