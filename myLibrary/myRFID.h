#include <MFRC522.h>
#include <SPI.h>

/*  
  Why I define GPIO of RFID in here?
  Because when I test the Board ESP8266 , only ONE way to connect with them.
  I'm trying replace their GPIO with serveral other GPIO but it's not woking.
  So I define it in here. 
  If your board working with other GPIO, please change define below.
  
    |--------------------------------------------------------|
    |      | SDA(SS) |   SCK   |   MOSI  |   MISO  |   RST   |
    |RFID  --------------------------------------------------- 
    |      |   15    |   14    |   13    |   12    |    2    |
    |--------------------------------------------------------|    
*/

#define RFID_SDA 15 //SDA of RFID
#define RFID_RST 2 //RST of RFID

MFRC522 mfrc522(RFID_SDA, RFID_RST);  // Create MFRC522 instance

void setupRfid();
String readByteFromRFID(byte *buffer, byte bufferSize);              // read byte from rfid then convert to string
String startRFID();

/************************************************SETUP RFID************************************************/
void setupRfid(){
  SPI.begin();      
  mfrc522.PCD_Init();   
  mfrc522.PCD_DumpVersionToSerial();  
  Serial.println(F("Watting for RFID Card . Please put your RFID Card over RFID Reader"));
}

/************************************************READ DATA FROM RFID************************************************/
String readByteFromRFID(byte *buffer, byte bufferSize) {
  String content = "";
  for (byte i = 0; i < bufferSize; i++) {
    content.concat(String(buffer[i] <0x10 ? "0" : ""));  // change mfrc522.uid.uidByte = buffer => Error ???
    content.concat(String(buffer[i],HEX));
  }
  return content;
}


/************************************************START RFID************************************************/
String startRFID(){  
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return "";
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return "";
  }
  Serial.print(F("Card UID:"));
  String content = readByteFromRFID(mfrc522.uid.uidByte,mfrc522.uid.size);
  Serial.println();
  return content;
}
