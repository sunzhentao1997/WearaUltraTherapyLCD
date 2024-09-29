/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_Config(lv_ui *ui)
{
	//Write codes Config
	ui->Config = lv_obj_create(NULL);
	lv_obj_set_size(ui->Config, 480, 800);
	lv_obj_set_scrollbar_mode(ui->Config, LV_SCROLLBAR_MODE_OFF);

	//Write style for Config, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->Config, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->Config, lv_color_hex(0x114c8b), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->Config, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Config_btn_6
	ui->Config_btn_6 = lv_btn_create(ui->Config);
	ui->Config_btn_6_label = lv_label_create(ui->Config_btn_6);
	lv_label_set_text(ui->Config_btn_6_label, "   震动                                       > ");
	lv_label_set_long_mode(ui->Config_btn_6_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->Config_btn_6_label, LV_ALIGN_LEFT_MID, 0, 0);
	lv_obj_set_style_pad_all(ui->Config_btn_6, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->Config_btn_6_label, LV_PCT(100));
	lv_obj_set_pos(ui->Config_btn_6, 19, 418);
	lv_obj_set_size(ui->Config_btn_6, 442, 67);

	//Write style for Config_btn_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->Config_btn_6, 166, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->Config_btn_6, lv_color_hex(0x509BE6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->Config_btn_6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->Config_btn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->Config_btn_6, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->Config_btn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->Config_btn_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->Config_btn_6, &lv_font_siyuan_33, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->Config_btn_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->Config_btn_6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Config_btn_5
	ui->Config_btn_5 = lv_btn_create(ui->Config);
	ui->Config_btn_5_label = lv_label_create(ui->Config_btn_5);
	lv_label_set_text(ui->Config_btn_5_label, "   亮度                                       > ");
	lv_label_set_long_mode(ui->Config_btn_5_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->Config_btn_5_label, LV_ALIGN_LEFT_MID, 0, 0);
	lv_obj_set_style_pad_all(ui->Config_btn_5, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->Config_btn_5_label, LV_PCT(100));
	lv_obj_set_pos(ui->Config_btn_5, 19, 230);
	lv_obj_set_size(ui->Config_btn_5, 442, 67);

	//Write style for Config_btn_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->Config_btn_5, 166, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->Config_btn_5, lv_color_hex(0x509BE6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->Config_btn_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->Config_btn_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->Config_btn_5, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->Config_btn_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->Config_btn_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->Config_btn_5, &lv_font_siyuan_33, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->Config_btn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->Config_btn_5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Config_btn_4
	ui->Config_btn_4 = lv_btn_create(ui->Config);
	ui->Config_btn_4_label = lv_label_create(ui->Config_btn_4);
	lv_label_set_text(ui->Config_btn_4_label, "   频率                                       > ");
	lv_label_set_long_mode(ui->Config_btn_4_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->Config_btn_4_label, LV_ALIGN_LEFT_MID, 0, 0);
	lv_obj_set_style_pad_all(ui->Config_btn_4, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->Config_btn_4_label, LV_PCT(100));
	lv_obj_set_pos(ui->Config_btn_4, 19, 324);
	lv_obj_set_size(ui->Config_btn_4, 442, 67);

	//Write style for Config_btn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->Config_btn_4, 166, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->Config_btn_4, lv_color_hex(0x509BE6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->Config_btn_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->Config_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->Config_btn_4, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->Config_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->Config_btn_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->Config_btn_4, &lv_font_siyuan_33, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->Config_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->Config_btn_4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Config_btn_3
	ui->Config_btn_3 = lv_btn_create(ui->Config);
	ui->Config_btn_3_label = lv_label_create(ui->Config_btn_3);
	lv_label_set_text(ui->Config_btn_3_label, "   出厂参数                               > ");
	lv_label_set_long_mode(ui->Config_btn_3_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->Config_btn_3_label, LV_ALIGN_LEFT_MID, 0, 0);
	lv_obj_set_style_pad_all(ui->Config_btn_3, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->Config_btn_3_label, LV_PCT(100));
	lv_obj_set_pos(ui->Config_btn_3, 19, 136);
	lv_obj_set_size(ui->Config_btn_3, 442, 67);

	//Write style for Config_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->Config_btn_3, 166, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->Config_btn_3, lv_color_hex(0x509BE6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->Config_btn_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->Config_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->Config_btn_3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->Config_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->Config_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->Config_btn_3, &lv_font_siyuan_33, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->Config_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->Config_btn_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Config_btn_1
	ui->Config_btn_1 = lv_btn_create(ui->Config);
	ui->Config_btn_1_label = lv_label_create(ui->Config_btn_1);
	lv_label_set_text(ui->Config_btn_1_label, "保   存 ");
	lv_label_set_long_mode(ui->Config_btn_1_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->Config_btn_1_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->Config_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->Config_btn_1_label, LV_PCT(100));
	lv_obj_set_pos(ui->Config_btn_1, 38, 695);
	lv_obj_set_size(ui->Config_btn_1, 135, 67);

	//Write style for Config_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->Config_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->Config_btn_1, lv_color_hex(0x00BAAB), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->Config_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->Config_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->Config_btn_1, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->Config_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->Config_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->Config_btn_1, &lv_font_siyuanB_36, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->Config_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->Config_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Config_label_1
	ui->Config_label_1 = lv_label_create(ui->Config);
	lv_label_set_text(ui->Config_label_1, "LIUS");
	lv_label_set_long_mode(ui->Config_label_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->Config_label_1, 19, 15);
	lv_obj_set_size(ui->Config_label_1, 84, 45);

	//Write style for Config_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->Config_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->Config_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->Config_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->Config_label_1, &lv_font_siyuanB_36, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->Config_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->Config_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->Config_label_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->Config_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->Config_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->Config_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->Config_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->Config_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->Config_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->Config_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Config_btn_7
	ui->Config_btn_7 = lv_btn_create(ui->Config);
	ui->Config_btn_7_label = lv_label_create(ui->Config_btn_7);
	lv_label_set_text(ui->Config_btn_7_label, "返   回 ");
	lv_label_set_long_mode(ui->Config_btn_7_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->Config_btn_7_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->Config_btn_7, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->Config_btn_7_label, LV_PCT(100));
	lv_obj_set_pos(ui->Config_btn_7, 289, 695);
	lv_obj_set_size(ui->Config_btn_7, 153, 67);

	//Write style for Config_btn_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->Config_btn_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->Config_btn_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->Config_btn_7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->Config_btn_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->Config_btn_7, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->Config_btn_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->Config_btn_7, lv_color_hex(0x114C8B), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->Config_btn_7, &lv_font_siyuanB_36, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->Config_btn_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->Config_btn_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//The custom code of Config.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->Config);

	//Init events for screen.
	events_init_Config(ui);
}
