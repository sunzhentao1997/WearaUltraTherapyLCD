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



void setup_scr_main(lv_ui *ui)
{
	//Write codes main
	ui->main = lv_obj_create(NULL);
	lv_obj_set_size(ui->main, 480, 800);
	lv_obj_set_scrollbar_mode(ui->main, LV_SCROLLBAR_MODE_OFF);

	//Write style for main, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->main, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->main, lv_color_hex(0x114c8b), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->main, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_label_1
	ui->main_label_1 = lv_label_create(ui->main);
	lv_label_set_text(ui->main_label_1, "");
	lv_label_set_long_mode(ui->main_label_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->main_label_1, 16, 96);
	lv_obj_set_size(ui->main_label_1, 448, 497);

	//Write style for main_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->main_label_1, 51, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->main_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_label_1, &lv_customer_font_NSHBold_36, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->main_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->main_label_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->main_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->main_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->main_label_1, lv_color_hex(0x2a84e3), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->main_label_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_label_2
	ui->main_label_2 = lv_label_create(ui->main);
	lv_label_set_text(ui->main_label_2, "30:00");
	lv_label_set_long_mode(ui->main_label_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->main_label_2, 16, 250);
	lv_obj_set_size(ui->main_label_2, 448, 91);

	//Write style for main_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->main_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_label_2, &lv_customer_font_NSHBold_70, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->main_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->main_label_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->main_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_label_3
	ui->main_label_3 = lv_label_create(ui->main);
	lv_label_set_text(ui->main_label_3, "剩余治疗时间 ");
	lv_label_set_long_mode(ui->main_label_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->main_label_3, 16, 335);
	lv_obj_set_size(ui->main_label_3, 448, 51);

	//Write style for main_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->main_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_label_3, &lv_customer_font_NSHMedium_40, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->main_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->main_label_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->main_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_label_4
	ui->main_label_4 = lv_label_create(ui->main);
	lv_label_set_text(ui->main_label_4, "声功率(mW) ");
	lv_label_set_long_mode(ui->main_label_4, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->main_label_4, 75, 445);
	lv_obj_set_size(ui->main_label_4, 186, 43);

	//Write style for main_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->main_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->main_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->main_label_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_label_4, &lv_customer_font_NSHMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->main_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->main_label_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->main_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->main_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->main_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->main_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->main_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->main_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->main_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_label_5
	ui->main_label_5 = lv_label_create(ui->main);
	lv_label_set_text(ui->main_label_5, "当前档位 ");
	lv_label_set_long_mode(ui->main_label_5, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->main_label_5, 242, 445);
	lv_obj_set_size(ui->main_label_5, 163, 42);

	//Write style for main_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->main_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->main_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->main_label_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_label_5, &lv_customer_font_NSHMedium_28, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->main_label_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->main_label_5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->main_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->main_label_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->main_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->main_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->main_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->main_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->main_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_label_6
	ui->main_label_6 = lv_label_create(ui->main);
	lv_label_set_text(ui->main_label_6, "600");
	lv_label_set_long_mode(ui->main_label_6, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->main_label_6, 75, 473);
	lv_obj_set_size(ui->main_label_6, 163, 98);

	//Write style for main_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->main_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->main_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->main_label_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_label_6, &lv_customer_font_NSHBold_60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->main_label_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->main_label_6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->main_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->main_label_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->main_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->main_label_6, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->main_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->main_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->main_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_paging
	ui->main_paging = lv_btn_create(ui->main);
	ui->main_paging_label = lv_label_create(ui->main_paging);
	lv_label_set_text(ui->main_paging_label, "LIUS");
	lv_label_set_long_mode(ui->main_paging_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->main_paging_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->main_paging, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->main_paging_label, LV_PCT(100));
	lv_obj_set_pos(ui->main_paging, 19, 14);
	lv_obj_set_size(ui->main_paging, 84, 45);

	//Write style for main_paging, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->main_paging, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->main_paging, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->main_paging, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_paging, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->main_paging, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_paging, &lv_customer_font_NSHBold_36, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->main_paging, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->main_paging, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_change
	ui->main_change = lv_btn_create(ui->main);
	ui->main_change_label = lv_label_create(ui->main_change);
	lv_label_set_text(ui->main_change_label, "请选择 ");
	lv_label_set_long_mode(ui->main_change_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->main_change_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->main_change, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->main_change_label, LV_PCT(100));
	lv_obj_set_pos(ui->main_change, 255, 477);
	lv_obj_set_size(ui->main_change, 174, 101);

	//Write style for main_change, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->main_change, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->main_change, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->main_change, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_change, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->main_change, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_change, &lv_customer_font_NSHBold_50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->main_change, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->main_change, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_stop
	ui->main_stop = lv_btn_create(ui->main);
	ui->main_stop_label = lv_label_create(ui->main_stop);
	lv_label_set_text(ui->main_stop_label, "停 止 治 疗 ");
	lv_label_set_long_mode(ui->main_stop_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->main_stop_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->main_stop, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->main_stop_label, LV_PCT(100));
	lv_obj_set_pos(ui->main_stop, 19, 637);
	lv_obj_set_size(ui->main_stop, 447, 117);

	//Write style for main_stop, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->main_stop, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->main_stop, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->main_stop, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->main_stop, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->main_stop, 74, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_stop, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->main_stop, lv_color_hex(0xed610d), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_stop, &lv_customer_font_NSHBold_60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->main_stop, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->main_stop, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_ulock
	ui->main_ulock = lv_btn_create(ui->main);
	ui->main_ulock_label = lv_label_create(ui->main_ulock);
	lv_label_set_text(ui->main_ulock_label, "长按解锁 ");
	lv_label_set_long_mode(ui->main_ulock_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->main_ulock_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->main_ulock, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->main_ulock_label, LV_PCT(100));
	lv_obj_set_pos(ui->main_ulock, 19, 637);
	lv_obj_set_size(ui->main_ulock, 447, 117);

	//Write style for main_ulock, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->main_ulock, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->main_ulock, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->main_ulock, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->main_ulock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->main_ulock, 74, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_ulock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->main_ulock, lv_color_hex(0x139987), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_ulock, &lv_customer_font_NSHBold_60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->main_ulock, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->main_ulock, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_start
	ui->main_start = lv_btn_create(ui->main);
	ui->main_start_label = lv_label_create(ui->main_start);
	lv_label_set_text(ui->main_start_label, "开 始 治 疗 ");
	lv_label_set_long_mode(ui->main_start_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->main_start_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->main_start, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->main_start_label, LV_PCT(100));
	lv_obj_set_pos(ui->main_start, 19, 637);
	lv_obj_set_size(ui->main_start, 447, 117);

	//Write style for main_start, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->main_start, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->main_start, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->main_start, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->main_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->main_start, 74, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_start, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->main_start, lv_color_hex(0x114C8B), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_start, &lv_customer_font_NSHBold_60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->main_start, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->main_start, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_switch2
	ui->main_switch2 = lv_btn_create(ui->main);
	ui->main_switch2_label = lv_label_create(ui->main_switch2);
	lv_label_set_text(ui->main_switch2_label, "2档 ");
	lv_label_set_long_mode(ui->main_switch2_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->main_switch2_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->main_switch2, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->main_switch2_label, LV_PCT(100));
	lv_obj_set_pos(ui->main_switch2, 255, 637);
	lv_obj_set_size(ui->main_switch2, 209, 117);

	//Write style for main_switch2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->main_switch2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->main_switch2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->main_switch2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->main_switch2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->main_switch2, 74, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_switch2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->main_switch2, lv_color_hex(0x114c8b), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_switch2, &lv_customer_font_NSHBold_60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->main_switch2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->main_switch2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_switch1
	ui->main_switch1 = lv_btn_create(ui->main);
	ui->main_switch1_label = lv_label_create(ui->main_switch1);
	lv_label_set_text(ui->main_switch1_label, "1档 ");
	lv_label_set_long_mode(ui->main_switch1_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->main_switch1_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->main_switch1, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->main_switch1_label, LV_PCT(100));
	lv_obj_set_pos(ui->main_switch1, 16, 637);
	lv_obj_set_size(ui->main_switch1, 209, 117);

	//Write style for main_switch1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->main_switch1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->main_switch1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->main_switch1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->main_switch1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->main_switch1, 74, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_switch1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->main_switch1, lv_color_hex(0x114c8b), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_switch1, &lv_customer_font_NSHBold_60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->main_switch1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->main_switch1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_arc_1
	ui->main_arc_1 = lv_arc_create(ui->main);
	lv_arc_set_mode(ui->main_arc_1, LV_ARC_MODE_NORMAL);
	lv_arc_set_range(ui->main_arc_1, 0, 1800);
	lv_arc_set_bg_angles(ui->main_arc_1, 180, 0);
	lv_arc_set_value(ui->main_arc_1, 1800);
	lv_arc_set_rotation(ui->main_arc_1, 0);
	lv_obj_set_pos(ui->main_arc_1, 56, 136);
	lv_obj_set_size(ui->main_arc_1, 368, 368);

	//Write style for main_arc_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->main_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->main_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_width(ui->main_arc_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->main_arc_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->main_arc_1, lv_color_hex(0x114c8b), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->main_arc_1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->main_arc_1, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->main_arc_1, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->main_arc_1, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->main_arc_1, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for main_arc_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_arc_width(ui->main_arc_1, 16, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui->main_arc_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_color(ui->main_arc_1, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for main_arc_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->main_arc_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->main_arc_1, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->main_arc_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->main_arc_1, 0, LV_PART_KNOB|LV_STATE_DEFAULT);

	//The custom code of main.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->main);

	//Init events for screen.
	events_init_main(ui);
}
