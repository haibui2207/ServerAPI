#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "wifi_info.h"


const char* ssid = SSID;
const char* password = WPA_KEY;
String host = HOST;

void setup() {
 
  Serial.begin(115200);                                  //Serial connection
  setup_wifi();    
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

  Post(host);
}

void Post(String host){
  if (WiFi.status() == WL_CONNECTED) { 
 
    HTTPClient http;  
 
    http.begin(host);
    http.addHeader("Content-Type", "application/json");
    
    int httpCode = http.POST("{\"pin\":6,\"state\":1}");   
    String payload = http.getString();  
 
    Serial.print("Post code return :");   
    Serial.println(httpCode);  
    Serial.println(payload);    
    
    http.end();   
  }
  else{
    Serial.println("Connect to server Failed. Reconnecting...");    
  } 
}
 
void loop() {
 if (WiFi.status() == WL_CONNECTED) { 
 
    HTTPClient http;  
    Serial.print("Connecting to host: ");
    Serial.println(host);
 
    http.begin(host);  
    int httpCode = http.GET();                                                                  
    Serial.println(httpCode);
    if (httpCode > 0) { 
      String payload = http.getString();  
      Serial.println(payload);                     
    } 
    http.end();  
    delay(10000); 
  }
  else{
    Serial.println("Connect to server Failed. Reconnecting...");    
    setup_wifi();  
  }     
}
