#define RXD2 19
#define TXD2 21
#include <esp_sleep.h>
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
  for(int i=0;i<5;i++){
       Serial2.println("AT+CSCLK=2\r");
   delay(100);
     while (Serial2.available()) {
    //Serial.write(".");
    Serial.write(Serial2.read());
  }
  }
  for(int i=0;i<5;i++){
       Serial2.println("AT+CFUN=4,0\r");
   delay(100);
     while (Serial2.available()) {
    //Serial.write(".");
    Serial.write(Serial2.read());
  }
  }
   
   
   
   esp_light_sleep_start();
   Serial.println("Loopback program started");delay(500);
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

  for(int i=0;i<10;i++){
       Serial2.println("AT+CSCLK=0\r");
   delay(100);
     while (Serial2.available()) {
    //Serial.write(".");
    Serial.write(Serial2.read());
  }
  }
  }
}