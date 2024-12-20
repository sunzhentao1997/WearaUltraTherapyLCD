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
static uint8_t BatLevel = 0;
static uint8_t BatLevel_old = 0;
static uint16_t DevAdc_SampleFilt(uint16_t *buff, uint8_t len);

const uint8_t BatLevelBuff[21] =
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
	3.301, // 5%
	3.384, // 10%
	3.418, // 15%
	3.453, // 20%
	3.479, // 25%
	3.495, // 30%
	3.507, // 35%
	3.519, // 40%
	3.535, // 45%
	3.552, // 50%
	3.573, // 55%
	3.603, // 60%
	3.634, // 65%
	3.668, // 70%
	3.703, // 75%
	3.742, // 80%
	3.789, // 85%
	3.831, // 90%
	3.882, // 95%
	3.998, // 100%
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
	4.103, // 75%
	4.142, // 80%
	4.189, // 85%
	4.231, // 90%
	4.282, // 95%
	4.398, // 100%
};

void DevAdc_Init(void)
{
	float BatVolTemp = 0.0f;
	uint8_t tag_i = 0;

	for (tag_i = 0; tag_i < 15; tag_i++)
	{
		HAL_ADC_Start_DMA(&hadc1, &AdcVal, 1);
	
		BatVolTemp = (float)AdcVal * 3300.0f / 4096.0f;
		BatVolTemp = BatVolTemp / 0.9936;
		BatVolTemp = BatVolTemp / 0.66385;
		BatVolFilter[tag_i] = (uint16_t)BatVolTemp;
	}
	BatteryVol = DevAdc_SampleFilt(BatVolFilter, 15);
}

/*
 * 函数名：DevAdc_MainFunc
 * 功能：ADC采样主函数
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：无
 */
void DevAdc_MainFunc(void)
{
    static uint8_t SampleCount = 0;
    float BatVolTemp = 0.0f;
    
    // 启动ADC并使用DMA传输数据
    HAL_StatusTypeDef adcStatus = HAL_ADC_Start_DMA(&hadc1, &AdcVal, 1);
    if (adcStatus != HAL_OK) 
    {
        // 处理启动ADC失败的情况
        return;
    }

    // 计算ADC值对应的电压值
    BatVolTemp = (float)AdcVal * 3300.0f / 4096.0f;
    BatVolTemp = (BatVolTemp / 0.66666f);
    
    // 将转换后的电压值存储到滤波数组中，并更新采样计数
    BatVolFilter[SampleCount] = (uint16_t)BatVolTemp;
    SampleCount = (SampleCount + 1) % 15; 

    // 对滤波后的电压值进行采样滤波，并更新电池电压值
    BatteryVol = DevAdc_SampleFilt(BatVolFilter, 15);
}

/*
 * 函数名：AdcSampleFilt
 * 功能：对ADC采样值进行滤波
 * 输入参数：buff：滤波数组；len：滤波数组长度
 * 输出参数：无
 * 返 回 值：滤波后的电压值
 */
static uint16_t DevAdc_SampleFilt(uint16_t *buff, uint8_t len)
{
	uint8_t tag_i = 0;
	uint16_t max_val = 0;
	uint16_t min_val = 0;
	uint32_t sum = 0;
	float average = 0.0;

	if (len < 3)
	{
		return 0;
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

/*
 * 函数名：BatteryLevelInit
 * 功能：初始化电池等级
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：无
 */
void BatteryLevelInit(void)
{
	uint8_t bat_sta = BatteryState; // 直接赋值
	uint8_t tag_i = 0;

	if (bat_sta == BOOST)
	{
		if (BatteryVol <= battery_voltage_idle[0])
		{
			BatLevel = Battery_Level1;
		}
		else if (BatteryVol >= battery_voltage_idle[20])
		{
			BatLevel = Battery_Level5;
		}
		else
		{
			for (tag_i = 0; tag_i < 20; tag_i++) // 优化循环条件，避免越界
			{
				if (BatteryVol > battery_voltage_idle[tag_i] && BatteryVol <= battery_voltage_idle[tag_i + 1])
				{
					BatLevel = BatLevelBuff[tag_i];
					break; // 找到后跳出循环
				}
			}
		}
	}
	else if (bat_sta == CHARGE)
	{
		if (BatteryVol <= battery_voltage_charge[0])
		{
			BatLevel = Battery_Level1;
		}
		else if (BatteryVol >= battery_voltage_charge[20])
		{
			BatLevel = Battery_Level4;
		}
		else
		{
			for (tag_i = 0; tag_i < 20; tag_i++)
			{
				if (BatteryVol > battery_voltage_charge[tag_i] && BatteryVol <= battery_voltage_charge[tag_i + 1])
				{
					BatLevel = BatLevelBuff[tag_i];
					if (BatLevel > Battery_Level4)
					{
						BatLevel = Battery_Level4; // 确保电池等级不超过4
					}
					break; // 找到后跳出循环
				}
			}
		}
	}
	else if (bat_sta == CHARGE_FINISH)
	{
		BatLevel = Battery_Level5;
	}
	else
	{
		// 处理未知状态，记录错误或采取默认措施
		return; // 提前返回
	}

	// 更新电池等级和发送状态
	if (SendBatteryStateData > BatLevel)
	{
		SendBatteryStateData = BatLevel;
	}
	else
	{
		BatLevel = SendBatteryStateData; // 确保同步
	}

	BatLevel_old = BatLevel; // 统一更新
}

void BatteryLevelGet(void)
{
		uint8_t bat_sta = 0;
		uint8_t tag_i = 0;
		uint32_t new_tick;
		static uint32_t old_tick;
		static uint8_t SaveBatteryFlg = 0;
  	float batval = 0.0f; 
		static uint8_t DevSta_old = IDLE_STATE;
		static uint8_t RefreshFlg = 0;
	
		bat_sta = BatteryState;
		batval = (float)BatteryVol / 1000.0f;
		switch(bat_sta)
		{
			case BOOST:
				RefreshFlg = 0;
			
				if(DevWorkState != WORK_STATE)
				{
					if(batval <= battery_voltage_idle[0])
					{
							BatLevel = Battery_Level1;
					}else if(batval >= battery_voltage_idle[20])
					{
							BatLevel = Battery_Level5;
					}else
					{
							for(tag_i = 0;tag_i < 21;tag_i++)
							{
									if((batval > battery_voltage_idle[tag_i]) && (batval <= battery_voltage_idle[tag_i+1]))
									{
											BatLevel = BatLevelBuff[tag_i];
									}
							}
					}
				}else
				{
					if(batval <= battery_voltage_work[0])
					{
							BatLevel = Battery_Level1;
					}else if(batval >= battery_voltage_work[20])
					{
							BatLevel = Battery_Level5;
					}else
					{
							for(tag_i = 0;tag_i < 21;tag_i++)
							{
									if((batval > battery_voltage_work[tag_i]) && (batval <= battery_voltage_work[tag_i+1]))
									{
											batval = BatLevelBuff[tag_i];
									}
							}
					}	
				}
				
				if(BatLevel < BatLevel_old)
				{
						BatLevel_old = BatLevel;
						SendBatteryStateData = BatLevel_old;
				}else
				{
						SendBatteryStateData = BatLevel_old;
				}
			break;
			
			case CHARGE:
				if(batval <= battery_voltage_charge[0])
					{
							BatLevel = Battery_Level1;
					}else if(batval >= battery_voltage_charge[20])
					{
							BatLevel = Battery_Level5;
					}else
					{
							for(tag_i = 0;tag_i < 21;tag_i++)
							{
									if((batval > battery_voltage_charge[tag_i]) && (batval <= battery_voltage_charge[tag_i+1]))
									{
											BatLevel = BatLevelBuff[tag_i];
									}
							}
					}
					
					if(BatLevel == Battery_Level5)
					{
						BatLevel = Battery_Level4;
					}
					
					if(BatLevel > BatLevel_old)
					{
							BatLevel_old = BatLevel;
							SendBatteryStateData = BatLevel_old;
							if(RefreshFlg == 0)
							{
								EraseFlash(FLASH_BATTERYLEVEL);
								RefreshFlg = 1;
							}
					}else
					{
							SendBatteryStateData = BatLevel_old;
					}
			break;
			
			case CHARGE_FINISH:
				BatLevel = Battery_Level5;
				BatLevel_old = BatLevel;
				SendBatteryStateData = BatLevel_old;
				break;
			default:
				break;
		}
		
		if((DevSta_old == WORK_STATE) && (DevWorkState != WORK_STATE))
		{
			  SaveBatteryFlg = 1;
		}else if((DevSta_old == CHARGE_STATE) && (DevWorkState != CHARGE_STATE))
		{
				SaveBatteryFlg = 1;
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
}
