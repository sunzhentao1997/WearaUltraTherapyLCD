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
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim9;

#define ULTRA_HANDLE	(&htim3)

#define ULTRA_CHB			TIM_CHANNEL_1
#define ULTRA_CHA			TIM_CHANNEL_2

#define MOTOR_HANDLE 	(&htim5)

#define MOTOR_CHB			TIM_CHANNEL_2
#define MOTOR_CHA			TIM_CHANNEL_3

#define BEEP_HANDLE			(&htim9)

#define BEEP_CHANNLE		TIM_CHANNEL_2

#define BEEP_ON()					__HAL_TIM_SetCompare(BEEP_HANDLE,BEEP_CHANNLE,180)
#define BEEP_OFF()				__HAL_TIM_SetCompare(BEEP_HANDLE,BEEP_CHANNLE,0)

#define FLASH_LOWBATTERY	  0x81C0000
#define FLASH_SAVE_ADDR 		0x81E0000

/*main*/
extern uint32_t ScreenTime;										//屏幕主界面数据刷新时间
extern uint32_t StandyTime;										//待机时间
extern uint32_t ChargeRecvTime;								//充电接收时间
extern uint32_t BatteryTime;									//主界面电量刷新时间
extern uint32_t BackLedTime;			  					//背光开启时间
extern uint32_t PowerOnTime;									//正式开机时间
extern uint32_t Charge_Time;									//充电时长
extern uint8_t CompleteFlg;										//开机成功标志位
extern uint32_t ChargeRecvTime;

/*adc*/
extern uint16_t BatteryVol;										//adc电压采样

/*beep*/
extern int8_t BeepCount;											//蜂鸣器启动次数
extern uint8_t BeepFlg;												//蜂鸣器启动标志

/*control*/
extern uint16_t Low_Battery_Flg;							//低电量标志位						
extern Dev_Work_State DevWorkState;						//设备工作状态

/*mpc5043*/
extern Battery_Level SendBatteryStateData;	 //电池电量数据

#endif
