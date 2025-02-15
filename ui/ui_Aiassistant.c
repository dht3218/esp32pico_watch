// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: dht8-3

#include "ui.h"

void ui_Aiassistant_screen_init(void)
{
    ui_Aiassistant = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Aiassistant, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    ui_object_set_themeable_style_property(ui_Aiassistant, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                           _ui_theme_color_Back);
    ui_object_set_themeable_style_property(ui_Aiassistant, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                           _ui_theme_alpha_Back);
    ui_object_set_themeable_style_property(ui_Aiassistant, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_GRAD_COLOR,
                                           _ui_theme_color_Mask2);
    lv_obj_set_style_bg_main_stop(ui_Aiassistant, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_Aiassistant, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Aiassistant, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Container11 = lv_obj_create(ui_Aiassistant);
    lv_obj_remove_style_all(ui_Container11);
    lv_obj_set_width(ui_Container11, 111);
    lv_obj_set_height(ui_Container11, 279);
    lv_obj_set_x(ui_Container11, 66);
    lv_obj_set_y(ui_Container11, -1);
    lv_obj_set_align(ui_Container11, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Container11, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    ui_object_set_themeable_style_property(ui_Container11, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                           _ui_theme_color_Mask2);
    ui_object_set_themeable_style_property(ui_Container11, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                           _ui_theme_alpha_Mask2);
    ui_object_set_themeable_style_property(ui_Container11, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_GRAD_COLOR,
                                           _ui_theme_color_Back);
    lv_obj_set_style_bg_main_stop(ui_Container11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_Container11, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Container11, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_aiassistantSpinner1 = lv_spinner_create(ui_Aiassistant, 1000, 90);
    lv_obj_set_width(ui_aiassistantSpinner1, 80);
    lv_obj_set_height(ui_aiassistantSpinner1, 80);
    lv_obj_set_x(ui_aiassistantSpinner1, 0);
    lv_obj_set_y(ui_aiassistantSpinner1, 80);
    lv_obj_set_align(ui_aiassistantSpinner1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_aiassistantSpinner1, LV_OBJ_FLAG_CLICKABLE);      /// Flags
    lv_obj_set_style_arc_width(ui_aiassistantSpinner1, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_object_set_themeable_style_property(ui_aiassistantSpinner1, LV_PART_INDICATOR | LV_STATE_DEFAULT, LV_STYLE_ARC_COLOR,
                                           _ui_theme_color_Front);
    ui_object_set_themeable_style_property(ui_aiassistantSpinner1, LV_PART_INDICATOR | LV_STATE_DEFAULT, LV_STYLE_ARC_OPA,
                                           _ui_theme_alpha_Front);

    ui_aiassistantSpinner2 = lv_spinner_create(ui_aiassistantSpinner1, 1000, 90);
    lv_obj_set_width(ui_aiassistantSpinner2, 40);
    lv_obj_set_height(ui_aiassistantSpinner2, 40);
    lv_obj_set_align(ui_aiassistantSpinner2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_aiassistantSpinner2, LV_OBJ_FLAG_CLICKABLE);      /// Flags
    lv_obj_set_style_blend_mode(ui_aiassistantSpinner2, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    ui_object_set_themeable_style_property(ui_aiassistantSpinner2, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_ARC_COLOR,
                                           _ui_theme_color_Mask1);
    ui_object_set_themeable_style_property(ui_aiassistantSpinner2, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_ARC_OPA,
                                           _ui_theme_alpha_Mask1);

    ui_object_set_themeable_style_property(ui_aiassistantSpinner2, LV_PART_INDICATOR | LV_STATE_DEFAULT, LV_STYLE_ARC_COLOR,
                                           _ui_theme_color_Mask2);
    ui_object_set_themeable_style_property(ui_aiassistantSpinner2, LV_PART_INDICATOR | LV_STATE_DEFAULT, LV_STYLE_ARC_OPA,
                                           _ui_theme_alpha_Mask2);
    lv_obj_set_style_arc_width(ui_aiassistantSpinner2, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_aiassistantlabel2 = lv_label_create(ui_Aiassistant);
    lv_obj_set_width(ui_aiassistantlabel2, LV_SIZE_CONTENT);   /// 16
    lv_obj_set_height(ui_aiassistantlabel2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_aiassistantlabel2, 0);
    lv_obj_set_y(ui_aiassistantlabel2, -20);
    lv_obj_set_align(ui_aiassistantlabel2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_aiassistantlabel2, "listening...");
    ui_object_set_themeable_style_property(ui_aiassistantlabel2, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_Front);
    ui_object_set_themeable_style_property(ui_aiassistantlabel2, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_Front);
    lv_obj_set_style_text_align(ui_aiassistantlabel2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_aiassistantlabel2, &ui_font_SongDenisty16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonBACK6 = lv_btn_create(ui_Aiassistant);
    lv_obj_set_width(ui_ButtonBACK6, 53);
    lv_obj_set_height(ui_ButtonBACK6, 50);
    lv_obj_set_x(ui_ButtonBACK6, -90);
    lv_obj_set_y(ui_ButtonBACK6, -13);
    lv_obj_set_align(ui_ButtonBACK6, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonBACK6, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonBACK6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ButtonBACK6, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonBACK6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_aiassistantSwitch1 = lv_btn_create(ui_Aiassistant);
    lv_obj_set_width(ui_aiassistantSwitch1, 84);
    lv_obj_set_height(ui_aiassistantSwitch1, 30);
    lv_obj_set_x(ui_aiassistantSwitch1, 0);
    lv_obj_set_y(ui_aiassistantSwitch1, -80);
    lv_obj_set_align(ui_aiassistantSwitch1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_aiassistantSwitch1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_aiassistantSwitch1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    ui_object_set_themeable_style_property(ui_aiassistantSwitch1, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                           _ui_theme_color_Front);
    ui_object_set_themeable_style_property(ui_aiassistantSwitch1, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                           _ui_theme_alpha_Front);
    ui_object_set_themeable_style_property(ui_aiassistantSwitch1, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_Back);
    ui_object_set_themeable_style_property(ui_aiassistantSwitch1, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_Back);
    lv_obj_set_style_text_font(ui_aiassistantSwitch1, &ui_font_SongDenisty16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_aiassistantSwitchtext = lv_label_create(ui_aiassistantSwitch1);
    lv_obj_set_width(ui_aiassistantSwitchtext, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_aiassistantSwitchtext, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_aiassistantSwitchtext, LV_ALIGN_CENTER);
    lv_label_set_text(ui_aiassistantSwitchtext, "本地模型");
    ui_object_set_themeable_style_property(ui_aiassistantSwitchtext, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_COLOR,
                                           _ui_theme_color_Mask2);
    ui_object_set_themeable_style_property(ui_aiassistantSwitchtext, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA,
                                           _ui_theme_alpha_Mask2);

    lv_obj_add_event_cb(ui_aiassistantlabel2, ui_event_aiassistantlabel2, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonBACK6, ui_event_ButtonBACK6, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_aiassistantSwitch1, ui_event_aiassistantSwitch1, LV_EVENT_ALL, NULL);

}
