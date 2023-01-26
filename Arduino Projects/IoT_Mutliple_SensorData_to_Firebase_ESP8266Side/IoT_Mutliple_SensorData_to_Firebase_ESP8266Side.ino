#include <Wire.h>
#include <BH1750.h>
//#include <i2cdetect.h>
#include "DHT.h" // Click here to get the library: http://librarymanager/All#DHTesp
#include <SoftwareSerial.h>

#include <ESP8266Firebase.h>
#include <ESP8266WiFi.h>

#define WIFI_SSID "Jitu"                                          
#define WIFI_PASSWORD "jitu1234"
//#define PROJECT_ID "esp-with-multi-sensor"                   
#define PROJECT_ID "esp-with-multi-sensor-default-rtdb"   // Project ID with user name
Firebase firebase(PROJECT_ID);  

String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors

int phVal=0, soilMoisVal=0; // sensors 
// This function sends Arduino's up time every second to Virtual Pin (1).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.

int LT_SDApin = 14; // D5
int LT_SCLpin = 12; // D6
int dhtPin = 15;    // D8 
//int digiPin0 = 16;  // D0
//int digiPin1 = 5;   // D1
float waitedTime = 0;
///ph
//unsigned long int avgValue;  //Store the average value of the sensor feedback
//float b;
//int buf[10],temp;
///ph

DHT dht(dhtPin, DHT22); // temparature sensor
BH1750 lightMeter; //light sensor


void setup() {
  
  //Serial.begin(115200); 
  Serial.begin(9600);                               
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
    waitedTime = waitedTime + 0.5;
    if(waitedTime>60){
     Serial.println("Time out, could connect!");
     break;
     }
  }
  
  if(WiFi.status() == WL_CONNECTED)
  {
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  }
  
  // initialize digital pin LED_BUILTIN as an output.
  //pinMode(LED_BUILTIN, OUTPUT);
  //digitalWrite(LED_BUILTIN, HIGH); 
  //pinMode(analogPin,INPUT);
  
  //Serial.begin(115200);
  //i2cdetect();
  //String thisBoard= ARDUINO_BOARD;
  //Serial.println(thisBoard);

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin(LT_SDApin, LT_SCLpin); //(D5->SDA,D6->SCL) pwm
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);
  // For Wemos / Lolin D1 Mini Pro and the Ambient Light shield use Wire.begin(D2, D1);

  lightMeter.begin();
  dht.begin();

  Serial.println(F("BH1750 Test begin"));
}

// the loop function runs over and over again forever
void loop() {
  if (Serial.available() == 0 ) 
   {
    Serial.println("Serial available = 0");
    delay(2000);
  //Blynk.run();
  //timer.run(); // Initiates BlynkTimer
   }
  if (Serial.available() > 0 ) 
  {
  delay(2000);
  float lux = lightMeter.readLightLevel();
  delay(100);//for temparature
  //firebase.setInt("Light_Intensity",lux);
  
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lux");
  //delay(1000); //for light

  float h = dht.readHumidity();
  //firebase.setInt("Air_Humid",h);
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  //firebase.setInt("Air_Temp",t);
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity of Air: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.println(" *F\t");
  //Serial.print("Heat index: ");
  //Serial.print(hic);
  //Serial.print(" *C ");
  //Serial.print(hif);
  //Serial.println(" *F");

  //if (Serial.available() > 0 ) 
  //{
    rdata = Serial.read(); 
    myString = myString + rdata; 
   // Serial.print(rdata);
    if( rdata == '\n')
    {
      // Serial.println(myString); 
      // Serial.println("fahad");
      // new code
      String sonsorData1 = getValue(myString, ',', 0);
      String sonsorData2 = getValue(myString, ',', 1);
      //String n = getValue(myString, ',', 2); 
      
      phVal = sonsorData1.toInt();
      soilMoisVal = sonsorData2.toInt();
      //thirdVal = n.toInt();
      //Serial.print("Sensor 1: ");
      //Serial.println(phVal);
      //Serial.print("Sensor 2: ");
      //Serial.println(secondVal);

        ///PH///
      //int measuringVal = analogRead(analogPin);
      //int measuringVal = readPH();
      int measuringVal = phVal;
      //Serial.print("Measuring Raw Value: ");
      //Serial.println(measuringVal);
    
      double vltValue = 5/1024.0 * measuringVal;
      //Serial.print("Voltage Value: ");
      //Serial.println(vltValue, 3);
    
      float P0 = 7 + ((2.5 - vltValue) / 0.18);
      //Serial.print("");
      //firebase.setInt("W_pH",P0);
      Serial.print("pH Value : ");
      Serial.println(P0, 3);
    
        ///SoilMoisture///
      float soilMoisture = soilMoisVal;
      int mois = map(soilMoisture, 1023, 0, 0, 100); //Mapping the range 0-1023 to 0-100
      //firebase.setInt("Soil_Mois",mois);
      Serial.print("Soil Moisture : ");
      Serial.print(mois);
      Serial.println(" %");
      
      
      myString = "";
      // end new code
    }
  }


  
  Serial.println("----------------end---------------");
  //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  //delay(100);                      // wait for a second
  //digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  //delay(100);                      // wait for a second
  //delay(1000);
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

  
