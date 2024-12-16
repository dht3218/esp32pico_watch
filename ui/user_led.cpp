#include "user_led.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include <Arduino.h>
#include "esp_task_wdt.h"


#define LEDC_HS_TIMER LEDC_TIMER_1
#define LEDC_HS_MODE LEDC_HIGH_SPEED_MODE
#define LEDC_HS_CH2_GPIO (4)
#define LEDC_HS_CH2_CHANNEL LEDC_CHANNEL_2

ledc_channel_config_t ledc_RED_cfg = {
  .gpio_num = LEDC_HS_CH2_GPIO,
  .speed_mode = LEDC_HS_MODE,
  .channel = LEDC_HS_CH2_CHANNEL,
  //.intr_type=LEDC_INTR_DISABLE,
  .timer_sel = LEDC_HS_TIMER,
  .duty = 0,
  .hpoint = 0,
  //.output_invert=0

};

void LED_tim_init(void) {
  const ledc_timer_config_t ledc_timer = {
    .speed_mode = LEDC_HS_MODE,           // timer mode
    .duty_resolution = LEDC_TIMER_8_BIT,  // resolution of PWM duty
    .timer_num = LEDC_HS_TIMER,           // timer index
    .freq_hz = 4000,                      // frequency of PWM signal
    .clk_cfg = LEDC_AUTO_CLK,             // Auto select the source clock
  };
  ledc_timer_config(&ledc_timer);
}



void user_led_set_duty(uint8_t duty) {
  ledc_set_duty(ledc_RED_cfg.speed_mode, ledc_RED_cfg.channel, duty);
  ledc_update_duty(ledc_RED_cfg.speed_mode, ledc_RED_cfg.channel);
}

void led_init(void) {
  LED_tim_init();

  ledc_channel_config(&ledc_RED_cfg);
  user_led_set_duty(40);
  ledc_fade_func_install(0);
}
void led_set(int dut) {
  //LED_tim_init();
  Serial.print("dut");
  Serial.println(dut);
  //ledc_channel_config(&ledc_RED_cfg);
  user_led_set_duty(dut);
  //ledc_fade_func_install(0);
}

//dut取0到255


void led_task() {
  int dut = 0;
  while (1) {
    user_led_set_duty(dut);
    Serial.println(dut);
    vTaskDelay(50);
    dut += 1;
  }
}
void led_off(void) {
  ledc_stop(LEDC_HS_MODE, LEDC_HS_CH2_CHANNEL, 0); // 停止PWM信号输出
  digitalWrite(4,LOW);
}
