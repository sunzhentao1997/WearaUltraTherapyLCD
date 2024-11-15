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

#include "tim.h"
#include "lv_mainstart.h"
#include "dev_app.h"

uint8_t UnlockFlg = 1;

/*****************************************************************************************************
 *
 *										主页事件处理
 *
 ****************************************************************************************************/
static void main_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_SCREEN_LOAD_START:
	{
		lv_obj_add_flag(guider_ui.main_continue, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_stop, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_pause, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_suo, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_ulock, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_start, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_btn_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_btn_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_label_12, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_label_13, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

static void main_paging_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) 
		{
			case LV_EVENT_CLICKED:
			{
				ClickCount++;
				ScreenState = OTHER;
				Screen_Id = CONFIG_SCREEN;
				DevWorkState = PASUE_STATE;
				ui_load_scr_animation(&guider_ui, &guider_ui.password1, guider_ui.password1_del, &guider_ui.main_del, setup_scr_password1, LV_SCR_LOAD_ANIM_FADE_ON, 50, 50, false, false);
				break;
			}
			case LV_EVENT_PRESSED:
			{
				BeepFlg = 1;
				BeepCount = 2;
				break;
			}
				break;
			default:
				break;
    }
}

static void main_stop_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
		case LV_EVENT_PRESSING:
		{
			lv_obj_set_style_bg_img_recolor_opa(guider_ui.main_stop, 200, LV_PART_MAIN);
			break;
		}
		case LV_EVENT_RELEASED:
		{
			lv_obj_set_style_bg_img_recolor_opa(guider_ui.main_stop, 0, LV_PART_MAIN);
			lv_obj_add_flag(guider_ui.main_stop, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.main_start, LV_OBJ_FLAG_HIDDEN);
			break;
		}
		case LV_EVENT_PRESSED:
		{
			BeepFlg = 1;
			BeepCount = 2;
		}
    default:
        break;
    }
}

static void main_pause_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
		case LV_EVENT_PRESSING:
		{
			lv_obj_set_style_bg_img_recolor_opa(guider_ui.main_pause, 200, LV_PART_MAIN);
			break;
		}
		case LV_EVENT_RELEASED:
		{
			lv_obj_set_style_bg_img_recolor_opa(guider_ui.main_pause, 0, LV_PART_MAIN);
			lv_obj_add_flag(guider_ui.main_pause, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.main_continue, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.main_stop, LV_OBJ_FLAG_HIDDEN);
			break;
		}
		case LV_EVENT_PRESSED:
		{
			BeepFlg = 1;
			BeepCount = 2;
		}
    default:
        break;
    }
}

static void main_continue_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
		case LV_EVENT_PRESSING:
		{
			lv_obj_set_style_bg_img_recolor_opa(guider_ui.main_continue, 200, LV_PART_MAIN);
			break;
		}
		case LV_EVENT_RELEASED:
		{
			lv_obj_clear_flag(guider_ui.main_suo, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.main_ulock, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.main_pause, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.main_continue, LV_OBJ_FLAG_HIDDEN);
			lv_obj_set_style_bg_img_recolor_opa(guider_ui.main_continue, 0, LV_PART_MAIN);
			lv_obj_add_flag(guider_ui.main_stop, LV_OBJ_FLAG_HIDDEN);
			break;
		}
		case LV_EVENT_PRESSED:
		{
			BeepFlg = 1;
			BeepCount = 2;
		}
    default:
			break;
    }
}

static void main_suo_event_handler (lv_event_t *e)
{
		static int32_t old_x = 70;
		static int8_t step = 5;
		static uint16_t slider_pos_old = 95;
	
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
			case LV_EVENT_PRESSING:
			{
				if(slider_pos < 95)
				{
						slider_pos = 95;
				}else if(slider_pos > 385)
				{
						slider_pos = 405;
				}
				
				if(((slider_pos - slider_pos_old) < 100) && ((slider_pos - slider_pos_old) > -100))
				{
						slider_pos_old = slider_pos;
				}else
				{
				}
				
				step = (slider_pos_old - old_x) / 2;
 
				old_x = old_x + step;
				
				if(old_x < 95)
				{
						old_x = 95;
				}else if(old_x > 380)
				{
						old_x = 380;
				}
				
				//lv_obj_set_pos(guider_ui., (lv_coord_t)(old_x - 25), 662);
				
				if(old_x == 380)
				{
					UnlockFlg = 1;
					if(UnlockCount > 500)
					{
						lv_obj_add_flag(guider_ui.main_start, LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(guider_ui.main_ulock, LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(guider_ui.main_suo, LV_OBJ_FLAG_HIDDEN);
						lv_obj_clear_flag(guider_ui.main_stop, LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(guider_ui.main_btn_1, LV_OBJ_FLAG_HIDDEN);
						lv_obj_set_pos(guider_ui.main_btn_1, 70, 662);
						UnlockFlg = 0;
					}
				}else
				{
						UnlockCount = 0;
				}
				break;
			}
			case LV_EVENT_RELEASED:
			{
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
	case LV_EVENT_PRESSING:
	{
		lv_obj_set_style_bg_img_recolor_opa(guider_ui.main_start, 255, LV_PART_MAIN);
		break;
	}
	case LV_EVENT_RELEASED:
	{
		lv_obj_set_style_bg_img_recolor_opa(guider_ui.main_start, 0, LV_PART_MAIN);
		lv_obj_add_flag(guider_ui.main_start, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_ulock, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_suo, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_continue, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_stop, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_pause, LV_OBJ_FLAG_HIDDEN);
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
		lv_obj_add_flag(guider_ui.main_btn_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_btn_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_label_12, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_label_13, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_start, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_suo, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_ulock, LV_OBJ_FLAG_HIDDEN);
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
		lv_obj_add_flag(guider_ui.main_btn_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_btn_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_label_12, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_label_13, LV_OBJ_FLAG_HIDDEN);
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
	lv_obj_add_event_cb(ui->main_stop, main_stop_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->main_pause, main_pause_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->main_continue, main_continue_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->main_suo, main_suo_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->main_start, main_start_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->main_btn_1, main_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->main_btn_2, main_btn_2_event_handler, LV_EVENT_ALL, ui);
}

static void config_param_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.param, guider_ui.param_del, &guider_ui.config_del, setup_scr_param, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, true);
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
		ui_load_scr_animation(&guider_ui, &guider_ui.light, guider_ui.light_del, &guider_ui.config_del, setup_scr_light, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

static void config_vibra_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.vibra, guider_ui.vibra_del, &guider_ui.config_del, setup_scr_vibra, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, true);
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
		ui_load_scr_animation(&guider_ui, &guider_ui.freq, guider_ui.freq_del, &guider_ui.config_del, setup_scr_freq, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

static void config_lock_on_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.password2, guider_ui.password2_del, &guider_ui.config_del, setup_scr_password2, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, true);
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
	case LV_EVENT_PRESSING:
	{
		lv_obj_set_style_bg_img_recolor_opa(guider_ui.config_back, 200, LV_PART_MAIN);
		break;
	}
	case LV_EVENT_RELEASED:
	{
		lv_obj_set_style_bg_img_recolor_opa(guider_ui.config_back, 0, LV_PART_MAIN);
		ui_load_scr_animation(&guider_ui, &guider_ui.main, guider_ui.main_del, &guider_ui.config_del, setup_scr_main, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, true);
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
	lv_obj_add_event_cb(ui->config_vibra, config_vibra_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->config_freq, config_freq_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->config_lock_on, config_lock_on_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->config_back, config_back_event_handler, LV_EVENT_ALL, ui);
}

static void param_back_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_PRESSING:
	{
		lv_obj_set_style_bg_img_recolor_opa(guider_ui.param_back, 200, LV_PART_MAIN);
		break;
	}
	case LV_EVENT_RELEASED:
	{
		lv_obj_set_style_bg_img_recolor_opa(guider_ui.param_back, 0, LV_PART_MAIN);
		ui_load_scr_animation(&guider_ui, &guider_ui.config, guider_ui.config_del, &guider_ui.param_del, setup_scr_config, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

static void param_DeviceId_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_clear_flag(guider_ui.param_btnm_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_Del, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_label_7, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_back_p, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

static void param_Power_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_clear_flag(guider_ui.param_Del, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_label_7, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_back_p, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_btnm_1, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

static void param_Temp_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_clear_flag(guider_ui.param_Del, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_label_7, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_back_p, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_btnm_1, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

static void param_btnm_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_t * obj = lv_event_get_target(e);
		uint32_t id = lv_btnmatrix_get_selected_btn(obj);

		switch (id) {
		case (0):
		{
			break;
		}
		case (1):
		{
			break;
		}
		case (2):
		{
			break;
		}
		case (3):
		{
			break;
		}
		case (4):
		{
			break;
		}
		case (5):
		{
			break;
		}
		case (6):
		{
			break;
		}
		case (7):
		{
			break;
		}
		case (8):
		{
			break;
		}
		case (9):
		{
			break;
		}
		case (10):
		{
			break;
		}
		case (11):
		{
			lv_obj_add_flag(guider_ui.param_Del, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.param_label_7, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.param_back_p, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.param_btnm_1, LV_OBJ_FLAG_HIDDEN);
			break;
		}
		default:
			break;
		}
		break;
	}
    default:
        break;
    }
}

static void param_back_p_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.param_Del, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_label_7, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_back_p, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_btnm_1, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

static void param_Del_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		break;
	}
    default:
        break;
    }
}

void events_init_param (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->param_back, param_back_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->param_DeviceId, param_DeviceId_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->param_Power, param_Power_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->param_Temp, param_Temp_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->param_btnm_1, param_btnm_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->param_back_p, param_back_p_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->param_Del, param_Del_event_handler, LV_EVENT_ALL, ui);
}

static void light_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_SCREEN_UNLOAD_START:
	{
		lv_obj_add_flag(guider_ui.light_label_9, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.light_btn_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.light_label_8, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.light_label_7, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

static void light_back_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_PRESSING:
	{
		lv_obj_set_style_bg_img_recolor_opa(guider_ui.light_back, 200, LV_PART_MAIN);
		break;
	}
	case LV_EVENT_RELEASED:
	{
		lv_obj_set_style_bg_img_recolor_opa(guider_ui.light_back, 0, LV_PART_MAIN);
		ui_load_scr_animation(&guider_ui, &guider_ui.config, guider_ui.config_del, &guider_ui.light_del, setup_scr_config, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

static void light_save_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_PRESSING:
	{
		lv_obj_set_style_bg_img_recolor_opa(guider_ui.light_save, 200, LV_PART_MAIN);
		break;
	}
	case LV_EVENT_RELEASED:
	{
		lv_obj_clear_flag(guider_ui.light_label_9, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.light_btn_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.light_label_8, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.light_label_7, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_style_bg_img_recolor_opa(guider_ui.light_save, 0, LV_PART_MAIN);
		break;
	}
    default:
        break;
    }
}

static void light_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.light_label_9, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.light_btn_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.light_label_8, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.light_label_7, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

void events_init_light (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->light, light_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->light_back, light_back_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->light_save, light_save_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->light_btn_1, light_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void vibra_back_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_PRESSING:
	{
		lv_obj_set_style_bg_img_recolor_opa(guider_ui.vibra_back, 200, LV_PART_MAIN);
		break;
	}
	case LV_EVENT_RELEASED:
	{
		lv_obj_set_style_bg_img_recolor_opa(guider_ui.vibra_save, 0, LV_PART_MAIN);
		ui_load_scr_animation(&guider_ui, &guider_ui.config, guider_ui.config_del, &guider_ui.vibra_del, setup_scr_config, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

static void vibra_save_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_PRESSING:
	{
		lv_obj_set_style_bg_img_recolor_opa(guider_ui.vibra_save, 200, LV_PART_MAIN);
		break;
	}
	case LV_EVENT_RELEASED:
	{
		lv_obj_set_style_bg_img_recolor_opa(guider_ui.vibra_save, 0, LV_PART_MAIN);
		lv_obj_add_flag(guider_ui.vibra_btn_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibra_label_10, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibra_label_9, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibra_label_8, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

static void vibra_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.vibra_btn_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibra_label_10, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibra_label_9, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibra_label_8, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

void events_init_vibra (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->vibra_back, vibra_back_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->vibra_save, vibra_save_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->vibra_btn_1, vibra_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void freq_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_SCREEN_UNLOAD_START:
	{
		lv_obj_add_flag(guider_ui.freq_btn_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.freq_label_10, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.freq_label_9, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.freq_label_8, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

static void freq_back_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_PRESSING:
	{
		lv_obj_set_style_bg_img_recolor_opa(guider_ui.freq_save, 200, LV_PART_MAIN);
		break;
	}
	case LV_EVENT_RELEASED:
	{
		lv_obj_set_style_bg_img_recolor_opa(guider_ui.freq_save, 0, LV_PART_MAIN);
		ui_load_scr_animation(&guider_ui, &guider_ui.config, guider_ui.config_del, &guider_ui.freq_del, setup_scr_config, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

static void freq_save_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_PRESSING:
	{
		lv_obj_set_style_bg_img_recolor_opa(guider_ui.freq_save, 200, LV_PART_MAIN);
		break;
	}
	case LV_EVENT_RELEASED:
	{
		lv_obj_set_style_bg_img_recolor_opa(guider_ui.freq_save, 0, LV_PART_MAIN);
		lv_obj_clear_flag(guider_ui.freq_btn_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.freq_label_10, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.freq_label_9, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.freq_label_8, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

static void freq_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.freq_btn_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.freq_label_10, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.freq_label_9, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.freq_label_8, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

void events_init_freq (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->freq, freq_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->freq_back, freq_back_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->freq_save, freq_save_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->freq_btn_1, freq_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void password1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_SCREEN_UNLOADED:
	{
		lv_obj_add_flag(guider_ui.password1_label_14, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password1_btn_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password1_label_16, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password1_label_15, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

static void password1_btnm_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_t * obj = lv_event_get_target(e);
		uint32_t id = lv_btnmatrix_get_selected_btn(obj);

		switch (id) {
		case (0):
		{
			break;
		}
		case (1):
		{
			break;
		}
		case (2):
		{
			break;
		}
		case (3):
		{
			break;
		}
		case (4):
		{
			break;
		}
		case (5):
		{
			break;
		}
		case (6):
		{
			break;
		}
		case (7):
		{
			break;
		}
		case (8):
		{
			break;
		}
		case (9):
		{
			break;
		}
		case (10):
		{
			break;
		}
		case (11):
		{
			break;
		}
		default:
			break;
		}
		break;
	}
    default:
        break;
    }
}

static void password1_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.main, guider_ui.main_del, &guider_ui.password1_del, setup_scr_main, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, true);
		break;
	}
    default:
        break;
    }
}

static void password1_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.password1_btn_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password1_label_16, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password1_label_15, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password1_label_14, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_style_bg_opa(guider_ui.password1_label_7, 0, LV_PART_MAIN);
		lv_obj_set_style_bg_opa(guider_ui.password1_label_6, 0, LV_PART_MAIN);
		lv_obj_set_style_bg_opa(guider_ui.password1_label_5, 0, LV_PART_MAIN);
		lv_obj_set_style_bg_opa(guider_ui.password1_label_4, 0, LV_PART_MAIN);
		lv_obj_set_style_bg_opa(guider_ui.password1_label_3, 0, LV_PART_MAIN);
		lv_obj_set_style_bg_opa(guider_ui.password1_label_2, 0, LV_PART_MAIN);
		break;
	}
    default:
        break;
    }
}

void events_init_password1 (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->password1, password1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->password1_btnm_1, password1_btnm_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->password1_btn_1, password1_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->password1_btn_2, password1_btn_2_event_handler, LV_EVENT_ALL, ui);
}

static void password2_btnm_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_t * obj = lv_event_get_target(e);
		uint32_t id = lv_btnmatrix_get_selected_btn(obj);

		switch (id) {
		case (0):
		{
			break;
		}
		case (1):
		{
			break;
		}
		case (2):
		{
			break;
		}
		case (3):
		{
			break;
		}
		case (4):
		{
			break;
		}
		case (5):
		{
			break;
		}
		case (6):
		{
			break;
		}
		case (7):
		{
			break;
		}
		case (8):
		{
			break;
		}
		case (9):
		{
			break;
		}
		case (10):
		{
			break;
		}
		case (11):
		{
			break;
		}
		default:
			break;
		}
		break;
	}
    default:
        break;
    }
}

static void password2_btn_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		break;
	}
    default:
        break;
    }
}

void events_init_password2 (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->password2_btnm_1, password2_btnm_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->password2_btn_3, password2_btn_3_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
