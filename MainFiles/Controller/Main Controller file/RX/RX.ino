/* RX
 * https://maniacbug.github.io/RF24/classRF24.html
 * 
 * VCC - 3.3v
 * GND - GND
 * CSN - 8
 * CE - 7
 * SCK - 13
 * MOSI - 11
 * MISO - 12
 */

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <PCF8574.h>
#include <Arduino.h>
#include <Wire.h>
#define In1	4
#define In2	5
#define In3	2
#define In4	3
#define In6 10
#define In8 9
#define MAX_SPEED 255 //từ 0-255
#define MIN_SPEED 0
#define SERVOMIN  90 //độ dài xung tối thiểu; xung PPM
#define SERVOMAX  600
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver mod_1 = Adafruit_PWMServoDriver(0x40);
PCF8574 pcf8574(0x20);


RF24 radio(7, 8); // CE, CSN
const uint64_t pipes[3] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL };
byte PWM1 = 0;
byte PWM2 = 4;
byte PWM3 = 8;
byte PWM4 = 11;
int alter = 30;
int angleAlt = 2;
byte Altx = 35;
byte Alty = 150;
byte Altz = 20;
int mang[4];
int mangservo[4];

int topulse(int goc) //chuyển góc thành xung
{
  int xung = map(goc, 0, 180, SERVOMIN, SERVOMAX);
  return xung;
}

void setup() 
{
  pcf8574.begin();//
  pinMode(In1, OUTPUT);
	pinMode(In2, OUTPUT);
	pinMode(In3, OUTPUT);
	pinMode(In4, OUTPUT);
  pinMode(In6, OUTPUT);
  pinMode(In8, OUTPUT);
  pcf8574.write(0,LOW);
  pcf8574.write(1,LOW);
  Serial.begin(9600);
  mod_1.begin();
  mod_1.setOscillatorFrequency(27000000);
  mod_1.setPWMFreq(60);
  if (!radio.begin()) 
  {
    Serial.println("Module không khởi động được...!!");
    while (1) {}
  } 
  
  radio.openReadingPipe(1, pipes[0]);
  radio.openReadingPipe(2, pipes[1]);
  //Lệnh openReadingPipe có số đường truyền từ 0-5
  //Nhưng đường 0 đã được dùng cho ghi (mặc định)
  //Vì vậy chỉ dùng 1-5, nếu dùng không sẽ bị chồng lấn
  //Mở 1 kênh có địa chỉ 12345 trên đường truyền 1
  //kênh này chỉ đọc data trên địa chỉ 12345   
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(80);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
  
  if (!radio.available())
  {
    Serial.println("Chưa kết nối được với TX...!!");
    Serial.println("CHỜ KẾT NỐI.......");
  } 
}


void loop() 
{
  if (radio.available()) 
  {
    radio.read(&mang, sizeof(mang));
    radio.read(&mangservo, sizeof(mangservo));
  
  
    Serial.print("X: "); Serial.print(Altx);Serial.print("      ");
    Serial.print("Y: "); Serial.print(Alty);Serial.print("      ");
    Serial.print("Z: "); Serial.print(Altz);Serial.print("      ");
    Serial.print("X 2 : "); Serial.print(mang[0]);Serial.print("      ");
    Serial.print("Y 2 : "); Serial.print(mang[1]);Serial.print("      ");
    Serial.print("Z 2 : "); Serial.print(mang[2]);Serial.print("      ");
    Serial.print("Trang thai nut : ");Serial.println(mangservo[3]);
    
    
  /*
  mangservo là mảng gia tốc dành cho xe, mang là mảng gia tốc diều khiển tay gắp
  mangservo[0]: x xe
  mangservo[1]: y xe
  mangservo[2]: z xe
  mang[0]: x tay gắp
  mang[1]: y tay gắp
  mang[2]: z tay gắp
  */
  if (mang[3] == 1) {
  if (mangservo[0] > alter){
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    pcf8574.write(0,LOW);
    digitalWrite(In6, HIGH);
    pcf8574.write(1,LOW);
    digitalWrite(In8,HIGH);
  } else if (mangservo[0] < alter * -1) {
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    pcf8574.write(0,HIGH);
    digitalWrite(In6, LOW);
    pcf8574.write(1,HIGH);
    digitalWrite(In8,LOW);
  } else if (mangservo[1] > alter ) {
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    pcf8574.write(0,HIGH);
    digitalWrite(In6, LOW);
    pcf8574.write(1,LOW);
    digitalWrite(In8,HIGH);
  } else if ( mangservo[1] < alter * -1 ){
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    pcf8574.write(0,LOW);
    digitalWrite(In6, HIGH);
    pcf8574.write(1,HIGH);
    digitalWrite(In8,LOW);
  } /* else if ( mangservo[2] > alter ) {
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    pcf8574.write(0,LOW);
    digitalWrite(In6, HIGH);
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    pcf8574.write(1,HIGH);
    digitalWrite(In8,LOW);
  } else if ( mangservo[2] < alter * -1) {
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    pcf8574.write(0,HIGH);
    digitalWrite(In6, LOW);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    pcf8574.write(1,LOW);
    digitalWrite(In8,HIGH);
  }*/
  else {
    digitalWrite(In1, LOW);
    digitalWrite(In2, LOW);
    digitalWrite(In3, LOW);
    digitalWrite(In4, LOW);
    pcf8574.write(0,LOW);
    digitalWrite(In6, LOW);
    pcf8574.write(1,LOW);
    digitalWrite(In8,LOW);  
  }

  } else {
    digitalWrite(In1, LOW);
    digitalWrite(In2, LOW);
    digitalWrite(In3, LOW);
    digitalWrite(In4, LOW);
  }

  //  
  if (mang[0] > alter) {
    if (Altx < 90) { Altx += angleAlt;}
    mod_1.setPWM(PWM2, 0, topulse(Altx));
    Serial.print("Duoi thang");
  } else if (mang[0] < alter * -1) {
    if (Altx > 30) { Altx -= angleAlt;}
    mod_1.setPWM(PWM2, 0, topulse(Altx));
    Serial.print("Cong lai");
  }  //
  if (mang[1] > alter) {
    if (Alty < 180) { Alty += angleAlt;}
    mod_1.setPWM(PWM3, 0, topulse(Alty));
    Serial.print("len");
  } else if (mang[1] < alter * -1) {
    if (Alty > 140) { Alty -= angleAlt;}
    mod_1.setPWM(PWM3, 0, topulse(Alty));
    Serial.print("xuong");
  }
  
  
  if ( mang[2] > alter ) {
    if (Altz < 30) { Altz += angleAlt;}
    mod_1.setPWM(PWM1, 0, topulse(Altz));
    Serial.print("trai");
  } else if (mang[2] < alter * -1) {
    if (Altz > 0) { Altz -= angleAlt;}
    mod_1.setPWM(PWM1, 0, topulse(Altz));
    Serial.print("phai");
  }
  
  if ( mang[3] == 1 ) {
    mod_1.setPWM(PWM4, 0, topulse(60));
  } else if (mang[3] != 1) {
    mod_1.setPWM(PWM4, 0, topulse(0));
  }

  }
}
