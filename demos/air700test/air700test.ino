#define RXD2 19
#define TXD2 21
#include <esp_sleep.h>
void getT4G() {
  Serial2.println("AT+CIPGSMLOC=2,1\r");
  String response = "";
  while (!Serial2.available()) delay(10);
  Serial.println("AT+CIPGSMLOC=2,1\r");
  while (Serial2.available()) {
    //char c = Serial2.readString();
    // Serial.write(c);  // 将收到的数据打印到主串口
    response = Serial2.readString();
    //
    // if (c == '\r') {

    //   // 检查是否收到完整的响应
    //   //String response = Serial.readStringUntil('\n');
    if (response.length() > 20) {
      // 解析时间信息
      String timeString = response.substring(16, 35);  // 提取时间部分
      Serial.println(timeString);
      int Tyear = atoi(timeString.substring(0, 4).c_str());
      int Tmon = atoi(timeString.substring(5, 7).c_str());
      int Tday = atoi(timeString.substring(8, 10).c_str());
      int Thour = atoi(timeString.substring(11, 13).c_str());
      int Tmin = atoi(timeString.substring(14, 16).c_str());
      int Tsec = atoi(timeString.substring(17, 19).c_str());

      // 打印解析结果
      Serial.println(Tyear);
      Serial.println(Tmon);
      Serial.println(Tday);
      Serial.println(Thour);
      Serial.println(Tmin);
      Serial.println(Tsec);

      //     // // 调整RTC模块
      //     // DateTime now = DateTime(Tyear, Tmon, Tday, Thour, Tmin, Tsec);
      //     // rtc.adjust(now);  // 假设你已经初始化了RTC模块
    }
  }
}
void setup() {

  pinMode(35, INPUT_PULLUP);
  gpio_wakeup_enable(GPIO_NUM_35, GPIO_INTR_LOW_LEVEL);  // 使用INT_PIN 34作为中断引脚，低电平触发中断
  esp_sleep_enable_gpio_wakeup();

  //   Serial.println("Loopback wakeup");
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  delay(1000);

  delay(1000);
  Serial2.println("AT+IPR=9600\r");

  for (int i = 0; i < 5; i++) {
    Serial2.println("AT+CFUN=1\r");
    delay(100);
    while (Serial2.available()) {
      //Serial.write(".");
      Serial.write(Serial2.read());
    }
  }
  for (int i = 0; i < 5; i++) {
    Serial2.println("AT+CSCLK=2\r");
    delay(100);
    while (Serial2.available()) {
      //Serial.write(".");
      Serial.write(Serial2.read());
    }
  }
  for (int i = 0; i < 2; i++) {
    Serial2.println("ATE0\r");
    delay(100);
    while (Serial2.available()) {
      //Serial.write(".");
      Serial.write(Serial2.read());
    }
  }
getT4G();
  // Serial2.println("AT+CIPGSMLOC=2,1\r");
  // String response = "";
  // while (!Serial2.available()) delay(10);
  // Serial.println("AT+CIPGSMLOC=2,1\r");
  // while (Serial2.available()) {
  //   //char c = Serial2.readString();
  //   // Serial.write(c);  // 将收到的数据打印到主串口
  //   response = Serial2.readString();
  //   //
  //   // if (c == '\r') {

  //   //   // 检查是否收到完整的响应
  //   //   //String response = Serial.readStringUntil('\n');
  //   if (response.length() > 20) {
  //     // 解析时间信息
  //     String timeString = response.substring(16, 35);  // 提取时间部分
  //     Serial.println(timeString);
  //     int Tyear = atoi(timeString.substring(0, 4).c_str());
  //     int Tmon = atoi(timeString.substring(5, 7).c_str());
  //     int Tday = atoi(timeString.substring(8, 10).c_str());
  //     int Thour = atoi(timeString.substring(11, 13).c_str());
  //     int Tmin = atoi(timeString.substring(14, 16).c_str());
  //     int Tsec = atoi(timeString.substring(17, 19).c_str());

  //     // 打印解析结果
  //     Serial.println(Tyear);
  //     Serial.println(Tmon);
  //     Serial.println(Tday);
  //     Serial.println(Thour);
  //     Serial.println(Tmin);
  //     Serial.println(Tsec);

  //     //     // // 调整RTC模块
  //     //     // DateTime now = DateTime(Tyear, Tmon, Tday, Thour, Tmin, Tsec);
  //     //     // rtc.adjust(now);  // 假设你已经初始化了RTC模块
  //   }

  //   //   for(int i=0;i<5;i++){
  //   //      Serial2.println("AT+CFUN=4,0\r");
  //   //  delay(100);
  //   //    while (Serial2.available()) {
  //   //   //Serial.write(".");
  //   //   Serial.write(Serial2.read());
  //   // }
  //   // }
  // }
  // //esp_light_sleep_start();
  // Serial.println("Loopback program started");
  // delay(500);
}
String a = "";
void loop() {
  while (Serial.available()) {
    a = Serial.readString();
    //Serial.write(".");
    Serial.println(a);
    a += "\r";
    Serial2.println(a);
    a = "";
  }

  //Serial2.write("@config@baund@115200###");
  delay(10);
  while (Serial2.available()) {
    //Serial.write(".");
    Serial.write(Serial2.read());
  }
  // delay(1000);

  if (digitalRead(35) == 0) {

    for (int i = 0; i < 10; i++) {
      Serial2.println("AT+CSCLK=0\r");
      delay(100);
      while (Serial2.available()) {
        //Serial.write(".");
        Serial.write(Serial2.read());
      }
    }
  }
}
