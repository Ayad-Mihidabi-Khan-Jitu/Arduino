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
#define WIFI_SSID "jitu"
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


const int trigPin = 12; //D6
const int echoPin = 14; //D5
int dhtPin = 15;        // D8 

float duration = 0, distance = 0;

DHT dht(dhtPin, DHT11); // temparature sensor

void setup() {
  Serial.begin(9600); // Starts the serial communication
  dht.begin();
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

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

  digitalWrite(trigPin,LOW); // jodi age theke pin ta on thake
  //delay(2);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration=pulseIn(echoPin,HIGH);
  //int timeInsec = timeInmicro/1000000;
  //distenceInmeter = (340*timeInsec);
  //double distenceIncentimeter = distenceInmeter/100;
  distance = (duration*0.034)/2;

  Serial.print(distance);
  Serial.println(" cm");

  float h = dht.readHumidity();
  //firebase.setInt("Air_Humid",h);
  // Read temperature as Celsius (the default)
  float temp = dht.readTemperature();

  Serial.print("Humidity of Air: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" *C ");

  if(distance<30)
  {
      //lcd.print(String(distance) + "% HIG");
      json.set("Water_Level", "HIGH");
  }
  else if(distance<70)
  {
      //lcd.print(String(distance) + "% MID");
      json.set("Water_Level", "MID");

  }
  else
  {
    //lcd.print(String(distance) + "% LOW");
    json.set("Water_Level", "LOW");

  }

  ///Set json
  //json.set("Water_Level", distance);
  json.set("Temp", temp);
  json.set("Humid", h);
  Firebase.setJSON(fbdo, "Sensors", json);
  delay(1000);

}