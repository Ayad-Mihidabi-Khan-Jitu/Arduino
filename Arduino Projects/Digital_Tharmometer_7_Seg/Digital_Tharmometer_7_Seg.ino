int digit[10][7]={ // a-0 b-1 c-2 d-3 e-4 f-5 g-6
                {1,1,1,1,1,1,0},// 0
                {0,1,1,0,0,0,0},// 1 
                {1,1,0,1,1,0,1},// 2
                {1,1,1,1,0,0,1},// 3
                {0,1,1,0,0,1,1},// 4 a e d 0
                {1,0,1,1,0,1,1},// 5
                {1,0,1,1,1,1,1},// 6
                {1,1,1,0,0,1,0},// 7 d e g 0
                {1,1,1,1,1,1,1},// 8
                {1,1,1,1,0,1,1} // 9
            };
int pin[10]={0,1,2,3,4,5,6,7,8,A5};

void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<10;i++){
    if(i==9){pinMode(pin[i],INPUT);}
    else    {pinMode(pin[i],OUTPUT);}
  }
}

double sensorValue,mvolt;
int temp=0;
void loop() {
  // put your main code here, to run repeatedly:
   sensorValue = analogRead(pin[9]);
   mvolt=(sensorValue*5000)/1024; 
   temp=mvolt/10;

   //for(int eye=1;eye<=20;eye++){
     //delay(1000);   
     digitalWrite(pin[7],LOW);
    
     for(int i=0;i<7;i++){
        digitalWrite(i,digit[temp/10][i]);
       
     }delay(20);
     digitalWrite(pin[7],HIGH); 
    
     
     digitalWrite(pin[8],LOW);
     
     for(int i=0;i<7;i++){
        digitalWrite(i,digit[temp%10][i]);
       
     }delay(20);
     digitalWrite(pin[8],HIGH);
    
      
     // }
      
     }
