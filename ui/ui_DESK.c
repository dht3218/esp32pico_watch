// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: dht8-3
#define AppTotal 7
#define iconNOWnum desktopcnt
#define iconPREnum (iconNOWnum - 1 < 0) ? desktopcnt - 1 + AppTotal : desktopcnt - 1
#define iconNEXnum (iconNOWnum + 1 > AppTotal - 1) ? desktopcnt + 1 - AppTotal : desktopcnt + 1
#define iconPRE2num (iconNOWnum - 2 < 0) ? desktopcnt - 2 + AppTotal : desktopcnt - 2
#define iconNEX2num (iconNOWnum + 2 > AppTotal - 1) ? desktopcnt + 2 - AppTotal : desktopcnt + 2
#include "ui.h"

void ui_DESK_screen_init(void) {
  dispnow = -1;
  ui_DESK = lv_obj_create(NULL);
  lv_obj_clear_flag(ui_DESK, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  ui_object_set_themeable_style_property(ui_DESK, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                         _ui_theme_color_Back);
  ui_object_set_themeable_style_property(ui_DESK, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA, _ui_theme_alpha_Back);
  ui_object_set_themeable_style_property(ui_DESK, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_GRAD_COLOR,
                                         _ui_theme_color_Mask2);
  lv_obj_set_style_bg_main_stop(ui_DESK, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_grad_stop(ui_DESK, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_grad_dir(ui_DESK, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_Container2 = lv_obj_create(ui_DESK);
  lv_obj_remove_style_all(ui_Container2);
  lv_obj_set_width(ui_Container2, 111);
  lv_obj_set_height(ui_Container2, 279);
  lv_obj_set_x(ui_Container2, 66);
  lv_obj_set_y(ui_Container2, -1);
  lv_obj_set_align(ui_Container2, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_Container2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  ui_object_set_themeable_style_property(ui_Container2, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                         _ui_theme_color_Mask2);
  ui_object_set_themeable_style_property(ui_Container2, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                         _ui_theme_alpha_Mask2);
  ui_object_set_themeable_style_property(ui_Container2, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_GRAD_COLOR,
                                         _ui_theme_color_Back);
  lv_obj_set_style_bg_main_stop(ui_Container2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_grad_stop(ui_Container2, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_grad_dir(ui_Container2, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_iconPRE2 = lv_img_create(ui_DESK);
  lv_img_set_src(ui_iconPRE2, ui_imgset_icon[iconPRE2num]);
  lv_obj_set_width(ui_iconPRE2, LV_SIZE_CONTENT);   /// 64
  lv_obj_set_height(ui_iconPRE2, LV_SIZE_CONTENT);  /// 64
  lv_obj_set_x(ui_iconPRE2, 13);
  lv_obj_set_y(ui_iconPRE2, 80);
  lv_obj_set_align(ui_iconPRE2, LV_ALIGN_CENTER);
  lv_obj_add_flag(ui_iconPRE2, LV_OBJ_FLAG_ADV_HITTEST);   /// Flags
  lv_obj_clear_flag(ui_iconPRE2, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(ui_iconPRE2, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
  ui_object_set_themeable_style_property(ui_iconPRE2, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                         _ui_theme_color_Mask2);
  ui_object_set_themeable_style_property(ui_iconPRE2, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                         _ui_theme_alpha_Mask2);
  ui_object_set_themeable_style_property(ui_iconPRE2, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_GRAD_COLOR,
                                         _ui_theme_color_Front);
  lv_obj_set_style_bg_grad_dir(ui_iconPRE2, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_iconNEX2 = lv_img_create(ui_DESK);
  lv_img_set_src(ui_iconNEX2, ui_imgset_icon[iconNEX2num]);
  lv_obj_set_width(ui_iconNEX2, LV_SIZE_CONTENT);   /// 64
  lv_obj_set_height(ui_iconNEX2, LV_SIZE_CONTENT);  /// 64
  lv_obj_set_x(ui_iconNEX2, 10);
  lv_obj_set_y(ui_iconNEX2, -97);
  lv_obj_set_align(ui_iconNEX2, LV_ALIGN_CENTER);
  lv_obj_add_flag(ui_iconNEX2, LV_OBJ_FLAG_ADV_HITTEST);   /// Flags
  lv_obj_clear_flag(ui_iconNEX2, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(ui_iconNEX2, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
  ui_object_set_themeable_style_property(ui_iconNEX2, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                         _ui_theme_color_Mask2);
  ui_object_set_themeable_style_property(ui_iconNEX2, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                         _ui_theme_alpha_Mask2);
  ui_object_set_themeable_style_property(ui_iconNEX2, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_GRAD_COLOR,
                                         _ui_theme_color_Front);
  lv_obj_set_style_bg_grad_dir(ui_iconNEX2, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_iconNEX = lv_img_create(ui_DESK);
  lv_img_set_src(ui_iconNEX, ui_imgset_icon[iconNEXnum]);
  lv_obj_set_width(ui_iconNEX, LV_SIZE_CONTENT);   /// 64
  lv_obj_set_height(ui_iconNEX, LV_SIZE_CONTENT);  /// 64
  lv_obj_set_x(ui_iconNEX, 10);
  lv_obj_set_y(ui_iconNEX, -97);
  lv_obj_set_align(ui_iconNEX, LV_ALIGN_CENTER);
  lv_obj_add_flag(ui_iconNEX, LV_OBJ_FLAG_ADV_HITTEST);   /// Flags
  lv_obj_clear_flag(ui_iconNEX, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(ui_iconNEX, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
  ui_object_set_themeable_style_property(ui_iconNEX, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                         _ui_theme_color_Mask2);
  ui_object_set_themeable_style_property(ui_iconNEX, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                         _ui_theme_alpha_Mask2);
  ui_object_set_themeable_style_property(ui_iconNEX, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_GRAD_COLOR,
                                         _ui_theme_color_Front);
  lv_obj_set_style_bg_grad_dir(ui_iconNEX, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_iconPRE = lv_img_create(ui_DESK);
  lv_img_set_src(ui_iconPRE, ui_imgset_icon[iconPREnum]);
  lv_obj_set_width(ui_iconPRE, LV_SIZE_CONTENT);   /// 64
  lv_obj_set_height(ui_iconPRE, LV_SIZE_CONTENT);  /// 64
  lv_obj_set_x(ui_iconPRE, 13);
  lv_obj_set_y(ui_iconPRE, 80);
  lv_obj_set_align(ui_iconPRE, LV_ALIGN_CENTER);
  lv_obj_add_flag(ui_iconPRE, LV_OBJ_FLAG_ADV_HITTEST);   /// Flags
  lv_obj_clear_flag(ui_iconPRE, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(ui_iconPRE, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
  ui_object_set_themeable_style_property(ui_iconPRE, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                         _ui_theme_color_Mask2);
  ui_object_set_themeable_style_property(ui_iconPRE, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                         _ui_theme_alpha_Mask2);
  ui_object_set_themeable_style_property(ui_iconPRE, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_GRAD_COLOR,
                                         _ui_theme_color_Front);
  lv_obj_set_style_bg_grad_dir(ui_iconPRE, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_iconNOW = lv_img_create(ui_DESK);
  lv_img_set_src(ui_iconNOW, ui_imgset_icon[iconNOWnum]);
  lv_obj_set_width(ui_iconNOW, LV_SIZE_CONTENT);   /// 64
  lv_obj_set_height(ui_iconNOW, LV_SIZE_CONTENT);  /// 64
  lv_obj_set_x(ui_iconNOW, -23);
  lv_obj_set_y(ui_iconNOW, -9);
  lv_obj_set_align(ui_iconNOW, LV_ALIGN_CENTER);
  lv_obj_add_flag(ui_iconNOW, LV_OBJ_FLAG_ADV_HITTEST);   /// Flags
  lv_obj_clear_flag(ui_iconNOW, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_img_set_zoom(ui_iconNOW, 400);
  lv_obj_set_style_radius(ui_iconNOW, 20000, LV_PART_MAIN | LV_STATE_DEFAULT);
  ui_object_set_themeable_style_property(ui_iconNOW, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                         _ui_theme_color_Mask2);
  ui_object_set_themeable_style_property(ui_iconNOW, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                         _ui_theme_alpha_Mask2);
  ui_object_set_themeable_style_property(ui_iconNOW, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_GRAD_COLOR,
                                         _ui_theme_color_Front);
  lv_obj_set_style_bg_grad_dir(ui_iconNOW, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_Container1 = lv_obj_create(ui_DESK);
  lv_obj_remove_style_all(ui_Container1);
  lv_obj_set_width(ui_Container1, 132);
  lv_obj_set_height(ui_Container1, 194);
  lv_obj_set_x(ui_Container1, 117);
  lv_obj_set_y(ui_Container1, -9);
  lv_obj_set_align(ui_Container1, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_Container1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(ui_Container1, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
  ui_object_set_themeable_style_property(ui_Container1, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                         _ui_theme_color_Front);
  ui_object_set_themeable_style_property(ui_Container1, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                         _ui_theme_alpha_Front);
  ui_object_set_themeable_style_property(ui_Container1, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_GRAD_COLOR,
                                         _ui_theme_color_Mask2);
  lv_obj_set_style_bg_main_stop(ui_Container1, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_grad_stop(ui_Container1, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_grad_dir(ui_Container1, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_ButtonDown = lv_btn_create(ui_DESK);
  lv_obj_set_width(ui_ButtonDown, 44);
  lv_obj_set_height(ui_ButtonDown, 50);
  lv_obj_set_x(ui_ButtonDown, 80);
  lv_obj_set_y(ui_ButtonDown, 90);
  lv_obj_set_align(ui_ButtonDown, LV_ALIGN_CENTER);
  lv_obj_add_flag(ui_ButtonDown, LV_OBJ_FLAG_SCROLL_ON_FOCUS);  /// Flags
  lv_obj_clear_flag(ui_ButtonDown, LV_OBJ_FLAG_SCROLLABLE);     /// Flags
  lv_obj_set_style_bg_color(ui_ButtonDown, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_ButtonDown, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_ButtonUp = lv_btn_create(ui_DESK);
  lv_obj_set_width(ui_ButtonUp, 44);
  lv_obj_set_height(ui_ButtonUp, 50);
  lv_obj_set_x(ui_ButtonUp, 80);
  lv_obj_set_y(ui_ButtonUp, -90);
  lv_obj_set_align(ui_ButtonUp, LV_ALIGN_CENTER);
  lv_obj_add_flag(ui_ButtonUp, LV_OBJ_FLAG_SCROLL_ON_FOCUS);  /// Flags
  lv_obj_clear_flag(ui_ButtonUp, LV_OBJ_FLAG_SCROLLABLE);     /// Flags
  lv_obj_set_style_bg_color(ui_ButtonUp, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_ButtonUp, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_ButtonCen = lv_btn_create(ui_DESK);
  lv_obj_set_width(ui_ButtonCen, 53);
  lv_obj_set_height(ui_ButtonCen, 50);
  lv_obj_set_x(ui_ButtonCen, 88);
  lv_obj_set_y(ui_ButtonCen, -13);
  lv_obj_set_align(ui_ButtonCen, LV_ALIGN_CENTER);
  lv_obj_add_flag(ui_ButtonCen, LV_OBJ_FLAG_SCROLL_ON_FOCUS);  /// Flags
  lv_obj_clear_flag(ui_ButtonCen, LV_OBJ_FLAG_SCROLLABLE);     /// Flags
  lv_obj_set_style_bg_color(ui_ButtonCen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_ButtonCen, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_battery0 = lv_obj_create(ui_DESK);
  lv_obj_set_width(ui_battery0, 32);
  lv_obj_set_height(ui_battery0, 15);
  lv_obj_set_x(ui_battery0, -2);
  lv_obj_set_y(ui_battery0, 125);
  lv_obj_set_align(ui_battery0, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_battery0, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(ui_battery0, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
  ui_object_set_themeable_style_property(ui_battery0, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                         _ui_theme_color_Mask1);
  ui_object_set_themeable_style_property(ui_battery0, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                         _ui_theme_alpha_Mask1);
  ui_object_set_themeable_style_property(ui_battery0, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_COLOR,
                                         _ui_theme_color_Front);
  ui_object_set_themeable_style_property(ui_battery0, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_OPA,
                                         _ui_theme_alpha_Front);
  /* 设置边框宽度 */
  lv_obj_set_style_border_width(ui_battery0, 1, LV_PART_MAIN | LV_STATE_DEFAULT);  // 将边框宽度设置为1
  ui_batvalue = lv_label_create(ui_battery0);
  lv_obj_set_width(ui_batvalue, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(ui_batvalue, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(ui_batvalue, LV_ALIGN_CENTER);
  getbat();

  ui_object_set_themeable_style_property(ui_batvalue, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                         _ui_theme_color_Front);
  ui_object_set_themeable_style_property(ui_batvalue, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                         _ui_theme_alpha_Front);

  ui_battery1 = lv_obj_create(ui_DESK);
  lv_obj_set_width(ui_battery1, 7);
  lv_obj_set_height(ui_battery1, 10);
  lv_obj_set_x(ui_battery1, 15);
  lv_obj_set_y(ui_battery1, 125);
  lv_obj_set_align(ui_battery1, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_battery1, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(ui_battery1, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
  ui_object_set_themeable_style_property(ui_battery1, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                         _ui_theme_color_Mask1);
  ui_object_set_themeable_style_property(ui_battery1, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                         _ui_theme_alpha_Mask1);
  ui_object_set_themeable_style_property(ui_battery1, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_COLOR,
                                         _ui_theme_color_Front);
  ui_object_set_themeable_style_property(ui_battery1, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BORDER_OPA,
                                         _ui_theme_alpha_Front);

  lv_obj_set_style_border_width(ui_battery1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);  // 将边框宽度设置为1


  lv_obj_add_event_cb(ui_ButtonDown, ui_event_ButtonDown, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_ButtonUp, ui_event_ButtonUp, LV_EVENT_ALL, NULL);
  lv_obj_add_event_cb(ui_ButtonCen, ui_event_ButtonCen, LV_EVENT_ALL, NULL);
  // lv_group_remove_all_objs(grouphand);
  // lv_group_add_obj(grouphand, ui_ButtonDown);
  // lv_group_add_obj(grouphand, ui_ButtonCen);
  // lv_group_add_obj(grouphand, ui_ButtonCen);
}
