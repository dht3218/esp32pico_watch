// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: dht8-3

#include "ui.h"

void ui_CLOCK_screen_init(void)
{
    ui_CLOCK = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_CLOCK, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    ui_object_set_themeable_style_property(ui_CLOCK, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                           _ui_theme_color_Back);
    ui_object_set_themeable_style_property(ui_CLOCK, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                           _ui_theme_alpha_Back);
    ui_object_set_themeable_style_property(ui_CLOCK, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_GRAD_COLOR,
                                           _ui_theme_color_Mask2);
    lv_obj_set_style_bg_main_stop(ui_CLOCK, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_CLOCK, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_CLOCK, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Container3 = lv_obj_create(ui_CLOCK);
    lv_obj_remove_style_all(ui_Container3);
    lv_obj_set_width(ui_Container3, 111);
    lv_obj_set_height(ui_Container3, 279);
    lv_obj_set_x(ui_Container3, 66);
    lv_obj_set_y(ui_Container3, -1);
    lv_obj_set_align(ui_Container3, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Container3, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    ui_object_set_themeable_style_property(ui_Container3, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                           _ui_theme_color_Mask2);
    ui_object_set_themeable_style_property(ui_Container3, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                           _ui_theme_alpha_Mask2);
    ui_object_set_themeable_style_property(ui_Container3, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_GRAD_COLOR,
                                           _ui_theme_color_Back);
    lv_obj_set_style_bg_main_stop(ui_Container3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_Container3, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Container3, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonDown1 = lv_btn_create(ui_CLOCK);
    lv_obj_set_width(ui_ButtonDown1, 44);
    lv_obj_set_height(ui_ButtonDown1, 50);
    lv_obj_set_x(ui_ButtonDown1, 80);
    lv_obj_set_y(ui_ButtonDown1, 90);
    lv_obj_set_align(ui_ButtonDown1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonDown1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonDown1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonDown1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonDown1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonUp1 = lv_btn_create(ui_CLOCK);
    lv_obj_set_width(ui_ButtonUp1, 44);
    lv_obj_set_height(ui_ButtonUp1, 50);
    lv_obj_set_x(ui_ButtonUp1, 80);
    lv_obj_set_y(ui_ButtonUp1, -90);
    lv_obj_set_align(ui_ButtonUp1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonUp1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonUp1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonUp1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonUp1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonCen1 = lv_btn_create(ui_CLOCK);
    lv_obj_set_width(ui_ButtonCen1, 53);
    lv_obj_set_height(ui_ButtonCen1, 50);
    lv_obj_set_x(ui_ButtonCen1, 88);
    lv_obj_set_y(ui_ButtonCen1, -13);
    lv_obj_set_align(ui_ButtonCen1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonCen1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonCen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonCen1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonCen1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Container5 = lv_obj_create(ui_CLOCK);
    lv_obj_remove_style_all(ui_Container5);
    lv_obj_set_width(ui_Container5, 200);
    lv_obj_set_height(ui_Container5, 220);
    lv_obj_set_x(ui_Container5, 0);
    lv_obj_set_y(ui_Container5, 1);
    lv_obj_set_align(ui_Container5, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Container5, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Container5, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_object_set_themeable_style_property(ui_Container5, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                           _ui_theme_color_Mask2);
    ui_object_set_themeable_style_property(ui_Container5, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                           _ui_theme_alpha_Mask2);
    ui_object_set_themeable_style_property(ui_Container5, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_GRAD_COLOR,
                                           _ui_theme_color_Mask1);
    lv_obj_set_style_bg_grad_dir(ui_Container5, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_HOUR = lv_label_create(ui_Container5);
    lv_obj_set_width(ui_HOUR, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_HOUR, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_HOUR, -22);
    lv_obj_set_y(ui_HOUR, -54);
    lv_obj_set_align(ui_HOUR, LV_ALIGN_CENTER);
    lv_label_set_text(ui_HOUR, "20");
    ui_object_set_themeable_style_property(ui_HOUR, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_Front);
    ui_object_set_themeable_style_property(ui_HOUR, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_Front);
    lv_obj_set_style_text_align(ui_HOUR, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_HOUR, &ui_font_CLOCKfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MIN = lv_label_create(ui_Container5);
    lv_obj_set_width(ui_MIN, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MIN, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_MIN, 26);
    lv_obj_set_y(ui_MIN, 60);
    lv_obj_set_align(ui_MIN, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MIN, "19");
    ui_object_set_themeable_style_property(ui_MIN, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_Front);
    ui_object_set_themeable_style_property(ui_MIN, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_Front);
    lv_obj_set_style_text_align(ui_MIN, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_MIN, &ui_font_CLOCKfont, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Panel2 = lv_obj_create(ui_Container5);
    lv_obj_set_width(ui_Panel2, 160);
    lv_obj_set_height(ui_Panel2, 20);
    lv_obj_set_align(ui_Panel2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    ui_object_set_themeable_style_property(ui_Panel2, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                           _ui_theme_color_Mask2);
    ui_object_set_themeable_style_property(ui_Panel2, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                           _ui_theme_alpha_Mask2);
    lv_obj_set_style_border_color(ui_Panel2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label3 = lv_label_create(ui_Panel2);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label3, "2024-11-2");
    lv_obj_set_style_text_align(ui_Label3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonBACK = lv_btn_create(ui_CLOCK);
    lv_obj_set_width(ui_ButtonBACK, 65);
    lv_obj_set_height(ui_ButtonBACK, 50);
    lv_obj_set_x(ui_ButtonBACK, -80);
    lv_obj_set_y(ui_ButtonBACK, 0);
    lv_obj_set_align(ui_ButtonBACK, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonBACK, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonBACK, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonBACK, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonBACK, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //lv_obj_add_event_cb(ui_ButtonDown1, ui_event_ButtonDown1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonBACK, ui_event_ButtonBACK, LV_EVENT_ALL, NULL);

}