// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: dht8-3

// #include <string>
#include "ui.h"
#include "ui_helpers.h"
#include "clock.h"
#include "cw2015.h"
#include "memo.h"
#include <arduino.h>

#include "AiassistantLocal.h"
float dispnow = 0;
int timeset[4] = { 0, 0, 0, 0 };
int wifistatu = 0;

///////////////////// VARIABLES ////////////////////
void iconNOW2PRE_Animation(lv_obj_t *TargetObject, int vTaskDelay);
void iconNEX2NOW_Animation(lv_obj_t *TargetObject, int vTaskDelay);
void iconAppear_Animation(lv_obj_t *TargetObject, int vTaskDelay);
void icondisapp_Animation(lv_obj_t *TargetObject, int vTaskDelay);
void iconPRE2NOW_Animation(lv_obj_t *TargetObject, int vTaskDelay);
void iconNOW2NEX_Animation(lv_obj_t *TargetObject, int vTaskDelay);

// SCREEN: ui_DESK
void ui_DESK_screen_init(void);
lv_obj_t *ui_DESK;
lv_obj_t *ui_Container2;
lv_obj_t *ui_iconPRE2;
lv_obj_t *ui_iconNEX2;
lv_obj_t *ui_iconNEX;
lv_obj_t *ui_iconPRE;
lv_obj_t *ui_iconNOW;
lv_obj_t *ui_Container1;
void ui_event_ButtonDown(lv_event_t *e);
lv_obj_t *ui_ButtonDown;
void ui_event_ButtonUp(lv_event_t *e);
lv_obj_t *ui_ButtonUp;
void ui_event_ButtonCen(lv_event_t *e);
lv_obj_t *ui_ButtonCen;
lv_obj_t *ui_battery0;
lv_obj_t *ui_batvalue;
lv_obj_t *ui_battery1;
// CUSTOM VARIABLES

// SCREEN: ui_CLOCK
void ui_CLOCK_screen_init(void);
lv_obj_t *ui_CLOCK;
lv_obj_t *ui_Container3;
//void ui_event_ButtonDown1(lv_event_t *e);
lv_obj_t *ui_ButtonDown1;
lv_obj_t *ui_ButtonUp1;
lv_obj_t *ui_ButtonCen1;
lv_obj_t *ui_Container5;
lv_obj_t *ui_HOUR;
lv_obj_t *ui_MIN;
lv_obj_t *ui_Panel2;
lv_obj_t *ui_Label3;
void ui_event_ButtonBACK(lv_event_t *e);
lv_obj_t *ui_ButtonBACK;

// CUSTOM VARIABLES

// SCREEN: ui_CALENDAR
void ui_CALENDAR_screen_init(void);
lv_obj_t *ui_CALENDAR;
lv_obj_t *ui_Container4;
void ui_event_ButtonDown2(lv_event_t *e);
void ui_event_ButtonUp2(lv_event_t *e);
lv_obj_t *ui_ButtonDown2;
lv_obj_t *ui_ButtonUp2;
lv_obj_t *ui_ButtonCen2;
lv_obj_t *ui_Calendar1;
void ui_event_ButtonBACK5(lv_event_t *e);
lv_obj_t *ui_ButtonBACK5;
void ui_event_ButtonCen2(lv_event_t *e);
// CUSTOM VARIABLES





// EVENTS
lv_obj_t *ui____initial_actions0;

// IMAGES AND IMAGE SETS
const lv_img_dsc_t *ui_imgset_icon[7] = { &ui_img_icon1_png, &ui_img_icon2_png, &ui_img_icon3_png, &ui_img_icon4_png, &ui_img_icon5_png, &ui_img_icon6_png, &ui_img_icon7_png };
int desktopcnt = 1;
#define AppTotal 7
#define iconNOWnum desktopcnt
#define iconPREnum (iconNOWnum - 1 < 0) ? desktopcnt - 1 + AppTotal : desktopcnt - 1
#define iconNEXnum (iconNOWnum + 1 > AppTotal - 1) ? desktopcnt + 1 - AppTotal : desktopcnt + 1
#define iconPRE2num (iconNOWnum - 2 < 0) ? desktopcnt - 2 + AppTotal : desktopcnt - 2
#define iconNEX2num (iconNOWnum + 2 > AppTotal - 1) ? desktopcnt + 2 - AppTotal : desktopcnt + 2
void iconLOOPdown1(lv_anim_t *a) {
  desktopcnt = (desktopcnt == AppTotal - 1) ? 0 : desktopcnt + 1;
  vTaskDelay(20);
  lv_img_set_src(ui_iconNEX, ui_imgset_icon[iconNEXnum]);
  lv_img_set_src(ui_iconNOW, ui_imgset_icon[iconNOWnum]);
  lv_img_set_src(ui_iconPRE, ui_imgset_icon[iconPREnum]);
  // lv_img_set_src(ui_iconPRE2, ui_imgset_icon[iconPRE2num]);
}
void iconLOOPup1(lv_anim_t *a) {
  desktopcnt = (desktopcnt == 0) ? AppTotal - 1 : desktopcnt - 1;
  vTaskDelay(20);
  // lv_img_set_src(ui_iconNEX2, ui_imgset_icon[iconNEX2num]);
  lv_img_set_src(ui_iconNEX, ui_imgset_icon[iconNEXnum]);
  lv_img_set_src(ui_iconNOW, ui_imgset_icon[iconNOWnum]);
  lv_img_set_src(ui_iconPRE, ui_imgset_icon[iconPREnum]);
}

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
#error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
// #if LV_COLOR_16_SWAP !=0
//     #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
// #endif

///////////////////// ANIMATIONS ////////////////////
void iconNOW2PRE_Animation(lv_obj_t *TargetObject, int vTaskDelay) {
  ui_anim_user_data_t *PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
  PropertyAnimation_0_user_data->target = TargetObject;
  PropertyAnimation_0_user_data->val = -1;
  lv_anim_t PropertyAnimation_0;
  lv_anim_init(&PropertyAnimation_0);
  lv_anim_set_time(&PropertyAnimation_0, 500);
  lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
  lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
  lv_anim_set_values(&PropertyAnimation_0, -23, 13);
  lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_overshoot);
  lv_anim_set_delay(&PropertyAnimation_0, vTaskDelay + 0);
  lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
  lv_anim_set_playback_time(&PropertyAnimation_0, 1);
  lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
  lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
  lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
  lv_anim_set_early_apply(&PropertyAnimation_0, false);
  lv_anim_start(&PropertyAnimation_0);
  ui_anim_user_data_t *PropertyAnimation_1_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
  PropertyAnimation_1_user_data->target = TargetObject;
  PropertyAnimation_1_user_data->val = -1;
  lv_anim_t PropertyAnimation_1;
  lv_anim_init(&PropertyAnimation_1);
  lv_anim_set_time(&PropertyAnimation_1, 500);
  lv_anim_set_user_data(&PropertyAnimation_1, PropertyAnimation_1_user_data);
  lv_anim_set_custom_exec_cb(&PropertyAnimation_1, _ui_anim_callback_set_y);
  lv_anim_set_values(&PropertyAnimation_1, -9, 80);
  lv_anim_set_path_cb(&PropertyAnimation_1, lv_anim_path_overshoot);
  lv_anim_set_delay(&PropertyAnimation_1, vTaskDelay + 0);
  lv_anim_set_deleted_cb(&PropertyAnimation_1, _ui_anim_callback_free_user_data);
  lv_anim_set_playback_time(&PropertyAnimation_1, 1);
  lv_anim_set_playback_delay(&PropertyAnimation_1, 0);
  lv_anim_set_repeat_count(&PropertyAnimation_1, 0);
  lv_anim_set_repeat_delay(&PropertyAnimation_1, 0);
  lv_anim_set_early_apply(&PropertyAnimation_1, false);
  lv_anim_start(&PropertyAnimation_1);
  ui_anim_user_data_t *PropertyAnimation_2_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
  PropertyAnimation_2_user_data->target = TargetObject;
  PropertyAnimation_2_user_data->val = -1;
  lv_anim_t PropertyAnimation_2;
  lv_anim_init(&PropertyAnimation_2);
  lv_anim_set_time(&PropertyAnimation_2, 500);
  lv_anim_set_user_data(&PropertyAnimation_2, PropertyAnimation_2_user_data);
  lv_anim_set_custom_exec_cb(&PropertyAnimation_2, _ui_anim_callback_set_image_zoom);
  lv_anim_set_values(&PropertyAnimation_2, 400, 256);
  lv_anim_set_path_cb(&PropertyAnimation_2, lv_anim_path_overshoot);
  lv_anim_set_delay(&PropertyAnimation_2, vTaskDelay + 0);
  lv_anim_set_deleted_cb(&PropertyAnimation_2, _ui_anim_callback_free_user_data);
  lv_anim_set_playback_time(&PropertyAnimation_2, 1);
  lv_anim_set_playback_delay(&PropertyAnimation_2, 0);
  lv_anim_set_repeat_count(&PropertyAnimation_2, 0);
  lv_anim_set_repeat_delay(&PropertyAnimation_2, 0);
  lv_anim_set_early_apply(&PropertyAnimation_2, false);
  lv_anim_set_ready_cb(&PropertyAnimation_2, iconLOOPdown1);
  lv_anim_start(&PropertyAnimation_2);
}
void iconNEX2NOW_Animation(lv_obj_t *TargetObject, int vTaskDelay) {
  ui_anim_user_data_t *PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
  PropertyAnimation_0_user_data->target = TargetObject;
  PropertyAnimation_0_user_data->val = -1;
  lv_anim_t PropertyAnimation_0;
  lv_anim_init(&PropertyAnimation_0);
  lv_anim_set_time(&PropertyAnimation_0, 500);
  lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
  lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
  lv_anim_set_values(&PropertyAnimation_0, 10, -23);
  lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_overshoot);
  lv_anim_set_delay(&PropertyAnimation_0, vTaskDelay + 0);
  lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
  lv_anim_set_playback_time(&PropertyAnimation_0, 1);
  lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
  lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
  lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
  lv_anim_set_early_apply(&PropertyAnimation_0, false);
  lv_anim_start(&PropertyAnimation_0);
  ui_anim_user_data_t *PropertyAnimation_1_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
  PropertyAnimation_1_user_data->target = TargetObject;
  PropertyAnimation_1_user_data->val = -1;
  lv_anim_t PropertyAnimation_1;
  lv_anim_init(&PropertyAnimation_1);
  lv_anim_set_time(&PropertyAnimation_1, 500);
  lv_anim_set_user_data(&PropertyAnimation_1, PropertyAnimation_1_user_data);
  lv_anim_set_custom_exec_cb(&PropertyAnimation_1, _ui_anim_callback_set_y);
  lv_anim_set_values(&PropertyAnimation_1, -97, -9);
  lv_anim_set_path_cb(&PropertyAnimation_1, lv_anim_path_overshoot);
  lv_anim_set_delay(&PropertyAnimation_1, vTaskDelay + 0);
  lv_anim_set_deleted_cb(&PropertyAnimation_1, _ui_anim_callback_free_user_data);
  lv_anim_set_playback_time(&PropertyAnimation_1, 1);
  lv_anim_set_playback_delay(&PropertyAnimation_1, 0);
  lv_anim_set_repeat_count(&PropertyAnimation_1, 0);
  lv_anim_set_repeat_delay(&PropertyAnimation_1, 0);
  lv_anim_set_early_apply(&PropertyAnimation_1, false);
  lv_anim_start(&PropertyAnimation_1);
  ui_anim_user_data_t *PropertyAnimation_2_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
  PropertyAnimation_2_user_data->target = TargetObject;
  PropertyAnimation_2_user_data->val = -1;
  lv_anim_t PropertyAnimation_2;
  lv_anim_init(&PropertyAnimation_2);
  lv_anim_set_time(&PropertyAnimation_2, 500);
  lv_anim_set_user_data(&PropertyAnimation_2, PropertyAnimation_2_user_data);
  lv_anim_set_custom_exec_cb(&PropertyAnimation_2, _ui_anim_callback_set_image_zoom);
  lv_anim_set_values(&PropertyAnimation_2, 256, 400);
  lv_anim_set_path_cb(&PropertyAnimation_2, lv_anim_path_overshoot);
  lv_anim_set_delay(&PropertyAnimation_2, vTaskDelay + 0);
  lv_anim_set_deleted_cb(&PropertyAnimation_2, _ui_anim_callback_free_user_data);
  lv_anim_set_playback_time(&PropertyAnimation_2, 1);
  lv_anim_set_playback_delay(&PropertyAnimation_2, 0);
  lv_anim_set_repeat_count(&PropertyAnimation_2, 0);
  lv_anim_set_repeat_delay(&PropertyAnimation_2, 0);
  lv_anim_set_early_apply(&PropertyAnimation_2, false);

  lv_anim_start(&PropertyAnimation_2);
}
void iconAppear_Animation(lv_obj_t *TargetObject, int vTaskDelay) {
  lv_img_set_src(ui_iconNEX2, ui_imgset_icon[iconNEX2num]);
  lv_img_set_src(ui_iconPRE2, ui_imgset_icon[iconPRE2num]);
  ui_anim_user_data_t *PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
  PropertyAnimation_0_user_data->target = TargetObject;
  PropertyAnimation_0_user_data->val = -1;
  lv_anim_t PropertyAnimation_0;
  lv_anim_init(&PropertyAnimation_0);
  lv_anim_set_time(&PropertyAnimation_0, 500);
  lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
  lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_image_zoom);
  lv_anim_set_values(&PropertyAnimation_0, 0, 256);
  lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
  lv_anim_set_delay(&PropertyAnimation_0, vTaskDelay + 0);
  lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
  lv_anim_set_playback_time(&PropertyAnimation_0, 0);
  lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
  lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
  lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
  lv_anim_set_early_apply(&PropertyAnimation_0, false);
  lv_anim_start(&PropertyAnimation_0);
}
void icondisapp_Animation(lv_obj_t *TargetObject, int vTaskDelay) {
  ui_anim_user_data_t *PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
  PropertyAnimation_0_user_data->target = TargetObject;
  PropertyAnimation_0_user_data->val = -1;
  lv_anim_t PropertyAnimation_0;
  lv_anim_init(&PropertyAnimation_0);
  lv_anim_set_time(&PropertyAnimation_0, 500);
  lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
  lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_image_zoom);
  lv_anim_set_values(&PropertyAnimation_0, 256, 0);
  lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
  lv_anim_set_delay(&PropertyAnimation_0, vTaskDelay + 0);
  lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
  lv_anim_set_playback_time(&PropertyAnimation_0, 1);
  lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
  lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
  lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
  lv_anim_set_early_apply(&PropertyAnimation_0, false);
  lv_anim_start(&PropertyAnimation_0);
}
void iconPRE2NOW_Animation(lv_obj_t *TargetObject, int vTaskDelay) {
  ui_anim_user_data_t *PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
  PropertyAnimation_0_user_data->target = TargetObject;
  PropertyAnimation_0_user_data->val = -1;
  lv_anim_t PropertyAnimation_0;
  lv_anim_init(&PropertyAnimation_0);
  lv_anim_set_time(&PropertyAnimation_0, 500);
  lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
  lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
  lv_anim_set_values(&PropertyAnimation_0, 13, -23);
  lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_overshoot);
  lv_anim_set_delay(&PropertyAnimation_0, vTaskDelay + 0);
  lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
  lv_anim_set_playback_time(&PropertyAnimation_0, 1);
  lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
  lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
  lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
  lv_anim_set_early_apply(&PropertyAnimation_0, false);
  lv_anim_start(&PropertyAnimation_0);
  ui_anim_user_data_t *PropertyAnimation_1_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
  PropertyAnimation_1_user_data->target = TargetObject;
  PropertyAnimation_1_user_data->val = -1;
  lv_anim_t PropertyAnimation_1;
  lv_anim_init(&PropertyAnimation_1);
  lv_anim_set_time(&PropertyAnimation_1, 500);
  lv_anim_set_user_data(&PropertyAnimation_1, PropertyAnimation_1_user_data);
  lv_anim_set_custom_exec_cb(&PropertyAnimation_1, _ui_anim_callback_set_y);
  lv_anim_set_values(&PropertyAnimation_1, 80, -9);
  lv_anim_set_path_cb(&PropertyAnimation_1, lv_anim_path_overshoot);
  lv_anim_set_delay(&PropertyAnimation_1, vTaskDelay + 0);
  lv_anim_set_deleted_cb(&PropertyAnimation_1, _ui_anim_callback_free_user_data);
  lv_anim_set_playback_time(&PropertyAnimation_1, 1);
  lv_anim_set_playback_delay(&PropertyAnimation_1, 0);
  lv_anim_set_repeat_count(&PropertyAnimation_1, 0);
  lv_anim_set_repeat_delay(&PropertyAnimation_1, 0);
  lv_anim_set_early_apply(&PropertyAnimation_1, false);
  lv_anim_start(&PropertyAnimation_1);
  ui_anim_user_data_t *PropertyAnimation_2_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
  PropertyAnimation_2_user_data->target = TargetObject;
  PropertyAnimation_2_user_data->val = -1;
  lv_anim_t PropertyAnimation_2;
  lv_anim_init(&PropertyAnimation_2);
  lv_anim_set_time(&PropertyAnimation_2, 500);
  lv_anim_set_user_data(&PropertyAnimation_2, PropertyAnimation_2_user_data);
  lv_anim_set_custom_exec_cb(&PropertyAnimation_2, _ui_anim_callback_set_image_zoom);
  lv_anim_set_values(&PropertyAnimation_2, 256, 400);
  lv_anim_set_path_cb(&PropertyAnimation_2, lv_anim_path_overshoot);
  lv_anim_set_delay(&PropertyAnimation_2, vTaskDelay + 0);
  lv_anim_set_deleted_cb(&PropertyAnimation_2, _ui_anim_callback_free_user_data);
  lv_anim_set_playback_time(&PropertyAnimation_2, 1);
  lv_anim_set_playback_delay(&PropertyAnimation_2, 0);
  lv_anim_set_repeat_count(&PropertyAnimation_2, 0);
  lv_anim_set_repeat_delay(&PropertyAnimation_2, 0);
  lv_anim_set_early_apply(&PropertyAnimation_2, false);

  lv_anim_start(&PropertyAnimation_2);
}
void iconNOW2NEX_Animation(lv_obj_t *TargetObject, int vTaskDelay) {
  ui_anim_user_data_t *PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
  PropertyAnimation_0_user_data->target = TargetObject;
  PropertyAnimation_0_user_data->val = -1;
  lv_anim_t PropertyAnimation_0;
  lv_anim_init(&PropertyAnimation_0);
  lv_anim_set_time(&PropertyAnimation_0, 500);
  lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
  lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
  lv_anim_set_values(&PropertyAnimation_0, -23, 10);
  lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_overshoot);
  lv_anim_set_delay(&PropertyAnimation_0, vTaskDelay + 0);
  lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
  lv_anim_set_playback_time(&PropertyAnimation_0, 1);
  lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
  lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
  lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
  lv_anim_set_early_apply(&PropertyAnimation_0, false);
  lv_anim_start(&PropertyAnimation_0);
  ui_anim_user_data_t *PropertyAnimation_1_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
  PropertyAnimation_1_user_data->target = TargetObject;
  PropertyAnimation_1_user_data->val = -1;
  lv_anim_t PropertyAnimation_1;
  lv_anim_init(&PropertyAnimation_1);
  lv_anim_set_time(&PropertyAnimation_1, 500);
  lv_anim_set_user_data(&PropertyAnimation_1, PropertyAnimation_1_user_data);
  lv_anim_set_custom_exec_cb(&PropertyAnimation_1, _ui_anim_callback_set_y);
  lv_anim_set_values(&PropertyAnimation_1, -9, -97);
  lv_anim_set_path_cb(&PropertyAnimation_1, lv_anim_path_overshoot);
  lv_anim_set_delay(&PropertyAnimation_1, vTaskDelay + 0);
  lv_anim_set_deleted_cb(&PropertyAnimation_1, _ui_anim_callback_free_user_data);
  lv_anim_set_playback_time(&PropertyAnimation_1, 1);
  lv_anim_set_playback_delay(&PropertyAnimation_1, 0);
  lv_anim_set_repeat_count(&PropertyAnimation_1, 0);
  lv_anim_set_repeat_delay(&PropertyAnimation_1, 0);
  lv_anim_set_early_apply(&PropertyAnimation_1, false);
  lv_anim_start(&PropertyAnimation_1);
  ui_anim_user_data_t *PropertyAnimation_2_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
  PropertyAnimation_2_user_data->target = TargetObject;
  PropertyAnimation_2_user_data->val = -1;
  lv_anim_t PropertyAnimation_2;
  lv_anim_init(&PropertyAnimation_2);
  lv_anim_set_time(&PropertyAnimation_2, 500);
  lv_anim_set_user_data(&PropertyAnimation_2, PropertyAnimation_2_user_data);
  lv_anim_set_custom_exec_cb(&PropertyAnimation_2, _ui_anim_callback_set_image_zoom);
  lv_anim_set_values(&PropertyAnimation_2, 400, 256);
  lv_anim_set_path_cb(&PropertyAnimation_2, lv_anim_path_overshoot);
  lv_anim_set_delay(&PropertyAnimation_2, vTaskDelay + 0);
  lv_anim_set_deleted_cb(&PropertyAnimation_2, _ui_anim_callback_free_user_data);
  lv_anim_set_playback_time(&PropertyAnimation_2, 1);
  lv_anim_set_playback_delay(&PropertyAnimation_2, 0);
  lv_anim_set_repeat_count(&PropertyAnimation_2, 0);
  lv_anim_set_repeat_delay(&PropertyAnimation_2, 0);
  lv_anim_set_early_apply(&PropertyAnimation_2, false);
  lv_anim_set_ready_cb(&PropertyAnimation_2, iconLOOPup1);
  lv_anim_start(&PropertyAnimation_2);
}

///////////////////// FUNCTIONS ////////////////////
void ui_event_ButtonDown(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {

    iconNEX2NOW_Animation(ui_iconNEX, 100);
    iconNOW2PRE_Animation(ui_iconNOW, 50);
    iconAppear_Animation(ui_iconNEX2, 0);
    icondisapp_Animation(ui_iconPRE, 0);
    icondisapp_Animation(ui_iconPRE2, 0);
  }
}

void ui_event_ButtonUp(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {

    iconNOW2NEX_Animation(ui_iconNOW, 50);
    iconPRE2NOW_Animation(ui_iconPRE, 100);
    iconAppear_Animation(ui_iconPRE2, 0);
    icondisapp_Animation(ui_iconNEX, 0);
    icondisapp_Animation(ui_iconNEX2, 0);
  }
}

void ui_event_ButtonCen(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    dispnow = iconNOWnum;
    switch (iconNOWnum) {
      case 0:
        dispnow = 0;

        _ui_screen_change(&ui_AiChat, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_AiChat_screen_init);

        break;
      case 1:
        dispnow = 1;
        _ui_screen_change(&ui_CLOCK, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_CLOCK_screen_init);
        Rtctaskcreate();

        break;
      case 2:
        dispnow = 2;
        _ui_screen_change(&ui_SETTING, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_SETTING_screen_init);
        break;
      case 3:
        dispnow = 3;
        _ui_screen_change(&ui_CALENDAR, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_CALENDAR_screen_init);
        break;
      case 4:
        dispnow = 4;
        led_set(120);
        _ui_screen_change(&ui_LIGHT, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_LIGHT_screen_init);
        break;
      case 5:
        dispnow = 5;
        ui_ALARM_screen_init();
        _ui_screen_change(&ui_ALARM, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ALARM_screen_init);
        break;

              case 6:
        dispnow = 6;
        
        ui_REMINDER_screen_init();
        _ui_screen_change(&ui_REMINDER, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_REMINDER_screen_init);
        break;
      default:
        break;
    }

    _ui_screen_delete(&ui_DESK);
  }
}

void ui_event_ButtonBACK(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    dispnow = -1;
    _ui_screen_delete(&ui_CLOCK);
    _ui_screen_change(&ui_DESK, LV_SCR_LOAD_ANIM_FADE_ON, 300, 0, &ui_DESK_screen_init);
    Rtctaskdelete();
  }
}
///////////////////// SCREENS ////////////////////

void ui_init(void) {
  lv_disp_t *dispp = lv_disp_get_default();
  lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                            true, LV_FONT_DEFAULT);
  lv_disp_set_theme(dispp, theme);
  ui_DESK_screen_init();
  // ui_CLOCK_screen_init();
  // ui_CALENDAR_screen_init();
  ui____initial_actions0 = lv_obj_create(NULL);
  lv_disp_load_scr(ui_DESK);
}
// SCREEN: ui_SETTING
void ui_SETTING_screen_init(void);
lv_obj_t *ui_SETTING;
lv_obj_t *ui_Container6;
lv_obj_t *ui_Container7;
lv_obj_t *ui_BLslider;
void ui_event_ButtonBACK1(lv_event_t *e);
lv_obj_t *ui_ButtonBACK1;
lv_obj_t *ui_backtext;
lv_obj_t *ui_BLtext;
void ui_event_ButtonGETTIME(lv_event_t *e);
lv_obj_t *ui_ButtonGETTIME;
lv_obj_t *ui_GetTimetext;
lv_obj_t *ui_SETTINGtext;
void ui_event_SETTINGKEY(lv_event_t *e);
lv_obj_t *ui_SETTINGKEY;
lv_obj_t *ui_WIFItext;
void ui_event_WIFIKEY(lv_event_t *e);
lv_obj_t *ui_WIFIKEY;
void ui_event_BLslider(lv_event_t *e);
// CUSTOM VARIABLES
int leddut = 40;

// SCREEN: ui_CALENDAR
void ui_CALENDAR_screen_init(void);

lv_obj_t *ui_CALENDAR;
lv_obj_t *ui_Container4;
lv_obj_t *ui_ButtonDown2;
lv_obj_t *ui_ButtonUp2;
lv_obj_t *ui_ButtonCen2;
lv_obj_t *ui_Calendar1;
// CUSTOM VARIABLES

//ui_CALENDAR
void ui_event_ButtonUp2(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    lv_calendar_date_t *current_date = lv_calendar_get_showed_date(ui_Calendar1);  // 获取当前显示的日期
    int Y = current_date->year;
    int M = current_date->month;  // 获取月份

    Y = (M == 12) ? Y + 1 : Y;
    M = (M == 12) ? 1 : M + 1;
    lv_calendar_set_showed_date(ui_Calendar1, Y, M);
  }
}
void ui_event_ButtonBACK5(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    dispnow = -1;
    _ui_screen_delete(&ui_CALENDAR);
    _ui_screen_change(&ui_DESK, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_DESK_screen_init);
  }
}
void ui_event_ButtonCen2(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    int Y = 2024;
    int M = 12;
    int D = 1;
    getDc(&Y, &M, &D);
    lv_calendar_set_today_date(ui_Calendar1, Y, M, D);
    lv_calendar_set_showed_date(ui_Calendar1, Y, M);
  }
}
void ui_event_ButtonDown2(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    lv_calendar_date_t *current_date = lv_calendar_get_showed_date(ui_Calendar1);  // 获取当前显示的日期
    int Y = current_date->year;
    int M = current_date->month;  // 获取月份

    Y = (M == 1) ? Y - 1 : Y;
    M = (M == 1) ? 12 : M - 1;
    lv_calendar_set_showed_date(ui_Calendar1, Y, M);
  }
}
// SCREEN: ui_SETTIME
void ui_SETTIME_screen_init(void);
lv_obj_t *ui_SETTIME;
lv_obj_t *ui_Container8;
lv_obj_t *ui_Container9;
lv_obj_t *ui_ButtonDown4;
lv_obj_t *ui_ButtonUp4;
lv_obj_t *ui_ButtonCen4;
void ui_event_ButtonBACK2(lv_event_t *e);
lv_obj_t *ui_ButtonBACK2;
lv_obj_t *ui_backtext1;
void ui_event_getTWifiBtn(lv_event_t *e);
lv_obj_t *ui_getTWifiBtn;
lv_obj_t *ui_getTWifi;
void ui_event_timeSetBtn(lv_event_t *e);
lv_obj_t *ui_timeSetBtn;
lv_obj_t *ui_timeSet;
lv_obj_t *ui_Hour0;
lv_obj_t *ui_hour0label;
lv_obj_t *ui_Hour1;
lv_obj_t *ui_hour1label;
lv_obj_t *ui_Min0;
lv_obj_t *ui_min0label;
lv_obj_t *ui_Min1;
lv_obj_t *ui_min1label;
lv_obj_t *ui_settimeLabel1;
int settimemod = 0;
void ui_event_Hour0(lv_event_t *e);
void ui_event_Hour1(lv_event_t *e);
void ui_event_Min0(lv_event_t *e);
void ui_event_Min1(lv_event_t *e);
// CUSTOM VARIABLES


// SCREEN: ui_AiChat
void ui_AiChat_screen_init(void);
lv_obj_t *ui_AiChat;
lv_obj_t *ui_Container10;
void ui_event_ButtonBACK4(lv_event_t *e);
lv_obj_t *ui_ButtonBACK4;
lv_obj_t *ui_aichattext1;
lv_obj_t *ui_aichattext2;
lv_obj_t *ui_aichatSpinner1;
void ui_event_ChatBtn(lv_event_t *e);
lv_obj_t *ui_ChatBtn;
// CUSTOM VARIABLES


// SCREEN: ui_Aiassistant
void ui_Aiassistant_screen_init(void);
lv_obj_t *ui_Aiassistant;
lv_obj_t *ui_Container11;
//void ui_event_ButtonBACK3(lv_event_t *e);
int Ailocalmode = 1;
lv_obj_t *ui_aiassistantSpinner1;
lv_obj_t *ui_aiassistantSpinner2;
lv_obj_t *ui_aiassistantlabel2;
void ui_event_aiassistantSwitch1(lv_event_t *e);
lv_obj_t *ui_aiassistantSwitch1;
lv_obj_t *ui_aiassistantlabel1;
void ui_event_ButtonBACK6(lv_event_t *e);
lv_obj_t *ui_ButtonBACK6;
lv_obj_t *ui_aiassistantSwitch1;
lv_obj_t *ui_aiassistantSwitchtext;
// CUSTOM VARIABLES



// SCREEN: ui_ALARM
int hour1;
int min1;
int hour2;
int min2;
int hour3;
int min3;
void ui_ALARM_screen_init(void);
lv_obj_t *ui_ALARM;
lv_obj_t *ui_Container13;
lv_obj_t *ui_Container15;
void ui_event_ButtonBACK9(lv_event_t *e);
lv_obj_t *ui_ButtonBACK9;
lv_obj_t *ui_backtext4;
lv_obj_t *ui_Alarm1;
void ui_event_Alarmkey(lv_event_t *e);
lv_obj_t *ui_Alarmkey;
void ui_event_Alarmbtn(lv_event_t *e);
lv_obj_t *ui_Alarmbtn;
lv_obj_t *ui_Alarmtext;
lv_obj_t *ui_Alarm2;
void ui_event_Alarmkey2(lv_event_t *e);
lv_obj_t *ui_Alarmkey2;
void ui_event_Alarmbtn2(lv_event_t *e);
lv_obj_t *ui_Alarmbtn2;
lv_obj_t *ui_Alarmtext2;
lv_obj_t *ui_Alarm3;
void ui_event_Alarmkey3(lv_event_t *e);
lv_obj_t *ui_Alarmkey3;
void ui_event_Alarmbtn3(lv_event_t *e);
lv_obj_t *ui_Alarmbtn3;
lv_obj_t *ui_Alarmtext3;





void ui_event_ButtonBACK1(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    dispnow = -1;
    _ui_screen_delete(&ui_SETTING);
    _ui_screen_change(&ui_DESK, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_DESK_screen_init);
  }
}

void ui_event_ButtonGETTIME(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    dispnow = 201;
    settimemod = 0;
    ui_SETTIME_screen_init();
    _ui_screen_delete(&ui_SETTING);
    _ui_screen_change(&ui_SETTIME, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_SETTIME_screen_init);
  }
}

void ui_event_SETTINGKEY(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_VALUE_CHANGED) {
    _ui_label_set_property(ui_SETTINGtext, _UI_LABEL_PROPERTY_TEXT, "ESP-PICO");
    SettingStart(e);
  }
}

void ui_event_BLslider(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_VALUE_CHANGED) {
    setBLight(e);
  }
}
void ui_event_WIFIKEY(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_VALUE_CHANGED) {
    lv_label_set_text(ui_WIFItext, " WIFI:...");
    delay(100);
    Wifistart(e);
  }
}

void ui_event_ButtonBACK2(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);
  if (settimemod == 0) {
    if (event_code == LV_EVENT_CLICKED) {
      dispnow = 2;
      _ui_screen_delete(&ui_SETTIME);
      ui_SETTING_screen_init();
      _ui_screen_change(&ui_SETTING, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_SETTING_screen_init);
    }
  } else {
    if (event_code == LV_EVENT_CLICKED) {
      dispnow = 5;
      //_ui_screen_delete(&ui_SETTIME);
      ui_ALARM_screen_init();
      _ui_screen_change(&ui_ALARM, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_ALARM_screen_init);
    }
  }
}

void ui_event_getTWifiBtn(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    getTWifi(e);
    // _ui_screen_delete(&ui_SETTIME);
    // _ui_screen_change(&ui_DESK, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_DESK_screen_init);
  }
}

void ui_event_timeSetBtn(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    SetClock(e);
  }
}

void ui_event_Hour0(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    setHour0(e);
  }
}

void ui_event_Hour1(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    setHour1(e);
  }
}

void ui_event_Min0(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    setMinu0(e);
  }
}

void ui_event_Min1(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    setMinu1(e);
  }
}


void ui_event_ButtonBACK4(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    dispnow = -1;
    chatstate = 0;
    _ui_screen_delete(&ui_AiChat);
    _ui_screen_change(&ui_DESK, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_DESK_screen_init);
  }
}
void ui_event_ChatBtn(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    ChatClick(e);
  }
}
// void ui_event_ButtonBACK3(lv_event_t *e) {
//   lv_event_code_t event_code = lv_event_get_code(e);

//   if (event_code == LV_EVENT_CLICKED) {
//     dispnow = -1;
//     _ui_screen_delete(&ui_CLOCK);
//     _ui_screen_change(&ui_DESK, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_DESK_screen_init);
//   }
// }

void ui_event_aiassistantSwitch1(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    aicount = 6;
    lv_label_set_text(ui_aiassistantSwitchtext, "云端模型");
  }
}

void ui_event_aiassistantlabel2(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);
  if (event_code == LV_EVENT_VALUE_CHANGED) {
    gotuofunc(e);
  }
}


void ui_event_ButtonBACK6(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    dispnow = -1;
    aicount = 5;
    setAssistantWebRecording(0);

    _ui_screen_delete(&ui_Aiassistant);
    _ui_screen_change(&ui_DESK, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_DESK_screen_init);
  }
}

void ui_event_tap2Clock(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    _ui_screen_delete(&ui_CLOCK);
    _ui_screen_change(&ui_DESK, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_DESK_screen_init);
  }
}

void ui_event_tap2Calendar(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    _ui_screen_delete(&ui_CLOCK);
    _ui_screen_change(&ui_DESK, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_DESK_screen_init);
  }
}

void ui_event_tap2Setting(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    _ui_screen_delete(&ui_CLOCK);
    _ui_screen_change(&ui_DESK, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_DESK_screen_init);
  }
}

void ui_event_tap2Settime(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    _ui_screen_delete(&ui_CLOCK);
    _ui_screen_change(&ui_DESK, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_DESK_screen_init);
  }
}

void ui_event_tap2Aichat(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    _ui_screen_delete(&ui_CLOCK);
    _ui_screen_change(&ui_DESK, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_DESK_screen_init);
  }
}
lv_group_t *grouphand;


// SCREEN: ui_LIGHT
void ui_LIGHT_screen_init(void);
lv_obj_t *ui_LIGHT;
void ui_event_ButtonBACK7(lv_event_t *e);
lv_obj_t *ui_ButtonBACK7;
void ui_event_ButtonUp5(lv_event_t *e);
lv_obj_t *ui_ButtonUp5;
void ui_event_ButtonDown5(lv_event_t *e);
lv_obj_t *ui_ButtonDown5;
lv_obj_t *ui_Image1;

void ui_event_ButtonBACK7(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    _ui_screen_delete(&ui_LIGHT);
    led_set(leddut);
    _ui_screen_change(&ui_DESK, LV_SCR_LOAD_ANIM_NONE, 0, 0, &ui_DESK_screen_init);
  }
}

void ui_event_ButtonUp5(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    setlightU(e);
  }
}

void ui_event_ButtonDown5(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    setlightD(e);
  }
}


void ui_event_ButtonBACK9(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    dispnow = -1;
    _ui_screen_delete(&ui_ALARM);
    _ui_screen_change(&ui_DESK, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_DESK_screen_init);
  }
}

void ui_event_Alarmkey(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_VALUE_CHANGED) {
    ALARM1cfg(e);
  }
}

void ui_event_Alarmbtn(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    ALARM1set(e);
  }
  if (event_code == LV_EVENT_CLICKED) {
    dispnow = 201;
    settimemod = 1;
    ui_SETTIME_screen_init();
    _ui_screen_change(&ui_SETTIME, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_SETTIME_screen_init);
  }
}

void ui_event_Alarmkey2(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_VALUE_CHANGED) {
    ALARM2cfg(e);
  }
}

void ui_event_Alarmbtn2(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    ALARM2set(e);
  }
  if (event_code == LV_EVENT_CLICKED) {
    dispnow = 201;
    settimemod = 2;
    ui_SETTIME_screen_init();
    _ui_screen_change(&ui_SETTIME, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_SETTIME_screen_init);
  }
}

void ui_event_Alarmkey3(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_VALUE_CHANGED) {
    ALARM3cfg(e);
  }
}

void ui_event_Alarmbtn3(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  if (event_code == LV_EVENT_CLICKED) {
    ALARM3set(e);
  }
  if (event_code == LV_EVENT_CLICKED) {
    dispnow = 201;
    settimemod = 3;
    ui_SETTIME_screen_init();
    _ui_screen_change(&ui_SETTIME, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_SETTIME_screen_init);
  }
}


// SCREEN: ui_REMINDER
void ui_REMINDER_screen_init(void);
lv_obj_t * ui_REMINDER;
lv_obj_t * ui_Container12;
void ui_event_ButtonBACK8(lv_event_t * e);
lv_obj_t * ui_ButtonBACK8;
lv_obj_t * ui_backtext3;
lv_obj_t * ui_TextArea1;
void ui_event_MemoRefresh(lv_event_t * e);
lv_obj_t * ui_MemoRefresh;
lv_obj_t * ui_MemoRefreshtext;
void ui_event_reminderDropdown2(lv_event_t * e);
lv_obj_t * ui_reminderDropdown2;
// CUSTOM VARIABLES

const char* reminderC[5];
void ui_event_reminderDropdown2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_VALUE_CHANGED) {
        changereminder(e);
    }
}
void ui_event_MemoRefresh(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        Memorefresh(e);
    }
}
void ui_event_ButtonBACK8(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
      dispnow=-1;
        _ui_screen_delete(&ui_REMINDER);
        _ui_screen_change(&ui_DESK, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, &ui_DESK_screen_init);
    }
}
