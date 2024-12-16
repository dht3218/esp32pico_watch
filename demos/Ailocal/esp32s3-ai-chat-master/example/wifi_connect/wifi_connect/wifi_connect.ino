#include <WiFi.h>

const char* ssid = "WiFi名称";
const char* password = "WiFi密码";

void setup() {
  //初始化串口
  Serial.begin(115200);
  delay(10);
    
  // 进行WiFi连接
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  //连接WIFI
  WiFi.begin(ssid, password);
  //等待WIFI连接成功
  while (WiFi.status() != WL_CONNECTED) { //WiFi.status()函数用于获取WiFi连接的状态
    //WL_CONNECTED，即连接状态
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

}

void loop() {
    
}