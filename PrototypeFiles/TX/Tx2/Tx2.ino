/*TX
 * https://maniacbug.github.io/RF24/classRF24.html
 * 
 * VCC - 3.3v
 * GND - GND
 * CSN - 10
 * CE - 7
 * SCK - 13 mặc định SPI
 * MOSI - 11 SPI
 * MISO - 12 SPI
 */
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); // 0x27 là địa chỉ của lcd 16x2

MPU6050 mpu6050(Wire);

int x, y, z;
int mang[3];  // mảng có hai phần tử
int mangservo[3];
RF24 radio(7, 10);               // CE, CSN
const uint64_t pipes[3] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL };//Mảng kí tự dạng chuỗi có 6 kí tự



void setup() {
  Serial.begin(9600);
  lcd.init(); 
  lcd.backlight(); //đèn nền bật
  // cài đặt số cột và số dòng 
  // in logo lên màn hình
  //lcd.print("Robocon");  
  //lcd.setCursor(0, 1);
  // lcd.print("THPT Tran Van On");
  // delay (2500);
  lcd.clear();

  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  mpu6050.update();
  if (!radio.begin()) {
    Serial.println("Module không khởi động được...!!");
    while (1) {}
  }

 
  radio.openWritingPipe(pipes);
  //Lệnh openWritingPipe mặc định là đường truyền 0
  //mở 1 kênh có địa chỉ 12345 trên đường truyền 0
  // kênh này ghi data lên địa chỉ 12345
  radio.setPALevel(RF24_PA_MIN);
  //Cài bộ khuyết địa công suất ở mức MIN, MAX, HIGH, LOW
  radio.setChannel(80);  // 125 kênh từ 0-124; TX v  à RX phải cùng kênh
                         // 2.4GHz ~ 2400Mhz, bước kênh là 1MHz
                         // setchannel(1) => 2401Mhz
                         // Cao nhất là 2525MHz, Tức là 2.525GHz

  radio.setDataRate(RF24_250KBPS);  //Tốc độ truyền dữ liệu trong không khí
                                    //250kbps, 1Mbps hoặc 2Mbps
                                    //250 thấp nhất nhưng truyền xa, 1Mb và 2Mb mạnh nhưng truyền không xa
  /*                                   
   * Tốc độ truyền dữ liệu không khí 2Mbps, băng thông 2MHz bị chiếm dụng nhiều tần số kênh 
   * rộng hơn độ phân giải của cài đặt tần số kênh RF
   * Vì vậy, để đảm bảo các kênh không chồng chéo và giảm kết nối chéo ở chế độ 2Mbps
   * bạn cần giữ khoảng cách 2MHz giữa hai kênh.                                    
   * 
   * A: Xe TX-RX kênh 80, tốc độ truyền là 2Mb 80, 81, 82
   * B: Máy bay TX-RX kênh 83, tốc độ truyền là 250Kb                                    
   */
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
  mang[0] = mpu6050.getAngleX();
  mang[1] = mpu6050.getAngleY();
  mang[2] = mpu6050.getAngleZ();
  // radio.write(&text, sizeof(text));

  radio.write(&mang, sizeof(mang));
  // &: Trả lại địa chỉ của một biến.
  // sizeof: trả về số byte bộ nhớ của một biến
  //hoặc là trả về tổng số byte bộ nhớ của một mản
  lcd.setCursor(0, 0);
  //print x
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