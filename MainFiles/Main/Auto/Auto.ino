/* Đây là phần ghi chú trong code
-Nối dây (Wiring):
+Color (Cảm biến màu sắc):
VCC - 3.3V
GND - GND
SCL - SCL
SDA - SDA
S1 jump G
+Ultrasonic (Cảm biến siêu âm):
VCC - 5V
Trig - Digital input 8 (any)
Echo - Digital input 7 (any)
GND - GND
-Tiến độ robot:
+ Dò line: xong
+ Cảm biến màu sắc: xong
+ Siêu âm: xong
+ Tay gấp: chưa
Các variables xuất hiện trong code:
+Cảm biến màu sắc
data[9]
rgb.Red: Độ
rgb.Green
rgb.Blue
rgb.Clear
Lux
CT
+Cảm biến siêu âm
trig = 8;     // chân trig của HC-SR04
echo = 7;     // chân echo của HC-SR04
*/

//Libraries-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <MotorDriver.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_TCS34725.h>
#define uint16_t unsigned int
//Variables--------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Cam bien mau sac
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_4X);
uint16_t r, g, b, c, colorTemp, lux;
//Cam bien sieu am
const int trig = 8;     // chân trig của HC-SR04
const int echo = 7;     // chân echo của HC-SR04
unsigned long duration; // biến đo thời gian
int distance;           // biến lưu khoảng cách
//Do line
int sen[6] = {0};
//Canh tay
Adafruit_PWMServoDriver mod_1 = Adafruit_PWMServoDriver(0x40);
#define SERVOMIN  90 //độ dài xung tối thiểu; xung PPM
#define SERVOMAX  600
/*
PWM1 quyet dinh quay
PWM2 quyet dinh len xuong
PWM3 quyet dinh duoi thang duoi cong
PWM4 queyt dinh gap hoac mo
*/
byte PWM1 = 0;
byte PWM2 = 2;
byte PWM3 = 1;
byte PWM4 = 3;
//Xe
MotorDriver m;
byte Speed = 50;
//Functions---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Cam bien mau sac

/*void iic_read(unsigned char add,unsigned char *data,unsigned char len)
{
  i2c_start_wait(0xb4);
   i2c_write(add);
   i2c_start_wait(0xb5);
   while(len-1)
   {
    *data++=i2c_readAck();
    len--;
    }
    *data=i2c_readNak();
    i2c_stop();
}
void serialEvent() {
  while (Serial.available()) {   
    Re_buf=(unsigned char)Serial.read();
   if (Re_buf=='a')
       sign=0;
    if (Re_buf=='b')    
       sign=1; 
      Re_buf=0; 
  }
} */

//line ngang
bool lineng() {
  if (sen[0] == 0) { return false; }
  if (sen[1] == 0) { return false; } 
  if (sen[2] == 0) { return false; }
  if (sen[3] == 0) { return false; }
  if (sen[4] == 0) { return false; }
  return true;
}

bool linedoc() {
  if (sen[0] == 1) { return false; }
  if (sen[1] == 1) { return false; } 
  if (sen[2] == 0) { return false; }
  if (sen[3] == 1) { return false; }
  if (sen[4] == 1) { return false; }
  return true;
}

bool twolineL() {
  if (sen[0] == 0) { return false; }
  if (sen[1] == 0) { return false; } 
  if (sen[2] == 1) { return false; }
  if (sen[3] == 1) { return false; }
  if (sen[4] == 1) { return false; }
  return true;
}

bool TwolineR() {
  if (sen[0] == 1) { return false; }
  if (sen[1] == 1) { return false; } 
  if (sen[2] == 1) { return false; }
  if (sen[3] == 0) { return false; }
  if (sen[4] == 0) { return false; }
  return true;
}

bool threelineL() {
  if (sen[0] == 0) { return false; }
  if (sen[1] == 0) { return false; } 
  if (sen[2] == 0) { return false; }
  if (sen[3] == 1) { return false; }
  if (sen[4] == 1) { return false; }
  return true;
}

bool threelineR() {
  if (sen[0] == 1) { return false; }
  if (sen[1] == 1) { return false; } 
  if (sen[2] == 0) { return false; }
  if (sen[3] == 0) { return false; }
  if (sen[4] == 0) { return false; }
  return true;
}

bool fourlineL() {
  if (sen[0] == 0) { return false; }
  if (sen[1] == 0) { return false; } 
  if (sen[2] == 0) { return false; }
  if (sen[3] == 0) { return false; }
  if (sen[4] == 1) { return false; }
  return true;
}

bool fourlineR() {
  if (sen[0] == 1) { return false; }
  if (sen[1] == 0) { return false; } 
  if (sen[2] == 0) { return false; }
  if (sen[3] == 0) { return false; }
  if (sen[4] == 0) { return false; }
  return true;
}

bool midL() {
  if (sen[0] == 1) { return false; }
  if (sen[1] == 0) { return false; } 
  if (sen[2] == 0) { return false; }
  if (sen[3] == 1) { return false; }
  if (sen[4] == 1) { return false; }
}

bool midR() {
  if (sen[0] == 1) { return false; }
  if (sen[1] == 1) { return false; } 
  if (sen[2] == 0) { return false; }
  if (sen[3] == 0) { return false; }
  if (sen[4] == 1) { return false; }
}
//xe
void TurnLeft() {
    m.motor(1,BRAKE,Speed);
    m.motor(2,FORWARD,Speed);
    m.motor(3,BRAKE,Speed);
    m.motor(4,BRAKE,Speed);
}
void TurnRight() {
    m.motor(1,BRAKE,Speed);
    m.motor(2,BRAKE,Speed);
    m.motor(3,BRAKE,Speed);
    m.motor(4,FORWARD,Speed);
}
void GoStraight() {
    m.motor(1,FORWARD,Speed);
    m.motor(2,FORWARD,Speed);
    m.motor(3,FORWARD,Speed);
    m.motor(4,FORWARD,Speed);
}


//Canh tay
int topulse(int goc) //chuyển góc thành xung
{
  int xung = map(goc, 0, 180, SERVOMIN, SERVOMAX);
  return xung;
}
/*
PWM1 quyet dinh quay
PWM2 quyet dinh len xuong
PWM3 quyet dinh duoi thang duoi cong
PWM4 queyt dinh gap hoac mo
*/
void ArmTurnLeft() {
  mod_1.setPWM(PWM1, 0, topulse(90));
  for (int i = 90; i<=120; i+=2) {
    delay(50);
    mod_1.setPWM(PWM1, 0, topulse(i));    
  }
}

void ArmTurnRight() {
  mod_1.setPWM(PWM1, 0, topulse(90));
  for (int i = 90; i>=60; i-=2) {
    delay(50);
    mod_1.setPWM(PWM1, 0, topulse(i));    
  }
}

void fold() {
    mod_1.setPWM(PWM4, 0, topulse(0)); 
    delay(1000);
    mod_1.setPWM(PWM4, 0, topulse(60));
}

void unfold() {
    mod_1.setPWM(PWM4, 0, topulse(60));
    delay(1000);
    mod_1.setPWM(PWM4, 0, topulse(0));
}
//Setups-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup() {
//Setup màu sắc
    sen[0] = digitalRead(22);
    sen[1] = digitalRead(24);
    sen[2] = digitalRead(26);
    sen[3] = digitalRead(28);
    sen[4] = digitalRead(30);
    sen[5] = digitalRead(32);
    Serial.print(sen[0]);
    Serial.print(sen[1]);
    Serial.print(sen[2]);
    Serial.print(sen[3]);
    Serial.print(sen[4]);
    Serial.print(sen[5]);
    Serial.begin(9600);
    //i2c_init();
//Setup siêu âm 
    pinMode(trig,OUTPUT);   // chân trig sẽ phát tín hiệu
    pinMode(echo,INPUT);    // chân echo sẽ nhận tín hiệ
//Setup pin xe
//Setup pin do line
    pinMode(22,INPUT);
    pinMode(24,INPUT);
    pinMode(26,INPUT);
    pinMode(28,INPUT);
    pinMode(30,INPUT);
    pinMode(32,INPUT);    
//setup canh tay
    mod_1.begin();
    mod_1.setOscillatorFrequency(27000000);
    mod_1.setPWMFreq(60);
}
//Code chính (Việc mà robot phải làm liên tục)---------------------------------------------------------------------------------------------------------------------------------
void loop() {
  //Dò line
  sen[5] = digitalRead(32);
  while (lineng() == false && sen[5] == 0) {
    sen[0] = digitalRead(22);
    sen[1] = digitalRead(24);
    sen[2] = digitalRead(26);
    sen[3] = digitalRead(28);
    sen[4] = digitalRead(30);
    sen[5] = digitalRead(32);
    Serial.print(sen[0]);
    Serial.print(sen[1]);
    Serial.print(sen[2]);
    Serial.print(sen[3]);
    Serial.print(sen[4]);
    Serial.print(sen[5]);
    if (threelineL() || twolineL() || midL()){
      TurnLeft();
    } else if (threelineR() || TwolineR() || midR()) {
      TurnRight();
    } else if (linedoc()) {
      GoStraight();
    }
  }

  while (not (r>g && r>b && r<c && lux>10 && lux<100) && not (r=g && r>b && g>b && lux>10 && lux<100) ) {
    //Cam bien mau
    tcs.getRawData(&r, &g, &b, &c);
    
    colorTemp = tcs.calculateColorTemperature(r, g, b); //Nhiệt độ màu theo thang đo Kelvin
    
    lux = tcs.calculateLux(r, g, b); //Độ rọi soi, cường độ sáng
    GoStraight();
  }
 //Siêu âm
    
  /* Phát xung từ chân trig */
  digitalWrite(trig,0);   // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trig,1);   // phát xung từ chân trig
  delayMicroseconds(5);   // xung có độ dài 5 microSeconds
  digitalWrite(trig,0);   // tắt chân trig
  
  /* Tính toán thời gian */
  // Đo độ rộng xung HIGH ở chân echo. 
  duration = pulseIn(echo,HIGH);  
  // Tính khoảng cách đến vật.
  distance = int(duration/2/29.412);
  if (distance <= 10 ) {
    if (r>g && r>b && r<c && lux>10 && lux<100) {
       ArmTurnLeft();
       fold();
       ArmTurnRight();
       unfold();
    } else if (r=g && r>b && g>b && lux>10 && lux<100) {
       ArmTurnRight();
       fold();
       ArmTurnLeft();
       unfold();
    }

  }

  /* In kết quả ra Serial Monitor */
  /*Serial.print(distance);
  Serial.println("cm");
  delay(200);*/
  //tay gấp
}
