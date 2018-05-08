#include "wifi_info.h"
#include "myHttpClient.h"
#include "myServo.h"
#include "myBell.h"

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

int haibui_pin4 = 4; //Led
int trungduyen_pin14 = 14; //Bell
int counter = 0;  //định thời cho bell
bool isDoorOpen = false;
 
/************************************************SETUP************************************************/
void setup() { 
  setupServo(myServo,SERVO_PIN);  
  pinMode(haibui_pin4,OUTPUT);
  pinMode(trungduyen_pin14,OUTPUT);
  //Set Baurate
  Serial.begin(115200);  
  setupWifi(ssid,password);  
}


/************************************************ LOOP ************************************************/
void loop() { 
  if (WiFi.status() == WL_CONNECTED) 
  {       
    String data = getHttpRespone(host);
    Serial.println(data);
    JsonObject& reponse_pin4 = getPinInJsonArray(data , haibui_pin4);
    JsonObject& reponse_pin14 = getPinInJsonArray(data , trungduyen_pin14); 
    JsonObject& reponse_servo_pin = getPinInJsonArray(data , SERVO_PIN); 
    
    int state_pin4 = reponse_pin4["state"];
    int state_pin14 = reponse_pin14["state"];
    int state_servo_pin = reponse_servo_pin["state"];

    if(state_servo_pin == 1){
      isDoorOpen = openDoor(myServo);
      postData(host,"{\"pin\":" + String(SERVO_PIN) + ",\"state\":0}");    // close door
    }
    
    if(state_pin4 == 1){      
      digitalWrite(haibui_pin4,HIGH); // ON LED
    }
    else {
      digitalWrite(haibui_pin4,LOW);
    }
    
    if(state_pin14 == 1) {
      startBell(trungduyen_pin14,counter); // ON BELL
      counter = (counter+1)%40;       
    }
    else {
      counter = 0;
      stopBell(trungduyen_pin14);
    }

    delay(2000); 
    isDoorOpen = closeDoor(myServo,isDoorOpen);    // close door
  }
  else{
    Serial.println("Connect to server Failed. Reconnecting...");    
    setupWifi(ssid,password);  
  }   
}

