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

#include "main.h"
#include "tim.h"
#include "lv_mainstart.h"
#include "dev_app.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


/*****************************************************************************************************
 * 
 *																						主页事件处理
 *
 ****************************************************************************************************/
static void main_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
	
    switch (code) 
		{
			case LV_EVENT_SCREEN_LOAD_START:
			{
				lv_obj_add_flag(guider_ui.main_start, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.main_ulock, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.main_stop, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.main_suo, LV_OBJ_FLAG_HIDDEN);
			break;
			}
			case LV_EVENT_SCREEN_LOADED:
			{
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
		if(ScreenState != WORK)
		{
			switch (code) 
			{
				case LV_EVENT_CLICKED:
				{
					ui_load_scr_animation(&guider_ui, &guider_ui.config, guider_ui.config_del, &guider_ui.main_del, setup_scr_config, LV_SCR_LOAD_ANIM_NONE, 50, 50, false, true);
					
					ScreenState = OTHER;
					Screen_Id = CONFIG_SCREEN;
					DevWorkState = PASUE_STATE;
				break;
				}
				default:
				break;
			}
		}else
		{
		}
}

static void main_change_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if(ScreenState != WORK)
	{
		switch (code) 
		{
			case LV_EVENT_CLICKED:
			{
				lv_obj_clear_flag(guider_ui.main_switch1, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(guider_ui.main_switch2, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.main_start, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.main_ulock, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.main_stop, LV_OBJ_FLAG_HIDDEN);
				lv_label_set_text(guider_ui.main_change_label, "请选择 ");
				lv_obj_add_flag(guider_ui.main_suo, LV_OBJ_FLAG_HIDDEN);
			break;
			}
			default:
        break;
    }
	}else
	{
	}
}

static void main_stop_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) 
		{
			case LV_EVENT_CLICKED:
			{
					lv_obj_clear_flag(guider_ui.main_switch1, LV_OBJ_FLAG_HIDDEN);
					lv_obj_clear_flag(guider_ui.main_switch2, LV_OBJ_FLAG_HIDDEN);
					lv_obj_add_flag(guider_ui.main_start, LV_OBJ_FLAG_HIDDEN);
					lv_obj_add_flag(guider_ui.main_ulock, LV_OBJ_FLAG_HIDDEN);
					lv_obj_add_flag(guider_ui.main_stop, LV_OBJ_FLAG_HIDDEN);
					lv_label_set_text(guider_ui.main_change_label, "请选择 ");
					lv_obj_set_style_text_font(guider_ui.main_change, &lv_customer_font_NSHBold_50, 0);
					lv_obj_add_flag(guider_ui.main_suo, LV_OBJ_FLAG_HIDDEN);
					
					DevWorkState = IDLE_STATE;
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
		lv_obj_add_flag(guider_ui.main_suo, LV_OBJ_FLAG_HIDDEN);
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
		lv_obj_clear_flag(guider_ui.main_suo, LV_OBJ_FLAG_HIDDEN);
		
		DevWorkState = WORK_STATE;
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
		lv_obj_add_flag(guider_ui.main_suo, LV_OBJ_FLAG_HIDDEN);
		UltraDuty = 66;
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
		lv_obj_add_flag(guider_ui.main_suo, LV_OBJ_FLAG_HIDDEN);
		UltraDuty = 25;
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

/*****************************************************************************************************
 * 
 *																						配置事件处理
 *
 ****************************************************************************************************/
static void config_param_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.param, guider_ui.param_del, &guider_ui.config_del, setup_scr_param, LV_SCR_LOAD_ANIM_NONE, 50, 50, true, true);
		Screen_Id = PARAM_SCREEN;
		
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
		ui_load_scr_animation(&guider_ui, &guider_ui.light, guider_ui.light_del, &guider_ui.config_del, setup_scr_light, LV_SCR_LOAD_ANIM_NONE, 50, 50, false, true);
		Screen_Id = LIGHT_SCREEN;
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
		ui_load_scr_animation(&guider_ui, &guider_ui.freq, guider_ui.freq_del, &guider_ui.config_del, setup_scr_freq, LV_SCR_LOAD_ANIM_NONE, 50, 50, false, true);
		Screen_Id = FREQ_SCREEN;
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
		ui_load_scr_animation(&guider_ui, &guider_ui.vibra, guider_ui.vibra_del, &guider_ui.config_del, setup_scr_vibra, LV_SCR_LOAD_ANIM_NONE, 50, 50, false, true);
		Screen_Id = VIBRA_SCREEN;
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
		ui_load_scr_animation(&guider_ui, &guider_ui.main, guider_ui.main_del, &guider_ui.config_del, setup_scr_main, LV_SCR_LOAD_ANIM_NONE, 50, 50, false, true);
		DevWorkState = IDLE_STATE;
		Screen_Id = MAIN_SCREEN;
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

/*****************************************************************************************************
 * 
 *																						参数事件处理
 *
 ****************************************************************************************************/
static uint8_t ParamBuff[6] = {0x20};
static uint8_t ParamBuffTemp[6] = {0x20,0x20,0x20,0x20,0x20,0x20};
static uint8_t ParamFlg = 0;
static int8_t ParamIndex = 0;

static void param_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_SCREEN_LOAD_START:
	{
		lv_obj_add_flag(guider_ui.param_btnm_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_btn_6, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_label_7, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

static void param_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		SlaveFlg = 1;
		break;
	}
    default:
        break;
    }
}

static void param_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.config, guider_ui.config_del, &guider_ui.param_del, setup_scr_config, LV_SCR_LOAD_ANIM_NONE, 50, 50, false, true);
		Screen_Id = CONFIG_SCREEN;
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
			ParamBuff[ParamIndex] = 0x31;
			ParamIndex++;
			lv_label_set_text(guider_ui.param_label_7, (const char*)&ParamBuff);
			break;
		}
		case (1):
		{
			ParamBuff[ParamIndex] = 0x32;
			ParamIndex++;
			lv_label_set_text(guider_ui.param_label_7, (const char*)&ParamBuff);
			break;
		}
		case (2):
		{
			ParamBuff[ParamIndex] = 0x33;
			ParamIndex++;
			lv_label_set_text(guider_ui.param_label_7, (const char*)&ParamBuff);
			break;
		}
		case (3):
		{
			ParamBuff[ParamIndex] = 0x34;
			ParamIndex++;
			lv_label_set_text(guider_ui.param_label_7, (const char*)&ParamBuff);
			break;
		}
		case (4):
		{
			ParamBuff[ParamIndex] = 0x35;
			ParamIndex++;
			lv_label_set_text(guider_ui.param_label_7, (const char*)&ParamBuff);
			break;
		}
		case (5):
		{
			ParamBuff[ParamIndex] = 0x36;
			ParamIndex++;
			lv_label_set_text(guider_ui.param_label_7, (const char*)&ParamBuff);
			break;
		}
		case (6):
		{
			ParamBuff[ParamIndex] = 0x37;
			ParamIndex++;
			lv_label_set_text(guider_ui.param_label_7, (const char*)&ParamBuff);
			break;
		}
		case (7):
		{
			ParamBuff[ParamIndex] = 0x38;
			ParamIndex++;
			lv_label_set_text(guider_ui.param_label_7, (const char*)&ParamBuff);
			break;
		}
		case (8):
		{
			ParamBuff[ParamIndex] = 0x39;
			ParamIndex++;
			lv_label_set_text(guider_ui.param_label_7, (const char*)&ParamBuff);
			break;
		}
		case (9):
		{
			ParamBuff[ParamIndex] = 0x2E;
			ParamIndex++;
			lv_label_set_text(guider_ui.param_label_7, (const char*)&ParamBuff);
			break;
		}
		case (10):
		{
			ParamBuff[ParamIndex] = 0x30;
			ParamIndex++;
			lv_label_set_text(guider_ui.param_label_7, (const char*)&ParamBuff);
			break;
		}
		case (11):
		{
			lv_obj_add_flag(guider_ui.param_btnm_1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.param_btn_2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.param_btn_1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.param_btn_6, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.param_label_7, LV_OBJ_FLAG_HIDDEN);
			if(ParamFlg == 3)
			{
				lv_label_set_text(guider_ui.param_btn_3_label, (const char*)&ParamBuff);
				memcpy(DevicesParam.DevParam.DeviceIdBuff,ParamBuff,6);
			}else if(ParamFlg == 4)
			{
				lv_label_set_text(guider_ui.param_btn_4_label, (const char*)&ParamBuff);
				memcpy(DevicesParam.DevParam.PowerBuff,ParamBuff,6);
			}else if(ParamFlg == 5)
			{
				lv_label_set_text(guider_ui.param_btn_5_label, (const char*)&ParamBuff);
				memcpy(DevicesParam.DevParam.TemperatureBuff,ParamBuff,6);
			}
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
				
		if(ParamIndex > 5)
		{
			 ParamIndex = 5;
		}
}

static void param_btn_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ParamFlg = 3;
		ParamIndex = 0;
		
		memcpy(ParamBuff,ParamBuffTemp,6);
		lv_obj_clear_flag(guider_ui.param_btnm_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_btn_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_btn_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_btn_6, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_label_7, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

static void param_btn_4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ParamFlg = 4;
		ParamIndex = 0;
		
		memcpy(ParamBuff,ParamBuffTemp,6);
		lv_obj_clear_flag(guider_ui.param_btnm_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_btn_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_btn_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_btn_6, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_label_7, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

static void param_btn_5_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ParamFlg = 5;
		ParamIndex = 0;
		
		memcpy(ParamBuff,ParamBuffTemp,6);
		lv_obj_clear_flag(guider_ui.param_btnm_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_btn_2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_btn_1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_btn_6, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_label_7, LV_OBJ_FLAG_HIDDEN);
		break;
	}
    default:
        break;
    }
}

static void param_btn_6_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) 
		{
			case LV_EVENT_CLICKED:
			{
				ParamBuff[ParamIndex] = 0x20;
				ParamIndex--;
				lv_label_set_text(guider_ui.param_label_7, (const char*)&ParamBuff);
				break;
			}
			default:
      break;
    }
		if(ParamIndex < 0)
		{
			ParamIndex = 0;
		}
}

void events_init_param (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->param, param_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->param_btn_1, param_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->param_btn_2, param_btn_2_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->param_btnm_1, param_btnm_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->param_btn_3, param_btn_3_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->param_btn_4, param_btn_4_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->param_btn_5, param_btn_5_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->param_btn_6, param_btn_6_event_handler, LV_EVENT_ALL, ui);
}


/*****************************************************************************************************
 * 
 *																						亮度事件处理
 *
 ****************************************************************************************************/
static void light_slider_1_event_handler (lv_event_t *e)
{
		int32_t tempval = 0;
	
		lv_obj_t *target = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
	
		tempval = lv_slider_get_value(target);
	  LightLevel = (uint8_t)tempval;
		tempval = LightLevel * 10;
    switch (code) 
		{
				case LV_EVENT_VALUE_CHANGED:
				{
						lv_label_set_text_fmt(guider_ui.light_label_3, "%d%%",LightLevel);
						__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,tempval);
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
		SlaveFlg = 1;
		break;
	}
    default:
        break;
    }
}

static void light_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.config, guider_ui.config_del, &guider_ui.light_del, setup_scr_config, LV_SCR_LOAD_ANIM_NONE, 50, 50, false, true);
		Screen_Id = CONFIG_SCREEN;
		break;
	}
    default:
        break;
    }
}

void events_init_light (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->light_slider_1, light_slider_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->light_btn_1, light_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->light_btn_2, light_btn_2_event_handler, LV_EVENT_ALL, ui);
}

/*****************************************************************************************************
 * 
 *																						频率事件处理
 *
 ****************************************************************************************************/
static void freq_roller_1_event_handler (lv_event_t *e)
{
   	uint16_t tempval = 0;
	
		lv_obj_t *target = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
	
		tempval = lv_roller_get_selected(target);
		
		FreqOffset = tempval;
	
    switch (code) 
		{
			case LV_EVENT_VALUE_CHANGED:
			{
				break;
			}
			default:
				break;
    }
}

static void freq_btn_1_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	
	switch (code) 
	{
		case LV_EVENT_CLICKED:
		{
				SlaveFlg = 1;
				break;
		}
    default:
        break;
  }
}

static void freq_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.config, guider_ui.config_del, &guider_ui.freq_del, setup_scr_config, LV_SCR_LOAD_ANIM_NONE, 50, 50, false, true);
		Screen_Id = CONFIG_SCREEN;
		break;
	}
    default:
        break;
    }
}

void events_init_freq (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->freq_roller_1, freq_roller_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->freq_btn_1, freq_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->freq_btn_2, freq_btn_2_event_handler, LV_EVENT_ALL, ui);
}
/*****************************************************************************************************
 * 
 *																						震动事件处理
 *
 ****************************************************************************************************/
static void vibra_slider_1_event_handler (lv_event_t *e)
{
		int32_t tempval = 0;
	
		lv_obj_t *target = lv_event_get_target(e);
    lv_event_code_t code = lv_event_get_code(e);
	
		tempval = lv_slider_get_value(target);
	  MotorLevel = tempval;
		tempval = tempval * 5;
	
    switch (code) 
		{
			case LV_EVENT_VALUE_CHANGED:
			{
				lv_label_set_text_fmt(guider_ui.vibra_label_3, "%d%%",tempval);
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
		SlaveFlg = 1;
		break;
	}
    default:
        break;
    }
}

static void vibra_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
	case LV_EVENT_CLICKED:
	{
		Screen_Id = CONFIG_SCREEN;
		ui_load_scr_animation(&guider_ui, &guider_ui.config, guider_ui.config_del, &guider_ui.vibra_del, setup_scr_config, LV_SCR_LOAD_ANIM_NONE, 50, 50, false, true);
		break;
	}
    default:
        break;
    }
}

void events_init_vibra (lv_ui *ui)
{
	lv_obj_add_event_cb(ui->vibra_slider_1, vibra_slider_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->vibra_btn_1, vibra_btn_1_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->vibra_btn_2, vibra_btn_2_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{
		
}
