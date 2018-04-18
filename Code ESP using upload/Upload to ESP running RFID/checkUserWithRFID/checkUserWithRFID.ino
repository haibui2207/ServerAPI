#include "wifi_info.h"
#include "myHttpClient.h"
#include "myRFID.h"
#include "myOLED.h"


/*
    ////////////////////////////////////////////
    //                                        //
    //   Code using ESP8266 Running RFID      //
    //                                        //
    ////////////////////////////////////////////
*/
 
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASS;
const char* userAPI = USER_API;
const char* pinAPI = PIN_API;
int pin = 10;

/************************************************ SETUP ************************************************/
void setup() {  
  pinMode(pin,OUTPUT);
  //Set Baurate
  Serial.begin(115200);  
  setupWifi(ssid,password);
  setupOled();  
  setupRfid();   
}

/************************************************LOOP************************************************/
void loop() { 
  if (WiFi.status() == WL_CONNECTED) 
  {         
    String rfid_content = startRFID();  
    if(rfid_content == "") {
      startOled(35, 25, "WELCOME"); 
      digitalWrite(pin, LOW);
      delay(2000); //important
      return;
    }
    Serial.print("RFID content : ");
    Serial.println(rfid_content);

    //GET 
    String URL = String(userAPI); 
    URL.concat(rfid_content);
    Serial.print("URL : ");
    Serial.println(URL);
    String data = getHttpRespone(URL); 
    if(data == ""){
      Serial.println("No data response");
      startOled(35, 25, "INVALID USER");
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
      startOled(35, 15, "WELCOME",35, 35, String(username));  
      
      if(username == "Hai Bui"){
        postData(pinAPI,"{\"pin\":4,\"state\":1}");     // On Led
        postData(pinAPI,"{\"pin\":2,\"state\":1}");     // Open door
      }
      if(username == "Trung Duyen"){
        postData(pinAPI,"{\"pin\":14,\"state\":1}");    // On Bell
        postData(pinAPI,"{\"pin\":2,\"state\":1}");     // Open door
      }
    }
    else{
      display.clear();
      display.drawString(35, 25, "INVALID USER");
      display.display();
      Serial.println("Invalid USER");
    }  
    delay(3000);
  }
  else{
    Serial.println("Connect to server Failed. Reconnecting...");    
    setupWifi(ssid,password);  
  }   
}


