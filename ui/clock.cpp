
#include "clock.h"
#include <Wire.h>
#include <RTClib.h>
#include <string>
using std::string;
#include "esp_task_wdt.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
PCF8563 rtc;
TaskHandle_t Rtc_task;
char* dayOfWeekName[] = {
  "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"
};
int getWeekday(int year, int month, int day) {
  // 计算日期的星期几
  int a = (14 - month) / 12;
  int y = year - a;
  int m = month + 12 * a - 2;
  int d = (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;

  // 将数字转换成星期几
  switch (d) {
    case 0:
      return 7;  // 周日
      break;
    case 1:
      return 1;  // 周一
      break;
    case 2:
      return 2;  // 周二
      break;
    case 3:
      return 3;  // 周三
      break;
    case 4:
      return 4;  // 周四
      break;
    case 5:
      return 5;  // 周五
      break;
    case 6:
      return 6;  // 周六
      break;
    default:
      return -1;  // 错误
  }
}
void RtcSetup0() {
  rtc.begin();

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    //rtc.adjust(DateTime(__DATE__, __TIME__));
    DateTime now = DateTime(2024, 11, 3, 12, 31, 56);
    rtc.adjust(now);
  }
}
void RtcSetup() {
  rtc.begin();
  DateTime now = DateTime(2024, 11, 3, 12, 31, 56);
  rtc.adjust(now);
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    //rtc.adjust(DateTime(__DATE__, __TIME__));
  }
}
string getT(int& H, int& M, int& S) {  //获取本地时间
  //RTC.begin();
  DateTime nowtime = rtc.now();
  //RTC.read(tm1);
  H = nowtime.hour();
  M = nowtime.minute();
  S = nowtime.second();

  string today = std::__cxx11::to_string(nowtime.year()) + "-" + std::__cxx11::to_string(nowtime.month()) + "-" + std::__cxx11::to_string(nowtime.day()) + " " + (dayOfWeekName[nowtime.dayOfTheWeek()]);
  Serial.print("Thour");
  Serial.print(H);
  Serial.print("Tmin");
  Serial.print(M);
  Serial.print("Tsec");
  Serial.print(S);
  Serial.print("--------------");
  Serial.print(nowtime.year());
  Serial.print(nowtime.month());
  Serial.print(nowtime.day());
  Serial.println("--------------");
  return today;
}


/**
 * 获取本地时间并将其转换为字符串格式。
 * 
 * 该函数首先获取当前时间，然后将其转换为字符串格式，
 * 包括年、月、日、星期几、时、分、秒。
 * 
 * @param H 指向小时的整数指针，用于存储获取到的小时数。
 * @param M 指向分钟的整数指针，用于存储获取到的分钟数。
 * @param S 指向秒的整数指针，用于存储获取到的秒数。
 * @return 返回包含本地时间的字符串。
 */
const char* getTc(int* H, int* M, int* S) {  //获取本地时间
  //RTC.begin();
  DateTime nowtime = rtc.now();
  //RTC.read(tm1);
  *H = nowtime.hour();
  *M = nowtime.minute();
  *S = nowtime.second();

  string today = std::__cxx11::to_string(nowtime.year()) + "-" + std::__cxx11::to_string(nowtime.month()) + "-" + std::__cxx11::to_string(nowtime.day()) + " " + (dayOfWeekName[nowtime.dayOfTheWeek()]);
  Serial.print("Thour");
  Serial.print(*H);
  Serial.print("Tmin");
  Serial.print(*M);
  Serial.print("Tsec");
  Serial.print(*S);
  Serial.print("--------------");
  Serial.print(nowtime.year());
  Serial.print(nowtime.month());
  Serial.print(nowtime.day());
  Serial.println("--------------");
  return today.c_str();
}
void getDc(int* Y, int* M, int* D) {  //获取本地时间
  //RTC.begin();
  DateTime nowtime = rtc.now();
  //RTC.read(tm1);
  *Y = nowtime.year();
  *M = nowtime.month();
  *D = nowtime.day();
  Serial.print("--------------");
  Serial.print(nowtime.year());
  Serial.print(nowtime.month());
  Serial.print(nowtime.day());
  Serial.println("--------------");
  return;
}



void RtcgetTwifi() {  //联网校时
  String TTime = "";
  // Stream& input;
  if (WiFi.status() == WL_CONNECTED) /*如果有网络就联网*/ {
    HTTPClient http;
    http.begin("http://quan.suning.com/getSysTime.do");  //Specify the URL
    int tryt = 0;
    while (tryt < 3) {
      int httpCode = http.GET();  //Make the request
      if (httpCode > 0) {         //Check for the returning code
        TTime = http.getString();
        Serial.println(httpCode);
        Serial.println(TTime);
        break;
      } else {
        Serial.println("Error on HTTP request");
        tryt++;
      }
    }
    // Stream& input;

    StaticJsonDocument<96> doc;

    DeserializationError error = deserializeJson(doc, TTime);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }
    const char* sysTime1 = doc["sysTime1"];  // "20230907233256"
    String timeString(sysTime1);
    // 提取年份
    int Tyear = atoi(timeString.substring(0, 4).c_str());

    // 提取月份
    int Tmon = atoi(timeString.substring(4, 6).c_str());

    // 提取日期
    int Tday = atoi(timeString.substring(6, 8).c_str());

    // 提取小时
    int Thour = atoi(timeString.substring(8, 10).c_str());

    // 提取分钟
    int Tmin = atoi(timeString.substring(10, 12).c_str());

    // 提取秒钟
    int Tsec = atoi(timeString.substring(12, 14).c_str());
    Serial.println(Tyear);
    Serial.println(Tmon);
    Serial.println(Tday);
    Serial.println(Thour);
    Serial.println(Tmin);
    Serial.println(Tsec);
    // setTime(Thour, Tmin, Tsec, Tday, Tmon, Tyear);
    DateTime now = DateTime(Tyear, Tmon, Tday, Thour, Tmin, Tsec);
    rtc.adjust(now);
    //setAlarm(alTime.aMin, alTime.aHour);
  }
}
void RtcSetTime(int Hour0, int Hour1, int Min0, int Min1) {
  DateTime now = rtc.now();
  int setH = Hour0 * 10 + Hour1;
  int setM = Min0 * 10 + Min1;
  now = DateTime(now.year(), now.month(), now.day(), setH, setM, 0);
  rtc.adjust(now);
}




int THour;
int TMin;
int TSec;

void Rtctask(void* arg) {
  while (1) {
    string today = getT(THour, TMin, TSec);
    const char* timeprt = today.c_str();
    lv_label_set_text(ui_Label3, timeprt);
    string temptime = (THour < 10) ? "0" + std::to_string(THour) : std::to_string(THour);
    timeprt = temptime.c_str();
    lv_label_set_text(ui_HOUR, timeprt);
    temptime = (TMin < 10) ? "0" + std::to_string(TMin) : std::to_string(TMin);
    timeprt = temptime.c_str();
    lv_label_set_text(ui_MIN, timeprt);
    vTaskDelay(500);
  }
}

void Rtctaskcreate() {
  xTaskCreatePinnedToCore(Rtctask, "Rtc_task", 4096, NULL, 2, &Rtc_task, 0);
}
void Rtctaskdelete() {
  if (Rtc_task != NULL) {
    vTaskDelete(Rtc_task);
    Rtc_task = NULL;
  }
}
