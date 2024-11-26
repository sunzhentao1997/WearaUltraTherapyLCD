/*
 * dev_adc.c
 *
 *  Created on: Sep 8, 2024
 *      Author: sunzhentao
 */

#include "dev_app.h"

extern ADC_HandleTypeDef hadc1;

uint16_t BatteryVol = 3500;
float battery_percent_output = 100;
static uint32_t AdcVal = 0;
static uint16_t BatVolFilter[15] = {0};

static uint16_t AdcSampleFilt(uint16_t *buff,uint8_t len);
static float look1_iflf_binlxpw(float u0, const float bp0[], const float table[], uint32_t maxIndex);
static void ElectricityDetectionAlgorithm(void);

const uint8_t BatteryBuff[21] = 
{
	Boost_Level1,
	Boost_Level1,
	Boost_Level1,
	Boost_Level1,
	Boost_Level1,
	Boost_Level2,
	Boost_Level2,
	Boost_Level2,
	Boost_Level2,
	Boost_Level3,
	Boost_Level3,
	Boost_Level3,
	Boost_Level3,
	Boost_Level4,
	Boost_Level4,
	Boost_Level4,
	Boost_Level4,
	Boost_Level5,
	Boost_Level5,
	Boost_Level5,
	Boost_Level5,
};

const float battery_voltage[21] = {
	3.000,											//0%
	3.501,											//5%
	3.584,											//10%
	3.618,											//15%
	3.653,											//20%
	3.679,											//25%
	3.695,											//30%
	3.707,											//35%
	3.719,											//40%
	3.735,											//45%
	3.752,											//50%
	3.773,											//55%
	3.803,											//60%
	3.834,											//65%
	3.868,											//70%
	3.903,											//75%
	3.942,											//80%
	3.989,											//85%		
	4.031,											//90%
	4.082,											//95%
	4.198,											//100%
};	

const float battery_percent[21] = {
	0 ,
	5 ,
	10 ,
	15 ,
	20 ,
	25 ,
	30 ,
	35 ,
	40 ,
	45 ,
	50 ,
	55 ,
	60 ,
	65 ,
	70 ,
	75 ,
	80 ,
	85 ,
	90 ,
	95  ,
	100 ,
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
	
	if(AdcInitFlg == 0)
	{
		for(tag_i = 0;tag_i < 15;tag_i++)
		{
			BatVolFilter[tag_i] = (uint16_t)BatVolTemp;
		}
		AdcInitFlg = 1;
	}else
	{
		BatVolFilter[SampleCount++] = (uint16_t)BatVolTemp;
		if(SampleCount > 14)
		{
			SampleCount = 0;
		}
	}

	BatteryVol = AdcSampleFilt(BatVolFilter,15);
	battery_voltage_input = (float)BatteryVol / 1000;
	battery_percent_output = look1_iflf_binlxpw(battery_voltage_input, battery_voltage, battery_percent, 20U);
	ElectricityDetectionAlgorithm();
}

static uint16_t AdcSampleFilt(uint16_t *buff,uint8_t len)
{
	uint8_t tag_i = 0;
	uint16_t max_val = 0;
	uint16_t min_val = 0;
	uint32_t sum = 0;
	float average = 0.0;

    if (len < 3) {
        return 0.0;
    }

    // 找到最大值和最小�?
    max_val = buff[0];
    min_val = buff[0];
    for (tag_i = 1; tag_i < len; tag_i++) {
        if (buff[tag_i] > max_val) {
            max_val = buff[tag_i];
        }
        if (buff[tag_i] < min_val) {
            min_val = buff[tag_i];
        }
    }

    // 去掉最大值和最小值，计算剩余元素的和
    for (tag_i = 0; tag_i < len; tag_i++) {
            sum += buff[tag_i];
    }

    // 计算平均�?
    average = (float)(sum - max_val - max_val) / (len - 2);
    return (uint16_t)average;
}



/**
 * @brief 使用二分查找法在查找表中进�?�插值查�?
 *
 * 该函数使用二分查找法在查找表�?查找给定的输入�? `u0`，并进�?�插值以获得更精�?的结果�?
 *
 * @param u0 输入值，用于在查找表�?进�?�查找�?
 * @param bp0 查找表的基点数组，包�?查找表的各个基点值�?
 * @param table 查找表数组，包含与基点�?�应的值�?
 * @param maxIndex 查找表的最大索引值，表示查找表的大小减一�?
 * @return 返回通过插值�?�算得到的查找结果�?
 */
static float look1_iflf_binlxpw(float u0, const float bp0[], const float table[], uint32_t maxIndex)
{
  float frac;
  uint32_t iRght;
  uint32_t iLeft;
  uint32_t bpIdx;

  if (u0 <= bp0[0U])
  {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  }
  else if (u0 < bp0[maxIndex])
  {
    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U)
    {
      if (u0 < bp0[bpIdx])
      {
        iRght = bpIdx;
      }
      else
      {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  }
  else
  {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  return (table[iLeft + 1U] - table[iLeft]) * frac + table[iLeft];
}

float PowerConsum = 0;
uint8_t BatLowFlg = 0;

static void ElectricityDetectionAlgorithm(void)
{
		static uint8_t CompleteFlg = 0;
		static float BatPercentMax = 0;
		static float BatPercentMin = 100.0;
		static float SinglePowerConsum = 0;
		float battery_voltage_output ;
	  float battery_percent_input;
	
		if(DevWorkState == WORK_STATE)
		{
				if(battery_percent_output < BatPercentMin)
				{
						BatPercentMin = battery_percent_output;
				}
				
				if(battery_percent_output > BatPercentMax)
				{
						BatPercentMax = battery_percent_output;
				}
				
				if((UltraWorkTim > 900000) && (CompleteFlg == 0))
				{
						CompleteFlg = 1;
						SinglePowerConsum = (BatPercentMax - BatPercentMin) * 2;
						if((SinglePowerConsum > (PowerConsum + 5)) || (SinglePowerConsum < (PowerConsum - 5)))
						{
								PowerConsum = PowerConsum;
						}
				}
		}else
		{
				UltraWorkTim = 0;
				battery_percent_input = 1 + PowerConsum * 1.2;
				battery_voltage_output = look1_iflf_binlxpw(battery_percent_input, battery_percent, battery_voltage, 20U);
				if(BatteryVol < battery_voltage_output)
				{
						BatLowFlg = 1;
				}
		}

}


