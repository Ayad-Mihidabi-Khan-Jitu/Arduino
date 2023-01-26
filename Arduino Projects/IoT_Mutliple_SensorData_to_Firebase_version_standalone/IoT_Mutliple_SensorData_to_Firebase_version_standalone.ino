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

#include <Wire.h>
#include <BH1750.h>
//#include <i2cdetect.h>
#include "DHT.h" // Click here to get the library: http://librarymanager/All#DHTesp

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

#define S0 D0
#define S1 D3
#define S2 D4
#define S3 D5
#define SIG A0
#define dhtPin D6
#define LT_SCLpin D1
#define LT_SDApin D2

DHT dht(dhtPin, DHT22); // temparature sensor
BH1750 lightMeter; // light sensor

unsigned long dataMillis = 0;
int count = 0;
String Sensor []= {"Soil","Water","Air"};
float reading []= {12.33,99.55,33.33}; 

void setup() {

  Serial.begin(115200);

  pinMode(S0,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin SO */        
  pinMode(S1,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S1 */  
  pinMode(S2,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S2 */ 
  pinMode(S3,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S3 */  
  pinMode(SIG, INPUT); 

  Wire.begin(LT_SDApin, LT_SCLpin);
  lightMeter.begin();
  dht.begin();
  Serial.println(F("BH1750 Test begin"));
  
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


  sensor(0,0,0,0); //Sensor 0
  int sensor0 = analogRead(SIG);
  int soilMois =  SoilMoisturePercent(sensor0);
  delay(100);

  sensor(1,0,0,0); //Sensor 1
  int sensor1 = analogRead(SIG);
  float waterPH= Water_PH_1(sensor1);
  delay(100);
  
  float lux = lightMeter.readLightLevel();
  delay(100);//for light

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  delay(100); //for temp

  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lux");

  Serial.print("Humidity of Air: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.println(" *F\t");
  
  Serial.print("Soil Moisture: ");
  Serial.println(soilMois);

  Serial.print("PH Sensor: ");
  Serial.println(sensor1);
  
  Serial.print("PH of Water: ");
  Serial.println(waterPH);

    json.set("Temp", t);
    json.set("Humid", h);
    json.set("Soil_Moisture", soilMois);
    json.set("Light", lux);
    json.set("Water_PH", waterPH);
    Firebase.setJSON(fbdo, "Sensors", json);



  /*
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


void sensor(int s0,int s1,int s2,int s3){
  digitalWrite(S0,s0);
  digitalWrite(S1,s1);
  digitalWrite(S2,s2);
  digitalWrite(S3,s3);
}

int SoilMoisturePercent(int sensorReading){
int mois = map(sensorReading, 1023, 0, 0, 100);
return mois;
}

float Water_PH(int sensorReading){
//sensorReading = map(sensorReading, 1023, 0, 0, 1023);
//Serial.println(sensorReading);
float voltage=sensorReading*(3.3/4095.0);
float ph=(3.3*voltage);
return ph;
}

float Water_PH_1(int sensorReading){
      //int measuringVal = analogRead(analogPin);
      //sensorReading = map(sensorReading, 1023, 0, 0, 1023);
      int measuringVal = sensorReading;    
      double vltValue = 5/1024.0 * measuringVal;
      //Serial.print("Voltage Value: ");
      //Serial.println(vltValue, 3);
    
      //float ph = 7 + ((2.5 - vltValue) / 0.18);
      float ph = 14 + ((2.5 - vltValue) / 0.18);
      //Serial.print("pH Value : ");
      return ph;
}


float Water_PH_2(){
  int buf[20],temp = 0,avgValue=0;
  for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
    { 
      sensor(1,0,0,0); //Sensor 1
      buf[i] = analogRead(SIG);
      //int sensorReading = analogRead(SIG);
      //buf[i] = map(sensorReading, 1023, 0, 0, 1023);
      Serial.println(buf[i]);
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
  phValue=3.5*phValue;
  return phValue;
}

/*
///Determination of ph

//method-1
float Water_PH(int sensorReading){
float voltage=sensorReading*(3.3/4095.0);
float ph=(3.3*voltage);
return ph;
}

//method-2
float Water_PH_1(int sensorReading){
      //int measuringVal = analogRead(analogPin);
      sensorReading = map(sensorReading, 1023, 0, 0, 1023);
      int measuringVal = sensorReading;    
      double vltValue = 5/1024.0 * measuringVal;
      //Serial.print("Voltage Value: ");
      //Serial.println(vltValue, 3);
    
      float ph = 7 + ((2.5 - vltValue) / 0.18);
      //Serial.print("pH Value : ");
      return ph;
}

//method-3
float Water_PH_2(){
  int buf[20],temp = 0,avgValue=0;
  for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
    { 
      sensor(1,0,0,0); //Sensor 1
      buf[i] = analogRead(SIG);
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
  phValue=3.5*phValue;
  return phValue;
}


*/
