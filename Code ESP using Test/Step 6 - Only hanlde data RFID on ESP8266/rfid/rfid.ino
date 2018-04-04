#include <ESP8266WiFi.h>
#include <SPI.h>
#include "MFRC522.h"
#include "wifi_info.h"

const char* ssid = SSID;
const char* password = WPA_KEY;

/*
SS 15
SCK 14
MOSI 13
MISO 12
RST 2
*/

#define SS_PIN 15
#define RST_PIN 2

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(115200);   // Initialize serial communications with the PC   
  setup_wifi();  
  start_rfid(); 
}

//SETUP WIFI
void setup_wifi(){
  Serial.println();
  Serial.print("Connecting to ");                                         //Print Serial monitoring
  Serial.println(ssid);
   
  //Connect to Wifi
  WiFi.begin(ssid,password);                                              //Connect to Wifi

  //Check if connect fail
  while(WiFi.status()!=WL_CONNECTED){                                     //Check if connect fail
    delay(1000);
    Serial.println("Can't connect. Reconnecting...\n");
  }
  //If connect success
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());       
}

void start_rfid(){
  SPI.begin();      
  mfrc522.PCD_Init();   
  mfrc522.PCD_DumpVersionToSerial();  
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

// Helper routine to dump a byte array as hex values to Serial
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) { 
 
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return;
    }
  
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) {
      return;
    }
  
    // Dump debug info about the card; PICC_HaltA() is automatically called
    Serial.print(F("Card UID:"));
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println();
    
    
    delay(1000);
  }
  else{
    Serial.println("Connect to server Failed. Reconnecting...");   
    setup_wifi(); 
  }   
}


