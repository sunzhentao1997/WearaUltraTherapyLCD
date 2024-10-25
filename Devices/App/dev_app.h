#ifndef __DEV_APP_H
#define __DEV_APP_H

#include "dev_ad9833.h"
#include "dev_adc.h"
#include "dev_beep.h"
#include "dev_flash.h"
#include "dev_mpc5043.h"
#include "dev_control.h"
#include "dev_gpio.h"

extern uint16_t BatteryVol;						//ADC 电压采样
extern uint8_t CompleteFlg;
extern uint16_t Low_Battery_Flg;
extern uint8_t ShuntDownFlg;					//关机标志位
extern uint8_t StartFlg;							//启动标志位
extern uint8_t RecvMPC5043Val;				
extern uint8_t BatteryLevelBuff[4];
extern uint32_t ChargeRecvTime;
extern Battery_Level SendBatteryStateData;
extern Dev_Work_State DevWorkState;
extern int8_t BeepCount;
extern uint8_t BeepFlg;

#endif
