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

#include "lv_mainstart.h"

static uint16_t MotorVal = 0;

void setup_scr_vibra(lv_ui *ui)
{
	 MotorVal = MotorLevel * 5;
	//Write codes vibra
	ui->vibra = lv_obj_create(NULL);
	ui->g_kb_vibra = lv_keyboard_create(ui->vibra);
	lv_obj_add_event_cb(ui->g_kb_vibra, kb_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_add_flag(ui->g_kb_vibra, LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_style_text_font(ui->g_kb_vibra, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_size(ui->vibra, 480, 800);
	lv_obj_set_scrollbar_mode(ui->vibra, LV_SCROLLBAR_MODE_OFF);

	//Write style for vibra, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->vibra, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->vibra, lv_color_hex(0x114C8B), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->vibra, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes vibra_label_1
	ui->vibra_label_1 = lv_label_create(ui->vibra);
	lv_label_set_text(ui->vibra_label_1, "LIUS");
	lv_label_set_long_mode(ui->vibra_label_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->vibra_label_1, 19, 14);
	lv_obj_set_size(ui->vibra_label_1, 84, 45);

	//Write style for vibra_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->vibra_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->vibra_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->vibra_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->vibra_label_1, &lv_customer_font_NSHBold_36, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->vibra_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->vibra_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->vibra_label_1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->vibra_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->vibra_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->vibra_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->vibra_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->vibra_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->vibra_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->vibra_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes vibra_label_2
	ui->vibra_label_2 = lv_label_create(ui->vibra);
	lv_label_set_text(ui->vibra_label_2, "震  动 ");
	lv_label_set_long_mode(ui->vibra_label_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->vibra_label_2, 19, 85);
	lv_obj_set_size(ui->vibra_label_2, 108, 33);

	//Write style for vibra_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->vibra_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->vibra_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->vibra_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->vibra_label_2, &lv_customer_font_NSHRegular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->vibra_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->vibra_label_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->vibra_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->vibra_label_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->vibra_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->vibra_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->vibra_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->vibra_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->vibra_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->vibra_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes vibra_slider_1
	ui->vibra_slider_1 = lv_slider_create(ui->vibra);
	lv_slider_set_range(ui->vibra_slider_1, 0, 20);
	lv_slider_set_mode(ui->vibra_slider_1, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->vibra_slider_1, MotorLevel, LV_ANIM_OFF);
	lv_obj_set_pos(ui->vibra_slider_1, 38, 212);
	lv_obj_set_size(ui->vibra_slider_1, 406, 26);

	//Write style for vibra_slider_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->vibra_slider_1, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->vibra_slider_1, lv_color_hex(0xc7c7c7), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->vibra_slider_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->vibra_slider_1, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->vibra_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->vibra_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for vibra_slider_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->vibra_slider_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->vibra_slider_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->vibra_slider_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->vibra_slider_1, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for vibra_slider_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->vibra_slider_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->vibra_slider_1, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->vibra_slider_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->vibra_slider_1, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes vibra_label_3
	ui->vibra_label_3 = lv_label_create(ui->vibra);
	lv_label_set_text_fmt(guider_ui.vibra_label_3, "%d%%",MotorVal);
	lv_label_set_long_mode(ui->vibra_label_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->vibra_label_3, 376, 175);
	lv_obj_set_size(ui->vibra_label_3, 70, 32);

	//Write style for vibra_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->vibra_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->vibra_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->vibra_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->vibra_label_3, &lv_customer_font_NSHRegular_27, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->vibra_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->vibra_label_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->vibra_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->vibra_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->vibra_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->vibra_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->vibra_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->vibra_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->vibra_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->vibra_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes vibra_btn_1
	ui->vibra_btn_1 = lv_btn_create(ui->vibra);
	ui->vibra_btn_1_label = lv_label_create(ui->vibra_btn_1);
	lv_label_set_text(ui->vibra_btn_1_label, "保  存 ");
	lv_label_set_long_mode(ui->vibra_btn_1_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->vibra_btn_1_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->vibra_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->vibra_btn_1_label, LV_PCT(100));
	lv_obj_set_pos(ui->vibra_btn_1, 38, 695);
	lv_obj_set_size(ui->vibra_btn_1, 153, 67);

	//Write style for vibra_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->vibra_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->vibra_btn_1, lv_color_hex(0x00baab), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->vibra_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->vibra_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->vibra_btn_1, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->vibra_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->vibra_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->vibra_btn_1, &lv_customer_font_NSHBold_30, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->vibra_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->vibra_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes vibra_btn_2
	ui->vibra_btn_2 = lv_btn_create(ui->vibra);
	ui->vibra_btn_2_label = lv_label_create(ui->vibra_btn_2);
	lv_label_set_text(ui->vibra_btn_2_label, "返  回 ");
	lv_label_set_long_mode(ui->vibra_btn_2_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->vibra_btn_2_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->vibra_btn_2, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->vibra_btn_2_label, LV_PCT(100));
	lv_obj_set_pos(ui->vibra_btn_2, 288, 695);
	lv_obj_set_size(ui->vibra_btn_2, 153, 67);

	//Write style for vibra_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->vibra_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->vibra_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->vibra_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->vibra_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->vibra_btn_2, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->vibra_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->vibra_btn_2, lv_color_hex(0x114C8B), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->vibra_btn_2, &lv_customer_font_NSHBold_30, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->vibra_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->vibra_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//The custom code of vibra.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->vibra);

	//Init events for screen.
	events_init_vibra(ui);
}
