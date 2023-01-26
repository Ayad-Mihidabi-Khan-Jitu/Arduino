int led = 3;
int analougeInput = A0;
double voltage=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  
}

void loop() {
  
  // the volts the analog pin, it converts the volts into (0-1024) integer value 
  //   
     voltage=analogRead(analougeInput)*0.0048828125;
     Serial.print(voltage);
     Serial.println(" volts");
     if(voltage > 2.5 )    {    
     digitalWrite(led,HIGH);
     }
     else{
       digitalWrite(led,LOW);
      }
}
