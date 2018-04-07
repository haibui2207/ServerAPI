#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "wifi_info.h"
#include <ArduinoJson.h>
#include <SPI.h>
#include "MFRC522.h"
#include <Adafruit_NeoPixel.h>
#include "SSD1306.h"
#include "Wire.h"

/*
    ////////////////////////////////////////////
    //                                        //
    //   Code using ESP8266 Running RFID      //
    //                                        //
    ////////////////////////////////////////////
*/

/*
  SDA(SS) 15
  SCK 14
  MOSI 13
  MISO 12
  RST 2
*/

#define SS_PIN 15
#define RST_PIN 2
 
const char* ssid = SSID;
const char* password = WPA_KEY;
const char* host = HOST;
int pin = 10;

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
SSD1306  display(0x3c, 4, 5);

/************************************************ SETUP ************************************************/
void setup() {  
  pinMode(pin,OUTPUT);
  //Set Baurate
  Serial.begin(115200);  
  setupWifi(ssid,password);
  setupOled();  
  setupRfid();   
}

/************************************************SETUP OLED************************************************/
void setupOled(){
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.drawString(35, 25, "WELCOME"); 
  display.display();                           
}

/************************************************SETUP WIFI************************************************/
void setupWifi(const char* ssid,const char* password){
  Serial.println();
  Serial.print("Connecting to ");                             
  Serial.println(ssid);
  
  //Connect to Wifi
  WiFi.begin(ssid,password);  
                  
  //Check if connect fail
  while(WiFi.status()!= WL_CONNECTED){                                  
    delay(1000);
    Serial.println("Can't connect. Reconnecting...\n");
  }
  
  //If connect success
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());                                 
}

/***************************FUNCTION DISPLAY AND CONVERT STRING TO JSONOBJECT***************************/
void displayStringAsJson(String data){
  int len = data.length() + 1;
  char buf[len];
  data.toCharArray(buf, len);  
  
  const size_t bufferSize = JSON_ARRAY_SIZE(20) + 20*JSON_OBJECT_SIZE(2);
  DynamicJsonBuffer jsonBuffer(bufferSize);
  JsonObject& obj = jsonBuffer.parseObject(data);  
  //check parse
  if (!obj.success()) Serial.println("parseObject() failed");
    
  obj.prettyPrintTo(Serial);
  Serial.println();
}

void displayStringAsJsonArray(String data){
  int len = data.length() + 1;
  char buf[len];
  data.toCharArray(buf, len);   
  
  const size_t bufferSize = JSON_ARRAY_SIZE(20) + 20*JSON_OBJECT_SIZE(2);
  DynamicJsonBuffer jsonBuffer(bufferSize);
  JsonArray& root = jsonBuffer.parseArray(data);  
  //check parse
  if (!root.success()) Serial.println("parseObject() failed");
  
  root.prettyPrintTo(Serial);
  Serial.println();
}

JsonObject& convertStringToJson(String data){
  int len = data.length() + 1;
  char buf[len];
  data.toCharArray(buf, len);  
  
  const size_t bufferSize = JSON_ARRAY_SIZE(20) + 20*JSON_OBJECT_SIZE(2);
  DynamicJsonBuffer jsonBuffer(bufferSize);
  JsonObject& obj = jsonBuffer.parseObject(data);  
  //check parse
  if (!obj.success()) Serial.println("parseObject() failed");
    
  return obj;
}

JsonObject& getIndexAtJsonArray(String data , int index){
  int len = data.length() + 1;
  char buf[len];
  data.toCharArray(buf, len);   
  
  const size_t bufferSize = JSON_ARRAY_SIZE(20) + 20*JSON_OBJECT_SIZE(2);
  DynamicJsonBuffer jsonBuffer(bufferSize);
  JsonArray& root = jsonBuffer.parseArray(data);  
  //check parse
  if (!root.success()) Serial.println("parseObject() failed");
    
  JsonObject& obj = root[index];   
  return obj;
}

/************************************************GET DATA************************************************/
String getHttpRespone(String URL){
  String data; 
  Serial.print("Connecting to host: ");
  Serial.println(URL); 
  HTTPClient http;  
  http.begin(URL);  
  int httpCode = http.GET();    
//  Serial.print("GET Respone Code : ");                                              
//  Serial.println(httpCode);
  if (httpCode > 0) {         
    data = http.getString();        
  } 
  http.end(); 
  return data;
}

/************************************************POSST DATA************************************************/
void postData(const char* host,String data){
  HTTPClient http;  
  http.begin(host);
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(data);   
  String payload = http.getString();  
//  Serial.print("Post Respone code :");   
//  Serial.println(httpCode);    
  http.end();  
}

/************************************************SETUP RFID************************************************/
void setupRfid(){
  SPI.begin();      
  mfrc522.PCD_Init();   
  mfrc522.PCD_DumpVersionToSerial();  
  Serial.println(F("Watting for RFID Card . Please put your RFID Card over RFID Reader"));
}

/************************************************READ DATA FROM RFID************************************************/
String dump_byte_array(byte *buffer, byte bufferSize) {
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
  String content = dump_byte_array(mfrc522.uid.uidByte,mfrc522.uid.size);
  Serial.println();
  return content;
}

/************************************************LOOP************************************************/
void loop() { 
  if (WiFi.status() == WL_CONNECTED) 
  {         
    String rfid_content = startRFID();  
    if(rfid_content == "") {
      display.clear();
      display.drawString(35, 25, "WELCOME"); 
      display.display();    
      digitalWrite(pin, LOW);
      delay(2000); //important
      return;
    }
    Serial.print("RFID content : ");
    Serial.println(rfid_content);

    //GET 
    String URL = String(host); 
    URL.concat(rfid_content);
    Serial.print("URL : ");
    Serial.println(URL);
    String data = getHttpRespone(URL); 
    if(data == ""){
      Serial.println("No data response");
      delay(2000);
      return;
    }
    JsonObject& control = convertStringToJson(data); 
    control.prettyPrintTo(Serial);
    Serial.println();
    String rfid_response = control["rfid"];
    if(rfid_response == rfid_content){
      String username = control["name"];
      Serial.print("USER : ");
      Serial.println(username);
      digitalWrite(pin, HIGH);
      //SHOW OLED
      display.clear();  
      display.drawString(35, 15, "WELCOME");    
      display.drawString(35, 35, String(username));      
      display.display();       
    }
    else{
      display.clear();
      display.drawString(35, 10, "WRONG CARD");
      Serial.println("Invalid USER");
    }  
    delay(5000);
  }
  else{
    Serial.println("Connect to server Failed. Reconnecting...");    
    setupWifi(ssid,password);  
  }   
}


