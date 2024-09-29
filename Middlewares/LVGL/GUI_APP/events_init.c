/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


static void param_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.Config, guider_ui.Config_del, &guider_ui.param_del, setup_scr_Config, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
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

static void lii_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.Config, guider_ui.Config_del, &guider_ui.lii_del, setup_scr_Config, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

void events_init_lii (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->lii_btn_1, lii_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void vibration_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.Config, guider_ui.Config_del, &guider_ui.vibration_del, setup_scr_Config, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

void events_init_vibration (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->vibration_btn_2, vibration_btn_2_event_handler, LV_EVENT_ALL, ui);
}

static void freq_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.Config, guider_ui.Config_del, &guider_ui.freq_del, setup_scr_Config, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
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

static void Config_btn_6_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.vibration, guider_ui.vibration_del, &guider_ui.Config_del, setup_scr_vibration, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

static void Config_btn_5_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.lii, guider_ui.lii_del, &guider_ui.Config_del, setup_scr_lii, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

static void Config_btn_4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.freq, guider_ui.freq_del, &guider_ui.Config_del, setup_scr_freq, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

static void Config_btn_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.param, guider_ui.param_del, &guider_ui.Config_del, setup_scr_param, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

static void Config_btn_7_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.main, guider_ui.main_del, &guider_ui.Config_del, setup_scr_main, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, false, true);
		break;
	}
    default:
        break;
    }
}

void events_init_Config (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->Config_btn_6, Config_btn_6_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->Config_btn_5, Config_btn_5_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->Config_btn_4, Config_btn_4_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->Config_btn_3, Config_btn_3_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->Config_btn_7, Config_btn_7_event_handler, LV_EVENT_ALL, ui);
}

static void main_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_SCREEN_LOAD_START:
	{
		lv_obj_add_flag(guider_ui.main_btn_6, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_btn_4, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_btn_3, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

static void main_btn_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.main_btn_3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_btn_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_btn_2, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

static void main_btn_4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_LONG_PRESSED:
	{
		lv_obj_add_flag(guider_ui.main_btn_4, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_btn_3, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

static void main_btn_6_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_clear_flag(guider_ui.main_btn_4, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_btn_6, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

static void main_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_label_set_text(guider_ui.main_btn_5_label, "2档 ");
		lv_obj_add_flag(guider_ui.main_btn_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_btn_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_btn_6, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

static void main_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_label_set_text(guider_ui.main_btn_5_label, "1档 ");
		lv_obj_add_flag(guider_ui.main_btn_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_btn_6, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_btn_1, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

static void main_btn_7_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.Config, guider_ui.Config_del, &guider_ui.main_del, setup_scr_Config, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

void events_init_main (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->main, main_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->main_btn_3, main_btn_3_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->main_btn_4, main_btn_4_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->main_btn_6, main_btn_6_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->main_btn_2, main_btn_2_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->main_btn_1, main_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->main_btn_7, main_btn_7_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
