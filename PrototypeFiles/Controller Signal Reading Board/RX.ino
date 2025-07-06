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
// #include <PCF8574.h>
#define In1	4
#define In2	5
#define In3	2
#define In4	3
#define In6 10
#define In8 9
#define MAX_SPEED 255 //từ 0-255
#define MIN_SPEED 0

// PCF8574 pcf8574(0x20);


RF24 radio(7, 8); // CE, CSN
const uint64_t pipes[3] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL };


int mang[6];


void setup() 
{
  // pcf8574.begin();//
  pinMode(In1, OUTPUT);
	pinMode(In2, OUTPUT);
	pinMode(In3, OUTPUT);
	pinMode(In4, OUTPUT);
  pinMode(In6, OUTPUT);
  pinMode(In8, OUTPUT);
  // pcf8574.write(0,LOW);
  // pcf8574.write(1,LOW);
  Serial.begin(9600);
  
  if (!radio.begin()) 
  {
    Serial.println("Module không khởi động được...!!");
    while (1) {}
  } 
  
radio.openReadingPipe(1, pipes[1]);
radio.openReadingPipe(2, pipes[2]);
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
    // char nhan[30] = ""; //30 là số kí tự trong mảng
    // radio.read(&nhan, sizeof(nhan));
    //radio.read(&mang, sizeof(mang));
    //radio.read(&mang2, sizeof(mang2));

    radio.read(&mang, sizeof(mang));


    Serial.print("X: "); Serial.print(mang[0]);Serial.print("      ");
    Serial.print("Y: "); Serial.print(mang[1]);Serial.print("      ");
    Serial.print("Z: "); Serial.print(mang[2]);Serial.print("      ");
    Serial.print("X 2 : "); Serial.print(mang[3]);Serial.print("      ");
    Serial.print("Y 2 : "); Serial.print(mang[4]);Serial.print("      ");
    Serial.print("Z 2 : "); Serial.println(mang[5]);
    
    

  if (mang[0] > 40){
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    // pcf8574.write(0,LOW);
    digitalWrite(In6, HIGH);
    // pcf8574.write(1,LOW);
    digitalWrite(In8,HIGH);
      
  } else if (mang[0] < -40) {
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    // pcf8574.write(0,HIGH);
    digitalWrite(In6, LOW);
    // pcf8574.write(1,HIGH);
    digitalWrite(In8,LOW);
  } else if (mang[1] > 40 ) 
  {
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    // pcf8574.write(0,HIGH);
    digitalWrite(In6, LOW);
    // pcf8574.write(1,LOW);
    digitalWrite(In8,HIGH);
  } else if ( mang[1] < - 40 ){
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    // pcf8574.write(0,LOW);
    digitalWrite(In6, HIGH);
    // pcf8574.write(1,HIGH);
    digitalWrite(In8,LOW);
  } else if ( mang[2] > 40 ) {
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
    // pcf8574.write(0,LOW);
    digitalWrite(In6, HIGH);
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    // pcf8574.write(1,HIGH);
    digitalWrite(In8,LOW);
  } else if ( mang[2] < -40 ) {
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    // pcf8574.write(0,HIGH);
    digitalWrite(In6, LOW);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    // pcf8574.write(1,LOW);
    digitalWrite(In8,HIGH);
  }
  else {
    digitalWrite(In1, LOW);
    digitalWrite(In2, LOW);
    digitalWrite(In3, LOW);
    digitalWrite(In4, LOW);
    // pcf8574.write(0,LOW);
    digitalWrite(In6, LOW);
    // pcf8574.write(1,LOW);
    digitalWrite(In8,LOW);  
  }
  /*
  if (mangservo[0] > alter) {
    delay(100);
    mod_1.setPWM(0, 0, topulse(0));
    delay(100);
    mod_1.setPWM(0, 0, topulse(90));
    delay(100);
    mod_1.setPWM(0, 0, topulse(180));
    delay(100);
  } else if (mangservo[0] < alter * -1) {
    delay(100);
    mod_1.setPWM(0, 0, topulse(180));
    delay(100);
    mod_1.setPWM(0, 0, topulse(90));
    delay(100);
    mod_1.setPWM(0, 0, topulse(0));
    delay(100);
  } else if (mangservo[1] > alter ) {
    delay(100);
    mod_1.setPWM(1, 0, topulse(0));
    delay(100);
    mod_1.setPWM(1, 0, topulse(90));
    delay(100);
    mod_1.setPWM(1, 0, topulse(180));
    delay(100);
  } else if ( mangservo[1] < alter * -1 ) {
    delay(100);
    mod_1.setPWM(1, 0, topulse(180));
    delay(100);
    mod_1.setPWM(1, 0, topulse(90));
    delay(100);
    mod_1.setPWM(1, 0, topulse(0));
    delay(100);
  }  else if ( mangservo[2] > alter ) {
    delay(100);
    mod_1.setPWM(2, 0, topulse(0));
    delay(100);
    mod_1.setPWM(2, 0, topulse(90));
    delay(100);
    mod_1.setPWM(2, 0, topulse(180));
    delay(100);
  } else if ( mang[2] < alter * -1 ) {
    delay(100);
    mod_1.setPWM(2, 0, topulse(180));
    delay(100);
    mod_1.setPWM(2, 0, topulse(90));
    delay(100);
    mod_1.setPWM(2, 0, topulse(0));
    delay(100);
  } else {
    mod_1.setPWM(0, 0, topulse(0));
    mod_1.setPWM(1, 0, topulse(0));
    mod_1.setPWM(2, 0, topulse(0));
  }*/

  }
}