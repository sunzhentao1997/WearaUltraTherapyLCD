/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *param;
	bool param_del;
	lv_obj_t *param_label_1;
	lv_obj_t *param_label_2;
	lv_obj_t *param_btn_1;
	lv_obj_t *param_btn_1_label;
	lv_obj_t *param_btn_2;
	lv_obj_t *param_btn_2_label;
	lv_obj_t *param_label_3;
	lv_obj_t *param_label_4;
	lv_obj_t *param_label_5;
	lv_obj_t *param_label_6;
	lv_obj_t *lii;
	bool lii_del;
	lv_obj_t *lii_btn_1;
	lv_obj_t *lii_btn_1_label;
	lv_obj_t *lii_btn_2;
	lv_obj_t *lii_btn_2_label;
	lv_obj_t *vibration;
	bool vibration_del;
	lv_obj_t *vibration_label_1;
	lv_obj_t *vibration_label_2;
	lv_obj_t *vibration_btn_1;
	lv_obj_t *vibration_btn_1_label;
	lv_obj_t *vibration_btn_2;
	lv_obj_t *vibration_btn_2_label;
	lv_obj_t *vibration_slider_1;
	lv_obj_t *vibration_label_3;
	lv_obj_t *freq;
	bool freq_del;
	lv_obj_t *freq_label_1;
	lv_obj_t *freq_roller_1;
	lv_obj_t *freq_label_2;
	lv_obj_t *freq_label_3;
	lv_obj_t *freq_btn_1;
	lv_obj_t *freq_btn_1_label;
	lv_obj_t *freq_btn_2;
	lv_obj_t *freq_btn_2_label;
	lv_obj_t *Config;
	bool Config_del;
	lv_obj_t *Config_btn_6;
	lv_obj_t *Config_btn_6_label;
	lv_obj_t *Config_btn_5;
	lv_obj_t *Config_btn_5_label;
	lv_obj_t *Config_btn_4;
	lv_obj_t *Config_btn_4_label;
	lv_obj_t *Config_btn_3;
	lv_obj_t *Config_btn_3_label;
	lv_obj_t *Config_btn_1;
	lv_obj_t *Config_btn_1_label;
	lv_obj_t *Config_label_1;
	lv_obj_t *Config_btn_7;
	lv_obj_t *Config_btn_7_label;
	lv_obj_t *main;
	bool main_del;
	lv_obj_t *main_label_2;
	lv_obj_t *main_arc_1;
	lv_obj_t *main_label_3;
	lv_obj_t *main_label_4;
	lv_obj_t *main_label_6;
	lv_obj_t *main_label_7;
	lv_obj_t *main_btn_3;
	lv_obj_t *main_btn_3_label;
	lv_obj_t *main_btn_4;
	lv_obj_t *main_btn_4_label;
	lv_obj_t *main_btn_5;
	lv_obj_t *main_btn_5_label;
	lv_obj_t *main_btn_6;
	lv_obj_t *main_btn_6_label;
	lv_obj_t *main_btn_2;
	lv_obj_t *main_btn_2_label;
	lv_obj_t *main_btn_1;
	lv_obj_t *main_btn_1_label;
	lv_obj_t *main_label_5;
	lv_obj_t *main_btn_7;
	lv_obj_t *main_btn_7_label;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);


extern lv_ui guider_ui;


void setup_scr_param(lv_ui *ui);
void setup_scr_lii(lv_ui *ui);
void setup_scr_vibration(lv_ui *ui);
void setup_scr_freq(lv_ui *ui);
void setup_scr_Config(lv_ui *ui);
void setup_scr_main(lv_ui *ui);

LV_FONT_DECLARE(lv_font_siyuanB_36)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_siyuan_16)
LV_FONT_DECLARE(lv_font_siyuanB_30)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_siyuan_25)
LV_FONT_DECLARE(lv_font_siyuan_27)
LV_FONT_DECLARE(lv_font_siyuan_33)
LV_FONT_DECLARE(lv_font_siyuanB_70)
LV_FONT_DECLARE(lv_font_siyuan_40)
LV_FONT_DECLARE(lv_font_siyuanB_60)


#ifdef __cplusplus
}
#endif
#endif
