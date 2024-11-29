/*
 * dev_mpc5043.c
 *
 *  Created on: Sep 8, 2024
 *      Author: sunzhentao
 */

#include "dev_app.h"

Battery_Level SendBatteryStateData = Battery_Level5;

static uint8_t ShuntDownFlg = 2;						//充电后关机标志位
static uint8_t RecvMPC5043Flg = 0;   				//接收MPC5043数据标志位
static uint8_t RecvMPC5043Val = 0;					//接收MPC5043数据
static uint8_t BatteryLevelBuff[4] = {0}; 	//电压等级滤波
uint8_t BatteryState = BOOST;

void DevMPC5043_MainFunc(void)
{
	uint8_t battery_level_state = 0;
	static uint8_t	battery_voltage_data = 0xff;

	//判断4次接收到的电量值是否相等，避免采样误差
	if((BatteryLevelBuff[0] == BatteryLevelBuff[1]) &&
	   (BatteryLevelBuff[1] == BatteryLevelBuff[2]) &&
	   (BatteryLevelBuff[2] == BatteryLevelBuff[3]))
	{
			if(((BatteryLevelBuff[0] & 0x80) == 0x80) && ((BatteryLevelBuff[0] & 0x02) == 0))
			{
					BatteryState = BOOST;
			}else if((BatteryLevelBuff[0] & 0x80) == 0)
			{
					if(BatteryLevelBuff[0] & 0x40)
					{
							BatteryState = CHARGE_FINISH;
					}else if(((BatteryLevelBuff[0] & 0x02) != 0) || (BatteryLevelBuff[0] == 0x38))
					{
							BatteryState = CHARGE;
					}
			}
	}
		
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	uint32_t charge_tick;
	static uint32_t charge_tick_old;
	static uint32_t ChargeRecvTime_old = 0;
	static uint8_t RecvCount = 0;
	static uint8_t Count = 0;
	if(GPIO_Pin == CHARGE_STATE_Pin)
	{
		if(RecvMPC5043Flg == 0)
		{
			if(HAL_GPIO_ReadPin(CHARGE_STATE_GPIO_Port, CHARGE_STATE_Pin))
			{
				ChargeRecvTime_old = ChargeRecvTime;
			}else
			{
				if(((ChargeRecvTime - ChargeRecvTime_old) > 38) && ((ChargeRecvTime - ChargeRecvTime_old) <= 41))
				{
					RecvMPC5043Flg = 1;
					ChargeRecvTime_old = ChargeRecvTime;
				}else
				{
					ChargeRecvTime_old = 0;
					ChargeRecvTime = 0;
				}
			}
		}else
		{
			if(HAL_GPIO_ReadPin(CHARGE_STATE_GPIO_Port, CHARGE_STATE_Pin))
			{
				RecvCount++;
				RecvMPC5043Val = RecvMPC5043Val << 1;
				if(((ChargeRecvTime - ChargeRecvTime_old) >= 3) && (ChargeRecvTime - ChargeRecvTime_old) <= 4)
				{
					RecvMPC5043Val = RecvMPC5043Val | 0x01;
				}else
				{
				}
			}else
			{
				ChargeRecvTime_old = ChargeRecvTime;
			}
		}

		if(RecvCount == 7)
		{
			RecvMPC5043Val = RecvMPC5043Val << 1;
			BatteryLevelBuff[Count] = RecvMPC5043Val;

			if(((RecvMPC5043Val & 0x02) && ((RecvMPC5043Val & 0x80) == 0)) ||
			  (((RecvMPC5043Val & 0x80) == 0) && ((RecvMPC5043Val & 0x30) != 0)))
			{
				charge_tick = HAL_GetTick();
				if((charge_tick - charge_tick_old) > 500)
				{
					ShuntDownFlg = 1;
					charge_tick_old = charge_tick;
				}else
				{
					
				}
			}else
			{
				 if(ShuntDownFlg == 1)
					{
						BatteryLevelBuff[0] = RecvMPC5043Val;
						BatteryLevelBuff[1] = RecvMPC5043Val;
						BatteryLevelBuff[2] = RecvMPC5043Val;
						BatteryLevelBuff[3] = RecvMPC5043Val;
					}else
					{
					}
					charge_tick = HAL_GetTick();
					charge_tick_old = charge_tick;
			}
			Count++;
			if(Count > 3)
			{
				Count = 0;
			}
			RecvCount = 0;
			ChargeRecvTime = 0;
			ChargeRecvTime_old = 0;
			RecvMPC5043Flg = 0;
		}
	}
}
