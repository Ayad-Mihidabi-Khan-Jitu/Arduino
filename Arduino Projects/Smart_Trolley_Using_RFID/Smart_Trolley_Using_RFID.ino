#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

double total = 0;
int count_prod = 0;
int a;

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  pinMode(3, INPUT_PULLUP);   //Push Switch
  pinMode(4, OUTPUT);   //Push Switch
  Serial.begin(9600);		// Initialize serial communications with the PC
  while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();			// Init SPI bus
  mfrc522.PCD_Init();		// Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called
  // mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    //Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  int a=digitalRead(3);
  if ((content.substring(1) == "23 4E 84 97") && a==1)
  {
    //35 78 132 151
    //Serial.setCursor(0, 0);
    Serial.println("Butter Added       ");
    //Serial.setCursor(0, 1);
    Serial.println("Price(Rm):4.00      ");
    digitalWrite(4,LOW);
    //digitalWrite(5,LOW);
    //digitalWrite(6,HIGH);
    delay(2000);
    total = total + 4.00;
    count_prod++;
    Serial.print("Total price of ");
    Serial.print(count_prod);
    Serial.print(" products: ");
    Serial.print(total);
    Serial.println(" tk");
    //digitalWrite(4,LOW);
    //digitalWrite(5,HIGH);
    //digitalWrite(6,LOW);
    
  }

  else if ((content.substring(1) == "23 4E 84 97") && a==0)
  {
    //35 78 132 151
    //Serial.setCursor(0, 0);
    Serial.println("Butter Removed       ");
    //Serial.setCursor(0, 1);
    Serial.println("Price(Rm):4.00      ");
    digitalWrite(4,HIGH);
    //digitalWrite(5,LOW);
    //digitalWrite(6,HIGH);
    delay(2000);
    digitalWrite(4,LOW);
    total = total - 4.00;
    count_prod--;
    Serial.print("Total price of ");
    Serial.print(count_prod);
    Serial.print(" products: ");
    Serial.print(total);
    Serial.println(" tk");
    //digitalWrite(4,LOW);
    //digitalWrite(5,HIGH);
    //digitalWrite(6,LOW);
    
  }



}

