#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "wifi_info.h"

const char* ssid = SSID;
const char* password = WPA_KEY;
String host = HOST;
 
void setup() {  
  //Set Baurate
  Serial.begin(115200);  
  setup_wifi();  
}

//SETUP WIFI
void setup_wifi(){
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
 
void loop() { 
  if (WiFi.status() == WL_CONNECTED) 
  {  
    Serial.print("Connecting to host: ");
    Serial.println(host);
    
    HTTPClient http;  
    http.begin(host);  
    
    int httpCode = http.GET();                                                                  
    Serial.println(httpCode);
    
    if (httpCode > 0) { 
        String payload = http.getString();
        Serial.println(payload);
    } 
    
    http.end(); 
    delay(20000);
  }
  else{
    Serial.println("Connect to server Failed. Reconnecting...");
    setup_wifi();     
  }   
}

