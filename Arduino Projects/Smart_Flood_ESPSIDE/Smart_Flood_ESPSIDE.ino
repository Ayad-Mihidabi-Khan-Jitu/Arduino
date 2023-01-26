///This code is edited by jitu
///Simplest version of firebase set and get with json

#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif
#include <SoftwareSerial.h>

//Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

//For json to data convert
#define ARDUINOJSON_USE_DOUBLE 1
#include <ArduinoJson.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "Jitu"
#define WIFI_PASSWORD "jitu1234"

/* 2. Define the RTDB URL */
#define DATABASE_URL "esp8266flood-default-rtdb.firebaseio.com"  //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
//#define DATABASE_URL "esp-with-multi-sensor-default-rtdb.firebaseio.com/"  //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 3. Define the Firebase Data object */
FirebaseData fbdo;

/* 4, Define the FirebaseAuth data for authentication data */
FirebaseAuth auth;

/* Define the FirebaseConfig data for config data */
FirebaseConfig config;

//For the usage of FirebaseJson, see examples/FirebaseJson/BasicUsage/Create_Parse_Edit.ino
FirebaseJson json;

//for string firebase data
FirebaseJson fdata;

//for storing json data
String jsonStr;

unsigned long dataMillis = 0;

String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors

void setup() {

  Serial.begin(9600);
  //Serial1.begin(9600, SERIAL_8N1, 13, 15);
  //Serial1.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the certificate file (optional) */
  //config.cert.file = "/cert.cer";
  //config.cert.file_storage = StorageType::FLASH;

  /* Assign the database URL(required) */
  config.database_url = DATABASE_URL;

  config.signer.test_mode = true;

  /**
     Set the database rules to allow public read and write.

       {
	      "rules": {
		      ".read": true,
		      ".write": true
	      }
        }

    */

  Firebase.reconnectWiFi(true);

  /* Initialize the library with the Firebase authen and config */
  Firebase.begin(&config, &auth);
}

void loop() {

      if (Serial.available() > 0 ) 
      {
      Serial.println("Serial Available");
      }
      String val = Serial.readString();
      Serial.print("From Serial: ");
      Serial.println(val);
      

      int distance = 0;
      int temp = 0;

      //json.set("Water_Level", 59);
      //json.set("Temp", 25);
      //Firebase.setJSON(fbdo, "Sensors", json);
      //Serial.printf("Set json... %s\n", Firebase.set(fbdo, F("/test/json"), json) ? "ok" : fbdo.errorReason().c_str());
      //Serial.printf("Set int... %s\n", Firebase.setInt(fbdo, "/test/int", 12) ? "ok" : fbdo.errorReason().c_str());


  if (Serial.available() == 8980 ) 
  {
    Serial.println("Serial Available");
    rdata = Serial.read(); 
    myString = myString + rdata; 
    if( rdata == '\n')
    {
      Serial.println(myString);
      String sensorData1 = getValue(myString, ',', 0);
      String sensorData2 = getValue(myString, ',', 1);
      //String n = getValue(myString, ',', 2); 
      distance = sensorData1.toInt();
      temp = sensorData2.toInt();

      Serial.println(distance);
      Serial.println(temp);
      
      myString = "";
      // end new code
    }  




      ///Set json
      json.set("Water_Level", distance);
      json.set("Temp", temp);
      Firebase.setJSON(fbdo, "Sensors", json);
      delay(1000);
  



  }

  /*
  if (millis() - dataMillis > 5000)
  {
  dataMillis = millis();
  Serial.printf("Set int... %s\n", Firebase.setInt(fbdo, "/test/int", count++) ? "ok" : fbdo.errorReason().c_str());
  
  if (count == 0) {
    json.set("value/round/" + String(count), F("cool!"));
    json.set(F("vaue/ts/.sv"), F("timestamp"));
    Serial.printf("Set json... %s\n", Firebase.set(fbdo, F("/test/json"), json) ? "ok" : fbdo.errorReason().c_str());
  } 
  else {
    json.add(String(count), "smart!");
    Serial.printf("Update node... %s\n", Firebase.updateNode(fbdo, F("/test/json/value/round"), json) ? "ok" : fbdo.errorReason().c_str());
  }

  Serial.println();
  }
  */
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
