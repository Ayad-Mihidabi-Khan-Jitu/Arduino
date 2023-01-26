/*
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>



String sdata; 
char auth[] = "L_NQwQJfrV6lyULZK6nhPB2jpK97yOg-";

// Your WIFI credentials.
// Set password to "" for open networks.
char ssid[] = "PSTU-Teachers";
char pass[] = "PSTU@ICT#2021";

BlynkTimer timer;

String  myString; // complete message from Arduino, which consists of sensors data
char rdata; // received characters


// This function sends Arduino's up time every second to Virtual Pin (1).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, millis() / 1000);
  
}



void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  timer.setInterval(1000L, sensorvalue1); 

}

void loop()
{
   if (Serial.available() == 0) 
   {
  Blynk.run();
  timer.run(); // Initiates BlynkTimer

   }
   
  if (Serial.available() > 0) 
  {
    rdata = Serial.read(); 
    myString = myString + rdata; 
  
  }

}

void sensorvalue1()
{
sdata = myString ;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V12, sdata);
   myString = "";
}

*/



// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID           "TMPLGoziIO6C"
#define BLYNK_DEVICE_NAME           "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "NE_5i5eTzRL76O0QMhGcXuu_opTFb_k9"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "PSTU-Teachers";
char pass[] = "PSTU@ICT#2021";

String  myString; // complete message from Arduino, which consists of sensors data
char rdata; // received characters
String sdata; 

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V1, value);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup()
{
  // Debug console
  //Serial.begin(115200);
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  //timer.setInterval(1000L, myTimerEvent);
  timer.setInterval(1000L, sensorvalue1); 
}

void loop()
{
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!

   if (Serial.available() == 0) 
   {
  Blynk.run();
  timer.run(); // Initiates BlynkTimer

   }
   
  if (Serial.available() > 0) 
  {
    rdata = Serial.read(); 
    myString = myString + rdata; 
  
  }
  
}

void sensorvalue1()
{
sdata = myString ;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  //Blynk.virtualWrite(V12, sdata);
  Blynk.virtualWrite(V3, sdata);
   myString = "";
}
