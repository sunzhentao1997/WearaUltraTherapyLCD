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



void setup_scr_vibration(lv_ui *ui)
{
	//Write codes vibration
	ui->vibration = lv_obj_create(NULL);
	lv_obj_set_size(ui->vibration, 480, 800);
	lv_obj_set_scrollbar_mode(ui->vibration, LV_SCROLLBAR_MODE_OFF);

	//Write style for vibration, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->vibration, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->vibration, lv_color_hex(0x114C8B), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->vibration, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes vibration_label_1
	ui->vibration_label_1 = lv_label_create(ui->vibration);
	lv_label_set_text(ui->vibration_label_1, "LIUS");
	lv_label_set_long_mode(ui->vibration_label_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->vibration_label_1, 19, 15);
	lv_obj_set_size(ui->vibration_label_1, 84, 45);

	//Write style for vibration_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_radius(ui->vibration_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->vibration_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->vibration_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->vibration_label_1, &lv_font_siyuanB_36, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->vibration_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->vibration_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->vibration_label_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->vibration_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->vibration_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->vibration_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->vibration_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->vibration_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->vibration_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->vibration_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes vibration_label_2
	ui->vibration_label_2 = lv_label_create(ui->vibration);
	lv_label_set_text(ui->vibration_label_2, "震 动 ");
	lv_label_set_long_mode(ui->vibration_label_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->vibration_label_2, 19, 85);
	lv_obj_set_size(ui->vibration_label_2, 108, 33);

	//Write style for vibration_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->vibration_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->vibration_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->vibration_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->vibration_label_2, &lv_font_siyuan_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->vibration_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->vibration_label_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->vibration_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->vibration_label_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->vibration_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->vibration_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->vibration_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->vibration_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->vibration_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->vibration_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes vibration_btn_1
	ui->vibration_btn_1 = lv_btn_create(ui->vibration);
	ui->vibration_btn_1_label = lv_label_create(ui->vibration_btn_1);
	lv_label_set_text(ui->vibration_btn_1_label, "保    存 ");
	lv_label_set_long_mode(ui->vibration_btn_1_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->vibration_btn_1_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->vibration_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->vibration_btn_1_label, LV_PCT(100));
	lv_obj_set_pos(ui->vibration_btn_1, 38, 695);
	lv_obj_set_size(ui->vibration_btn_1, 153, 67);

	//Write style for vibration_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->vibration_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->vibration_btn_1, lv_color_hex(0x00bAAB), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->vibration_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->vibration_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->vibration_btn_1, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->vibration_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->vibration_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->vibration_btn_1, &lv_font_siyuanB_30, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->vibration_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->vibration_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes vibration_btn_2
	ui->vibration_btn_2 = lv_btn_create(ui->vibration);
	ui->vibration_btn_2_label = lv_label_create(ui->vibration_btn_2);
	lv_label_set_text(ui->vibration_btn_2_label, "返    回 ");
	lv_label_set_long_mode(ui->vibration_btn_2_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->vibration_btn_2_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->vibration_btn_2, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->vibration_btn_2_label, LV_PCT(100));
	lv_obj_set_pos(ui->vibration_btn_2, 289, 695);
	lv_obj_set_size(ui->vibration_btn_2, 153, 67);

	//Write style for vibration_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->vibration_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->vibration_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->vibration_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->vibration_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->vibration_btn_2, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->vibration_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->vibration_btn_2, lv_color_hex(0x114c8b), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->vibration_btn_2, &lv_font_siyuanB_30, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->vibration_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->vibration_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes vibration_slider_1
	ui->vibration_slider_1 = lv_slider_create(ui->vibration);
	lv_slider_set_range(ui->vibration_slider_1, 0, 20);
	lv_slider_set_mode(ui->vibration_slider_1, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->vibration_slider_1, 10, LV_ANIM_OFF);
	lv_obj_set_pos(ui->vibration_slider_1, 38, 213);
	lv_obj_set_size(ui->vibration_slider_1, 406, 26);

	//Write style for vibration_slider_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->vibration_slider_1, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->vibration_slider_1, lv_color_hex(0xc7c7c7), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->vibration_slider_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->vibration_slider_1, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->vibration_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->vibration_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for vibration_slider_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->vibration_slider_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->vibration_slider_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->vibration_slider_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->vibration_slider_1, 60, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for vibration_slider_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->vibration_slider_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->vibration_slider_1, lv_color_hex(0xd0e8fd), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->vibration_slider_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->vibration_slider_1, 60, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes vibration_label_3
	ui->vibration_label_3 = lv_label_create(ui->vibration);
	lv_label_set_text(ui->vibration_label_3, "50%");
	lv_label_set_long_mode(ui->vibration_label_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->vibration_label_3, 376, 175);
	lv_obj_set_size(ui->vibration_label_3, 70, 32);

	//Write style for vibration_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->vibration_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->vibration_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->vibration_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->vibration_label_3, &lv_font_siyuan_27, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->vibration_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->vibration_label_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->vibration_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->vibration_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->vibration_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->vibration_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->vibration_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->vibration_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->vibration_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->vibration_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//The custom code of vibration.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->vibration);

	//Init events for screen.
	events_init_vibration(ui);
}
