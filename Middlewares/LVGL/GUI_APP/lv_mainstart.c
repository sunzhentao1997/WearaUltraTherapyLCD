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
static void ScreenOfInterest(void);
static void Screen_MainFunc(void);
static void BatteryDisplay_Main(uint8_t boostlevel);
static void BatteryDisplay_Config(uint8_t boostlevel);
static void BatteryDisplay_Param(uint8_t boostlevel);
static void BatteryDisplay_Light(uint8_t boostlevel);
static void BatteryDisplay_Freq(uint8_t boostlevel);
static void BatteryDisplay_Vibra(uint8_t boostlevel);
static void BatteryDisplay_Vibras(uint8_t boostlevel);
static void BatteryDisplay_Password1(uint8_t boostlevel);
static void BatteryDisplay_Password2(uint8_t boostlevel);
const BATTERYDISPLAY_FUNC battery_display_func[ScreenId_Max] =
	{
		[MAIN_SCREEN] = BatteryDisplay_Main,
		[CONFIG_SCREEN] = BatteryDisplay_Config,
		[PARAM_SCREEN] = BatteryDisplay_Param,
		[LIGHT_SCREEN] = BatteryDisplay_Light,
		[FREQ_SCREEN] = BatteryDisplay_Freq,
		[VIBRA_SCREEN] = BatteryDisplay_Vibra,
		[VIBRAS_SCREEN] = BatteryDisplay_Vibras,
		[CHAREG_SCREEN] = NULL,
		[PASSWORD1_SCREEN] = BatteryDisplay_Password1,
		[PASSWORD2_SCREEN] = BatteryDisplay_Password2,
};

DEVICESPARAM DevicesParam;			 // 设备出厂参数
SCREENID Screen_Id = BOOST_SCREEN;	 // 屏幕ID
SCREENSTATE ScreenState = IDLE;	 // 屏幕状态
SCREENSTATE ScreenState_old = IDLE; // 屏幕历史状态
lv_ui guider_ui;					 // GUI句柄

uint8_t VibraChangeFlg = 0;	   // 震动修改标志位
uint8_t SlaveFlg = 0;		   // 数据保存标志位
uint8_t UltraDuty = 25;		   // 脉冲占空比
uint16_t FreqOffset = 0;	   // 频率偏移
uint16_t LightLevel = 100;	   // 亮度
uint16_t LightLevel_old = 100; // 历史亮度
uint32_t MotorLevel = 0;	   // 震动等级
uint16_t back_pos = 40;
uint8_t DisplayFlg = 1;
uint8_t ParamLockFlg = 0;
uint8_t VibraEnableFlg = 1;
uint8_t VibraEnableFlg_old = 1;

static int16_t SliderVal = 1200;  // 滑块值
static uint8_t LowBatteryFlg = 0; // 低电量标志位
static char timebuf[] = "20:00";  // 时间显示
static uint16_t ClickTime = 0;	  // 点击时间

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

/* 屏幕主功能 */
void ScreenFunc(void)
{
	uint8_t id = 0;
	static uint8_t BatteryStaOld = BOOST;

	if (BatteryState != BOOST)
	{
		/*进入充电界面*/
		Screen_Charge();
		BatteryStaOld = BatteryState;
	}
	else
	{
		/*充电结束跳转放电界面*/
		if (BatteryStaOld != BOOST)
		{
			ui_load_scr_animation(&guider_ui, &guider_ui.main, guider_ui.main_del, &guider_ui.charge_del, setup_scr_main, LV_SCR_LOAD_ANIM_NONE, 50, 50, false, true);
			BatteryStaOld = BOOST;
		}
		Screen_Boost();
	}
}

/* 放电显示界面 */
static void Screen_Boost(void)
{
	static uint8_t BoostLevel = Battery_Level5;

	switch (Screen_Id)
	{
	case MAIN_SCREEN:
		Screen_MainFunc();
		break;

	default:
		break;
	}

	BoostLevel = SendBatteryStateData;
	if (BatteryTime > 500)
	{
		BatteryTime = 0;

		if (battery_display_func[Screen_Id])
		{
			battery_display_func[Screen_Id](BoostLevel);
		}
	}
}

static void Screen_Charge(void)
{
	uint8_t id;
	uint8_t chargelevel = 0;
	static uint8_t Send_Val = 0;
	static uint8_t chact = 0;
	static uint8_t ChargeFlg = 0;
	static uint16_t RefreshCount = 0;

	id = Screen_Id;

	/* 进入充电界面 */
	if (DevWorkState == CHARGE_STATE)
	{
		switch (id)
		{
		case MAIN_SCREEN:
			ui_load_scr_animation(&guider_ui, &guider_ui.charge, guider_ui.charge_del, &guider_ui.main_del, setup_scr_charge, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
			break;
		case CONFIG_SCREEN:
			ui_load_scr_animation(&guider_ui, &guider_ui.charge, guider_ui.charge_del, &guider_ui.config_del, setup_scr_charge, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
			break;
		case PARAM_SCREEN:
			ui_load_scr_animation(&guider_ui, &guider_ui.charge, guider_ui.charge_del, &guider_ui.param_del, setup_scr_charge, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
			break;
		case LIGHT_SCREEN:
			ui_load_scr_animation(&guider_ui, &guider_ui.charge, guider_ui.charge_del, &guider_ui.light_del, setup_scr_charge, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
			break;
		case FREQ_SCREEN:
			ui_load_scr_animation(&guider_ui, &guider_ui.charge, guider_ui.charge_del, &guider_ui.freq_del, setup_scr_charge, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
			break;
		case VIBRA_SCREEN:
			ui_load_scr_animation(&guider_ui, &guider_ui.charge, guider_ui.charge_del, &guider_ui.vibra_del, setup_scr_charge, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
			break;
		case VIBRAS_SCREEN:
			ui_load_scr_animation(&guider_ui, &guider_ui.charge, guider_ui.charge_del, &guider_ui.vibras_del, setup_scr_charge, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
			break;
		case PASSWORD1_SCREEN:
			ui_load_scr_animation(&guider_ui, &guider_ui.charge, guider_ui.charge_del, &guider_ui.password1_del, setup_scr_charge, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
			break;
		case PASSWORD2_SCREEN:
			ui_load_scr_animation(&guider_ui, &guider_ui.charge, guider_ui.charge_del, &guider_ui.password2_del, setup_scr_charge, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
			break;
		default:
			break;
		}
		Screen_Id = CHAREG_SCREEN;
	}

	/* 充电动画 */
	if (Screen_Id == CHAREG_SCREEN)
	{
		RefreshCount++;
		if (RefreshCount > 100)
		{
			RefreshCount = 0;
			if ((chact <= Battery_Level5) && (chact >= SendBatteryStateData))
			{
				chargelevel = chact;
				chact++;
			}
			else
			{
				chact = SendBatteryStateData;
				chargelevel = chact;
			}

			switch (chargelevel)
			{
			case 1:
				lv_obj_add_flag(guider_ui.charge_grate4, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.charge_grate3, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.charge_grate2, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.charge_grate1, LV_OBJ_FLAG_HIDDEN);
				break;
			case 2:
				lv_obj_add_flag(guider_ui.charge_grate4, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.charge_grate3, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.charge_grate2, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(guider_ui.charge_grate1, LV_OBJ_FLAG_HIDDEN);
				break;
			case 3:
				lv_obj_add_flag(guider_ui.charge_grate4, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.charge_grate3, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(guider_ui.charge_grate2, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(guider_ui.charge_grate1, LV_OBJ_FLAG_HIDDEN);
				break;
			case 4:
				lv_obj_add_flag(guider_ui.charge_grate4, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(guider_ui.charge_grate3, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(guider_ui.charge_grate2, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(guider_ui.charge_grate1, LV_OBJ_FLAG_HIDDEN);
				break;
			case 5:
				lv_obj_clear_flag(guider_ui.charge_grate4, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(guider_ui.charge_grate3, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(guider_ui.charge_grate2, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(guider_ui.charge_grate1, LV_OBJ_FLAG_HIDDEN);
				break;
			default:
				break;
			}
		}
	}
}

static void Screen_MainFunc(void)
{
	uint8_t state = ScreenState;
	static uint8_t BeatCount = 0;

	switch (state)
	{
	case IDLE:
		if (ScreenState != ScreenState_old)
		{
			SliderVal = 1200;
			ScreenState_old = ScreenState;
			ScreenTime = 0;

			memcpy(timebuf, "20:00", 5);
			lv_obj_add_flag(guider_ui.main_label_13, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.main_complete, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.main_finish, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.main_wave1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.main_wave2, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.main_wave3, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.main_wave4, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.main_wave5, LV_OBJ_FLAG_HIDDEN);
			lv_arc_set_value(guider_ui.main_arc_1, SliderVal);
			lv_label_set_text(guider_ui.main_time, timebuf);
		}
		else
		{
			BeatCount = 0;
			BeatTime = 0;
			if (ScreenTime >= 1500)
			{
				SliderVal = 1200;
				ScreenTime = 0;

				memcpy(timebuf, "20:00", 5);
				lv_arc_set_value(guider_ui.main_arc_1, SliderVal);
				lv_label_set_text(guider_ui.main_time, timebuf);
			}
		}
		break;

	case WORK:
		ScreenState_old = ScreenState;
		if (ScreenTime > 995)
		{
			SliderVal--;
			if (SliderVal < 0)
			{
				SliderVal = 0;
				ScreenState = STOP;
			}
			get_time_buff();
			lv_arc_set_value(guider_ui.main_arc_1, SliderVal);
			lv_label_set_text(guider_ui.main_time, timebuf);
			ScreenTime = 0;
		}
		if (BeatTime >= 400)
		{
			switch (BeatCount)
			{
			case 1:
				lv_obj_clear_flag(guider_ui.main_wave1, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.main_wave2, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.main_wave3, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.main_wave4, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.main_wave5, LV_OBJ_FLAG_HIDDEN);
				break;
			case 2:
				lv_obj_clear_flag(guider_ui.main_wave1, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(guider_ui.main_wave2, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.main_wave3, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.main_wave4, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.main_wave5, LV_OBJ_FLAG_HIDDEN);
				break;
			case 3:
				lv_obj_clear_flag(guider_ui.main_wave1, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(guider_ui.main_wave2, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(guider_ui.main_wave3, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.main_wave4, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.main_wave5, LV_OBJ_FLAG_HIDDEN);
				break;
			case 4:
				lv_obj_clear_flag(guider_ui.main_wave1, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(guider_ui.main_wave2, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(guider_ui.main_wave3, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(guider_ui.main_wave4, LV_OBJ_FLAG_HIDDEN);
				lv_obj_add_flag(guider_ui.main_wave5, LV_OBJ_FLAG_HIDDEN);
				break;
			case 5:
				lv_obj_clear_flag(guider_ui.main_wave1, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(guider_ui.main_wave2, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(guider_ui.main_wave3, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(guider_ui.main_wave4, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(guider_ui.main_wave5, LV_OBJ_FLAG_HIDDEN);
				break;
			default:
				break;
			}
			if(BeatCount >= 5)
			{
				BeatCount = 0;
			}
			BeatCount++;
			BeatTime = 0;
		}
		break;

	case PAUSE:
		BeatCount = 0;
		ScreenState_old = ScreenState;
	
		lv_obj_add_flag(guider_ui.main_wave1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_wave2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_wave3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_wave4, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_wave5, LV_OBJ_FLAG_HIDDEN);
		break;
	case COMPLETE:
		if (ScreenState != ScreenState_old)
		{
			BeepFlg = 2;
			BeepCount = 12;
			ScreenState_old = ScreenState;
			DevWorkState = IDLE_STATE;
			
			DevFlash_Write(FLASH_BATTERYLEVEL,(uint16_t *)&SendBatteryStateData,1);
			
			lv_obj_add_flag(guider_ui.main_ulock, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.main_suo, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.main_label_13, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.main_complete, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.main_start, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.main_start,LV_OBJ_FLAG_CLICKABLE);
			lv_obj_clear_flag(guider_ui.main_paging,LV_OBJ_FLAG_CLICKABLE);
		}
		break;
	case STOP:
		if (ScreenState != ScreenState_old)
		{
			BeepFlg = 2;
			BeepCount = 12;
			ScreenState_old = ScreenState;
			DevWorkState = IDLE_STATE;

			DevFlash_Write(FLASH_BATTERYLEVEL,(uint16_t *)&SendBatteryStateData,1);
			lv_obj_add_flag(guider_ui.main_ulock, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(guider_ui.main_suo, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.main_label_13, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.main_finish, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.main_start, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.main_start,LV_OBJ_FLAG_CLICKABLE);
			lv_obj_clear_flag(guider_ui.main_paging,LV_OBJ_FLAG_CLICKABLE);
		}
		break;
	case PAGING:
		ScreenState_old = ScreenState;
		break;
	default:
		break;
	}

	if (UnlockFlg == 1 && (UnlockCount > 500))
	{
		lv_obj_clear_flag(guider_ui.main_pause, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_stop, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_start, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_ulock, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_suo, LV_OBJ_FLAG_HIDDEN);
		lv_obj_set_pos(guider_ui.main_suo, 70, 655);
		UnlockFlg = 0;
	}
	else if (UnlockFlg == 2)
	{
		back_pos -= 20;
		if (back_pos < 70)
		{
			back_pos = 70;
			UnlockFlg = 0;
		}
		lv_obj_set_pos(guider_ui.main_suo, (lv_coord_t)back_pos, 655);
	}
}

static void BatteryDisplay_Config(uint8_t boostlevel)
{
	switch (boostlevel)
	{
	case Battery_Level1:
		lv_obj_add_flag(guider_ui.config_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.config_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.config_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.config_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level2:
		lv_obj_clear_flag(guider_ui.config_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.config_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.config_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.config_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level3:
		lv_obj_clear_flag(guider_ui.config_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.config_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.config_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.config_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level4:
		lv_obj_clear_flag(guider_ui.config_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.config_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.config_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.config_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level5:
		lv_obj_clear_flag(guider_ui.config_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.config_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.config_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.config_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	default:
		break;
	}
}

static void BatteryDisplay_Freq(uint8_t boostlevel)
{
	switch (boostlevel)
	{
	case Battery_Level1:
		lv_obj_add_flag(guider_ui.freq_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.freq_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.freq_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.freq_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level2:
		lv_obj_clear_flag(guider_ui.freq_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.freq_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.freq_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.freq_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level3:
		lv_obj_clear_flag(guider_ui.freq_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.freq_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.freq_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.freq_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level4:
		lv_obj_clear_flag(guider_ui.freq_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.freq_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.freq_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.freq_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level5:
		lv_obj_clear_flag(guider_ui.freq_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.freq_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.freq_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.freq_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	default:
		break;
	}
}

static void BatteryDisplay_Light(uint8_t boostlevel)
{
	switch (boostlevel)
	{
	case Battery_Level1:
		lv_obj_add_flag(guider_ui.light_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.light_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.light_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.light_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level2:
		lv_obj_clear_flag(guider_ui.light_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.light_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.light_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.light_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level3:
		lv_obj_clear_flag(guider_ui.light_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.light_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.light_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.light_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level4:
		lv_obj_clear_flag(guider_ui.light_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.light_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.light_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.light_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level5:
		lv_obj_clear_flag(guider_ui.light_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.light_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.light_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.light_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	default:
		break;
	}
}

static void BatteryDisplay_Main(uint8_t boostlevel)
{
	switch (boostlevel)
	{
	case Battery_Level1:
		lv_obj_add_flag(guider_ui.main_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level2:
		lv_obj_clear_flag(guider_ui.main_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level3:
		lv_obj_clear_flag(guider_ui.main_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level4:
		lv_obj_clear_flag(guider_ui.main_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.main_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level5:
		lv_obj_clear_flag(guider_ui.main_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.main_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	default:
		break;
	}
}

static void BatteryDisplay_Param(uint8_t boostlevel)
{
	switch (boostlevel)
	{
	case Battery_Level1:
		lv_obj_add_flag(guider_ui.param_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level2:
		lv_obj_clear_flag(guider_ui.param_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level3:
		lv_obj_clear_flag(guider_ui.param_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level4:
		lv_obj_clear_flag(guider_ui.param_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.param_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level5:
		lv_obj_clear_flag(guider_ui.param_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.param_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	default:
		break;
	}
}
static void BatteryDisplay_Password1(uint8_t boostlevel)
{
	switch (boostlevel)
	{
	case Battery_Level1:
		lv_obj_add_flag(guider_ui.password1_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password1_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password1_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password1_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level2:
		lv_obj_clear_flag(guider_ui.password1_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password1_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password1_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password1_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level3:
		lv_obj_clear_flag(guider_ui.password1_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.password1_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password1_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password1_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level4:
		lv_obj_clear_flag(guider_ui.password1_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.password1_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.password1_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password1_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level5:
		lv_obj_clear_flag(guider_ui.password1_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.password1_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.password1_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.password1_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	default:
		break;
	}
}

static void BatteryDisplay_Password2(uint8_t boostlevel)
{
	switch (boostlevel)
	{
	case Battery_Level1:
		lv_obj_add_flag(guider_ui.password2_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password2_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password2_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password2_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level2:
		lv_obj_clear_flag(guider_ui.password2_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password2_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password2_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password2_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level3:
		lv_obj_clear_flag(guider_ui.password2_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.password2_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password2_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password2_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level4:
		lv_obj_clear_flag(guider_ui.password2_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.password2_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.password2_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.password2_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level5:
		lv_obj_clear_flag(guider_ui.password2_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.password2_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.password2_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.password2_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	default:
		break;
	}
}

static void BatteryDisplay_Vibra(uint8_t boostlevel)
{
	switch (boostlevel)
	{
	case Battery_Level1:
		lv_obj_add_flag(guider_ui.vibra_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibra_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibra_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibra_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level2:
		lv_obj_clear_flag(guider_ui.vibra_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibra_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibra_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibra_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level3:
		lv_obj_clear_flag(guider_ui.vibra_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.vibra_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibra_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibra_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level4:
		lv_obj_clear_flag(guider_ui.vibra_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.vibra_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.vibra_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibra_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level5:
		lv_obj_clear_flag(guider_ui.vibra_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.vibra_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.vibra_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.vibra_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	default:
		break;
	}
}

static void BatteryDisplay_Vibras(uint8_t boostlevel)
{
	switch (boostlevel)
	{
	case Battery_Level1:
		lv_obj_add_flag(guider_ui.vibras_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibras_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibras_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibras_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level2:
		lv_obj_clear_flag(guider_ui.vibras_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibras_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibras_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibras_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level3:
		lv_obj_clear_flag(guider_ui.vibras_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.vibras_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibras_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibras_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level4:
		lv_obj_clear_flag(guider_ui.vibras_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.vibras_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.vibras_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.vibras_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	case Battery_Level5:
		lv_obj_clear_flag(guider_ui.vibras_grate1, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.vibras_grate2, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.vibras_grate3, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.vibras_grate4, LV_OBJ_FLAG_HIDDEN);
		break;
	default:
		break;
	}
}
/*******************************************************************************************************************
 *
 * 									屏幕触发功能
 *
 ******************************************************************************************************************/
void Screen_TriggerFunc(void)
{
	Vibration_Feedback();
	ScreenOfInterest();
}

static void Vibration_Feedback(void)
{
	uint32_t vibra_value = 0;
	if (VibraChangeFlg == 1)
	{
		vibra_value = (uint32_t)MotorLevel * 106;
		DevGpio_SetOutSta(MOTOR_GATE, GPIO_PIN_SET);
		__HAL_TIM_SetCompare(MOTOR_HANDLE, MOTOR_CHB, vibra_value);

		if (VibraFeedBackTime > 2000)
		{
			VibraChangeFlg = 0;
			VibraFeedBackTime = 0;
			DevGpio_SetOutSta(MOTOR_GATE, GPIO_PIN_RESET);
			__HAL_TIM_SetCompare(MOTOR_HANDLE, MOTOR_CHB, 0);
		}
	}
	else
	{
		VibraFeedBackTime = 0;
	}
}

/*工作期间2min无操作息屏*/
static void ScreenOfInterest(void)
{
	static uint8_t DisplayFlg_old = 0;
	if (DisplayTime > 120000)
	{
		DisplayFlg = 0;
	}

	if (DevWorkState == WORK_STATE)
	{
		if ((DisplayFlg == 1) && (DisplayFlg != DisplayFlg_old))
		{
			DisplayFlg_old = DisplayFlg;
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, LightLevel * 10);
		}
		else if ((DisplayFlg == 0) && (DisplayFlg != DisplayFlg_old))
		{
			DisplayFlg_old = DisplayFlg;
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, 10);
		}
	}
	else
	{
		if ((DisplayFlg == 1) && (DisplayFlg != DisplayFlg_old))
		{
			DisplayFlg_old = DisplayFlg;
			__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, LightLevel * 10);
		}
		DisplayTime = 0;
	}
}

