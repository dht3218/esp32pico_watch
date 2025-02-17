//陀螺仪相关
#include <Wire.h>
#include <esp_sleep.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
Adafruit_MPU6050 mpu;
int INT_PIN = 36;
int16_t gyro_x_threshold = 500;  // x轴角速度阈值
void mpu_init() {
  if (mpu.begin()) Serial.println("ok");
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
  mpu.setMotionDetectionThreshold(1);
  mpu.setMotionDetectionDuration(20);
  mpu.setInterruptPinLatch(false);
  mpu.setInterruptPinPolarity(true);
  mpu.setMotionInterrupt(true);           //是否开启运动检测触发中断
  mpu.setMotionDetectionThreshold(0x45);  //触发阈值
  pinMode(INT_PIN, INPUT_PULLUP);
}
int mpu_check() {  //陀螺仪触发检测
  if (mpu.getMotionInterruptStatus()) {
    sensors_event_t a, g, temp;
    int tick6050 = 0;
    int state6050 = 0;
    while (tick6050 < 20) {
      mpu_init();
      mpu.getEvent(&a, &g, &temp);
      if (!mpu.getMotionInterruptStatus() && abs(abs(g.gyro.z) - 1) < 1.5 && (abs(g.gyro.x) < 1.5 && abs(g.gyro.y) < 2)) {
        state6050 = 1;
        break;
      } else {
        break;
      }
      tick6050++;
      delay(10);
    }
    if (state6050 == 1) {
      Serial.println("detected");
      digitalWrite(4, HIGH);
      return 1;

    } else {
      mpu_init();
      Serial.println("nothing");
      return 0;
    }
  } else {
    return 0;
  }
}
#include <RTClib.h>
PCF8563 rtc;
DateTime alarm_l;
void setup() {
  Wire.begin(8, 7);
  Serial.begin(115200);
  Serial.println("init!");
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(__DATE__, __TIME__));
  } else {
    Serial.println("RTC OK");
    DateTime now = DateTime(2020, 4, 1, 12, 00, 0);
    rtc.adjust(now);
  }
  rtc.off_alarm();
  DateTime now = rtc.now();
  char buf[100];
  strncpy(buf, "DD.MM.YYYY hh:mm:ss", 100);
  Serial.println(now.format(buf));

  mpu_init();
  delay(1000);
  Serial.println("initok!");
  pinMode(35, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(36, INPUT_PULLUP);
  pinMode(38, INPUT_PULLUP);
  gpio_wakeup_enable(GPIO_NUM_38, GPIO_INTR_LOW_LEVEL);  // 使用INT_PIN 35作为中断引脚，低电平触发中断
  gpio_wakeup_enable(GPIO_NUM_35, GPIO_INTR_LOW_LEVEL);  // 使用INT_PIN 35作为中断引脚，低电平触发中断
  gpio_wakeup_enable(GPIO_NUM_36, GPIO_INTR_LOW_LEVEL);  // 使用INT_PIN 36作为中断引脚，低电平触发中断
  esp_sleep_enable_gpio_wakeup();
    Serial.println(digitalRead(35));
  Serial.println(digitalRead(36));
  Serial.println(digitalRead(38));
  //esp_sleep_enable_timer_wakeup(30 * 60 * 1000000);
  esp_light_sleep_start();
  Serial.println("wakeup!");
  Serial.println("wakeup!");
  Serial.println("wakeup!");
  Serial.println(digitalRead(35));
  Serial.println(digitalRead(36));
  Serial.println(digitalRead(38));
  mpu_check();
}

void loop() {
}