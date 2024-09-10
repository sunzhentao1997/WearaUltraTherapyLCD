/*
 * dev_adc.c
 *
 *  Created on: Sep 8, 2024
 *      Author: sunzhentao
 */

#include "../Devices/dev_adc.h"

#include "stdint.h"

extern ADC_HandleTypeDef hadc1;

uint32_t AdcVal = 0;
uint16_t BatteryVol = 3500;
uint16_t BatVolFilter[15] = {0};

static uint16_t AdcSampleFilt(uint16_t *buff,uint8_t len);


void DevAdc_Init(void)
{
	HAL_ADC_Start_DMA(&hadc1, &AdcVal, 1);
}

void DevAdc_MainFunc(void)
{
	static uint8_t AdcInitFlg = 0;
	static uint8_t SampleCount = 0;
	uint8_t tag_i = 0;
	float BatVolTemp = 0.0;
	HAL_ADC_Start_DMA(&hadc1, &AdcVal, 1);

	BatVolTemp = AdcVal * 3300 / 4096;
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

    // 找到最大值和最小值
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

    // 计算平均值
    average = (float)(sum - max_val - max_val) / (len - 2);
    return (uint16_t)average;
}
