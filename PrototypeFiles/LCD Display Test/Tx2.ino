#include <MPU6050_tockn.h>
#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); // 0x27 là địa chỉ của lcd 16x2

MPU6050 mpu6050(Wire);
int x, y, z;
byte button = 5;
int mang[4];  // mảng có hai phần tử
int mangservo[3];
RF24 radio(7, 10);               // CE, CSN
const uint64_t pipes[3] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL };//Mảng kí tự dạng chuỗi có 6 kí tự

void setup() {
  Serial.begin(9600);
  pinMode(button,INPUT_PULLUP);
  lcd.init(); 
  lcd.backlight();
  lcd.clear();
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  mpu6050.update();
  if (!radio.begin()) {
    Serial.println("Module không khởi động được...!!");
    while (1) {}
  }
  radio.openWritingPipe(pipes[0]);
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(80); 
  radio.setDataRate(RF24_250KBPS); 
  radio.stopListening();
  if (!radio.available()) {
    Serial.println("Chưa kết nối được với RX...!!");
    Serial.println("CHỜ KẾT NỐI.......");
  }
  x = mpu6050.getAngleX();
  y = mpu6050.getAngleY();
  z = mpu6050.getAngleZ();
  lcd.clear();
}

void loop() {
  
  mpu6050.update();
  x = mpu6050.getAngleX();
  y = mpu6050.getAngleY();
  z = mpu6050.getAngleZ();
  int Altx = int(round(x));
  int Alty = int(round(y));
  int Altz = int(round(z));

  if (x>360)
  {
    x=0  ;
  }
  if (y>360)
  {
    y=0  ;
  }
  if (z>360)
  {
    z=0  ;
  }

  if (x<0)
  {
    x=360  ;
  }
  if (y<0)
  {
    y=360  ;
  }
  if (z<0)
  {
    z=360  ;
  }
  
  mang[0] = mpu6050.getAngleX();
  mang[1] = mpu6050.getAngleY();
  mang[2] = mpu6050.getAngleZ();
  mang[3] = digitalRead(button);
  radio.write(&mang, sizeof(mang));
  lcd.setCursor(0, 0);
  lcd.print("X: ");
  lcd.setCursor(2, 0);
  if (Altx < 10 && Altx >= 0){
    lcd.print(Altx);
    lcd.setCursor(3, 0);
    lcd.print("  ");
  } else if (Altx <= -10 && Altx > -100) {
    lcd.print(Altx);
    lcd.setCursor(5, 0);
    lcd.print(" ");
  } else if (Altx > -10 && Altx < 0) {
    lcd.print(Altx);
    lcd.setCursor(4, 0);
    lcd.print(" ");
  } else if (Altx <= -100) {
    lcd.print(Altx);
    lcd.setCursor(6, 0);
    lcd.print(" ");
  } else if (Altx >= 10 && Altx < 100) {
    lcd.print(Altx);
    lcd.setCursor(4, 0);
    lcd.print(" ");
  } else if (Altx >= 100) {
    lcd.print(Altx);
    lcd.setCursor(5, 0);
    lcd.print(" ");
  }
  //print y
  lcd.setCursor(8, 0);
  lcd.print("Y: ");
  lcd.setCursor(10, 0);
  if (Alty < 10 && Alty >= 0){
    lcd.print(Alty);
    lcd.setCursor(11, 0);
    lcd.print("  ");
  } else if (Alty <= -10 && Alty > -100) {
    lcd.print(Alty);
    lcd.setCursor(13, 0);
    lcd.print(" ");
  } else if (Alty > -10 && Alty < 0) {
    lcd.print(Alty);
    lcd.setCursor(12, 0);
    lcd.print(" ");
  } else if (Alty <= -100) {
    lcd.print(Alty);
    lcd.setCursor(14, 0);
    lcd.print(" ");
  } else if (Alty >= 10 && Alty < 100) {
    lcd.print(Alty);
    lcd.setCursor(12, 0);
    lcd.print(" ");
  } else if (Alty >= 100) {
    lcd.print(Alty);
lcd.setCursor(13, 0);
    lcd.print(" ");
  }
  //print z
  lcd.setCursor(0, 1);
  lcd.print("Z: ");
  lcd.setCursor(2, 1);
  if (Altz < 10 && Altz >= 0){
    lcd.print(Altz);
    lcd.setCursor(3, 1);
    lcd.print("  ");
  } else if (Altz <= -10 && Altz > -100) {
    lcd.print(Altz);
    lcd.setCursor(5, 1);
    lcd.print(" ");
  } else if (Altz > -10 && Altz < 0) {
    lcd.print(Altz);
    lcd.setCursor(4, 1);
    lcd.print(" ");
  } else if (Altz <= -100) {
    lcd.print(Altz);
    lcd.setCursor(6, 1);
    lcd.print(" ");
  } else if (Altz >= 10 && Altz < 100) {
    lcd.print(Altz);
    lcd.setCursor(4, 1);
    lcd.print(" ");
  } else if (Altz >= 100) {
    lcd.print(Altz);
    lcd.setCursor(5, 1);
    lcd.print(" ");
  }
  Serial.print("X: ");
  Serial.print(Altx);
  Serial.print("      ");
  Serial.print("Y: ");
  Serial.print(Alty);
  Serial.print("      ");
  Serial.print("Z: ");
  Serial.println(Altz);
}