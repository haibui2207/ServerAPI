#include <ArduinoJson.h>
/*
 Bao gồm 4 hàm như sau : 
 void displayStringAsJson(String) 
 void displayStringAsJsonArray(String)
 JsonObject& convertStringToJson(String)
 JsonObject& getIndexAtJsonArray(String data , int index)
 */

String httpGET = "[{\"pin\":1,\"state\":1},{\"pin\":2,\"state\":1},{\"pin\":3,\"state\":1},{\"pin\":4,\"state\":1},{\"pin\":5,\"state\":1},{\"pin\":6,\"state\":0}]";
String httpGET2 = "{\"pin\":1,\"state\":1}";
      
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);    
  
//  displayStringAsJsonArray(httpGET);
//  displayStringAsJson(httpGET2);

  JsonObject& a = convertStringToJson(httpGET2);
  a.prettyPrintTo(Serial);
  Serial.println();

  int index = 5;
  JsonObject& b = getIndexAtJsonArray(httpGET,index);
  b.prettyPrintTo(Serial);
  Serial.println();
}

void displayStringAsJson(String data){
  int len = data.length() + 1;
  char buf[len];
  data.toCharArray(buf, len);  
  
  const size_t bufferSize = JSON_ARRAY_SIZE(20) + 20*JSON_OBJECT_SIZE(2);
  DynamicJsonBuffer jsonBuffer(bufferSize);
  JsonObject& obj = jsonBuffer.parseObject(data);  
  //check parse
  if (!obj.success()) 
    Serial.println("parseObject() failed");
  else
    Serial.println("parseObject() successed");
    
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
  if (!root.success()) 
    Serial.println("parseObject() failed");
  else
    Serial.println("parseObject() successed");
  
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
  if (!obj.success()) 
    Serial.println("parseObject() failed");
  else
    Serial.println("parseObject() successed");
    
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
  if (!root.success()) 
    Serial.println("parseObject() failed");
  else
    Serial.println("parseObject() successed");  
    
  JsonObject& obj = root[index]; 
  
  return obj;
}

void loop() {
  // put your main code here, to run repeatedly:

}
