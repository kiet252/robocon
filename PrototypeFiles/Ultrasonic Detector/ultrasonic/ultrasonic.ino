const int trig = 8; //Khai báo chân trig nối với chân số 8 là hằng số
const int echo = 7; //Khai báo chân echo nối với chân số 7 là hằng số

unsigned long thoigian; //Thời gian là kiểu số nguyên
int khoangcach; //Khoảng cách là kiểu số nguyên

void setup()
{
  Serial.begin(9600); //Mở cổng Serial ở 9600
  pinMode(trig, OUTPUT); //Chân trig xuất tín hiệu
  pinMode(echo, INPUT); //Chân echo nhận tín hiệu
}

void loop()
{
  //Phát xung từ chân trig, có độ rộng là 10ms
  digitalWrite(trig,0); //Tắt chân trig
  delayMicroseconds(2); 
  digitalWrite(trig,1); //bật chân trig để phát xung
  delayMicroseconds(10); //Xung có độ rộng là 10 microsecond
  digitalWrite(trig,0);

  //Chân echo sẽ nhận xung phản xạ lại
  //Và đo độ rộng xung cao ở chân echo
  thoigian = pulseIn (echo, HIGH);
  
  //Tính khoảng cách đến vật thể (Đơn vị đo là cm)
  //Tốc độ của âm thanh trong không khí là 340 m/s, tương đương 29,412 microSeconds/cm,
  //Do thời gian được tính từ lúc phát tín hiệu tới khi sóng âm phản xạ lại,
  //vì vậy phải chia cho 2
  khoangcach = int (thoigian / 2 / 29.412); 

  //In lên Serial kết quả
  delay(500);

}
