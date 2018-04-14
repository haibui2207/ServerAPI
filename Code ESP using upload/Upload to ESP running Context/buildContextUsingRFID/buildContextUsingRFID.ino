#include "wifi_info.h"
#include "myHttpClient.h"
#include "myServo.h"

/*
    ////////////////////////////////////////////
    //                                        //
    //   Code using ESP8266 Running Context   //
    //                                        //
    ////////////////////////////////////////////
*/
/*
    ////////////////////////////////////////////////
    //                                            //
    //   User "Hai Bui"     - change PIN  [4,5]   //
    //                                            //                                   
    //   User "Trung Duyen" - change PIN  [14,15] //
    //                                            //
    ////////////////////////////////////////////////
*/

#define SERVO_PIN 2

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASS;
const char* host = PIN_API;

Servo myServo;

 
/************************************************SETUP************************************************/
void setup() { 
  setupServo(myServo,SERVO_PIN);  
  //Set Baurate
  Serial.begin(115200);  
  setupWifi(ssid,password);  
}


/************************************************ LOOP ************************************************/
void loop() { 
  if (WiFi.status() == WL_CONNECTED) 
  {       
    //GET
    String data = getHttpRespone(host);
//    displayStringAsJsonArray(data);
    JsonObject& control = getIndexAtJsonArray(data , SERVO_PIN - 1); //array begin from 0
    control.prettyPrintTo(Serial);
    Serial.println();

    int state = control["state"];
    if(state == 1) {
      startServo(myServo);
    }

    delay(5000);   
    
  }
  else{
    Serial.println("Connect to server Failed. Reconnecting...");    
    setupWifi(ssid,password);  
  }   
}

