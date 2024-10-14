/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include "lv_mainstart.h"
#include <stdio.h>
#include "lvgl.h"


#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif
extern lv_ui guider_ui;
extern SCREENSTATE ScreenState;

static void main_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_SCREEN_LOAD_START:
	{
		lv_obj_add_flag(guider_ui.main_stop, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_ulock, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_start, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_switch2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_switch1, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

static void main_paging_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.config, guider_ui.config_del, &guider_ui.main_del, setup_scr_config, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

static void main_change_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_clear_flag(guider_ui.main_switch1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_switch2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_start, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_ulock, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_stop, LV_OBJ_FLAG_HIDDEN);
		lv_label_set_text(guider_ui.main_change_label, "请选择 ");
		break;
	}
    default:
        break;
    }
}

static void main_stop_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_clear_flag(guider_ui.main_switch1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_switch2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_start, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_ulock, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_stop, LV_OBJ_FLAG_HIDDEN);
		lv_label_set_text(guider_ui.main_change_label, "请选择 ");
		lv_obj_set_style_text_font(guider_ui.main_change, &lv_customer_font_NSHBold_50, 0);
		ScreenState = STOP;
		break;
	}
    default:
        break;
    }
}

static void main_ulock_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_LONG_PRESSED:
	{
		lv_obj_add_flag(guider_ui.main_switch1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_switch2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_start, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_ulock, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_stop, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

static void main_start_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.main_switch1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_switch2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_start, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_stop, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_ulock, LV_OBJ_FLAG_HIDDEN);
		ScreenState = WORK;
		break;
	}
    default:
        break;
    }
}

static void main_switch2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.main_switch1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_switch2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_stop, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_ulock, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_start, LV_OBJ_FLAG_HIDDEN);
		lv_label_set_text(guider_ui.main_change_label, "2档 ");
		lv_obj_set_style_text_font(guider_ui.main_change, &lv_customer_font_NSHBold_50, 0);
		ScreenState = READY;
		break;
	}
    default:
        break;
    }
}

static void main_switch1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_label_set_text(guider_ui.main_change_label, "1档 ");
		lv_obj_set_style_text_font(guider_ui.main_change, &lv_customer_font_NSHBold_50, 0);
		lv_obj_add_flag(guider_ui.main_switch2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_switch1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_start, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_stop, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_ulock, LV_OBJ_FLAG_HIDDEN);
		ScreenState = READY;
		break;
	}
    default:
        break;
    }
}

void events_init_main (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->main, main_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->main_paging, main_paging_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->main_change, main_change_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->main_stop, main_stop_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->main_ulock, main_ulock_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->main_start, main_start_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->main_switch2, main_switch2_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->main_switch1, main_switch1_event_handler, LV_EVENT_ALL, ui);
}

static void config_param_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.param, guider_ui.param_del, &guider_ui.config_del, setup_scr_param, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

static void config_light_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.light, guider_ui.light_del, &guider_ui.config_del, setup_scr_light, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

static void config_freq_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.freq, guider_ui.freq_del, &guider_ui.config_del, setup_scr_freq, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

static void config_vab_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.vibra, guider_ui.vibra_del, &guider_ui.config_del, setup_scr_vibra, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

static void config_back_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.main, guider_ui.main_del, &guider_ui.config_del, setup_scr_main, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

void events_init_config (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->config_param, config_param_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->config_light, config_light_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->config_freq, config_freq_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->config_vab, config_vab_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->config_back, config_back_event_handler, LV_EVENT_ALL, ui);
}

static void param_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.config, guider_ui.config_del, &guider_ui.param_del, setup_scr_config, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

void events_init_param (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->param_btn_2, param_btn_2_event_handler, LV_EVENT_ALL, ui);
}

static void freq_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.config, guider_ui.config_del, &guider_ui.freq_del, setup_scr_config, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

void events_init_freq (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->freq_btn_2, freq_btn_2_event_handler, LV_EVENT_ALL, ui);
}

static void vibra_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.config, guider_ui.config_del, &guider_ui.vibra_del, setup_scr_config, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

void events_init_vibra (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->vibra_btn_2, vibra_btn_2_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
