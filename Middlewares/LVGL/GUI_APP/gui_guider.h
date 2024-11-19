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
  
	lv_obj_t *main;
	bool main_del;
	lv_obj_t *main_paging;
	lv_obj_t *main_paging_label;
	lv_obj_t *main_label_7;
	lv_obj_t *main_label_3;
	lv_obj_t *main_time;
	lv_obj_t *main_grat1;
	lv_obj_t *main_grat2;
	lv_obj_t *main_grat3;
	lv_obj_t *main_grat4;
	lv_obj_t *main_label_11;
	lv_obj_t *main_label_4;
	lv_obj_t *main_label_10;
	lv_obj_t *main_arc_1;
	lv_obj_t *main_stop;
	lv_obj_t *main_stop_label;
	lv_obj_t *main_pause;
	lv_obj_t *main_pause_label;
	lv_obj_t *main_continue;
	lv_obj_t *main_continue_label;
	lv_obj_t *main_ulock;
	lv_obj_t *main_suo;
	lv_obj_t *main_suo_label;
	lv_obj_t *main_start;
	lv_obj_t *main_start_label;
	lv_obj_t *main_label_13;
	lv_obj_t *main_label_12;
	lv_obj_t *main_btn_1;
	lv_obj_t *main_btn_1_label;
	lv_obj_t *main_btn_2;
	lv_obj_t *main_btn_2_label;
	lv_obj_t *main_label_14;
	lv_obj_t *main_label_15;
	lv_obj_t *config;
	bool config_del;
	lv_obj_t *config_logo;
	lv_obj_t *config_battery;
	lv_obj_t *config_grat4;
	lv_obj_t *config_grat3;
	lv_obj_t *config_grat2;
	lv_obj_t *config_grat1;
	lv_obj_t *config_param;
	lv_obj_t *config_param_label;
	lv_obj_t *config_light;
	lv_obj_t *config_light_label;
	lv_obj_t *config_vibra;
	lv_obj_t *config_vibra_label;
	lv_obj_t *config_freq;
	lv_obj_t *config_freq_label;
	lv_obj_t *config_lock_on;
	lv_obj_t *config_lock_on_label;
	lv_obj_t *config_back;
	lv_obj_t *config_back_label;
	lv_obj_t *config_label_1;
	lv_obj_t *config_label_2;
	lv_obj_t *config_label_3;
	lv_obj_t *config_label_4;
	lv_obj_t *param;
	bool param_del;
	lv_obj_t *param_logo;
	lv_obj_t *param_battery;
	lv_obj_t *param_grat4;
	lv_obj_t *param_grat3;
	lv_obj_t *param_grat2;
	lv_obj_t *param_grat1;
	lv_obj_t *param_label_1;
	lv_obj_t *param_label_2;
	lv_obj_t *param_label_3;
	lv_obj_t *param_label_4;
	lv_obj_t *param_label_5;
	lv_obj_t *param_label_6;
	lv_obj_t *param_back;
	lv_obj_t *param_back_label;
	lv_obj_t *param_DeviceId;
	lv_obj_t *param_DeviceId_label;
	lv_obj_t *param_Power;
	lv_obj_t *param_Power_label;
	lv_obj_t *param_Temp;
	lv_obj_t *param_Temp_label;
	lv_obj_t *param_btnm_1;
	lv_obj_t *param_back_p;
	lv_obj_t *param_back_p_label;
	lv_obj_t *param_label_7;
	lv_obj_t *param_Del;
	lv_obj_t *param_Del_label;
	lv_obj_t *light;
	bool light_del;
	lv_obj_t *light_logo;
	lv_obj_t *light_battery;
	lv_obj_t *light_label_2;
	lv_obj_t *light_label_3;
	lv_obj_t *light_label_4;
	lv_obj_t *light_label_5;
	lv_obj_t *light_label_6;
	lv_obj_t *light_slider_1;
	lv_obj_t *light_precent;
	lv_obj_t *light_back;
	lv_obj_t *light_back_label;
	lv_obj_t *light_save;
	lv_obj_t *light_save_label;
	lv_obj_t *light_label_7;
	lv_obj_t *light_label_8;
	lv_obj_t *light_btn_1;
	lv_obj_t *light_btn_1_label;
	lv_obj_t *light_label_9;
	lv_obj_t *vibra;
	bool vibra_del;
	lv_obj_t *vibra_logo;
	lv_obj_t *vibra_battery;
	lv_obj_t *vibra_label_2;
	lv_obj_t *vibra_label_3;
	lv_obj_t *vibra_label_4;
	lv_obj_t *vibra_label_5;
	lv_obj_t *vibra_label_6;
	lv_obj_t *vibra_back;
	lv_obj_t *vibra_back_label;
	lv_obj_t *vibra_save;
	lv_obj_t *vibra_save_label;
	lv_obj_t *vibra_slider_1;
	lv_obj_t *vibra_label_7;
	lv_obj_t *vibra_label_8;
	lv_obj_t *vibra_label_9;
	lv_obj_t *vibra_label_10;
	lv_obj_t *vibra_btn_1;
	lv_obj_t *vibra_btn_1_label;
	lv_obj_t *vibras;
	bool vibras_del;
	lv_obj_t *vibras_logo;
	lv_obj_t *vibras_battery;
	lv_obj_t *vibras_label_2;
	lv_obj_t *vibras_label_3;
	lv_obj_t *vibras_label_4;
	lv_obj_t *vibras_label_5;
	lv_obj_t *vibras_label_6;
	lv_obj_t *vibras_back;
	lv_obj_t *vibras_back_label;
	lv_obj_t *vibras_sw_1;
	lv_obj_t *vibras_label_8;
	lv_obj_t *freq;
	bool freq_del;
	lv_obj_t *freq_logo;
	lv_obj_t *freq_battery;
	lv_obj_t *freq_label_2;
	lv_obj_t *freq_label_3;
	lv_obj_t *freq_label_4;
	lv_obj_t *freq_label_5;
	lv_obj_t *freq_label_6;
	lv_obj_t *freq_back;
	lv_obj_t *freq_back_label;
	lv_obj_t *freq_save;
	lv_obj_t *freq_save_label;
	lv_obj_t *freq_roller_1;
	lv_obj_t *freq_label_7;
	lv_obj_t *freq_label_8;
	lv_obj_t *freq_label_9;
	lv_obj_t *freq_label_10;
	lv_obj_t *freq_btn_1;
	lv_obj_t *freq_btn_1_label;
	lv_obj_t *password1;
	bool password1_del;
	lv_obj_t *password1_label_1;
	lv_obj_t *password1_btnm_1;
	lv_obj_t *password1_label_2;
	lv_obj_t *password1_label_3;
	lv_obj_t *password1_label_4;
	lv_obj_t *password1_label_5;
	lv_obj_t *password1_label_6;
	lv_obj_t *password1_label_7;
	lv_obj_t *password1_label_8;
	lv_obj_t *password1_label_9;
	lv_obj_t *password1_label_10;
	lv_obj_t *password1_label_11;
	lv_obj_t *password1_label_12;
	lv_obj_t *password1_label_13;
	lv_obj_t *password1_btn_1;
	lv_obj_t *password1_btn_1_label;
	lv_obj_t *password1_label_14;
	lv_obj_t *password1_label_15;
	lv_obj_t *password1_label_16;
	lv_obj_t *password1_btn_2;
	lv_obj_t *password1_btn_2_label;
	lv_obj_t *password2;
	bool password2_del;
	lv_obj_t *password2_label_1;
	lv_obj_t *password2_btnm_1;
	lv_obj_t *password2_label_2;
	lv_obj_t *password2_label_3;
	lv_obj_t *password2_label_4;
	lv_obj_t *password2_label_5;
	lv_obj_t *password2_label_6;
	lv_obj_t *password2_label_7;
	lv_obj_t *password2_label_8;
	lv_obj_t *password2_label_9;
	lv_obj_t *password2_label_10;
	lv_obj_t *password2_label_11;
	lv_obj_t *password2_label_12;
	lv_obj_t *password2_label_13;
	lv_obj_t *password2_btn_1;
	lv_obj_t *password2_btn_1_label;
	lv_obj_t *password2_label_14;
	lv_obj_t *password2_label_15;
	lv_obj_t *password2_btn_2;
	lv_obj_t *password2_btn_2_label;
	lv_obj_t *password2_label_19;
	lv_obj_t *password2_label_17;
	lv_obj_t *password2_btn_3;
	lv_obj_t *password2_btn_3_label;
	lv_obj_t *password2_label_18;
	lv_obj_t *charge;
	bool charge_del;
	lv_obj_t *charge_label_1;
	lv_obj_t *charge_label_2;
	lv_obj_t *charge_label_3;
	lv_obj_t *charge_label_4;
	lv_obj_t *charge_label_5;
	lv_obj_t *charge_label_6;
	lv_obj_t *charge_label_7;
	lv_obj_t *charge_label_8;
	lv_obj_t *boot;
	bool boot_del;
	lv_obj_t *boot_label_1;
	lv_obj_t *boot_label_2;
	lv_obj_t *boot_label_3;
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


void setup_scr_main(lv_ui *ui);
void setup_scr_config(lv_ui *ui);
void setup_scr_param(lv_ui *ui);
void setup_scr_light(lv_ui *ui);
void setup_scr_vibra(lv_ui *ui);
void setup_scr_vibras(lv_ui *ui);
void setup_scr_freq(lv_ui *ui);
void setup_scr_password1(lv_ui *ui);
void setup_scr_password2(lv_ui *ui);
void setup_scr_charge(lv_ui *ui);
void setup_scr_boot(lv_ui *ui);

LV_IMG_DECLARE(_battery_1_61x31);

LV_IMG_DECLARE(_pressing2_181x100);

LV_IMG_DECLARE(_pressing2_181x100);

LV_IMG_DECLARE(_pressing2_181x100);

LV_IMG_DECLARE(_pressed_406x100);

LV_IMG_DECLARE(_3232_60x123);

LV_IMG_DECLARE(_pressed_406x100);

LV_IMG_DECLARE(_battery_1_61x31);

LV_IMG_DECLARE(_back_154x68);

LV_IMG_DECLARE(_param_38x38);

LV_IMG_DECLARE(_light_38x38);

LV_IMG_DECLARE(_vibra_38x38);

LV_IMG_DECLARE(_freq_38x38);

LV_IMG_DECLARE(_battery_1_61x31);

LV_IMG_DECLARE(_back_154x68);

LV_IMG_DECLARE(_battery_1_61x31);

LV_IMG_DECLARE(_back_154x68);

LV_IMG_DECLARE(_save_154x68);

LV_IMG_DECLARE(_success_75x75);

LV_IMG_DECLARE(_battery_1_61x31);

LV_IMG_DECLARE(_back_154x68);

LV_IMG_DECLARE(_save_154x68);

LV_IMG_DECLARE(_success_75x75);

LV_IMG_DECLARE(_battery_1_61x31);

LV_IMG_DECLARE(_back_154x68);

LV_IMG_DECLARE(_battery_1_61x31);

LV_IMG_DECLARE(_back_154x68);

LV_IMG_DECLARE(_save_154x68);

LV_IMG_DECLARE(_success_75x75);

LV_IMG_DECLARE(_battery_1_61x31);

LV_IMG_DECLARE(_erro_75x75);

LV_IMG_DECLARE(_battery_1_61x31);

LV_IMG_DECLARE(_locked_88x88);

LV_IMG_DECLARE(_erro_88x88);

LV_FONT_DECLARE(lv_customer_font_NSHBold_36)
LV_FONT_DECLARE(lv_customer_font_NSHMedium_40)
LV_FONT_DECLARE(lv_customer_font_alimama_70)
LV_FONT_DECLARE(lv_customer_font_NSHRegular_18)
LV_FONT_DECLARE(lv_customer_font_NSHBold_40)
LV_FONT_DECLARE(lv_customer_font_alimama_45)
LV_FONT_DECLARE(lv_customer_font_NSHBold_60)
LV_FONT_DECLARE(lv_customer_font_NSHRegular_28)
LV_FONT_DECLARE(lv_customer_font_NSHRegular_33)
LV_FONT_DECLARE(lv_customer_font_NSHBold_33)
LV_FONT_DECLARE(lv_customer_font_NSHBold_30)
LV_FONT_DECLARE(lv_customer_font_NSHRegular_24)
LV_FONT_DECLARE(lv_customer_font_AlibabaMed_50)
LV_FONT_DECLARE(lv_customer_font_NSHBlack_43)
LV_FONT_DECLARE(lv_customer_font_NSHRegular_36)
LV_FONT_DECLARE(lv_customer_font_NSHRegular_48)
LV_FONT_DECLARE(lv_customer_font_NSHRegular_60)
LV_FONT_DECLARE(lv_customer_font_NSHRegular_50)
LV_FONT_DECLARE(lv_customer_font_alimama_28)
LV_FONT_DECLARE(lv_customer_font_Alibaba_25)


#ifdef __cplusplus
}
#endif
#endif
