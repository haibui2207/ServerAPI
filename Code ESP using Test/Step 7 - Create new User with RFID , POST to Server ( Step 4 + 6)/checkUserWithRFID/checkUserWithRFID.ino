#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "wifi_info.h"
#include <ArduinoJson.h>
#include <SPI.h>
#include "MFRC522.h"

/*
  Bao gồm : 
  void setupWifi()
  void displayStringAsJson(String) // 1 object
  void displayStringAsJsonArray(String)  //multi object
  JsonObject& convertStringToJson(String) // 1 object
  JsonObject& getIndexAtJsonArray(String data , int index) 
  void postData(String data)
  void setup_rfid() 
  String dump_byte_array(byte *buffer, byte bufferSize) // convert data read from RFID Reader
  String startRFID()
*/
/*
  SS 15
  SCK 14
  MOSI 13
  MISO 12
  RST 2
*/

#define SS_PIN 15
#define RST_PIN 2
 
const char* ssid = SSID;
const char* password = WPA_KEY;
String host = HOST;
int pin = 16;

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {  
  pinMode(pin,OUTPUT);
  //Set Baurate
  Serial.begin(115200);  
  setupWifi();  
  setup_rfid(); 
}

void setupWifi(){
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

String getHttpRespone(String url){
  String data; 
  Serial.print("Connecting to host: ");
  Serial.println(url); 
  HTTPClient http;  
  http.begin(host);  
  int httpCode = http.GET();    
//  Serial.print("GET Respone Code : ");                                               
//  Serial.println(httpCode);
  if (httpCode > 0) {         
    data = http.getString();        
  } 
  http.end(); 
  return data;
}

void postData(String url,String data){
  HTTPClient http;  
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(data);   
  String payload = http.getString();  
//  Serial.print("Post Respone code :");   
//  Serial.println(httpCode);    
  http.end();  
}

void setup_rfid(){
  SPI.begin();      
  mfrc522.PCD_Init();   
  mfrc522.PCD_DumpVersionToSerial();  
  Serial.println(F("Watting for RFID Card . Please put your RFID Card over RFID Reader"));
}

String dump_byte_array(byte *buffer, byte bufferSize) {
  String content = "";
  for (byte i = 0; i < bufferSize; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] <0x10 ? "0" : ""));
    content.concat(String(mfrc522.uid.uidByte[i],HEX));
  }
  return content;
}

String startRFID(){  
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return "";
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return "";
  }
  Serial.print(F("Card UID:"));
  String content = dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println();
  return content;
}

void loop() { 
  if (WiFi.status() == WL_CONNECTED) 
  {         
    String rfid_content = startRFID();  
    if(rfid_content == "") {
      digitalWrite(pin, HIGH);
      delay(2000); //important
      return;
    }
    Serial.print("RFID content : ");
    Serial.println(rfid_content);

    //GET  
    host.concat(rfid_content);
    Serial.print("URL : ");
    Serial.println(host);
    String data = getHttpRespone(host); 
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
      digitalWrite(pin, LOW);
    }
    else{
      Serial.println("Invalid USER");
    }  
    delay(5000);
  }
  else{
    Serial.println("Connect to server Failed. Reconnecting...");    
    setupWifi();
  }   
}

