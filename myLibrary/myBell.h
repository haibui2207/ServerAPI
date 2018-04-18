/************************************************START BELL************************************************/
void startBell(int pin , int counter){
  if(counter%2 == 0){
    digitalWrite(pin,HIGH);
  }
  else{
    digitalWrite(pin,LOW);
  }
}

/************************************************STOP BELL************************************************/
void stopBell(int pin){
  digitalWrite(pin,HIGH);
}

