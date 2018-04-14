#include <Servo.h>

int pos = 0;

/************************************************SETUP SERVO************************************************/
void setupServo(Servo servo,int pin){
  servo.attach(pin);
}

/************************************************START SERVO************************************************/
void startServo(Servo servo){
  for ( pos = 0; pos <= 180; pos += 5) {
    servo.write(pos);
    Serial.print("Pos= ");
    Serial.print(pos);
    Serial.println();
    delay(100);
  }
  for ( pos = 180; pos >= 0; pos -= 5) {
    servo.write(pos);
    Serial.print("Pos= ");
    Serial.print(pos);
    Serial.println();
    delay(100);
  }
}
