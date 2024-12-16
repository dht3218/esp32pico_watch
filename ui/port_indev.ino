#include <lvgl.h>
#include "ui.h"
#include "AiassistantLocal.h"
#include <EEPROM.h>
#include "esp_system.h"
#include "esp_task_wdt.h"
static void keypad_init(void);
static void keypad_read(_lv_indev_drv_t* indev, lv_indev_data_t* data);
static uint32_t keypad_get_key(void);
lv_indev_t* indev_keypad;

static void button_init(void);
static void button_read(_lv_indev_drv_t* indev, lv_indev_data_t* data);
static int8_t button_get_pressed_id(void);

lv_indev_t* indev_button;


void taplogic() {
  if (digitalRead(35) == LOW) {
    vTaskDelay(40);  //防止
    if (digitalRead(35) == LOW) {
      vTaskDelay(200);
      if (digitalRead(35) != LOW && dispnow != -2) {
        Serial.println("sleep");
        led_off();
        tft.writecommand(0x10);
        delay(100);



        pinMode(4, INPUT_PULLDOWN);
        pinMode(35, INPUT_PULLUP);
        Rtctaskdelete();
        gpio_wakeup_enable(GPIO_NUM_35, GPIO_INTR_LOW_LEVEL);  // 使用INT_PIN 34作为中断引脚，低电平触发中断
        esp_sleep_enable_gpio_wakeup();
        esp_sleep_enable_timer_wakeup(30*60 * 1000000);

        vTaskDelay(50);
        //         for (int i = 0; i < 3; i++) {
        //   Serial2.println("AT+CSCLK=2\r");
        //   delay(20);
        //   while (Serial2.available()) {
        //     //Serial.write(".");
        //     Serial.write(Serial2.read()); 
        //   }
        // }

        esp_light_sleep_start();

        esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
        if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_TIMER) {
          Serial.println("deepsleep");
          EEPROM.write(10, 1);
          delay(200);
          EEPROM.commit();
          esp_restart();
        }
        tft.writecommand(0x11);
        if (dispnow == 1) Rtctaskcreate();
        led_init();
        vTaskDelay(100);
        led_set(leddut);
        return;
      } else {
        if (dispnow != -2) {
          switch ((int)dispnow) {
            case 0:
              chatstate = 0;
              ;
              break;
            case 1: Rtctaskdelete(); break;
            case 4: led_set(leddut); break;
          }
          lv_obj_t* scr = lv_scr_act();
          _ui_screen_delete(&scr);
          Serial.println("AIassistant");
          dispnow = -2;
          _ui_screen_change(&ui_Aiassistant, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_Aiassistant_screen_init);
          AILocalsetup();
        }
      }
    }
  }
}




//lv_group_t* groupbtn;
void lv_port_indev_init(void) {
  static lv_indev_drv_t indev_drv;
  static lv_indev_drv_t indev_drv1;
  /*------------------
     * Keypad
     * -----------------*/

  /*Initialize your keypad or keyboard if you have*/
  keypad_init();

  // /*Register a keypad input device*/
  // indev_keypad = lv_indev_create();
  // lv_indev_set_type(indev_keypad, LV_INDEV_TYPE_KEYPAD);
  // lv_indev_set_read_cb(indev_keypad, keypad_read);
  grouphand = lv_group_create();
  //lv_group_set_default(grouphand);
  //lv_indev_set_group(indev_keypad, grouphand);

  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_KEYPAD;
  indev_drv.read_cb = keypad_read;
  indev_keypad = lv_indev_drv_register(&indev_drv);
  grouphand = lv_group_create();  //lv_group_set_default(grouphand);

  lv_indev_set_group(indev_keypad, grouphand);


  //

  button_init();

  /*Register a button input device*/

  lv_indev_drv_init(&indev_drv1);
  indev_drv1.type = LV_INDEV_TYPE_BUTTON;
  indev_drv1.read_cb = button_read;
  indev_button = lv_indev_drv_register(&indev_drv1);

  /*Assign buttons to points on the screen*/
  static const lv_point_t btn_points[9] = {
    { 200, 40 }, /*ButtonUp*/  //desktop
    { 200, 230 },
    /*ButtonDown*/  //desktop
    { 200, 120 },
    /*ButtonCen*/  //desktop
    { 30, 140 },   /*ButtonBack*/
    { 120, 60 },   /*AIlocalswitch*/


  };
  lv_indev_set_button_points(indev_button, btn_points);
  //groupbtn = lv_group_create();
  //lv_group_set_default(groupbtn);
  //lv_indev_set_group(indev_button, groupbtn);
}

#include <Arduino_APDS9960.h>
/*Initialize your keypad*/
static void keypad_init(void) {
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
  }
  Serial.println("APDS-9960 sensor OK");
  /*Your code comes here*/
  pinMode(35, INPUT);
}

/*Will be called by the library to read the mouse*/
static void keypad_read(lv_indev_drv_t* indev_drv, lv_indev_data_t* data) {
  if (dispnow == 2) {
    static uint32_t last_key = 0;
    //Serial.println("keypad_read");
    /*Get the current x and y coordinates*/
    //mouse_get_xy(&data->point.x, &data->point.y);

    /*Get whether the a key is pressed and save the pressed key*/
    uint32_t act_key = keypad_get_key();
    if (act_key != 0) {
      data->state = LV_INDEV_STATE_PR;

      /*Translate the keys to LVGL control characters according to your key definitions*/
      switch (act_key) {
        case 1:
          act_key = LV_KEY_PREV;
          break;
        case 2:
          act_key = LV_KEY_NEXT;
          break;
        case 3:
          act_key = LV_KEY_LEFT;
          break;
        case 4:
          act_key = LV_KEY_RIGHT;
          break;
        case 5:
          act_key = LV_KEY_ENTER;
          break;
      }

      last_key = act_key;
    } else {
      data->state = LV_INDEV_STATE_REL;
    }

    data->key = last_key;
  } else if (dispnow == 2.1) {
    static uint32_t last_key = 0;
    //Serial.println("keypad_read");
    /*Get the current x and y coordinates*/
    //mouse_get_xy(&data->point.x, &data->point.y);

    /*Get whether the a key is pressed and save the pressed key*/
    uint32_t act_key = keypad_get_key();
    if (act_key != 0) {
      data->state = LV_INDEV_STATE_PR;

      /*Translate the keys to LVGL control characters according to your key definitions*/
      switch (act_key) {
        case 1:
          act_key = LV_KEY_PREV;
          break;
        case 2:
          act_key = LV_KEY_NEXT;
          break;
        case 3:
          //act_key = LV_KEY_PREV;
          break;
        case 4:
          //act_key = LV_KEY_NEXT;
          break;
        case 5:
          act_key = LV_KEY_ENTER;
          break;
      }

      last_key = act_key;
    } else {
      data->state = LV_INDEV_STATE_REL;
    }

    data->key = last_key;
  }
}

/*Get the currently being pressed key.  0 if no key is pressed*/
static uint32_t keypad_get_key(void) {
  taplogic();
  if (APDS.gestureAvailable()) {
    // a gesture was detected, read and print to Serial Monitor
    int gesture = APDS.readGesture();
    Serial.println("gestureAvailable");
    switch (gesture) {
      case GESTURE_UP:
        Serial.println("UP");
        return 1;

      case GESTURE_DOWN:
        Serial.println("DOWN");
        return 2;

      case GESTURE_LEFT:
        Serial.println("LEFT");
        return 3;

      case GESTURE_RIGHT:
        Serial.println("RIGHT");
        return 4;

      default:
        // ignore
        break;
    }
    Serial.println("NOTHING");
    //vTaskDelay(100);
    return 0;
  }

  if (APDS.proximityAvailable()) {
    if (APDS.readProximity() == 0) {
      Serial.println("CLICK");
      vTaskDelay(100);
      return 5;
    }
  }
  return 0;
}



/*Initialize your buttons*/
static void button_init(void) {
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
  }
  Serial.println("APDS-9960 sensor OK");
  /*Your code comes here*/
  pinMode(35, INPUT);
}

/*Will be called by the library to read the button*/

static void button_read(lv_indev_drv_t* indev_drv, lv_indev_data_t* data) {
  if (dispnow != 2 && dispnow != 2.1) {

    //Serial.println("BUTTON");
    static uint8_t last_btn = 0;

    /*Get the pressed button's ID*/
    int8_t btn_act = button_get_pressed_id();

    if (btn_act >= 0) {
      vTaskDelay(100);
      data->state = LV_INDEV_STATE_PR;
      last_btn = btn_act;
      //Serial.println("BTNCLICK");

    } else {
      data->state = LV_INDEV_STATE_REL;
    }

    /*Save the last pressed button's ID*/
    data->btn_id = last_btn;
  }
}

/*Get ID  (0, 1, 2 ..) of the pressed button*/
static int8_t button_get_pressed_id(void) {
  taplogic();
  if (APDS.gestureAvailable()) {

    // a gesture was detected, read and print to Serial Monitor
    int gesture = APDS.readGesture();

    switch (gesture) {
      case GESTURE_UP:
        Serial.println("UP");
        return 0;

      case GESTURE_DOWN:
        Serial.println("DOWN");
        return 1;

      case GESTURE_LEFT:
        Serial.println("LEFT");
        return -1;

      case GESTURE_RIGHT:
        Serial.println("RIGHT");
        return 3;

      default:
        // ignore
        break;
    }
    Serial.println("NOTHING");
    //vTaskDelay(100);
    return 0;
  }

  if (APDS.proximityAvailable()) {
    if (APDS.readProximity() == 0) {
      Serial.println("CLICK");
      vTaskDelay(100);
      if (dispnow != -2) return 2;
      else if (dispnow == -2) return 4;
    }
  }
  /*No button pressed*/
  return -1;
}
