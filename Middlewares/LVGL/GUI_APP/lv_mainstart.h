#ifndef __LV_MAINSTART_H
#define __LV_MAINSTART_H

#include "stdint.h"

typedef enum
{
	READY,
	STOP,
	WORK,
	OTHER,
}SCREENSTATE;

typedef enum
{
	MAIN_SCREEN,
	CONFIG_SCREEN,
	PARAM_SCREEN,
	LIGHT_SCREEN,
	FREQ_SCREEN,
	VIBRA_SCREEN,
	CHAREG_SCREEN,
	LOWBATTERY_SCREEN,
}SCREENID;

typedef union
{
	uint16_t DevTempBuff[9];
	struct 
	{
		uint8_t DeviceIdBuff[6];
		uint8_t PowerBuff[6];
		uint8_t TemperatureBuff[6];
	}DevParam;
}DEVICESPARAM;

extern uint8_t UltraDuty;
extern uint8_t SlaveFlg;
extern uint16_t FreqOffset;
extern uint16_t LightLevel;
extern uint32_t MotorLevel;
extern SCREENID Screen_Id;
extern SCREENSTATE ScreenState;
extern DEVICESPARAM DevicesParam;
extern uint8_t ClickCount;
extern uint16_t slider_pos;
extern uint32_t UnlockCount;
extern uint8_t UnlockFlg;


void lv_mainstart(void);
void ScreenFunc(void);

#endif
