#include <ESP8266Firebase.h>
#include <ESP8266WiFi.h>

#define WIFI_SSID "Nihim"                                          
#define WIFI_PASSWORD "1234567890"
//#define PROJECT_ID "esp-with-multi-sensor"                   
#define PROJECT_ID "esp-with-multi-sensor-default-rtdb"   // Project ID with user name
Firebase firebase(PROJECT_ID);  
                                 
String fireStatus = "";                                   // led status received from firebase
int led = 5;  
int poten = A0;
                                                              
void setup() 
{
  Serial.begin(115200);
  delay(1000);    
  pinMode(led, OUTPUT);
  pinMode(poten, INPUT);

  //WiFi.mode(WIFI_STA);
  //WiFi.disconnect();
                   
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
  //Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                  // connect to firebase
  //Firebase.setString("Led_Status", "off");                       //send initial string of led status
  firebase.setString("Led_Status","off");
  firebase.setInt("P_Read",0);
}
 
void loop() 
{
  //fireStatus = Firebase.getString("Led_Status");
  int p_value = analogRead(poten);
  Serial.print("Potentiometer: ");
  Serial.println(p_value);
  
  firebase.setInt("P_Read",p_value);
  //firebase.pushInt("P_Read",p_value);
  fireStatus = firebase.getString("Led_Status");
  
  Serial.println(fireStatus);     
  if (fireStatus == "on") 
  {                                                          // compare the input of led status received from firebase
    Serial.println("Led Turned ON");                                                        
    digitalWrite(led, HIGH);                                                         // make external led ON
  } 
  else if (fireStatus == "off") 
  {                                                  // compare the input of led status received from firebase
    Serial.println("Led Turned OFF");
    digitalWrite(led, LOW);                                                         // make external led OFF
  }
  else 
  {
    Serial.println("Command Error! Please send on/Off");
  }
}

/*
#include <ESP8266WiFi.h>                                               
#include <FirebaseArduino.h>                                        

#define FIREBASE_HOST "esp-with-multi-sensor-default-rtdb.firebaseio.com"              // the project name address from firebase id
#define FIREBASE_AUTH "fxGMQhZAVYWWIrGiOgpBhuYwqnffbctTgFV37jnm"       // the secret key generated from firebase
#define WIFI_SSID "Nihim"                                          
#define WIFI_PASSWORD "1234567890"                                  
 
String fireStatus = "";                                                     // led status received from firebase
int led = 5;  
                                                              
void setup() 
{
  Serial.begin(115200);
  delay(1000);    
  pinMode(led, OUTPUT);                 
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
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                  // connect to firebase
  Firebase.setString("Led_Status", "off");                       //send initial string of led status
}
 
void loop() 
{
  fireStatus = Firebase.getString("Led_Status");                                      // get ld status input from firebase
  Serial.println(fireStatus);     
  if (fireStatus == "on") 
  {                                                          // compare the input of led status received from firebase
    Serial.println("Led Turned ON");                                                        
    digitalWrite(led, HIGH);                                                         // make external led ON
  } 
  else if (fireStatus == "off") 
  {                                                  // compare the input of led status received from firebase
    Serial.println("Led Turned OFF");
    digitalWrite(led, LOW);                                                         // make external led OFF
  }
  else 
  {
    Serial.println("Command Error! Please send on/Off");
  }
}
*/
