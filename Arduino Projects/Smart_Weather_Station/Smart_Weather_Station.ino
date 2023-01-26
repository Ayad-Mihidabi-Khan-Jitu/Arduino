#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif
#include <SoftwareSerial.h>
#include "DHT.h" // Click here to get the library: http://librarymanager/All#DHTesp
#include <addons/RTDBHelper.h>

//For json to data convert
#define ARDUINOJSON_USE_DOUBLE 1
#include <ArduinoJson.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "rajib"
#define WIFI_PASSWORD "rajib2696"

/* 2. Define the RTDB URL */
#define DATABASE_URL "esp8266-weather-7afa0-default-rtdb.firebaseio.com"  //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

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

DHT dht(D3, DHT11); //(sensor pin,sensor type)

void setup() {
  Serial.begin(9600); // Starts the serial communication
  dht.begin();

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

  /* Assign the database URL(required) */
  config.database_url = DATABASE_URL;

  config.signer.test_mode = true;

  Firebase.reconnectWiFi(true);

  /* Initialize the library with the Firebase authen and config */
  Firebase.begin(&config, &auth);
}

void loop() {
 
  weather();

}


void weather() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int r = analogRead(A0);

  r = map(r, 0, 1023, 0, 100);
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  ///Set json
  //json.set("Water_Level", distance);
  json.set("Temp", t);
  json.set("Humid", h);
  json.set("Rain", r);
  Firebase.setJSON(fbdo, "Sensors", json);
  delay(1000);


}
