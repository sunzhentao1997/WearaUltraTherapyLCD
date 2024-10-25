#include "main.h"
#include "tim.h"
#include "dev_app.h"

extern TIM_HandleTypeDef htim9;

#define BEEP_HANDLE			(&htim9)
#define BEEP_CHANNLE		TIM_CHANNEL_2

#define BEEP_ON()					__HAL_TIM_SetCompare(BEEP_HANDLE,BEEP_CHANNLE,180)
#define BEEP_OFF()				__HAL_TIM_SetCompare(BEEP_HANDLE,BEEP_CHANNLE,0)

int8_t BeepCount = 0;
uint8_t BeepFlg = 0;

void Beep_MainFunc(void)
{
		uint8_t tag_i;
		static uint8_t BeepTim = 0;
	
		if(BeepFlg == 1)
		{
				if((BeepCount % 2) == 0)
				{
						BEEP_ON();
				}else
				{
						BEEP_OFF();
				}
				
				BeepCount--;
				if(BeepCount < 0)
				{
						BEEP_OFF();
						BeepCount = 0;
						BeepFlg = 0;
				}
		}else if(BeepFlg == 2)
		{
				if(BeepCount % 4 == 0)
				{
						BeepTim++;
						if(BeepTim > 3)
						{
							BeepTim = 0;
							if((BeepCount % 2) == 0)
							{
									BEEP_ON();
							}else
							{
									BEEP_OFF();
							}
							BeepCount--;
						}
				}else
				{
						if((BeepCount % 2) == 0)
						{
								BEEP_ON();
						}else
						{
								BEEP_OFF();
						}
						BeepCount--;
				}
				
				if(BeepCount < 0)
				{
						BEEP_OFF();
						BeepCount = 0;
						BeepFlg = 0;
				}
		}else
		{
		}
}
