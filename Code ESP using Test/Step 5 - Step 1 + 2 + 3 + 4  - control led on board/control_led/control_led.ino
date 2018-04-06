#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "wifi_info.h"
#include <ArduinoJson.h>

/*
 Bao gồm : 
 void setupWifi()
 void displayStringAsJson(String) // 1 object
 void displayStringAsJsonArray(String)  //multi object
 JsonObject& convertStringToJson(String) // 1 object
 JsonObject& getIndexAtJsonArray(String data , int index) 
 void postData(String data)
 */
 
const char* ssid = SSID;
const char* password = WPA_KEY;
String host = HOST;
int pin = 16;
 
void setup() {  
  pinMode(pin,OUTPUT);
  //Set Baurate
  Serial.begin(115200);  
  setup_wifi(ssid,password);    
}

void setup_wifi(const char* ssid,const char* password){
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

String getHttpRespone(String host){
  String data; 
  Serial.print("Connecting to host: ");
  Serial.println(host); 
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

void postData(String host,String data){
  HTTPClient http;  
  http.begin(host);
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(data);   
  String payload = http.getString();  
//  Serial.print("Post Respone code :");   
//  Serial.println(httpCode);    
  http.end();  
}

void loop() { 
  if (WiFi.status() == WL_CONNECTED) 
  {       
    //GET
    String data = getHttpRespone(host);
//    displayStringAsJsonArray(data);
    JsonObject& control = getIndexAtJsonArray(data , pin - 1); //array begin from 0
    control.prettyPrintTo(Serial);
    Serial.println();

    int state = control["state"];
    digitalWrite(pin, state);

    if(state == 1)  state = 0;
    else  state = 1;
    
    //POST
    String dt = "{\"pin\":" + String(pin) + ",\"state\":"+ String(state) + "}"; // auto on off led
    postData(host,dt);   

    delay(20000);
  }
  else{
    Serial.println("Connect to server Failed. Reconnecting...");    
    setup_wifi(ssid,password);    
  }   
}

