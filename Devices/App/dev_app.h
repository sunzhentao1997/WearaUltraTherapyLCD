#ifndef __DEV_APP_H
#define __DEV_APP_H

#include "dev_ad9833.h"
#include "dev_adc.h"
#include "dev_beep.h"
#include "dev_flash.h"
#include "dev_mpc5043.h"
#include "dev_control.h"
#include "dev_gpio.h"

extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim9;
extern TIM_HandleTypeDef htim12;

#define ULTRA_HANDLE	(&htim2)
#define ULTRA_CHB			TIM_CHANNEL_1

#define MOTOR_HANDLE 	(&htim12)
#define MOTOR_CHB			TIM_CHANNEL_1

#define BEEP_HANDLE			(&htim9)
#define BEEP_CHANNLE		TIM_CHANNEL_2

#define LCDBL_HANDLE		(&htim5)
#define LCDBL_CHANNLE		TIM_CHANNEL_3

#define BEEP_ON()					__HAL_TIM_SetCompare(BEEP_HANDLE,BEEP_CHANNLE,180)
#define BEEP_OFF()				__HAL_TIM_SetCompare(BEEP_HANDLE,BEEP_CHANNLE,0)

#define FLASH_SHUNTDOWN			0x81A0000
#define FLASH_BATTERYLEVEL	0x81C0000
#define FLASH_SAVE_ADDR 		0x81E0000

/*main*/
extern uint32_t ScreenTime;										//屏幕主界面数据刷新时间
extern uint32_t StandyTime;										//待机时间
extern uint32_t ChargeRecvTime;								//充电接收时间
extern uint32_t BatteryTime;									//主界面电量刷新时间
extern uint32_t BackLedTime;			  					//背光开�?时间
extern uint32_t PowerOnTime;									//正式开机时�?
extern uint32_t Charge_Time;									//充电时长
extern uint8_t CompleteFlg;										//开机成功标志位
extern uint32_t ChargeRecvTime;
extern uint32_t ShuntDownCount;
extern uint32_t MotorTime;
extern uint32_t BeatTime;
extern uint32_t HintTime;
extern uint8_t LongPressFlg;
extern uint32_t LongPressTime;
/*adc*/
extern uint16_t BatteryVol;										//adc电压采样
extern uint32_t UltraWorkTim;									//超声工作时间

/*beep*/
extern int8_t BeepCount;											//蜂鸣器启动�?�数
extern uint8_t BeepFlg;												//蜂鸣器启动标�?

/*control*/					
extern Dev_Work_State DevWorkState;						//设�?�工作状�?

/*mpc5043*/
extern Battery_Level SendBatteryStateData;	 //电池电量数据
extern uint8_t BatteryState;

/*LCD*/
extern uint16_t slider_pos;

#endif
