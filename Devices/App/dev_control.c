#include "dev_app.h"

extern TIM_HandleTypeDef htim2;

#define MOTOR_HANDLE 	(&htim2)
#define MOTOR_CH1			TIM_CHANNEL_2
#define MOTOR_CH2			TIM_CHANNEL_3

uint8_t WorkStartFlg = 0;
uint8_t WorkFinish = 0;
Dev_Work_State DevWorkState = IDLE_STATE;

void DevSystem_Init(void)
{
		DevGpio_Init();
		AD9833_InitIo(AD9833_CH_A);
		AD9833_InitIo(AD9833_CH_B);
	
		AD9833_SetPara(AD9833_CH_A,AD9833_REG_FREQ0,1200000,AD9833_REG_PHASE1,2048,AD9833_OUT_TRIANGLE);
		AD9833_SetPara(AD9833_CH_B,AD9833_REG_FREQ0,1200000,AD9833_REG_PHASE1,2048,AD9833_OUT_TRIANGLE);
}

void DevAPP_MainFunc(void)
{
		uint8_t state = DevWorkState;
		static uint32_t StandyCount = 0;
	
		
		switch(state)
		{
			case IDLE_STATE:
				StandyCount++;
				if(StandyCount > 900)
				{
						DevWorkState = CLOSE_STATE;
					  StandyCount = 0;
				}
				
				DevGpio_SetOutSta(LTDCDC_EN,GPIO_PIN_RESET);			//关闭 45V DCDC
				DevGpio_SetOutSta(MOTOR_GATE,GPIO_PIN_RESET);
				DevGpio_SetOutSta(PWM_WAVE_A_EN,GPIO_PIN_RESET);
				DevGpio_SetOutSta(PWM_WAVE_B_EN,GPIO_PIN_RESET);
				DevGpio_SetOutSta(ULTRA_A_EN,GPIO_PIN_RESET);
				DevGpio_SetOutSta(ULTRA_B_EN,GPIO_PIN_RESET);
				
				__HAL_TIM_SetCompare(MOTOR_HANDLE,MOTOR_CH1,0);
				__HAL_TIM_SetCompare(MOTOR_HANDLE,MOTOR_CH2,0);
				
				
				break;
				
			case PASUE_STATE:
				
				if(WorkStartFlg == 1)
				{
						WorkFinish = 1;
				}
				StandyCount = 0;
				
				DevGpio_SetOutSta(LTDCDC_EN,GPIO_PIN_RESET);			//关闭 45V DCDC
				DevGpio_SetOutSta(MOTOR_GATE,GPIO_PIN_RESET);
				DevGpio_SetOutSta(PWM_WAVE_A_EN,GPIO_PIN_RESET);
				DevGpio_SetOutSta(PWM_WAVE_B_EN,GPIO_PIN_RESET);
				DevGpio_SetOutSta(ULTRA_A_EN,GPIO_PIN_RESET);
				DevGpio_SetOutSta(ULTRA_B_EN,GPIO_PIN_RESET);
				
				__HAL_TIM_SetCompare(MOTOR_HANDLE,MOTOR_CH1,0);
				__HAL_TIM_SetCompare(MOTOR_HANDLE,MOTOR_CH2,0);
				
				break;
			
			case CHARGE_STATE:
				StandyCount = 0;
				DevGpio_Init();
				break;
			
			case WORK_STATE:
					
				break;
			
			case CLOSE_STATE:
				
					DevGpio_SetOutSta(CONTROL_CLOSE,GPIO_PIN_SET);
			break;
			
			default:
				break;
		}
}


