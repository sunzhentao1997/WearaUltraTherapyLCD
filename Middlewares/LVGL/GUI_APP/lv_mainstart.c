#include "lv_mainstart.h"
#include "gui_guider.h"
#include "events_init.h"
#include "lvgl.h"
#include <stdio.h>

#include "dev_app.h"

static void Screen_Boost(void);
static void Screen_Charge(void);

extern Battery_Level SendBatteryStateData;

DEVICESPARAM DevicesParam;

lv_ui guider_ui;
SCREENID Screen_Id = MAIN_SCREEN;
SCREENSTATE ScreenState = READY;
SCREENSTATE ScreenState_old = READY;
int16_t SliderVal = 1800;
uint32_t MotorLevel = 0;
uint16_t FreqOffset = 0;
uint8_t SlaveFlg = 0;
uint8_t LowBatteryFlg = 0;
uint16_t LightLevel = 50;
char timebuf[] = "30:00";

uint32_t ScreenCount = 0;
uint32_t BatteryCount = 0;

void lv_mainstart(void)
{
    setup_ui(&guider_ui);
   	events_init(&guider_ui);
}

static void get_time_buff(void)
{
		timebuf[0] = (char)(SliderVal / 60 / 10 + 0x30); 
		timebuf[1] = (char)(SliderVal / 60 % 10 + 0x30); 
		timebuf[3] = (char)(SliderVal % 60 / 10 + 0x30); 
		timebuf[4] = (char)(SliderVal % 10 + 0x30); 
}

void ScreenFunc(void)
{
		uint8_t id = 0;
		static uint8_t BatteryStaOld = Boost_Level5;
//		SendBatteryStateData = Boost_Level2;
//		LowBatteryFlg = 1;
	
		if(SendBatteryStateData < Boost_Level1)
		{
				/*进入充电界面*/
				Screen_Charge();
			  BatteryStaOld = (uint8_t)SendBatteryStateData;
		}else if(LowBatteryFlg == 1)
		{
			  /*低电量进入低电量界面*/
			  id = Screen_Id;
				switch(id)
				{
					case MAIN_SCREEN:
						ui_load_scr_animation(&guider_ui, &guider_ui.lowbattery, guider_ui.lowbattery_del, &guider_ui.main_del, setup_scr_lowbattery, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
					break;
					case CONFIG_SCREEN:
						ui_load_scr_animation(&guider_ui, &guider_ui.lowbattery, guider_ui.lowbattery_del, &guider_ui.config_del, setup_scr_lowbattery, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
					break;
					case PARAM_SCREEN:
						ui_load_scr_animation(&guider_ui, &guider_ui.lowbattery, guider_ui.lowbattery_del, &guider_ui.param_del, setup_scr_lowbattery, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
					break;
					case LIGHT_SCREEN:
						ui_load_scr_animation(&guider_ui, &guider_ui.lowbattery, guider_ui.lowbattery_del, &guider_ui.light_del, setup_scr_lowbattery, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
					break;
					case FREQ_SCREEN:
						ui_load_scr_animation(&guider_ui, &guider_ui.lowbattery, guider_ui.lowbattery_del, &guider_ui.freq_del, setup_scr_lowbattery, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
					break;
					case VIBRA_SCREEN:
						ui_load_scr_animation(&guider_ui, &guider_ui.lowbattery, guider_ui.lowbattery_del, &guider_ui.vibra_del, setup_scr_lowbattery, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
					break;
					default:
						
					break;
				}
				
				Screen_Id = LOWBATTERY_SCREEN;
		}else
		{
				/*充电结束跳转放电界面*/
				if(BatteryStaOld < Boost_Level1)
				{
					ui_load_scr_animation(&guider_ui, &guider_ui.main, guider_ui.main_del, &guider_ui.Charge_del, setup_scr_main, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
					BatteryStaOld = (uint8_t)SendBatteryStateData;
				}
				Screen_Boost();
		}
}

void Screen_Boost(void)
{
		static uint8_t BoostLevel = Boost_Level5;
		if(ScreenState == WORK)
		{
				ScreenState_old = ScreenState;
			  if(ScreenCount >= 1000)
				{
					SliderVal--;
					if(SliderVal < 0)
					{
						SliderVal = 0;
						ScreenState = STOP;
					}
					get_time_buff();
					lv_arc_set_value(guider_ui.main_arc_1, SliderVal);
					lv_label_set_text(guider_ui.main_label_2, timebuf);
					ScreenCount = 0;
				}
		}else if(ScreenState == READY)
		{
				if(ScreenState != ScreenState_old)
				{
						SliderVal = 1800;
						ScreenState_old = ScreenState;
						ScreenCount = 0;
					
						memcpy(timebuf,"30:00",5);
						lv_arc_set_value(guider_ui.main_arc_1, SliderVal);
						lv_label_set_text(guider_ui.main_label_2, timebuf);
						
				}else
				{
					if(ScreenCount >= 1500)
					{
						SliderVal = 1800;
						ScreenCount = 0;
						
						memcpy(timebuf,"30:00",5);
						lv_arc_set_value(guider_ui.main_arc_1, SliderVal);
						lv_label_set_text(guider_ui.main_label_2, timebuf);
					}
				}
				
		}else if(ScreenState == STOP)
		{
				if(ScreenState != ScreenState_old)
				{
						BeepFlg = 2;
					  BeepCount = 8;
						SliderVal = 0;
						ScreenCount = 0;
						ScreenState_old = ScreenState;
					  DevWorkState = IDLE_STATE;
					
						memcpy(timebuf,"00:00",5);
					
						lv_obj_add_flag(guider_ui.main_ulock, LV_OBJ_FLAG_HIDDEN);
						lv_obj_clear_flag(guider_ui.main_switch2, LV_OBJ_FLAG_HIDDEN);
						lv_obj_clear_flag(guider_ui.main_switch1, LV_OBJ_FLAG_HIDDEN);
					
						lv_label_set_text(guider_ui.main_label_6, "— — ");
					  lv_label_set_text(guider_ui.main_change_label, "请选择 ");
						lv_label_set_text(guider_ui.main_label_3, "治疗已完成 ");
						lv_arc_set_value(guider_ui.main_arc_1, SliderVal);
						lv_label_set_text(guider_ui.main_label_2, timebuf);
				}else
				{
						if(ScreenCount >= 1500)
						{
							SliderVal = 0;
							memcpy(timebuf,"00:00",5);
							lv_label_set_text(guider_ui.main_label_3, "治疗已完成 ");
							lv_arc_set_value(guider_ui.main_arc_1, SliderVal);
							lv_label_set_text(guider_ui.main_label_2, timebuf);
							ScreenCount = 0;
						}
				}
		}else
		{
		}
		
		if(BatteryCount > 500)
		{
			BatteryCount = 0;
			
			if((BoostLevel < SendBatteryStateData) && (SendBatteryStateData >= Boost_Level1))
			{
					BoostLevel = BoostLevel;
			}else
			{
					BoostLevel = SendBatteryStateData;
			}
			
			if((Low_Battery_Flg == 1) && (ScreenState != WORK))
			{
					LowBatteryFlg = 1;
			}
			
			if(Screen_Id == MAIN_SCREEN)
			{
				switch(BoostLevel)
				{
					case Boost_Level1:
						lv_obj_add_flag(guider_ui.main_label_9, LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(guider_ui.main_label_10, LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(guider_ui.main_label_11, LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(guider_ui.main_label_12, LV_OBJ_FLAG_HIDDEN);
						break;
					case Boost_Level2:
						lv_obj_clear_flag(guider_ui.main_label_9, LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(guider_ui.main_label_10, LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(guider_ui.main_label_11, LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(guider_ui.main_label_12, LV_OBJ_FLAG_HIDDEN);
						break;
					case Boost_Level3:
						lv_obj_clear_flag(guider_ui.main_label_9, LV_OBJ_FLAG_HIDDEN);
						lv_obj_clear_flag(guider_ui.main_label_10, LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(guider_ui.main_label_11, LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(guider_ui.main_label_12, LV_OBJ_FLAG_HIDDEN);
						break;
					case Boost_Level4:
						lv_obj_clear_flag(guider_ui.main_label_9, LV_OBJ_FLAG_HIDDEN);
						lv_obj_clear_flag(guider_ui.main_label_10, LV_OBJ_FLAG_HIDDEN);
						lv_obj_clear_flag(guider_ui.main_label_11, LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(guider_ui.main_label_12, LV_OBJ_FLAG_HIDDEN);
						break;
					case Boost_Level5:
						lv_obj_clear_flag(guider_ui.main_label_9, LV_OBJ_FLAG_HIDDEN);
						lv_obj_clear_flag(guider_ui.main_label_10, LV_OBJ_FLAG_HIDDEN);
						lv_obj_clear_flag(guider_ui.main_label_11, LV_OBJ_FLAG_HIDDEN);
						lv_obj_clear_flag(guider_ui.main_label_12, LV_OBJ_FLAG_HIDDEN);
						break;
					default:
						break;
				}
			}
		}
}

void Screen_Charge(void)
{
		uint8_t id;
		uint8_t chargelevel = 0;
		static uint8_t Send_Val = 0;
		static uint8_t chact = 0;
		static uint8_t ChargeFlg = 0;
		static uint16_t RefreshCount = 0; 
		
		id = Screen_Id; 
		if(DevWorkState == CHARGE_STATE)
		{		
				switch(id)
				{
					case MAIN_SCREEN:
						ui_load_scr_animation(&guider_ui, &guider_ui.Charge, guider_ui.Charge_del, &guider_ui.main_del, setup_scr_Charge, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
					break;
					case CONFIG_SCREEN:
						ui_load_scr_animation(&guider_ui, &guider_ui.Charge, guider_ui.Charge_del, &guider_ui.config_del, setup_scr_Charge, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
					break;
					case PARAM_SCREEN:
						ui_load_scr_animation(&guider_ui, &guider_ui.Charge, guider_ui.Charge_del, &guider_ui.param_del, setup_scr_Charge, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
					break;
					case LIGHT_SCREEN:
						ui_load_scr_animation(&guider_ui, &guider_ui.Charge, guider_ui.Charge_del, &guider_ui.light_del, setup_scr_Charge, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
					break;
					case FREQ_SCREEN:
						ui_load_scr_animation(&guider_ui, &guider_ui.Charge, guider_ui.Charge_del, &guider_ui.freq_del, setup_scr_Charge, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
					break;
					case VIBRA_SCREEN:
						ui_load_scr_animation(&guider_ui, &guider_ui.Charge, guider_ui.Charge_del, &guider_ui.vibra_del, setup_scr_Charge, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
					break;
					case LOWBATTERY_SCREEN:
						ui_load_scr_animation(&guider_ui, &guider_ui.Charge, guider_ui.Charge_del, &guider_ui.lowbattery_del, setup_scr_Charge, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
					break;
					default:
						
					break;
				}
				Screen_Id = CHAREG_SCREEN;
		}
		
		if(Screen_Id == CHAREG_SCREEN)
		{
				RefreshCount++;
				if(RefreshCount > 60)
				{
					  RefreshCount = 0;
						if((chact < Boost_Level1) && (chact >= SendBatteryStateData))
						{
								chargelevel = chact;
								chact++;
						}else
						{
								chact = SendBatteryStateData;
								chargelevel = chact;
						}
						
					switch(chargelevel)
					{
						case 1:
								lv_obj_add_flag(guider_ui.Charge_label_3, LV_OBJ_FLAG_HIDDEN);
								lv_obj_add_flag(guider_ui.Charge_label_4, LV_OBJ_FLAG_HIDDEN);
								lv_obj_add_flag(guider_ui.Charge_label_5, LV_OBJ_FLAG_HIDDEN);
								lv_obj_add_flag(guider_ui.Charge_label_6, LV_OBJ_FLAG_HIDDEN);
							break;
						case 2:
								lv_obj_add_flag(guider_ui.Charge_label_3, LV_OBJ_FLAG_HIDDEN);
								lv_obj_add_flag(guider_ui.Charge_label_4, LV_OBJ_FLAG_HIDDEN);
								lv_obj_add_flag(guider_ui.Charge_label_5, LV_OBJ_FLAG_HIDDEN);
								lv_obj_clear_flag(guider_ui.Charge_label_6, LV_OBJ_FLAG_HIDDEN);
							break;
						case 3:
								lv_obj_add_flag(guider_ui.Charge_label_3, LV_OBJ_FLAG_HIDDEN);
								lv_obj_add_flag(guider_ui.Charge_label_4, LV_OBJ_FLAG_HIDDEN);
								lv_obj_clear_flag(guider_ui.Charge_label_5, LV_OBJ_FLAG_HIDDEN);
								lv_obj_clear_flag(guider_ui.Charge_label_6, LV_OBJ_FLAG_HIDDEN);
							break;
						case 4:
								lv_obj_add_flag(guider_ui.Charge_label_3, LV_OBJ_FLAG_HIDDEN);
								lv_obj_clear_flag(guider_ui.Charge_label_4, LV_OBJ_FLAG_HIDDEN);
								lv_obj_clear_flag(guider_ui.Charge_label_5, LV_OBJ_FLAG_HIDDEN);
								lv_obj_clear_flag(guider_ui.Charge_label_6, LV_OBJ_FLAG_HIDDEN);
							break;
						case 5:
								lv_obj_clear_flag(guider_ui.Charge_label_3, LV_OBJ_FLAG_HIDDEN);
								lv_obj_clear_flag(guider_ui.Charge_label_4, LV_OBJ_FLAG_HIDDEN);
								lv_obj_clear_flag(guider_ui.Charge_label_5, LV_OBJ_FLAG_HIDDEN);
								lv_obj_clear_flag(guider_ui.Charge_label_6, LV_OBJ_FLAG_HIDDEN);
							break;
						default:
							break;
					}
				}
		}
}

