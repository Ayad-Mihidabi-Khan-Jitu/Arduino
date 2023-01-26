#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

///F
#include <ESP8266Firebase.h>
#define WIFI_SSID "Nihim"                                          
#define WIFI_PASSWORD "1234567890"
//#define PROJECT_ID "esp-with-multi-sensor"                   
#define PROJECT_ID "esp-with-multi-sensor-default-rtdb"   // Project ID with user name
Firebase firebase(PROJECT_ID);  
///F

String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors

int firstVal, secondVal; // sensors 
// This function sends Arduino's up time every second to Virtual Pin (1).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.

void setup()
{
  // Debug console
  //Serial.begin(9600);
  Serial.begin(115200);

  //timer.setInterval(1000L,sensorvalue1); 
  //timer.setInterval(1000L,sensorvalue2); 

  ///F
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                               
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  ///F

}

void loop()
{
   if (Serial.available() == 0 ) 
   {
  //Blynk.run();
  //timer.run(); // Initiates BlynkTimer
   }
   
  if (Serial.available() > 0 ) 
  {
    rdata = Serial.read(); 
    myString = myString+ rdata; 
   // Serial.print(rdata);
    if( rdata == '\n')
    {
      // Serial.println(myString); 
      // Serial.println("fahad");
      // new code
      String l = getValue(myString, ',', 0);
      String m = getValue(myString, ',', 1);
      //String n = getValue(myString, ',', 2); 
      
      
      firstVal = l.toInt();
      secondVal = m.toInt();
      //thirdVal = n.toInt();
      Serial.print("Sensor 1: ");
      Serial.println(firstVal);
      Serial.print("Sensor 2: ");
      Serial.println(secondVal);

      ///F
      firebase.setInt("Soil_Mois",secondVal);
      firebase.setInt("W_pH",firstVal);
      ///F
      //delay(1000);
      myString = "";
      // end new code
    }
  }

  //Serial.println("--------------");

  

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
