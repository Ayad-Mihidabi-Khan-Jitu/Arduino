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
int Pin[13]={0,1,2,3,4,5,6,7,8,9,10,11,12};



void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<13;i++){
    pinMode(Pin[i],OUTPUT);
    if(i>6){
       digitalWrite(Pin[i],HIGH);
      }
    }
    
  }

  int mi = 0,hr = 0;
  
void loop() {
  // put your main code here, to run repeatedly:
     
    for(int t=1;t<=60;t++){
      for(int eye=1;eye<=20;eye++){
     //delay(1000);
      int myTime = t;
      //if(mi>60 || hr > 60) {mi = 0; hr =0;}
      //else {mi = mi+mi/60; hr = hr + hr/3600; }
     digitalWrite(Pin[11],LOW);
     //digitalWrite(Pin[9],LOW);
     //digitalWrite(Pin[7],LOW);
     for(int i=0;i<7;i++){
        digitalWrite(i,digit[myTime/10][i]);
        //digitalWrite(i,digit[mi/10][i]);
        //digitalWrite(i,digit[hr/10][i]);
     }delay(20);
     digitalWrite(Pin[11],HIGH); 
     //digitalWrite(Pin[9],HIGH);
     //digitalWrite(Pin[7],HIGH);  
     
     digitalWrite(Pin[12],LOW);
     //digitalWrite(Pin[10],LOW);
     //digitalWrite(Pin[8],LOW);
     for(int i=0;i<7;i++){
        digitalWrite(i,digit[myTime%10][i]);
        //digitalWrite(i,digit[mi%10][i]);
        //digitalWrite(i,digit[hr%10][i]);
     }delay(20);
     digitalWrite(Pin[12],HIGH);
     //digitalWrite(Pin[10],HIGH);
     //digitalWrite(Pin[8],HIGH);
      
      }
      
     }//delay(1000);

     
  }  
