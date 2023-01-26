///This code is edited by jitu
///Simplest version of firebase set and get 
///Using ESP8266Firebase Library which needs only projectID

/*
  Make sure your Firebase project's ".read" and ".write" rules are set to "true".
  Avoiding this will result in an error.
  For more details- https://github.com/Rupakpoddar/ESP8266Firebase/blob/master/README.md
*/

#include <ESP8266Firebase.h>
#include <ESP8266WiFi.h>
#include <FirebaseJson.h>

#define _SSID "PSTU-Students"        // Your WiFi SSID
#define _PASSWORD "PSTU#2019"    // Your WiFi Password
#define PROJECT_ID "esp8266-sensordata-b45b1-default-rtdb"   // Your Firebase Project ID. Can be found in project settings.

/*
  // FAST METHOD
  // REQUIRES PERIODIC UPDATE OF FINGERPRINT (EVERY 1 YEAR)
  // OUTDATED FINGERPRINT WILL STOP THE SERVICE
  // LATEST FINGERPRINT CAN BE FOUND AT- https://www.grc.com/fingerprints.htm?domain=test.firebaseio.com
  // REPLACE COLONS(:) WITH A SPACE(" ") AS SHOWN BELOW
  // 03:9E:4F:E6:83:FC:40:EF:FC:B2:C5:EF:36:0E:7C:3C:42:20:1B:8F ==> 03 9E 4F E6 83 FC 40 EF FC B2 C5 EF 36 0E 7C 3C 42 20 1B 8F
  #define FINGERPRINT "03 9E 4F E6 83 FC 40 EF FC B2 C5 EF 36 0E 7C 3C 42 20 1B 8F"
  Firebase firebase(PROJECT_ID, FINGERPRINT);
  // UNCOMMENT THIS BLOCK AND COMMENT THE LINE BELOW
*/
 
Firebase firebase(PROJECT_ID);    // SLOW BUT HASTLE-FREE METHOD FOR LONG TERM USAGE. DOES NOT REQUIRE PERIODIC UPDATE OF FINGERPRINT
String sensor []= {"Soil","Water","Air"};
float reading []= {12.33,99.55,33.33}; 

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  // Connect to WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(_SSID);
  WiFi.begin(_SSID, _PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }

  Serial.println("");
  Serial.println("WiFi Connected");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  digitalWrite(LED_BUILTIN, HIGH);
  firebase.json(true);
}

void loop() {
  
  // Examples of setting String, integer and float values.
  //firebase.setString("Example/setString", "It's Working");
  
  
  //This sets index, Sensor, Name serialwise. One after one
  for(int i=0; i<3; i++){

    //setting index, sensor name, value
    firebase.setInt("Sensors/Index", i);
    firebase.setString("Sensors/SensorName", sensor[i]);
    firebase.setFloat("Sensors/Value", reading[i]);

    // Example of getting an int.
    int data2 = firebase.getInt("Sensors/Index");
    Serial.print("Received int: ");
    Serial.println(data2);

    // Example of getting a String.
    String data1 = firebase.getString("Sensors/SensorName");
    Serial.print("Received String: ");
    Serial.println(data1);

    // Example of getting a float.
    float data3 = firebase.getFloat("Sensors/Value");
    Serial.print("Received float: ");
    Serial.println(data3);

    //delay(1000);
  }
  


}
