#include <Servo.h>

/************************************************SETUP SERVO************************************************/
void setupServo(Servo servo,int pin){
  servo.attach(pin);
  servo.write(0);
}

/************************************************OPEN DOOR************************************************/
bool openDoor(Servo servo){
  int pos;
  for ( pos = 0; pos <= 90; pos += 5) {
    servo.write(pos);
    delay(100);
  }
  return true;
}

/************************************************CLOSE DOOR************************************************/
bool closeDoor(Servo servo,bool isOpen){ 
  if(isOpen == true){
    int pos;
    for ( pos = 90; pos >= 0; pos -= 5) {
      servo.write(pos);    
      delay(100);
    }    
  }
  return false;
}
