//https://randomnerdtutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
///ESP-NOW One-Way Communication
//ESP8266 NodeMCU Sender Sketch
/*
ESP-NOW is a “protocol developed by Espressif, which enables multiple devices to communicate with one another without using Wi-Fi. 
The protocol is similar to the low-power 2.4GHz wireless connectivity (…) . 
The pairing between devices is needed prior to their communication. After the pairing is done, 
the connection is safe and peer-to-peer, with no handshake being required.”
This means that after pairing a device with each other, the connection is persistent. In other words, 
if suddenly one of your boards loses power or resets, when it restarts, 
it will automatically connect to its peer to continue the communication.
In simple words, ESP-NOW is a fast communication protocol that can be used to exchange small messages (=> 250 bytes) between ESP8266 boards.
///For example, in one-way communication, you can have scenarios like this:
One ESP8266 board sending data to another ESP8266 board

Here’s what we should include in the sender sketch:

Initialize ESP-NOW;
Register a callback function upon sending data – the OnDataSent function will be executed when a message is sent. 
This can tell us if the message was successfully delivered or not;
Add a peer device (the receiver). For this, you need to know the the receiver MAC address;
Send a message to the peer device.
On the receiver side, the sketch should include:

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

//ESP 8266MOD MAC address: 8C:CE:4E:E3:44:40
//ESP-12F MAC address: 9C:9C:1F:45:DB:C1

#include <ESP8266WiFi.h>
#include <espnow.h>

//RECEIVER MAC Address
uint8_t receiverMacAddress [] = {0x8C,0xCE,0x4E,0xE3,0x44,0x40};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message{
char alphabet[32];
int number;
String word;
bool isTrue;
}struct_message;

// Create a struct_message called sendingData
struct_message sendingData;

unsigned long lastTime = 0;  
unsigned long timerDelay = 2000;  // send readings timer

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
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
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer, pair with another ESP-NOW device to send data.
  //The esp_now_add_peer accepts the following arguments:
  //in this order: mac address, role, wi-fi channel, key, and key length.
  esp_now_add_peer(receiverMacAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

}
 
void loop(){

  for(int i = 0; i<26; i++){
    //strcpy(sendingData.alphabet, "THIS IS A CHAR");
    sendingData.alphabet[i] = (i%26) + 'A';   
    sendingData.number = i;
    sendingData.word = "send strin"; // maximum 10 character
    //strcpy(sendingData.word, "THIS IS A CHAR");
    sendingData.isTrue = 1;

    esp_now_send(receiverMacAddress, (uint8_t *) &sendingData, sizeof(sendingData));
    delay(1000);
  }
  

}