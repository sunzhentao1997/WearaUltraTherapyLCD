#ifndef __LV_MAINSTART_H
#define __LV_MAINSTART_H

#include "stdint.h"

typedef enum
{
	IDLE,
	WORK,
	PAUSE,
	COMPLETE,
	STOP,
	PAGING,
}SCREENSTATE;

typedef enum
{
	BOOST_SCREEN,
	MAIN_SCREEN,
	CONFIG_SCREEN,
	PARAM_SCREEN,
	LIGHT_SCREEN,
	FREQ_SCREEN,
	VIBRA_SCREEN,
	VIBRAS_SCREEN,
	CHAREG_SCREEN,
	PASSWORD1_SCREEN,
	PASSWORD2_SCREEN,
	ScreenId_Max,
}SCREENID;

typedef union
{
	uint16_t DevTempBuff[15];
	struct 
	{
		uint8_t DeviceIdBuff[10];
		uint8_t PowerBuff[10];
		uint8_t TemperatureBuff[10];
	}DevParam;
}DEVICESPARAM;

extern uint8_t UltraDuty;
extern uint8_t SlaveFlg;
extern uint16_t FreqOffset;
extern uint16_t LightLevel;
extern uint16_t MotorLevel;
extern SCREENID Screen_Id;
extern SCREENSTATE ScreenState;
extern DEVICESPARAM DevicesParam;
extern uint8_t ClickCount;
extern uint16_t slider_pos;
extern uint32_t UnlockCount;
extern uint8_t UnlockFlg;
extern uint8_t VibraChangeFlg;	
extern uint32_t VibraFeedBackTime;
extern uint32_t DisplayTime;
extern uint8_t DisplayFlg;
extern uint16_t back_pos;
extern uint8_t ParamLockFlg;
extern uint8_t VibraEnableFlg;
extern uint8_t VibraEnableFlg_old;
extern uint16_t LightLevel_old;
extern uint16_t MotorLevelTemp;

void lv_mainstart(void);
void ScreenFunc(void);
void Screen_TriggerFunc(void);
typedef void (*BATTERYDISPLAY_FUNC)(uint8_t boostlevel);
extern const BATTERYDISPLAY_FUNC battery_display_func[ScreenId_Max];

#endif
