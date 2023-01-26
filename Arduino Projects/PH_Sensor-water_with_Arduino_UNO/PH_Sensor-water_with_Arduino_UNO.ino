#define SensorPin A0          //pH meter Analog output to Arduino Analog Input 0
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10],temp;
 
// for float value to string converstion
  int f;
  float val; // also works with double. 
  char buff2[10];
  String valueString = "";
  String Value = ""; 
  
void setup()
{
  pinMode(A0,INPUT);  
  Serial.begin(9600);  
  //Serial.begin(115200);  
}
void loop()
{
  
  ///Method-1
  int measuringVal = analogRead(A0);
  Serial.print("Measuring Raw Value: ");
  Serial.println(measuringVal);

  double vltValue = 5/1024.0 * measuringVal;
  Serial.print("Voltage Value: ");
  Serial.println(vltValue, 3);

  float P0 = 7 + ((2.5 - vltValue) / 0.18);
  Serial.print("");
  Serial.print("pH Value : ");
  Serial.println(P0, 3);
  delay(2000);
  

  /*
  ///Method-2
  for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=3.5*phValue;                      //convert the millivolt into pH value
  Serial.println(phValue);
  Value =  dtostrf(phValue, 4, 2, buff2);  //4 is mininum width, 6 is precision
  valueString = valueString + Value +","; 
  //Serial.println(valueString);
  valueString = "";
  delay(2000);
  */
 
}


/*
      Meterial            PH
 ------------------------------
   Vim+Bliching+Wheel   ~11.54
   Bliching Power       ~10.21
   Wheel Power           ~9.31
   Vim                   ~8.60
   Pure Water            ~7.00
   Milk                  ~6.32
   Hexisol               ~5.18
   Lemon                 ~2.21
   Harpic                ~0.21
   
   
   
*/
