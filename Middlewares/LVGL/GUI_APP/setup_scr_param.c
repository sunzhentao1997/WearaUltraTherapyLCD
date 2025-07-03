/*
* Copyright 2024 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
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
#include "dev_app.h"

static uint8_t ParamTempBuff[10] = {0};

void setup_scr_param(lv_ui *ui)
{
		uint8_t boostlevel = SendBatteryStateData;
    //Write codes param
    ui->param = lv_obj_create(NULL);
    lv_obj_set_size(ui->param, 480, 800);
    lv_obj_set_scrollbar_mode(ui->param, LV_SCROLLBAR_MODE_OFF);

    //Write style for param, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->param, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->param, lv_color_hex(0x114c8b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->param, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_logo
    ui->param_logo = lv_label_create(ui->param);
    lv_label_set_text(ui->param_logo, "LIUS");
    lv_label_set_long_mode(ui->param_logo, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->param_logo, 42, 40);
    lv_obj_set_size(ui->param_logo, 87, 37);

    //Write style for param_logo, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->param_logo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_logo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_logo, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->param_logo, &lv_customer_font_NSHBold_36, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_logo, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->param_logo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->param_logo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_logo, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->param_logo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->param_logo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->param_logo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->param_logo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->param_logo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_logo, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_lowpower
    ui->param_lowpower = lv_label_create(ui->param);
    lv_label_set_text(ui->param_lowpower, "");
    lv_label_set_long_mode(ui->param_lowpower, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->param_lowpower, 371, 44);
    lv_obj_set_size(ui->param_lowpower, 61, 31);

    //Write style for param_lowpower, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->param_lowpower, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_lowpower, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_lowpower, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->param_lowpower, &lv_customer_font_NSHRegular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_lowpower, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->param_lowpower, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->param_lowpower, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_lowpower, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->param_lowpower, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->param_lowpower, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->param_lowpower, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->param_lowpower, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->param_lowpower, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->param_lowpower, &_low_power_61x31, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->param_lowpower, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->param_lowpower, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_lowpower, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_battery
    ui->param_battery = lv_label_create(ui->param);
    lv_label_set_text(ui->param_battery, " ");
    lv_label_set_long_mode(ui->param_battery, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->param_battery, 371, 44);
    lv_obj_set_size(ui->param_battery, 61, 31);

    //Write style for param_battery, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->param_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_battery, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->param_battery, &lv_customer_font_NSHRegular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_battery, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->param_battery, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->param_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_battery, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->param_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->param_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->param_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->param_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->param_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->param_battery, &_battery_1_61x31, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->param_battery, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_img_recolor_opa(ui->param_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_battery, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_grate4
    ui->param_grate4 = lv_label_create(ui->param);
    lv_label_set_text(ui->param_grate4, " ");
    lv_label_set_long_mode(ui->param_grate4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->param_grate4, 411, 50);
    lv_obj_set_size(ui->param_grate4, 9, 19);

    //Write style for param_grate4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->param_grate4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_grate4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_grate4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->param_grate4, &lv_customer_font_NSHRegular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_grate4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->param_grate4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->param_grate4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_grate4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->param_grate4, 103, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->param_grate4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->param_grate4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->param_grate4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->param_grate4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->param_grate4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->param_grate4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_grate4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_grate3
    ui->param_grate3 = lv_label_create(ui->param);
    lv_label_set_text(ui->param_grate3, " ");
    lv_label_set_long_mode(ui->param_grate3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->param_grate3, 400, 50);
    lv_obj_set_size(ui->param_grate3, 9, 19);

    //Write style for param_grate3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->param_grate3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_grate3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_grate3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->param_grate3, &lv_customer_font_NSHRegular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_grate3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->param_grate3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->param_grate3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_grate3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->param_grate3, 141, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->param_grate3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->param_grate3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->param_grate3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->param_grate3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->param_grate3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->param_grate3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_grate3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_grate2
    ui->param_grate2 = lv_label_create(ui->param);
    lv_label_set_text(ui->param_grate2, " ");
    lv_label_set_long_mode(ui->param_grate2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->param_grate2, 389, 50);
    lv_obj_set_size(ui->param_grate2, 9, 19);

    //Write style for param_grate2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->param_grate2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_grate2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_grate2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->param_grate2, &lv_customer_font_NSHRegular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_grate2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->param_grate2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->param_grate2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_grate2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->param_grate2, 206, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->param_grate2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->param_grate2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->param_grate2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->param_grate2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->param_grate2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->param_grate2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_grate2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_grate1
    ui->param_grate1 = lv_label_create(ui->param);
    lv_label_set_text(ui->param_grate1, " ");
    lv_label_set_long_mode(ui->param_grate1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->param_grate1, 378, 50);
    lv_obj_set_size(ui->param_grate1, 9, 19);

    //Write style for param_grate1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->param_grate1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_grate1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_grate1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->param_grate1, &lv_customer_font_NSHRegular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_grate1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->param_grate1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->param_grate1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_grate1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->param_grate1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->param_grate1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->param_grate1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->param_grate1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->param_grate1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->param_grate1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->param_grate1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_grate1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_label_1
    ui->param_label_1 = lv_label_create(ui->param);
    lv_label_set_text(ui->param_label_1, " 出厂参数 ");
    lv_label_set_long_mode(ui->param_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->param_label_1, 33, 103);
    lv_obj_set_size(ui->param_label_1, 127, 31);

    //Write style for param_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->param_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->param_label_1, &lv_customer_font_NSHRegular_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->param_label_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->param_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->param_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->param_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->param_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->param_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->param_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_label_2
    ui->param_label_2 = lv_label_create(ui->param);
    lv_label_set_text(ui->param_label_2, "      设备编号:                                      TFB ");
    lv_label_set_long_mode(ui->param_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->param_label_2, 28, 151);
    lv_obj_set_size(ui->param_label_2, 424, 95);

    //Write style for param_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->param_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_label_2, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->param_label_2, &lv_customer_font_NSHRegular_33, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->param_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->param_label_2, 12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_label_2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->param_label_2, 167, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->param_label_2, lv_color_hex(0x509BE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->param_label_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->param_label_2, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->param_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->param_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->param_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_label_3
    ui->param_label_3 = lv_label_create(ui->param);
    lv_label_set_text(ui->param_label_3, "      软件发布版本:                             TFB-ULT-v1 ");
    lv_label_set_long_mode(ui->param_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->param_label_3, 28, 263);
    lv_obj_set_size(ui->param_label_3, 424, 95);

    //Write style for param_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->param_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_label_3, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->param_label_3, &lv_customer_font_NSHRegular_33, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->param_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->param_label_3, 12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_label_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->param_label_3, 167, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->param_label_3, lv_color_hex(0x509BE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->param_label_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->param_label_3, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->param_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->param_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->param_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_label_4
    ui->param_label_4 = lv_label_create(ui->param);
    lv_label_set_text(ui->param_label_4, "      软件完整版本:                             TFB-ULT-v1.0.1 ");
    lv_label_set_long_mode(ui->param_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->param_label_4, 28, 374);
    lv_obj_set_size(ui->param_label_4, 424, 95);

    //Write style for param_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->param_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_label_4, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_label_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->param_label_4, &lv_customer_font_NSHRegular_33, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->param_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->param_label_4, 12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_label_4, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->param_label_4, 167, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->param_label_4, lv_color_hex(0x509BE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->param_label_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->param_label_4, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->param_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->param_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->param_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_label_5
    ui->param_label_5 = lv_label_create(ui->param);
    lv_label_set_text(ui->param_label_5, "      功    率:                     W ");
    lv_label_set_long_mode(ui->param_label_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->param_label_5, 28, 485);
    lv_obj_set_size(ui->param_label_5, 424, 67);

    //Write style for param_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->param_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_label_5, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_label_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->param_label_5, &lv_customer_font_NSHRegular_33, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_label_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->param_label_5, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->param_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_label_5, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->param_label_5, 168, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->param_label_5, lv_color_hex(0x509BE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->param_label_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->param_label_5, 18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->param_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->param_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->param_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_label_6
    ui->param_label_6 = lv_label_create(ui->param);
    lv_label_set_text(ui->param_label_6, "      温    度:                     ℃ ");
    lv_label_set_long_mode(ui->param_label_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->param_label_6, 28, 567);
    lv_obj_set_size(ui->param_label_6, 424, 67);

    //Write style for param_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->param_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_label_6, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_label_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->param_label_6, &lv_customer_font_NSHRegular_33, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_label_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->param_label_6, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->param_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_label_6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->param_label_6, 168, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->param_label_6, lv_color_hex(0x509BE6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->param_label_6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->param_label_6, 18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->param_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->param_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->param_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_back
    ui->param_back = lv_btn_create(ui->param);
    ui->param_back_label = lv_label_create(ui->param_back);
    lv_label_set_text(ui->param_back_label, " 返     回 ");
    lv_label_set_long_mode(ui->param_back_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->param_back_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->param_back, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->param_back_label, LV_PCT(100));
    lv_obj_set_pos(ui->param_back, 295, 698);
    lv_obj_set_size(ui->param_back, 154, 68);

    //Write style for param_back, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->param_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->param_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_back, 37, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_back, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->param_back, &_back_154x68, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->param_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui->param_back, lv_color_hex(0x0a2847), LV_PART_MAIN|LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_img_recolor_opa(ui->param_back, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_back, lv_color_hex(0x114C8B), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->param_back, &lv_customer_font_NSHBold_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_back, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_back, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_DeviceId
		memset(ParamTempBuff,0,10);
		memcpy(ParamTempBuff,DevicesParam.DevParam.DeviceIdBuff,10);
		
    ui->param_DeviceId = lv_btn_create(ui->param);
    ui->param_DeviceId_label = lv_label_create(ui->param_DeviceId);
	lv_label_set_text(ui->param_DeviceId_label, (const char*)&ParamTempBuff);
    lv_label_set_long_mode(ui->param_DeviceId_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->param_DeviceId_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_pad_all(ui->param_DeviceId, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->param_DeviceId_label, LV_PCT(100));
    lv_obj_set_pos(ui->param_DeviceId, 115, 194);
    lv_obj_set_size(ui->param_DeviceId, 251, 46);

    //Write style for param_DeviceId, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->param_DeviceId, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->param_DeviceId, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_DeviceId, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_DeviceId, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_DeviceId, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->param_DeviceId, &lv_customer_font_NSHRegular_33, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_DeviceId, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_DeviceId, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_Power
	memset(ParamTempBuff,0,10);
	memcpy(ParamTempBuff,DevicesParam.DevParam.PowerBuff,10);
	
    ui->param_Power = lv_btn_create(ui->param);
    ui->param_Power_label = lv_label_create(ui->param_Power);
	lv_label_set_text(ui->param_Power_label, (const char*)&ParamTempBuff);
    lv_label_set_long_mode(ui->param_Power_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->param_Power_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->param_Power, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->param_Power_label, LV_PCT(100));
    lv_obj_set_pos(ui->param_Power, 219, 490);
    lv_obj_set_size(ui->param_Power, 166, 61);

    //Write style for param_Power, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->param_Power, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->param_Power, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_Power, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_Power, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_Power, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->param_Power, &lv_customer_font_NSHRegular_33, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_Power, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_Power, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_Temp
		memset(ParamTempBuff,0,10);
		memcpy(ParamTempBuff,DevicesParam.DevParam.TemperatureBuff,10);
	
    ui->param_Temp = lv_btn_create(ui->param);
    ui->param_Temp_label = lv_label_create(ui->param_Temp);
	lv_label_set_text(ui->param_Temp_label, (const char *)&ParamTempBuff);
    lv_label_set_long_mode(ui->param_Temp_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->param_Temp_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->param_Temp, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->param_Temp_label, LV_PCT(100));
    lv_obj_set_pos(ui->param_Temp, 219, 572);
    lv_obj_set_size(ui->param_Temp, 166, 61);

    //Write style for param_Temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->param_Temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->param_Temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_Temp, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_Temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_Temp, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->param_Temp, &lv_customer_font_NSHRegular_33, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_Temp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_Temp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_btn_1
    ui->param_btn_1 = lv_btn_create(ui->param);
    ui->param_btn_1_label = lv_label_create(ui->param_btn_1);
    lv_label_set_text(ui->param_btn_1_label, " 保     存 ");
    lv_label_set_long_mode(ui->param_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->param_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->param_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->param_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->param_btn_1, 42, 698);
    lv_obj_set_size(ui->param_btn_1, 154, 68);

    //Write style for param_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->param_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->param_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_btn_1, 37, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->param_btn_1, &_save_154x68, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->param_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor(ui->param_btn_1, lv_color_hex(0x0a2847), LV_PART_MAIN|LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_img_recolor_opa(ui->param_btn_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->param_btn_1, &lv_customer_font_NSHBold_30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_btnm_1
    ui->param_btnm_1 = lv_btnmatrix_create(ui->param);
    static const char *param_btnm_1_text_map[] = {"1", "2", "3", "\n", "4", "5", "6", "\n", "7", "8", "9", "\n", ".", "0", "Ent", "",};
    lv_btnmatrix_set_map(ui->param_btnm_1, param_btnm_1_text_map);
    lv_obj_set_pos(ui->param_btnm_1, 3, 504);
    lv_obj_set_size(ui->param_btnm_1, 472, 289);
    lv_obj_add_flag(ui->param_btnm_1, LV_OBJ_FLAG_HIDDEN);

    //Write style for param_btnm_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->param_btnm_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->param_btnm_1, 18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->param_btnm_1, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->param_btnm_1, 19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->param_btnm_1, 21, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui->param_btnm_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui->param_btnm_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_btnm_1, 11, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->param_btnm_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->param_btnm_1, lv_color_hex(0x114C8B), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->param_btnm_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for param_btnm_1, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->param_btnm_1, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_btnm_1, lv_color_hex(0xffffff), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->param_btnm_1, &lv_customer_font_NSHRegular_33, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_btnm_1, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_btnm_1, 4, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->param_btnm_1, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->param_btnm_1, lv_color_hex(0x93e3ff), LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->param_btnm_1, LV_GRAD_DIR_NONE, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_btnm_1, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write style for param_btnm_1, Part: LV_PART_ITEMS, State: LV_STATE_PRESSED.
    lv_obj_set_style_border_width(ui->param_btnm_1, 0, LV_PART_ITEMS|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->param_btnm_1, lv_color_hex(0xffffff), LV_PART_ITEMS|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->param_btnm_1, &lv_customer_font_NSHRegular_33, LV_PART_ITEMS|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->param_btnm_1, 255, LV_PART_ITEMS|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->param_btnm_1, 4, LV_PART_ITEMS|LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui->param_btnm_1, 255, LV_PART_ITEMS|LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(ui->param_btnm_1, lv_color_hex(0x93e3ff), LV_PART_ITEMS|LV_STATE_PRESSED);
    lv_obj_set_style_bg_grad_dir(ui->param_btnm_1, LV_GRAD_DIR_NONE, LV_PART_ITEMS|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->param_btnm_1, 2, LV_PART_ITEMS|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_color(ui->param_btnm_1, lv_color_hex(0x93e3ff), LV_PART_ITEMS|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_opa(ui->param_btnm_1, 255, LV_PART_ITEMS|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_spread(ui->param_btnm_1, 2, LV_PART_ITEMS|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_ofs_x(ui->param_btnm_1, 0, LV_PART_ITEMS|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_ofs_y(ui->param_btnm_1, 1, LV_PART_ITEMS|LV_STATE_PRESSED);

    //Write codes param_back_p
    ui->param_back_p = lv_btn_create(ui->param);
    ui->param_back_p_label = lv_label_create(ui->param_back_p);
    lv_label_set_text(ui->param_back_p_label, " ◀ ");
    lv_label_set_long_mode(ui->param_back_p_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->param_back_p_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->param_back_p, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->param_back_p_label, LV_PCT(100));
    lv_obj_set_pos(ui->param_back_p, 22, 466);
    lv_obj_set_size(ui->param_back_p, 88, 55);
    lv_obj_add_flag(ui->param_back_p, LV_OBJ_FLAG_HIDDEN);

    //Write style for param_back_p, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->param_back_p, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->param_back_p, lv_color_hex(0x93E3FF), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->param_back_p, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->param_back_p, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_back_p, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_back_p, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_back_p, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->param_back_p, &lv_customer_font_NSHRegular_33, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_back_p, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_back_p, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_label_7
    ui->param_label_7 = lv_label_create(ui->param);
    lv_label_set_text(ui->param_label_7, "1234567890");
    lv_label_set_long_mode(ui->param_label_7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->param_label_7, 111, 466);
    lv_obj_set_size(ui->param_label_7, 258, 55);
    lv_obj_add_flag(ui->param_label_7, LV_OBJ_FLAG_HIDDEN);

    //Write style for param_label_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->param_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_label_7, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_label_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->param_label_7, &lv_customer_font_NSHRegular_33, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_label_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->param_label_7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->param_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_label_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->param_label_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->param_label_7, lv_color_hex(0x93e3ff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->param_label_7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->param_label_7, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->param_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->param_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->param_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_Del
    ui->param_Del = lv_btn_create(ui->param);
    ui->param_Del_label = lv_label_create(ui->param_Del);
    lv_label_set_text(ui->param_Del_label, "Del");
    lv_label_set_long_mode(ui->param_Del_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->param_Del_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->param_Del, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->param_Del_label, LV_PCT(100));
    lv_obj_set_pos(ui->param_Del, 370, 466);
    lv_obj_set_size(ui->param_Del, 83, 55);
    lv_obj_add_flag(ui->param_Del, LV_OBJ_FLAG_HIDDEN);

    //Write style for param_Del, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->param_Del, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->param_Del, lv_color_hex(0x93e3ff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->param_Del, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->param_Del, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_Del, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_Del, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_Del, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->param_Del, &lv_customer_font_NSHRegular_33, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_Del, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_Del, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_label_10
    ui->param_label_10 = lv_label_create(ui->param);
    lv_label_set_text(ui->param_label_10, " ");
    lv_label_set_long_mode(ui->param_label_10, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->param_label_10, 0, 0);
    lv_obj_set_size(ui->param_label_10, 480, 800);
    lv_obj_add_flag(ui->param_label_10, LV_OBJ_FLAG_HIDDEN);

    //Write style for param_label_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->param_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_label_10, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->param_label_10, &lv_customer_font_NSHRegular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_label_10, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->param_label_10, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->param_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_label_10, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->param_label_10, 171, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->param_label_10, lv_color_hex(0x114c8B), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->param_label_10, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->param_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->param_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->param_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->param_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_label_10, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_label_9
    ui->param_label_9 = lv_label_create(ui->param);
    lv_label_set_text(ui->param_label_9, " 保存成功 ");
    lv_label_set_long_mode(ui->param_label_9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->param_label_9, 55, 323);
    lv_obj_set_size(ui->param_label_9, 368, 206);
    lv_obj_add_flag(ui->param_label_9, LV_OBJ_FLAG_HIDDEN);

    //Write style for param_label_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->param_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_label_9, 30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_label_9, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->param_label_9, &lv_customer_font_AlibabaMed_50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_label_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->param_label_9, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->param_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_label_9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->param_label_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->param_label_9, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->param_label_9, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->param_label_9, 121, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->param_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->param_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->param_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_label_8
    ui->param_label_8 = lv_label_create(ui->param);
    lv_label_set_text(ui->param_label_8, " ");
    lv_label_set_long_mode(ui->param_label_8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->param_label_8, 199, 350);
    lv_obj_set_size(ui->param_label_8, 75, 75);
    lv_obj_add_flag(ui->param_label_8, LV_OBJ_FLAG_HIDDEN);

    //Write style for param_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->param_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_label_8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->param_label_8, &lv_customer_font_NSHRegular_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_label_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->param_label_8, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->param_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_label_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->param_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->param_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->param_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->param_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->param_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->param_label_8, &_success_75x75, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->param_label_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_img_recolor_opa(ui->param_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes param_btn_2
    ui->param_btn_2 = lv_btn_create(ui->param);
    ui->param_btn_2_label = lv_label_create(ui->param_btn_2);
    lv_label_set_text(ui->param_btn_2_label, "×");
    lv_label_set_long_mode(ui->param_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->param_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->param_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->param_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->param_btn_2, 364, 335);
    lv_obj_set_size(ui->param_btn_2, 45, 41);
    lv_obj_add_flag(ui->param_btn_2, LV_OBJ_FLAG_HIDDEN);

    //Write style for param_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->param_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->param_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->param_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->param_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->param_btn_2, lv_color_hex(0x808080), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->param_btn_2, &lv_customer_font_NSHBlack_43, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->param_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->param_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of param.


    //Update current screen layout.
		if(ParamLockFlg == 1) 
		{
			lv_obj_add_flag(ui->param_btn_1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(ui->param_label_5, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(ui->param_label_6, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(ui->param_Power, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(ui->param_Temp, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(ui->param_DeviceId, LV_OBJ_FLAG_CLICKABLE);
			lv_obj_clear_flag(ui->param_Power, LV_OBJ_FLAG_CLICKABLE);
			lv_obj_clear_flag(ui->param_Temp, LV_OBJ_FLAG_CLICKABLE);
		}
	
	switch (boostlevel)
	{
	case Battery_Level1:
		lv_obj_add_flag(guider_ui.param_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_grate4, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_battery, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_lowpower, LV_OBJ_FLAG_HIDDEN);
		break;
	
	case Battery_Level2:
		lv_obj_clear_flag(guider_ui.param_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_grate4, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_battery, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_lowpower, LV_OBJ_FLAG_HIDDEN);	
		break;
	
	case Battery_Level3:
		lv_obj_clear_flag(guider_ui.param_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_grate4, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_battery, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_lowpower, LV_OBJ_FLAG_HIDDEN);
		break;
	
	case Battery_Level4:
		lv_obj_clear_flag(guider_ui.param_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_grate4, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_battery, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_lowpower, LV_OBJ_FLAG_HIDDEN);
		break;
	
	case Battery_Level5:
		lv_obj_clear_flag(guider_ui.param_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_grate4, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_battery, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_lowpower, LV_OBJ_FLAG_HIDDEN);
		break;
	
	default:
		break;
	}
    lv_obj_update_layout(ui->param);

    //Init events for screen.
    events_init_param(ui);
}

