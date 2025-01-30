#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ui.h>
#include "clock.h"
#include <Wire.h>
#include <esp_sleep.h>
#include "user_led.h"
#include "cw2015.h"
#include "driver/i2c.h"
#include "esp32-hal-cpu.h"
#include <EEPROM.h>
#define RXD2 19
#define TXD2 21



#define LVUSED 1
#ifdef LVUSED
const char *batv = "999";
void update_bat_data(lv_timer_t *timer) {
  if (dispnow == -1) getbat();
}

/* 创建一个定时器，每200ms更新一次数据 */


#endif


/*Don't forget to set Sketchbook location in File/Preferences to the path of your UI project (the parent foder of this INO file)*/

/*Change to your screen resolution*/
static const uint16_t screenWidth = 240;
static const uint16_t screenHeight = 280;
extern int livecnt;
static lv_disp_draw_buf_t draw_buf;
lv_color_t *buf_3_1 = (lv_color_t *)heap_caps_malloc(screenWidth * screenHeight * sizeof(lv_color_t) / 8, MALLOC_CAP_DMA);
lv_color_t *buf_3_2 = (lv_color_t *)heap_caps_malloc(screenWidth * screenHeight * sizeof(lv_color_t) / 8, MALLOC_CAP_DMA);
// static lv_color_t buf_3_1[screenWidth * screenHeight / 10];
// static lv_color_t buf_3_2[screenWidth * screenHeight 10];
lv_color_t *dmaBufferPtr = buf_3_1;

bool dmaBufferSel = 0;
TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char *buf) {
  Serial.printf(buf);
  Serial.flush();
}
#endif


/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  if (dmaBufferSel) {
    dmaBufferPtr = buf_3_2;
  } else {
    dmaBufferPtr = buf_3_1;
  }
  dmaBufferSel = !dmaBufferSel;
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);
  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1 + 20, w, h);
  tft.pushPixelsDMA((uint16_t *)&color_p->full, w * h);
  tft.endWrite();
  lv_disp_flush_ready(disp);
}

IRAM_ATTR void lvgl_task(void *arg) {
  ui_init();

  while (true) {
    vTaskDelay(1);
    lv_timer_handler();
  }
}
extern void print_wakeup_reason();
extern void led_init();
extern void MPUsetup();
extern void lv_port_indev_init(void);
void setup() {
  EEPROM.begin(4096);  //只读存储器初始化
  //lv_color_t *buf = (lv_color_t *)heap_caps_malloc(screenWidth * screenHeight * sizeof(lv_color_t) , MALLOC_CAP_SPIRAM);
  Serial.begin(115200); /* prepare for possible serial debug */
                        //pinMode(4, OUTPUT);
                        //digitalWrite(4, HIGH);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println(EEPROM.read(100));
  livecnt = 0;
  //int x = 0;
  Wire.begin(8, 7);
  RtcSetup0();
  if (EEPROM.read(100)) setAlarm();
  //getalarmall(&x, &x, &x, &x, &x, &x);
  pinMode(35, INPUT_PULLUP);
  MPUsetup();
  CW2015wakeUp();
  print_wakeup_reason();
  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0) {
    Serial.println("闹钟已触发");
    alarmmusic();
    setAlarm();
  }

  if (EEPROM.read(10) == 1) {
    Serial.println("deepsleep");
    EEPROM.write(10, 0);
    delay(200);
    EEPROM.commit();
    esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_38, 0);
    esp_deep_sleep_start();
  }
  //isAlarmedcheck();
  if (!EEPROM.read(10) == 1) {
    for (int i = 0; i < 5; i++) {
      Serial2.println("AT+CFUN=1\r");
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
    for (int i = 0; i < 1; i++) {
      Serial2.println("AT+CSCLK=0\r");
      delay(100);
      while (Serial2.available()) {
        //Serial.write(".");
        Serial.write(Serial2.read());
      }
    }
  }
  pinMode(35, INPUT_PULLUP);
  pinMode(36, INPUT_PULLUP);
  pinMode(38, INPUT_PULLUP);
  //gpio_wakeup_enable(GPIO_NUM_35, GPIO_INTR_LOW_LEVEL);  // 使用INT_PIN 34作为中断引脚，低电平触发中断
  gpio_wakeup_enable(GPIO_NUM_38, GPIO_INTR_LOW_LEVEL);
  gpio_wakeup_enable(GPIO_NUM_35, GPIO_INTR_LOW_LEVEL);  // 使用INT_PIN 34作为中断引脚，低电平触发中断
  gpio_wakeup_enable(GPIO_NUM_36, GPIO_INTR_LOW_LEVEL);
  esp_sleep_enable_gpio_wakeup();

  //esp_light_sleep_start();
  String LVGL_Arduino = "Hello Arduino! ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

  Serial.println(LVGL_Arduino);
  Serial.println("I am LVGL_Arduino");

  lv_init();

#if LV_USE_LOG != 0
  lv_log_register_print_cb(my_print); /* register print function for debugging */
#endif

  tft.begin();        /* TFT init */
  tft.setRotation(2); /* Landscape orientation, flipped */
  tft.initDMA();
  //  lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight  );
  lv_disp_draw_buf_init(&draw_buf, buf_3_1, buf_3_2, screenWidth * screenHeight / 8);
  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  //disp_drv.full_refresh = 1;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  // /*Initialize the (dummy) input device driver*/
  // static lv_indev_drv_t indev_drv;
  // lv_indev_drv_init( &indev_drv );
  // indev_drv.type = LV_INDEV_TYPE_POINTER;
  // indev_drv.read_cb = my_touchpad_read;
  // lv_indev_drv_register( &indev_drv );
  //esp_phy_disable();
  // Wire.begin(8, 7);
  //i2c_driver_delete(I2C_NUM_0);  // 假设使用的是I2C端口0


  lv_port_indev_init();


  xTaskCreatePinnedToCore(lvgl_task, "lvgl_task", 2 * 8192, NULL, 15, NULL, 1);
  led_init();
  led_set(leddut);

  int H;
  int M;
  int S;
  getTc(&H, &M, &S);
  getTc(&H, &M, &S);
  const char *date = getTc(&H, &M, &S);
  if (date) {
    // 提取年份部分（前四个字符）
    char yearStr[5];
    strncpy(yearStr, date, 4);  // 复制前四个字符
    yearStr[4] = '\0';          // 添加字符串结束符

    // 将年份字符串转换为整数
    int year = atoi(yearStr);

    // 判断年份是否大于2024
    if (year < 2025) {
      getT4G();
    }



  }


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



  lv_timer_create(update_bat_data, 1000, NULL);
  Serial.println("Setup done");
}
//extern void led_task();
void loop() {
  //led_task();
  //  vTaskDelay(500);
  //  Serial.println(desktopcnt);
}
