#include <Servo.h>

int servo = 9;
int goc; // create servo object to control a servo
Servo myservo1;

void setup() {
  //myservo1.attach(servo);
  myservo1.attach(8,600,2300);  // (pin, min, max
}

void loop() {
  goc = myservo1.read();
  /*myservo1.write(0);  // tell servo to go to a particular angle
  delay(500);*/Serial.print(goc);
    myservo1.write(0);
    delay(1000);
    myservo1.write(60);
    delay(5000);
}