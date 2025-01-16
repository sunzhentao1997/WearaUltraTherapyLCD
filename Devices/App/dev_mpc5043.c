/*
 * dev_mpc5043.c
 *
 *  Created on: Sep 8, 2024
 *      Author: sunzhentao
 */

#include "dev_app.h"

Battery_Level SendBatteryStateData = Battery_Level5;
Battery_Level BatLevel_old = Battery_Level5;

static uint8_t ShuntDownFlg = 2;		  // 充电后关机标志位
static uint8_t RecvMPC5043Flg = 0;		  // 接收MPC5043数据标志位
static uint8_t RecvMPC5043Val = 0;		  // 接收MPC5043数据
static uint8_t BatteryLevelBuff[4] = {0}; // 电压等级滤波
uint8_t BatteryState = BOOST;
uint8_t ChargeLevel = 0;

static uint8_t BoostBatBuff[16] = 
{
	0x80,0x84,0x88,0x8C,0x90,0x94,0x98,0x9C,0xA0,0xA4,0xA8,0xAC,0xB0,0xB4,0xB8,0xBC
};

static uint8_t ChargeBatBuff[17] = 
{
	0x02,0x06,0x0A,0x0E,0x12,0x16,0x1A,0x1E,0x22,0x26,0x2A,0x2E,0x32,0x36,0x38,0x3A,0x7C,
};
static uint8_t BoostBatLevel[16] = 
{
		Battery_Level1,
		Battery_Level1,
		Battery_Level1,
		Battery_Level1,
		Battery_Level1,
		Battery_Level1,
		Battery_Level2,
		Battery_Level2,
		Battery_Level3,
		Battery_Level3,
		Battery_Level4,
		Battery_Level4,
		Battery_Level4,
		Battery_Level5,
		Battery_Level5,
		Battery_Level5,
};

static uint8_t BoostBatLevel_work[16] = 
{
		Battery_Level1,
		Battery_Level1,
		Battery_Level1,
		Battery_Level1,
		Battery_Level1,
		Battery_Level2,
		Battery_Level2,
		Battery_Level3,
		Battery_Level3,
		Battery_Level4,
		Battery_Level4,
		Battery_Level4,
		Battery_Level5,
		Battery_Level5,
		Battery_Level5,
		Battery_Level5,
};

static uint8_t ChargeBatLevel[17] = 
{
		Battery_Level1,
		Battery_Level1,
		Battery_Level1,
		Battery_Level1,
		Battery_Level1,
		Battery_Level1,
		Battery_Level2,
		Battery_Level2,
		Battery_Level2,
		Battery_Level3,
		Battery_Level3,
		Battery_Level3,
		Battery_Level4,
		Battery_Level4,
		Battery_Level4,
		Battery_Level4,
		Battery_Level5,
};

static void BatteryLevelGet(void);

/*
 * @函数名称：DevMPC5043_MianFunc
 * @函数功能：MPC5043数据处理函数
 * @输入参数：无	
 * @返回参数：无
 */
void DevMPC5043_MainFunc(void)
{
	// 判断4次接收到的电量值是否相等，避免采样误差
	if ((BatteryLevelBuff[0] != BatteryLevelBuff[1]) ||
			(BatteryLevelBuff[1] != BatteryLevelBuff[2]) ||
			(BatteryLevelBuff[2] != BatteryLevelBuff[3]))
	{
		return ;
	}else
	{
		BatteryLevelGet();
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	uint32_t charge_tick;
	static uint32_t charge_tick_old;
	static uint32_t ChargeRecvTime_old = 0;
	static uint8_t RecvCount = 0;
	static uint8_t Count = 0;
	if (GPIO_Pin == CHARGE_STATE_Pin)
	{
		if (RecvMPC5043Flg == 0)
		{
			if (HAL_GPIO_ReadPin(CHARGE_STATE_GPIO_Port, CHARGE_STATE_Pin))
			{
				ChargeRecvTime_old = ChargeRecvTime;
			}
			else
			{
				if (((ChargeRecvTime - ChargeRecvTime_old) > 38) && ((ChargeRecvTime - ChargeRecvTime_old) <= 41))
				{
					RecvMPC5043Flg = 1;
					ChargeRecvTime_old = ChargeRecvTime;
				}
				else
				{
					ChargeRecvTime_old = 0;
					ChargeRecvTime = 0;
				}
			}
		}
		else
		{
			if (HAL_GPIO_ReadPin(CHARGE_STATE_GPIO_Port, CHARGE_STATE_Pin))
			{
				RecvCount++;
				RecvMPC5043Val = RecvMPC5043Val << 1;
				if (((ChargeRecvTime - ChargeRecvTime_old) >= 3) && (ChargeRecvTime - ChargeRecvTime_old) <= 4)
				{
					RecvMPC5043Val = RecvMPC5043Val | 0x01;
				}
				else
				{
				}
			}
			else
			{
				ChargeRecvTime_old = ChargeRecvTime;
			}
		}

		if (RecvCount == 7)
		{
			RecvMPC5043Val = RecvMPC5043Val << 1;
			BatteryLevelBuff[Count] = RecvMPC5043Val;

			if (((RecvMPC5043Val & 0x02) && ((RecvMPC5043Val & 0x80) == 0)) ||
				(((RecvMPC5043Val & 0x80) == 0) && ((RecvMPC5043Val & 0x30) != 0)))
			{
				charge_tick = HAL_GetTick();
				if ((charge_tick - charge_tick_old) > 500)
				{
					ShuntDownFlg = 1;
					charge_tick_old = charge_tick;
				}
				else
				{
				}
			}
			else
			{
				if (ShuntDownFlg == 1)
				{
					BatteryLevelBuff[0] = RecvMPC5043Val;
					BatteryLevelBuff[1] = RecvMPC5043Val;
					BatteryLevelBuff[2] = RecvMPC5043Val;
					BatteryLevelBuff[3] = RecvMPC5043Val;
				}
				else
				{
				}
				charge_tick = HAL_GetTick();
				charge_tick_old = charge_tick;
			}
			Count++;
			if (Count > 3)
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

static void BatteryLevelGet(void)
{
		uint32_t new_tick = 0;
		uint8_t battery_level_state = 0;
		uint8_t tag_i = 0;
		static uint8_t BatteryState_old = BOOST;
		static uint8_t DevSta_old = IDLE_STATE;
		static uint8_t SaveBatteryFlg = 0;
		static uint8_t battery_voltage_data = 0xff;
		static uint8_t RefreshFlg = 0;
		static uint32_t old_tick = 0;
	
		if(BatteryLevelBuff[0] & 0x80)
		{
			for(tag_i = 0;tag_i < 16;tag_i++)
			{
					if(BatteryLevelBuff[0] == BoostBatBuff[tag_i])
					{
							if(DevWorkState == WORK_STATE)
							{
									SendBatteryStateData = BoostBatLevel_work[tag_i];
							}else
							{
									SendBatteryStateData = BoostBatLevel[tag_i];
							}
												
							if(SendBatteryStateData >= BatLevel_old)
							{
									SendBatteryStateData = BatLevel_old;
							}else
							{
									BatLevel_old = SendBatteryStateData;
							}
							BatteryState = BOOST;
							break;
					}
			}
		}else
		{
			for(tag_i = 0;tag_i < 17;tag_i++)
			{
				if(BatteryLevelBuff[0] == ChargeBatBuff[tag_i])
				{
					SendBatteryStateData = ChargeBatLevel[tag_i];
					ChargeLevel = SendBatteryStateData;
					BatteryState = CHARGE;
					
					if((RefreshFlg == 0) && ((Charge_Time > 120000) || (SendBatteryStateData > BatLevel_old)))
					{
						EraseFlash(FLASH_BATTERYLEVEL,1);
						RefreshFlg = 1;
					}
					BatLevel_old = SendBatteryStateData;
					break;
				}
			}
		}
		
		if((DevSta_old == WORK_STATE) && (DevWorkState != WORK_STATE))
			{
					SaveBatteryFlg = 1;
			}
			
			if((BatteryState_old != BatteryState) && (BatteryState == BOOST))
			{
					BatLevel_old = Battery_Level5;
			}
			
			new_tick = HAL_GetTick();
			if(SaveBatteryFlg == 1)
			{
					if((new_tick - old_tick) > 1000)
					{
							old_tick = new_tick;
							if(DevFlash_Write(FLASH_BATTERYLEVEL, (uint16_t *)&SendBatteryStateData, 1) == HAL_OK)
							{
								 SaveBatteryFlg = 0;
							}
					}
			}else
			{
					old_tick = new_tick;
			}
			DevSta_old = DevWorkState;
			BatteryState_old = BatteryState;
}
