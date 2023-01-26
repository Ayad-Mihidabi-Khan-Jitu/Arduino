///This code is edited by jitu
///Simplest version of firebase set and get with json
///Using ESP8266Firebase Library which needs only DATABASE_URL

/**
 * Created by K. Suwatchai (Mobizt)
 * 
 * Email: k_suwatchai@hotmail.com
 * 
 * Github: https://github.com/mobizt/Firebase-ESP8266
 * 
 * Copyright (c) 2022 mobizt
 *
*/

/** This example will show how to access the RTDB in Test Mode (no authentication).
*/

#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

//Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

//For json to data convert
#define ARDUINOJSON_USE_DOUBLE 1
#include <ArduinoJson.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "PSTU-Students"
#define WIFI_PASSWORD "PSTU#2019"

/* 2. Define the RTDB URL */
#define DATABASE_URL "esp8266-sensordata-b45b1-default-rtdb.firebaseio.com"  //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

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
int count = 0;
String sensor []= {"Soil","Water","Air"};
float reading []= {12.33,99.55,33.33}; 

void setup() {

  Serial.begin(115200);

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
  
   for(int i=0; i<3; i++){

    ///Set json
    json.set("Index", i);
    json.set("SensorName", sensor[i]);
    json.set("Value", reading[i]);
    Firebase.setJSON(fbdo, "Sensors", json);

    // Get json from the database.
    Firebase.RTDB.getJSON(&fbdo, "/Sensors", &fdata);
    //json to string
    fdata.toString(jsonStr, true);
    //deserializeJson
    const size_t capacity = JSON_OBJECT_SIZE(3) + 50;
    DynamicJsonDocument doc(capacity);
    deserializeJson(doc, jsonStr);

    // Store the deserialized data.
    int index = doc["Index"]; // "It's Working"
    String sensorName = doc["SensorName"]; // 123
    float value = doc["Value"]; // 45.32
    
    Serial.print("Index: ");
    Serial.println(index);

    Serial.print("Sensor Name: ");
    Serial.println(sensorName);

    Serial.print("Sensor Value: ");
    Serial.println(value);
    Serial.println("---------------");

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
