#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver mod_1 = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN  90 //độ dài xung tối thiểu; xung PPM
#define SERVOMAX  600

int topulse(int goc) //chuyển góc thành xung
{
  int xung = map(goc, 0, 180, SERVOMIN, SERVOMAX);
  return xung;
}

void setup() 
{
  Serial.begin(115200);

  mod_1.begin();
  mod_1.setOscillatorFrequency(27000000);
  mod_1.setPWMFreq(60);
}

void loop() 
{
  /*for (int i = 0; i<=130; i+=10) {
    delay(250);
    mod_1.setPWM(4, 0, topulse(i));    
  }
  for (int i = 130; i>=0; i-=10) {
    delay(250);
    mod_1.setPWM(4, 0, topulse(i));    
  }*/
  /*for (int i = 0; i<=130; i+=10) {
    delay(250);
    mod_1.setPWM(2, 0, topulse(i));    
  }*/
  /*delay(1000);
  for (int i = 60; i<=180; i+=2) {
    delay(100);
    mod_1.setPWM(4, 0, topulse(i));    
  }
  for (int i = 180; i>=0; i-=2) {
    delay(100);
    mod_1.setPWM(0, 0, topulse(i));    
  }
  for (int i = 0; i<=180; i+=2) {
    delay(100);
    mod_1.setPWM(8, 0, topulse(i));    
  }  
  for (int i = 60; i<=180; i+=2) {
    delay(100);
    mod_1.setPWM(11, 0, topulse(i));    
  }
  for (int i = 180; i>=60; i-=2) {
    delay(100);
    mod_1.setPWM(11, 0, topulse(i));    
  }
  for (int i = 180; i>=0; i-=2) {
    delay(100);
    mod_1.setPWM(8, 0, topulse(i));    
  } 
  for (int i = 0; i>=180; i+=2) {
    delay(100);
    mod_1.setPWM(0, 0, topulse(i));    
  }
  for (int i = 180; i>=60; i-=2) {
    delay(100);
    mod_1.setPWM(4, 0, topulse(i));    
  }*/
  
  for (int i = 60; i<=180; i+=2) {
    delay(100);
    mod_1.setPWM(0, 0, topulse(i));    
  }
  for (int i = 180; i>=60; i-=2) {
    delay(100);
    mod_1.setPWM(0, 0, topulse(i));    
  }
  // 0- tay; 1 - len xuong; 2- gan xa
}