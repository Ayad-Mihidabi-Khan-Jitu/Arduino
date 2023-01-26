#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup()
    {
      //Begin nodemcu serial-0 channel 
      Serial.begin(9600); 
      mySerial.begin(9600);
      
      Serial.println("Initializing..."); 
      delay(1000);

      /*
      mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
      updateSerial();
      mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
      updateSerial();
      mySerial.println("AT+CREG?"); //Check whether it has registered in the network
      updateSerial();

      mySerial.println("ATI"); //Get the module name and revision
      updateSerial();
      mySerial.println("AT+COPS? "); //Check that you’re connected to the network, in this case BSNL
      updateSerial();
      mySerial.println("AT+COPS=?"); //Return the list of operators present in the network.
      updateSerial();   
      mySerial.println("AT+CBC");  
      updateSerial();   
      */

      /*
      ///sms send
      mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
      updateSerial();
      mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
      updateSerial();
      //mySerial.println("AT+CMGS=\"+ZZxxxxxxxxxx\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
      mySerial.println("AT+CMGS=\"+8801676243435\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
      updateSerial();
      mySerial.print("Last Minute Engineers | lastminuteengineers.com"); //text content
      updateSerial();
      mySerial.write(26);
      */

      ///call 
      mySerial.println("AT"); //Once the handshake test is successful, i t will back to OK
      updateSerial();   
      mySerial.println("ATD+ +8801676243435;"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
      updateSerial();
      delay(20000); // wait for 20 seconds...
      mySerial.println("ATH"); //hang up
      updateSerial();

    }

  void loop()
    {
      updateSerial();
    //if (Serial.available()) {
    //Serial.write(Serial.read());
    //}
    
    /*
    ///For esp8266
    Serial.print("AT");  //Start Configuring GSM Module
    delay(1000);         //One second delay
    Serial.println();
    Serial.println("AT+CMGF=1");  // Set GSM in text mode
    delay(1000);                  // One second delay
    Serial.println();
    Serial.print("AT+CMGS=");     // Enter the receiver number
    Serial.print("\"+8801676243435\"");
    Serial.println();
    delay(1000);
    Serial.print("www.microcontroller-project.com"); // SMS body - Sms Text
    delay(1000);
    Serial.println();
    Serial.write(26);                //CTRL+Z Command to send text and end session
    while(1);                        //Just send the text ones and halt 
    */
    }

  void updateSerial()
  {
    delay(500);
    while (Serial.available()) 
    {
      mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
    }
    while(mySerial.available()) 
    {
      Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
    }
  }