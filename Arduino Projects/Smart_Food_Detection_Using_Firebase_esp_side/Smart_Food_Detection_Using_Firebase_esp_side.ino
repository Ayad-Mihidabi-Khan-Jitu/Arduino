#include <SoftwareSerial.h>
//#include <ESP8266Firebase.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define WIFI_SSID "PSTU-Teachers"                                       
#define WIFI_PASSWORD "PSTU@ICT#2021" 

#define FIREBASE_HOST "esp8266-sensordata-b45b1-default-rtdb.firebaseio.com"      
#define FIREBASE_AUTH "xA6v6wHpLscMIw6tqJ847DuMjJjFuQyVETeTCU0V" 
              
//#define PROJECT_ID "esp8266-sensordata-b45b1-default-rtdb"   // Project ID with user name
//Firebase firebase(PROJECT_ID);  
//SoftwareSerial ardu(14, 12, false, 256);
SoftwareSerial ardu(14, 12);

String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors

//int phVal=0, soilMoisVal=0; // sensors 
float waitedTime = 0;

void setup() {
  
  //Serial.begin(115200); 
  Serial.begin(9600);    
  ardu.begin(9600);                           
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
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);  
  
}

// the loop function runs over and over again forever
void loop() {

  if(WiFi.status() == WL_CONNECTED)
    Serial.println("connected");
    else
    Serial.println("connected not");
    
  if (Serial.available() == 0 ) 
   {
    Serial.println("Serial available = 0");
    delay(2000);
  //Blynk.run();
  //timer.run(); // Initiates BlynkTimer
   }
  if (Serial.available() > 0 ) 
  {
  
    //rdata = ardu.read(); 
    //myString = myString + rdata;
    myString = ardu.readString(); 
    Serial.println(myString);
    delay(100);

    //firebase.setString("Food_Status",myString);
    Firebase.setString("Food_Status","jitu");
    delay(2000);
      
    //myString = "";
    // end new code
    }
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

  
