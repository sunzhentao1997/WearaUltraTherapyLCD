#include "lv_mainstart.h"
#include "gui_guider.h"
#include "events_init.h"
#include "lvgl.h"
#include <stdio.h>
#include "usart.h"

#include "dev_app.h"
#include "tim.h"

static void Screen_Boost(void);
static void Screen_Charge(void);
static void Vibration_Feedback(void);

DEVICESPARAM DevicesParam;													//设备出厂参数
SCREENID Screen_Id = MAIN_SCREEN;										//屏幕ID
SCREENSTATE ScreenState = READY;										//屏幕状态
SCREENSTATE ScreenState_old = READY;								//屏幕历史状态
lv_ui guider_ui;																		//GUI句柄

uint8_t VibraChangeFlg = 0;													//震动修改标志位
uint8_t ClickCount = 0;
uint8_t SlaveFlg = 0;																//数据保存标志位
uint8_t UltraDuty = 0;															//脉冲占空比
uint16_t FreqOffset = 0;														//频率偏移
uint16_t LightLevel = 100;														//亮度
uint32_t MotorLevel = 0;														//震动等级						

static int16_t SliderVal = 1200;										//滑块值
static uint8_t LowBatteryFlg = 0;										//低电量标志位
static char timebuf[] = "20:00";										//时间显示
static uint16_t ClickTime = 0;

extern uint16_t back_pos;

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
		Vibration_Feedback();
	#if 0
		uint8_t id = 0;
		static uint8_t BatteryStaOld = Boost_Level5;
//		SendBatteryStateData = Boost_Level3;
//		LowBatteryFlg = 0;
		if(ClickCount == 1)
		{
			ClickTime++;	
			if(ClickTime > 200)
			{
				ClickTime = 0;
				ClickCount = 0;
			}
		}else if(ClickCount == 2)
		{
			ClickTime = 0;
			ClickCount = 0;
		}else
		{
				ClickTime = 0;
		}
		
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
					ui_load_scr_animation(&guider_ui, &guider_ui.main, guider_ui.main_del, &guider_ui.Charge_del, setup_scr_main, LV_SCR_LOAD_ANIM_NONE, 50, 50, false, true);
					BatteryStaOld = (uint8_t)SendBatteryStateData;
				}
				Screen_Boost();
		}
		
		if(UnlockFlg == 1 && (UnlockCount > 500))
		{
				lv_obj_add_flag(guider_ui.main_switch1, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.main_switch2, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.main_start, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.main_ulock, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(guider_ui.main_stop, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.main_suo, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.main_btn_1, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.main_label_9, LV_OBJ_FLAG_HIDDEN);
				lv_obj_set_pos(guider_ui.main_btn_1, 70, 662);
				UnlockFlg = 0;
		}else if(UnlockFlg == 2)
		{
			back_pos -= 20;
			if(back_pos < 70)
			{
				back_pos = 70;
				UnlockFlg = 0;
			}
			lv_obj_set_pos(guider_ui.main_btn_1, (lv_coord_t)back_pos, 662);
		}
		#endif
}

uint8_t test[5] = {0x31,0x32,0x33,0x34,0x35}; 
static void Screen_Boost(void)
{
	#if 0
		static uint8_t BoostLevel = Boost_Level5;
		if(ScreenState == WORK)
		{
				ScreenState_old = ScreenState;
			  if(ScreenTime >= 1000)
				{
					SliderVal--;
					if(SliderVal < 0)
					{
						SliderVal = 0;
						ScreenState = STOP;
					}
					get_time_buff();
					lv_arc_set_value(guider_ui.main_arc_1, SliderVal);
					lv_label_set_text(guider_ui.main_time, timebuf);
					ScreenTime = 0;
				}
		}else if(ScreenState == READY)
		{
				if(ScreenState != ScreenState_old)
				{
						SliderVal = 1200;
						ScreenState_old = ScreenState;
						ScreenTime = 0;
					
						memcpy(timebuf,"20:00",5);
						lv_arc_set_value(guider_ui.main_arc_1, SliderVal);
						lv_label_set_text(guider_ui.main_time, timebuf);
						
				}else
				{
					if(ScreenTime >= 1500)
					{
						SliderVal = 1200;
						ScreenTime = 0;
						
						memcpy(timebuf,"20:00",5);
						lv_arc_set_value(guider_ui.main_arc_1, SliderVal);
						lv_label_set_text(guider_ui.main_time, timebuf);
					}
				}
				
		}else if(ScreenState == STOP)
		{
				if(ScreenState != ScreenState_old)
				{
						BeepFlg = 2;
					  BeepCount = 12;
						SliderVal = 0;
						ScreenTime = 0;
						ScreenState_old = ScreenState;
					  DevWorkState = IDLE_STATE;
					
						memcpy(timebuf,"00:00",5);
					
						lv_obj_add_flag(guider_ui.main_ulock, LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(guider_ui.main_suo, LV_OBJ_FLAG_HIDDEN);
						lv_obj_clear_flag(guider_ui.main_switch2, LV_OBJ_FLAG_HIDDEN);
						lv_obj_clear_flag(guider_ui.main_switch1, LV_OBJ_FLAG_HIDDEN);
					
						lv_label_set_text(guider_ui.main_UltraPower, "—— ");
					  lv_label_set_text(guider_ui.main_change_label, "请选择 ");
						lv_label_set_text(guider_ui.main_label_3, "治疗已完成 ");
						lv_arc_set_value(guider_ui.main_arc_1, SliderVal);
						lv_label_set_text(guider_ui.main_time, timebuf);
				}else
				{
						if(ScreenTime >= 1500)
						{
							SliderVal = 0;
							memcpy(timebuf,"00:00",5);
							lv_label_set_text(guider_ui.main_label_3, "治疗已完成 ");
							lv_arc_set_value(guider_ui.main_arc_1, SliderVal);
							lv_label_set_text(guider_ui.main_time, timebuf);
							ScreenTime = 0;
						}
				}
		}else
		{
		}
		
		if(BatteryTime > 500)
		{
			BatteryTime = 0;
			
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
						lv_obj_add_flag(guider_ui.main_grat1, LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(guider_ui.main_grat2, LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(guider_ui.main_grat3, LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(guider_ui.main_grat4, LV_OBJ_FLAG_HIDDEN);
						break;
					case Boost_Level2:
						lv_obj_clear_flag(guider_ui.main_grat1, LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(guider_ui.main_grat2, LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(guider_ui.main_grat3, LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(guider_ui.main_grat4, LV_OBJ_FLAG_HIDDEN);
						break;
					case Boost_Level3:
						lv_obj_clear_flag(guider_ui.main_grat1, LV_OBJ_FLAG_HIDDEN);
						lv_obj_clear_flag(guider_ui.main_grat2, LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(guider_ui.main_grat3, LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(guider_ui.main_grat4, LV_OBJ_FLAG_HIDDEN);
						break;
					case Boost_Level4:
						lv_obj_clear_flag(guider_ui.main_grat1, LV_OBJ_FLAG_HIDDEN);
						lv_obj_clear_flag(guider_ui.main_grat2, LV_OBJ_FLAG_HIDDEN);
						lv_obj_clear_flag(guider_ui.main_grat3, LV_OBJ_FLAG_HIDDEN);
						lv_obj_add_flag(guider_ui.main_grat4, LV_OBJ_FLAG_HIDDEN);
						break;
					case Boost_Level5:
						lv_obj_clear_flag(guider_ui.main_grat1, LV_OBJ_FLAG_HIDDEN);
						lv_obj_clear_flag(guider_ui.main_grat2, LV_OBJ_FLAG_HIDDEN);
						lv_obj_clear_flag(guider_ui.main_grat3, LV_OBJ_FLAG_HIDDEN);
						lv_obj_clear_flag(guider_ui.main_grat4, LV_OBJ_FLAG_HIDDEN);
						break;
					default:
						break;
				}
			}
		}
	#endif
}

static void Screen_Charge(void)
{
	#if 0
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
				if(RefreshCount > 80)
				{
						//HAL_UART_Transmit(&huart1,test,5,0xFFFF);
						__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, 500);
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
		#endif
}

static void Vibration_Feedback(void)
{
	uint32_t vibra_value = 0;
	if(VibraChangeFlg == 1)
	{
		vibra_value = (uint32_t)MotorLevel * 106;
		DevGpio_SetOutSta(MOTOR_GATE,GPIO_PIN_SET);
		__HAL_TIM_SetCompare(MOTOR_HANDLE,MOTOR_CHB,vibra_value);

		if(VibraFeedBackTime > 2000)
		{
			VibraChangeFlg = 0;
			VibraFeedBackTime = 0;
			DevGpio_SetOutSta(MOTOR_GATE,GPIO_PIN_RESET);
			__HAL_TIM_SetCompare(MOTOR_HANDLE,MOTOR_CHB,0);
		}
	}
	else
	{
		VibraFeedBackTime = 0;
	}
}

uint32_t DisplayTime = 0;
uint8_t DisplayFlg = 1;
static void  ScreenOfInterest(void)
{

	if(DisplayTime > 120000)
	{
		DisplayFlg = 0;
	}

	if((DisplayFlg == 1) && (DevWorkState == WORK_STATE))
	{
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, LightLevel*10);
	}else if((DisplayFlg == 0) && (DevWorkState == WORK_STATE))	
	{
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, 10);
	}
}

