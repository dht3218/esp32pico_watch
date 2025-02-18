
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
int getDaysInMonth(int year, int month) {
  // 返回指定年月的天数
  int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  if (month == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) {
    return 29;  // 闰年2月有29天
  }
  return daysInMonth[month - 1];
}
void getT4G() {
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
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
  vTaskDelay(200);
  //for (int i = 0; i < 5; i++) {
  Serial2.println("AT+CIPGSMLOC=2,1\r");
  Serial2.println("AT+CIPGSMLOC=2,1\r");
  String response = "";
  String timeString = "";
  int cnt = 0;
  int state = 0;

  while (1) {
    cnt += 1;
    response = Serial2.readString();
    Serial.println(response);
    //delay(10);
    if (response.indexOf("/") != -1 && response.indexOf("+NITZ: ") != -1) {
      state = 1;
      timeString = response.substring((response.indexOf("+NITZ: ") + 7), (response.indexOf("+NITZ: ") + 7 + 19));
      Serial.println("break0");
      break;
    } else if (response.indexOf("/") != -1 && response.indexOf("+CIPGSMLOC: ") != -1) {
      state = 2;
      timeString = re  sponse.substring((response.indexOf("+CIPGSMLOC: ") + 14), (response.indexOf("+CIPGSMLOC: ") + 14 + 19));
      Serial.println("break1");
      break;
    } else {
      if (cnt >= 10) {
        Serial.println("break2");
        break;
      }
      continue;
    }
  }

  //Serial.println("AT+CIPGSMLOC=2,1\r");
  //while (Serial2.available()) {
  //response = Serial2.readString();
  if (response.length() > 16) {
    // 解析时间信息
    //String timeString = response.substring(8, 27);  // 提取时间部分
    Serial.print("timeString");
    Serial.println(timeString);
    int Tyear = atoi(timeString.substring(0, 4).c_str());
    int Tmon = atoi(timeString.substring(5, 7).c_str());
    int Tday = atoi(timeString.substring(8, 10).c_str());
    int Thour = atoi(timeString.substring(11, 13).c_str());
    int Tmin = atoi(timeString.substring(14, 16).c_str());
    int Tsec = atoi(timeString.substring(17, 19).c_str());
    // 将UTC时间加8小时
    if (state == 1) {
      Thour += 8;

      // 处理时间进位
      if (Thour >= 24) {
        Thour -= 24;
        Tday += 1;
        // 检查日期是否需要进位
        if (Tday > getDaysInMonth(Tyear, Tmon)) {
          Tday = 1;
          Tmon += 1;
          if (Tmon > 12) {
            Tmon = 1;
            Tyear += 1;
          }
        }
      }
    }
    // 打印解析结果
    Serial.println(Tyear);
    Serial.println(Tmon);
    Serial.println(Tday);
    Serial.println(Thour);
    Serial.println(Tmin);
    Serial.println(Tsec);

    // // 调整RTC模块
    if (Tyear >= 2025) {
      DateTime now = DateTime(Tyear, Tmon, Tday, Thour, Tmin, Tsec);
      rtc.adjust(now);
    }  //  else {
    //   break;
    // }
    return;
  }
  //}
  //}
  for (int i = 0; i < 3; i++) {
    Serial2.println("AT+CSCLK=2\r");
    delay(100);
    while (Serial2.available()) {
      //Serial.write(".");
      Serial.write(Serial2.read());
    }
  }

  for (int i = 0; i < 3; i++) {
    Serial2.println("AT+CFUN=4,0\r");
    delay(100);
    while (Serial2.available()) {
      //Serial.write(".");
      Serial.write(Serial2.read());
    }
  }
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
  } else {
    for (int i = 0; i < 5; i++) {
      Serial2.println("AT+CFUN=1\r");
      delay(100);
      while (Serial2.available()) {
        //Serial.write(".");
        Serial.write(Serial2.read());
      }
    }
    getT4G();
    for (int i = 0; i < 3; i++) {
      Serial2.println("AT+CSCLK=2\r");
      delay(100);
      while (Serial2.available()) {
        //Serial.write(".");
        Serial.write(Serial2.read());
      }
    }
    for (int i = 0; i < 3; i++) {
      Serial2.println("AT+CFUN=4,0\r");
      delay(100);
      while (Serial2.available()) {
        //Serial.write(".");
        Serial.write(Serial2.read());
      }
    }
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

void setTimechar(int timeset, int num) {

  if (num <= 3) {
    string temp = std::__cxx11::to_string(timeset);
    const char* tempc = temp.c_str();
    switch (num) {
      case 0: lv_label_set_text(ui_hour0label, tempc); break;
      case 1: lv_label_set_text(ui_hour1label, tempc); break;
      case 2: lv_label_set_text(ui_min0label, tempc); break;
      case 3: lv_label_set_text(ui_min1label, tempc); break;
      default: break;
    }
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


struct Alarmt {  //闹钟相关结构体
  bool ok;       //是否启用闹钟
  int alarmnum;
  int hour1;
  int min1;
  int hour2;
  int min2;
  int hour3;
  int min3;
};
int defaultclock = 1;  //默认转腕亮屏显示的时钟
Alarmt alTime = {
  false,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
};
int clockflag = 0;

bool isAlarmTriggered(void) {
  uint8_t data;
  bool flag;
  Wire.beginTransmission(0x51);
  Wire.write(0x01);
  Wire.endTransmission();
  Wire.requestFrom(0x51, 1);
  data = Wire.read();
  flag = bitRead(data, 3);
  return (flag);
}
/////////////////////////////alarm
#include "EEPROM.h"
#include "driver/i2s.h"
#include "esp_log.h"
#include <math.h>
#include <string.h>


#define I2S_SAMPLE_RATE 16000
#define I2S_CHANNEL I2S_CHANNEL_FMT_ONLY_LEFT
#define I2S_DATABITS I2S_BITS_PER_SAMPLE_16BIT
#define I2S_BUFFER_SIZE (1024 * 2)
#define I2S_OUT_PORT I2S_NUM_1
#define I2S_OUT_BCLK 14
#define I2S_OUT_LRC 2
#define I2S_OUT_DOUT 27
typedef struct {
  char note;
  int duration;
} NoteDuration;

const int NOTE_C4 = 262, NOTE_D4 = 294, NOTE_E4 = 330, NOTE_F4 = 349,
          NOTE_G4 = 392, NOTE_A4 = 440, NOTE_B4 = 494, NOTE_C5 = 523;

const NoteDuration noteDurations[] = {
  { 's', 250 }, { 'S', 125 }, { 'l', 500 }, { 'L', 1000 }, { 'o', 1000 }, { '0', 1000 }
};

float Soundscale[8]{
  0, 261.6, 293.7, 329.6, 349.2, 392, 440, 493.9
};
void generate_tone(int16_t* buffer, int length, int frequency, int duration) {
  double t = 0.0;
  int samples = (int)(I2S_SAMPLE_RATE * (duration / 1000.0));
  for (int i = 0; i < samples && i < length; i++) {
    buffer[i] = (int16_t)(32767 * sin(2 * M_PI * frequency * t));
    t += 1.0 / I2S_SAMPLE_RATE;
  }
  for (int i = samples; i < length; i++) {
    buffer[i] = 0;
  }
}

float soundchoice(char x) {
  switch (x) {
    case '0': return Soundscale[0]; break;

    case 'a': return Soundscale[1]; break;
    case 'b': return Soundscale[2]; break;
    case 'c': return Soundscale[3]; break;
    case 'd': return Soundscale[4]; break;
    case 'e': return Soundscale[5]; break;
    case 'f': return Soundscale[6]; break;
    case 'g': return Soundscale[7]; break;

    case '1': return 2 * Soundscale[1]; break;
    case '2': return 2 * Soundscale[2]; break;
    case '3': return 2 * Soundscale[3]; break;
    case '4': return 2 * Soundscale[4]; break;
    case '5': return 2 * Soundscale[5]; break;
    case '6': return 2 * Soundscale[6]; break;
    case '7': return 2 * Soundscale[7]; break;

    case 'A': return 4 * Soundscale[1]; break;
    case 'B': return 4 * Soundscale[2]; break;
    case 'C': return 4 * Soundscale[3]; break;
    case 'D': return 4 * Soundscale[4]; break;
    case 'E': return 4 * Soundscale[5]; break;
    case 'F': return 4 * Soundscale[6]; break;
    case 'G': return 4 * Soundscale[7]; break;
  }
}
void i2s_play_music(const char* music) {


  int16_t buffer[I2S_BUFFER_SIZE];
  int musictick = 0;
  while (musictick < strlen(music)) {
    if (digitalRead(35) == LOW) {
      vTaskDelay(400);  //防止
      if (digitalRead(35) == LOW) {
        break;
      }
    }
    char x0 = music[musictick];
    char x1 = music[musictick + 1];

    float frequency = soundchoice(x0);
    int duration = 300;  //noteDurations[0].duration;  // 默认时长

    switch (x1) {
      case 's': duration = 0.75 * duration; break;
      case 'S': duration = 0.5 * duration; break;
      case 'l': duration = 1.5 * duration; break;
      case 'L': duration = 2 * duration; break;
      default: duration = 1 * duration; break;
    }

    // 计算总样本数
    int total_samples = (I2S_SAMPLE_RATE * duration) / 1000;


    int samples_per_write = I2S_BUFFER_SIZE;

    // 循环生成音频数据并写入 I2S 缓冲区
    for (int i = 0; i < total_samples; i += samples_per_write) {
      int samples_to_generate = (i + samples_per_write > total_samples) ? (total_samples - i) : samples_per_write;

      generate_tone(buffer, I2S_BUFFER_SIZE, frequency, samples_to_generate);

      size_t bytes_written;
      ESP_ERROR_CHECK(i2s_write(I2S_OUT_PORT, &buffer, sizeof(buffer), &bytes_written, portMAX_DELAY));
    }


    switch (x1) {
      case 's': musictick += 2; break;
      case 'S': musictick += 2; break;
      case 'l': musictick += 2; break;
      case 'L': musictick += 2; break;
      case 'o':
        musictick = 0;
        vTaskDelay(1000);
        break;
      default: musictick = (musictick < strlen(music) - 1) ? musictick + 1 : 0; break;
    }
  }

  i2s_driver_uninstall(I2S_OUT_PORT);
}



void alarmsetup() {
  //Serial.begin(115200);
  pinMode(20, OUTPUT);
  digitalWrite(20, LOW);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  i2s_config_t i2s_config_out = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = I2S_SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_STAND_I2S),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = 512,
  };
  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_OUT_BCLK,
    .ws_io_num = I2S_OUT_LRC,
    .data_out_num = I2S_OUT_DOUT,
    .data_in_num = -1
  };
  i2s_driver_install(I2S_OUT_PORT, &i2s_config_out, 0, NULL);
  i2s_set_pin(I2S_OUT_PORT, &pin_config);
  Serial.println("ok");
}
const char* changtingwai = "5l3s5AL0s6As65L0s5l1s23l2s12L005l3s5Al70s6lAl5L05l2s34lg1L006lAlAL07l6s7AL06s7As66s53s10s2L0s53s5Al70s6lAl5l0s5l2s34lg0s1L005L2s34Lg0s1L0000";
void musicloop(const char* music0) {
  alarmsetup();
  while (1) {
    ESP_LOGI("I2S", "Starting I2S music playback...");
    i2s_play_music(music0);
    ESP_LOGI("I2S", "Music playback finished.");
    if (digitalRead(35) == LOW) break;
  }
}




void alarmmusic() {
  rtc.off_alarm();
  musicloop(changtingwai);
}

bool isAlarmedcheck() {
  // Serial.println("alarmcheck");
  if (isAlarmTriggered()) {
    Serial.println("off_alarm");
    rtc.off_alarm();


    if (alTime.ok) {
      //if (alTime.alarmnum)
      //alTime.ok = false;
      Serial.println("闹钟已触发");
      musicloop(changtingwai);
      //EEPROM.write(100, int(alTime.ok));
      //EEPROM.commit();
      setAlarm();
      return 1;
    }

    clockflag = 1;
  }
  return 0;
}
void alarmget() {
  DateTime alarmgot = rtc.get_alarm();
  int H = alarmgot.hour();
  int M = alarmgot.minute();
}
//添加某个闹钟
void addAlarm(int alarmIndex) {
  if (alarmIndex >= 1 && alarmIndex <= 3) {
    alTime.alarmnum |= (1 << (alarmIndex - 1));  // 使用或操作设置对应位为1
  }
  alTime.ok = true;
  EEPROM.write(100, alTime.ok);
  EEPROM.write(105, alTime.alarmnum);
  EEPROM.commit();

  Serial.print("alTime.alarmnum");
  Serial.println(alTime.alarmnum);
  Serial.print("alTime.ok");
  Serial.println(alTime.ok);
}

// 删除某个闹钟
void removeAlarm(int alarmIndex) {
  if (alarmIndex >= 1 && alarmIndex <= 3) {
    alTime.alarmnum &= ~(1 << (alarmIndex - 1));  // 使用与操作清除对应位
  }
  EEPROM.write(105, alTime.alarmnum);
  if (alTime.alarmnum == 0) {
    alTime.ok = false;
    EEPROM.write(100, 0);
  }
  EEPROM.commit();

  Serial.print("alTime.alarmnum");
  Serial.println(alTime.alarmnum);
  Serial.print("alTime.ok");
  Serial.println(alTime.ok);
}

// 计算两个时间之间的差值（单位：分钟）
int timeDifference(int currentHour, int currentMin, int alarmHour, int alarmMin) {
  int currentTotalMin = currentHour * 60 + currentMin;
  int alarmTotalMin = alarmHour * 60 + alarmMin;

  // 如果闹钟时间小于当前时间，则加上一天的分钟数（1440分钟）
  if (alarmTotalMin < currentTotalMin) {
    alarmTotalMin += 24 * 60;
  }

  return alarmTotalMin - currentTotalMin;
}
int alarmumget() {
  return alTime.alarmnum;
}
// 找出离当前时间最近的闹钟
int findNearestAlarm(int currentHour, int currentMin) {
  int nearestAlarmIndex = 0;
  int smallestDifference = INT_MAX;

  // 遍历所有闹钟
  for (int i = 1; i <= 3; i++) {
    // 检查第 i 个闹钟是否启用
    if (alTime.alarmnum & (1 << (i - 1))) {
      int alarmHour = 0;
      int alarmMin = 0;

      // 根据索引选择对应的闹钟时间
      switch (i) {
        case 1:
          alarmHour = alTime.hour1;
          alarmMin = alTime.min1;
          break;
        case 2:
          alarmHour = alTime.hour2;
          alarmMin = alTime.min2;
          break;
        case 3:
          alarmHour = alTime.hour3;
          alarmMin = alTime.min3;
          break;
      }

      // 计算当前时间与闹钟时间的差值
      int difference = timeDifference(currentHour, currentMin, alarmHour, alarmMin);

      // 如果当前闹钟时间更接近，更新最近闹钟索引
      if (difference != 0) {
        if (difference < smallestDifference) {
          smallestDifference = difference;
          nearestAlarmIndex = i;
        }
      }
    }
  }

  return nearestAlarmIndex;
}





void getalarmall(int* hour1, int* min1, int* hour2, int* min2, int* hour3, int* min3) {
  alTime.ok = EEPROM.read(100);
  alTime.alarmnum = EEPROM.read(105);
  alTime.hour1 = EEPROM.read(110);
  alTime.min1 = EEPROM.read(115);
  alTime.hour2 = EEPROM.read(120);
  alTime.min2 = EEPROM.read(125);
  alTime.hour3 = EEPROM.read(130);
  alTime.min3 = EEPROM.read(135);
  *hour1 = alTime.hour1;
  *min1 = alTime.min1;
  *hour2 = alTime.hour2;
  *min2 = alTime.min2;
  *hour3 = alTime.hour3;
  *min3 = alTime.min3;
  Serial.print("alTime.ok");
  Serial.println(alTime.ok);
  Serial.print("alTime.alarmnum");
  Serial.println(alTime.alarmnum);
  Serial.print("alTime1- ");
  Serial.print(alTime.hour1);
  Serial.print(":");
  Serial.println(alTime.min1);
  Serial.print("alTime2- ");
  Serial.print(alTime.hour2);
  Serial.print(":");
  Serial.println(alTime.min2);
  Serial.print("alTime3- ");
  Serial.print(alTime.hour3);
  Serial.print(":");
  Serial.println(alTime.min3);
}
void setAlarm() {

  int x;
  getalarmall(&x, &x, &x, &x, &x, &x);
  DateTime alarm = rtc.now();
  int H = alarm.hour();
  int M = alarm.minute();
  int alarmhour;
  int alarmmin;
  switch (findNearestAlarm(H, M)) {
    case 1:
      alarmhour = alTime.hour1;
      alarmmin = alTime.min1;
      break;
    case 2:
      alarmhour = alTime.hour2;
      alarmmin = alTime.min2;
      break;
    case 3:
      alarmhour = alTime.hour3;
      alarmmin = alTime.min3;
      break;
    default: alarmhour = 255; alarmmin = 255;
  }
  Serial.print("alarmchoose");
  Serial.println(findNearestAlarm(H, M));
  alarm.setminute(alarmmin);
  alarm.sethour(alarmhour);

  rtc.set_alarm(alarm, { 1, 1, 0, 0 });
  rtc.on_alarm();
  EEPROM.write(100, 1);
  EEPROM.commit();
  alTime.ok = true;
}

void gettimeC(int hour, int min, int alarmnum) {
  string h = (hour < 10) ? "0" + std::to_string(hour) : std::to_string(hour);
  string m = (min < 10) ? "0" + std::to_string(min) : std::to_string(min);
  string t = h + ":" + m + " ";
  Serial.println(t.c_str());
  const char* tc = t.c_str();
  switch (alarmnum) {
    case 1: lv_label_set_text(ui_Alarmtext, tc); break;
    case 2: lv_label_set_text(ui_Alarmtext2, tc); break;
    case 3: lv_label_set_text(ui_Alarmtext3, tc); break;
  }
}