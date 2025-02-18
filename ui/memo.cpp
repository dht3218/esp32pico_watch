#include "ui.h"
#include "memo.h"
#include <EEPROM.h>
#include <Arduino.h>
#include "freertos/FreeRTOS.h"  // 包含 FreeRTOS 核心库
#include "freertos/task.h"      // 包含任务管理库
// 定义Air700E模块的串口引脚
#define RXD2 19
#define TXD2 21

String reminder[5];

// 巴法云的API地址和参数
String UID = "7eb1ac59940547489d7a779e2111a151";
String TOPIC = "message";  //主题名字，可在控制台新建
int calculateCIPSENDLength(String uid, String topic) {
  String data = "cmd=9&uid=" + uid + "&topic=" + topic;
  return data.length();
}
void DecodeReminder(String TcpClient_Buff) {
  int topicIndex = TcpClient_Buff.indexOf("&topic=") + 7;  //c语言字符串查找，查找&topic=位置，并移动7位，不懂的可百度c语言字符串查找
  int msgIndex = TcpClient_Buff.indexOf("&msg=");          //c语言字符串查找，查找&msg=位置
  //getTopic = TcpClient_Buff.substring(topicIndex, msgIndex);  //c语言字符串截取，截取到topic,不懂的可百度c语言字符串截取
  String getMsg = TcpClient_Buff.substring(msgIndex + 5);  //c语言字符串截取，截取到消息
  //Serial.print("topic:------");
  //Serial.println(getTopic);  //打印截取到的主题值
  ///Serial.print("msg:--------");
  Serial.println(getMsg);  //打印截取到的消息值


  int rmdlength[5];
  int position[6];

  position[0] = getMsg.indexOf("*1*");  //根据*1*截取五段备忘
  position[1] = getMsg.indexOf("*2*");
  position[2] = getMsg.indexOf("*3*");
  position[3] = getMsg.indexOf("*4*");
  position[4] = getMsg.indexOf("*5*");
  position[5] = getMsg.indexOf("*6*");

  for (int i = 0; i < 5; i++) {
    rmdlength[i] = position[i + 1] - position[i] - 2;
  }
  for (int i = 0; i < 5; i++) {

    reminder[i] = getMsg.substring(position[i] + 3, position[i + 1]);
    reminderC[i] = reminder[i].c_str();
    int index = 100 * i;
    EEPROM.writeString(200 + index, reminder[i]);

    Serial.println(reminder[i]);
  }
  EEPROM.commit();
}


void getReminder() {
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  for (int i = 0; i < 5; i++) Serial2.println("AT+CGATT=?\r");
  vTaskDelay(200);
  Serial2.println("AT+CFUN=1\r");
  Serial2.println("AT+CFUN=1\r");
  for (int i = 0; i < 200; i++) {
    String res = Serial2.readString();
    Serial.println(res);
    if (res.indexOf("/") != -1) {
      Serial.println("break");
      break;
    } else continue;
  }
  Serial2.println("AT+CGATT=1\r");
  Serial2.println("AT+CGATT=1\r");

  Serial2.println("AT+CIPSHUT\r");
  String response = "";
  int cnt = 0;
  while (1) {
    String res = Serial2.readString();
    Serial.println(res);
    if (res.indexOf("SHUT OK") != -1) {
      Serial.println("break");
      break;
    } else continue;
  }

  int slength = calculateCIPSENDLength(UID, TOPIC);
  Serial2.println("AT+CIPSTART=\"TCP\",\"bemfa.com\",8344\r");
  Serial2.println("AT+CIPSTART=\"TCP\",\"bemfa.com\",8344\r");
  for (int i = 0; i < 200; i++) {
    String res = Serial2.readString();
    Serial.println(res);
    if (res.indexOf("CONNECT OK") != -1) break;
    else continue;
  }

  // 发送 AT+CIPSEND 命令
  Serial2.print("AT+CIPSEND=");
  Serial2.println(slength);
  for (int i = 0; i < 200; i++) {
    String res = Serial2.readString();
    Serial.println(res);
    if (res.indexOf(">") != -1) break;
    else continue;
  }

  // 发送实际数据
  Serial2.print("cmd=9&uid=");
  Serial2.print(UID);
  Serial2.print("&topic=");
  Serial2.print(TOPIC);
  vTaskDelay(100);  // 等待模块响应
  String Reminderget = Serial2.readString();
  DecodeReminder(Reminderget);

  for (int i = 0; i < 2; i++) {
    Serial2.println("AT+CSCLK=2\r");
    delay(100);
    while (Serial2.available()) {
      //Serial.write(".");
      Serial.write(Serial2.read());
    }
  }

  for (int i = 0; i < 2; i++) {
    Serial2.println("AT+CFUN=4,0\r");
    delay(100);
    while (Serial2.available()) {
      //Serial.write(".");
      Serial.write(Serial2.read());
    }
  }
}
void getReminderfromEEPROM() {
  for (int i = 0; i < 5; i++) {
    int index = 100 * i;
    String reminder = EEPROM.readString(200 + index);
    reminderC[i] = reminder.c_str();
    Serial.println(reminderC[i]);
  }
}