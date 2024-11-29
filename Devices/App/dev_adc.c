/*
 * dev_adc.c
 *
 *  Created on: Sep 8, 2024
 *      Author: sunzhentao
 */

#include "dev_app.h"
#include "usart.h"

extern ADC_HandleTypeDef hadc1;

uint16_t BatteryVol = 3500;
float battery_percent_output = 100;
static uint32_t AdcVal = 0;
static uint16_t BatVolFilter[15] = {0};

static uint16_t AdcSampleFilt(uint16_t *buff, uint8_t len);

const uint8_t BatteryBuff[21] =
{
		Battery_Level1,
		Battery_Level1,
		Battery_Level1,
		Battery_Level1,
		Battery_Level1,
		Battery_Level2,
		Battery_Level2,
		Battery_Level2,
		Battery_Level2,
		Battery_Level3,
		Battery_Level3,
		Battery_Level3,
		Battery_Level3,
		Battery_Level4,
		Battery_Level4,
		Battery_Level4,
		Battery_Level4,
		Battery_Level5,
		Battery_Level5,
		Battery_Level5,
		Battery_Level5,
};

const float battery_voltage_idle[21] = {
	3.000, // 0%
	3.501, // 5%
	3.584, // 10%
	3.618, // 15%
	3.653, // 20%
	3.679, // 25%
	3.695, // 30%
	3.707, // 35%
	3.719, // 40%
	3.735, // 45%
	3.752, // 50%
	3.773, // 55%
	3.803, // 60%
	3.834, // 65%
	3.868, // 70%
	3.903, // 75%
	3.942, // 80%
	3.989, // 85%
	4.031, // 90%
	4.082, // 95%
	4.198, // 100%
};

const float battery_voltage_work[21] = {
	3.000, // 0%
	3.501, // 5%
	3.584, // 10%
	3.618, // 15%
	3.653, // 20%
	3.679, // 25%
	3.695, // 30%
	3.707, // 35%
	3.719, // 40%
	3.735, // 45%
	3.752, // 50%
	3.773, // 55%
	3.803, // 60%
	3.834, // 65%
	3.868, // 70%
	3.903, // 75%
	3.942, // 80%
	3.989, // 85%
	4.031, // 90%
	4.082, // 95%
	4.198, // 100%
};

const float battery_voltage_charge[21] = {
	3.200, // 0%
	3.701, // 5%
	3.784, // 10%
	3.818, // 15%
	3.853, // 20%
	3.879, // 25%
	3.895, // 30%
	3.907, // 35%
	3.919, // 40%
	3.935, // 45%
	3.952, // 50%
	3.973, // 55%
	4.003, // 60%
	4.034, // 65%
	4.068, // 70%
	3.103, // 75%
	3.142, // 80%
	3.189, // 85%
	4.231, // 90%
	4.282, // 95%
	4.398, // 100%
};

void DevAdc_Init(void)
{
	HAL_ADC_Start_DMA(&hadc1, &AdcVal, 1);
}

void DevAdc_MainFunc(void)
{
	static uint8_t AdcInitFlg = 0;
	static uint8_t SampleCount = 0;
	float battery_voltage_input = 4.2;

	uint8_t tag_i = 0;
	float BatVolTemp = 0.0f;

	HAL_ADC_Start_DMA(&hadc1, &AdcVal, 1);

	BatVolTemp = (float)AdcVal * 3300.0f / 4096.0f;
	BatVolTemp = BatVolTemp / 0.9936;
	BatVolTemp = BatVolTemp / 0.66385;

	if (AdcInitFlg == 0)
	{
		for (tag_i = 0; tag_i < 15; tag_i++)
		{
			BatVolFilter[tag_i] = (uint16_t)BatVolTemp;
		}
		AdcInitFlg = 1;
	}
	else
	{
		BatVolFilter[SampleCount++] = (uint16_t)BatVolTemp;
		if (SampleCount > 14)
		{
			SampleCount = 0;
		}
	}

	BatteryVol = AdcSampleFilt(BatVolFilter, 15);
}

static uint16_t AdcSampleFilt(uint16_t *buff, uint8_t len)
{
	uint8_t tag_i = 0;
	uint16_t max_val = 0;
	uint16_t min_val = 0;
	uint32_t sum = 0;
	float average = 0.0;

	if (len < 3)
	{
		return 0.0;
	}

	// 找到最大值和最小值
	max_val = buff[0];
	min_val = buff[0];
	for (tag_i = 1; tag_i < len; tag_i++)
	{
		if (buff[tag_i] > max_val)
		{
			max_val = buff[tag_i];
		}
		if (buff[tag_i] < min_val)
		{
			min_val = buff[tag_i];
		}
	}

	// 去掉最大值和最小值，计算剩余元素的和
	for (tag_i = 0; tag_i < len; tag_i++)
	{
		sum += buff[tag_i];
	}

	// 计算平均值
	average = (float)(sum - max_val - max_val) / (len - 2);
	return (uint16_t)average;
}

void BatteryLevelGet(void)
{
	uint8_t tag_i = 0;
	float battery_val = 0;
	static uint8_t expre = 0;
	static uint8_t BatterySaveFlg = 0;
	static uint8_t BatLevel = 0;
	static uint8_t BatChaLevel = Battery_Level1;
	static uint8_t BatDisLevel = Battery_Level5;
	
	if((expre == CHARGE_STATE) && (DevWorkState == CLOSE_STATE) && (BatterySaveFlg == 1))
	{
			DevFlash_Write(FLASH_BATTERYLEVEL,(uint16_t *)&SendBatteryStateData,1);
	}
	
	if((DevWorkState != WORK_STATE) && (DevWorkState != CHARGE_STATE))
	{
			expre = IDLE_STATE;
	}else
	{
			expre = DevWorkState;
	}
	
	battery_val = (float)BatteryVol / 1000;
		
	switch (expre)
	{
	case IDLE_STATE:
		if (battery_val < battery_voltage_idle[0])
		{
			BatLevel = BatteryBuff[0];
		}
		else if (battery_val > battery_voltage_idle[20])
		{
			BatLevel = BatteryBuff[20];
		}
		else
		{
			for (tag_i = 0; tag_i < 20; tag_i++)
			{
				if ((battery_val >= battery_voltage_idle[tag_i]) && (battery_val < battery_voltage_idle[tag_i + 1]))
				{
					BatLevel = BatteryBuff[tag_i];
					break;
				}
			}
		}
		
		if(BatLevel < SendBatteryStateData)
		{
				SendBatteryStateData = BatLevel;
		}else
		{
				
		}
		break;

	case WORK_STATE:
		if (battery_val < battery_voltage_work[0])
		{
			BatLevel = BatteryBuff[0];
		}
		else if (battery_val > battery_voltage_idle[20])
		{
			BatLevel = BatteryBuff[20];
		}
		else
		{
			for (tag_i = 0; tag_i < 20; tag_i++)
			{
				if ((battery_val >= battery_voltage_work[tag_i]) && (battery_val < battery_voltage_work[tag_i + 1]))
				{
					BatLevel = BatteryBuff[tag_i];
					break;
				}
			}
		}
		
		if(BatLevel < SendBatteryStateData)
		{
			SendBatteryStateData = BatLevel;
		}else
		{

		}
		break;
	case CHARGE_STATE:
		if(BatLevel >= BatChaLevel)
		{
				BatChaLevel = BatLevel;
				SendBatteryStateData = BatLevel;
				BatterySaveFlg = 1;
		}
		
		if (battery_val < battery_voltage_charge[0])
		{
			BatLevel = BatteryBuff[0];
		}
		else if (battery_val > battery_voltage_charge[20])
		{
			BatLevel = BatteryBuff[20];
		}
		else
		{
			for (tag_i = 0; tag_i < 20; tag_i++)
			{
				if ((battery_val >= battery_voltage_charge[tag_i]) && (battery_val < battery_voltage_charge[tag_i + 1]))
				{
					BatLevel = BatteryBuff[tag_i+1];
					break;
				}
			}
		}
		break;

	default:
		break;
	}
}
