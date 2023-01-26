///https://randomnerdtutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
///ESP-NOW One-Way Communication
//ESP8266 NodeMCU Receiver Sketch

/*
For one way communication only receiver address is needed.
Sender needs only the receiver address to pear the receiver.
The callback function at the receiver has the same function as sender end to receive data

Initialize ESP-NOW;
Register for a receive callback function (OnDataRecv). This is a function that will be executed when a message is received.
Inside that callback function save the message into a variable to execute any task with that information.
ESP-NOW works with callback functions that are called when a device receives a message or when a message is sent 
(you get if the message was successfully delivered or if it failed).

ESP-NOW Useful Functions
Here’s a summary of most essential ESP-NOW functions:

Function Name and Description
esp_now_init() Initializes ESP-NOW. You must initialize Wi-Fi before initializing ESP-NOW. Returns 0, if succeed.
esp_now_set_self_role(role) the role can be: ESP_NOW_ROLE_IDLE = 0,
ESP_NOW_ROLE_CONTROLLER, ESP_NOW_ROLE_SLAVE, ESP_NOW_ROLE_COMBO, ESP_NOW_ROLE_MAX
esp_now_add_peer(uint8 mac_addr, uint8 role, uint8 channel, uint8 key, uint8 key_len) Call this function to pair a device.
esp_now_send(uint8 mac_address, uint8 data, int len) Send data with ESP-NOW.
esp_now_register_send_cb() Register a callback function that is triggered upon sending data. When a message is sent, a function is called 
– this function returns whether the delivery was successful or not.
esp_now_register_rcv_cb() Register a callback function that is triggered upon receiving data. 
When data is received via ESP-NOW, a function is called.
*/
#include <ESP8266WiFi.h>
#include <espnow.h>

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message{
char alphabet[32];
int number;
String word;
bool isTrue;
}struct_message;

int lenOfData;

// Create a struct_message called sendingData
struct_message receivedData;

void OnDataRecv(uint8_t * recvMAC, uint8_t *incomingData, uint8_t len){
  memcpy(&receivedData, incomingData, sizeof(receivedData));
  lenOfData = len;

}

void setup(){
  Serial.begin(115200);
  //Serial.println();
  Serial.print("ESP8266 Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
  WiFi.mode(WIFI_STA);

  //initializing esp_now protocol
  if(esp_now_init() == 0)
  Serial.println("esp_now protocol initialized");
  else{
    Serial.println("error initializing esp_now protocol");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);

}

void loop(){
    
    for(int i = 0; i<26; i++){
    Serial.print("Bytes received: ");
    Serial.println(lenOfData);
    Serial.print("Char: ");
    Serial.println(receivedData.alphabet[i]);
    Serial.print("Int: ");
    Serial.println(receivedData.number);
    Serial.print("String: ");
    Serial.println(receivedData.word);
    Serial.print("Bool: ");
    Serial.println(receivedData.isTrue);

    delay(1000);
    }

}