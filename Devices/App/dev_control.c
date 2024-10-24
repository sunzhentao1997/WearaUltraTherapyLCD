#include "dev_app.h"
#include "lv_mainstart.h"

extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim3;

#define ULTRA_HANDLE	(&htim3)
#define ULTRA_CHB			TIM_CHANNEL_1
#define ULTRA_CHA			TIM_CHANNEL_2

#define MOTOR_HANDLE 	(&htim5)
#define MOTOR_CHB			TIM_CHANNEL_2
#define MOTOR_CHA			TIM_CHANNEL_3

#define FLASH_LOWBATTERY	  0x81C0000
#define FLASH_SAVE_ADDR 		0x81E0000


uint16_t FlashStoreBuff[17] = {0};
uint8_t ParamChangeFlg[3] = {0};
uint8_t FreqParam_A = 0;
uint8_t FreqParam_B = 0;
uint8_t VibraParam = 0;
uint16_t Low_Battery_Flg = 0;
uint8_t WorkStartFlg = 0;
uint8_t WorkFinish = 0;
uint32_t u32_FreqParam_A = 0;
uint32_t u32_FreqParam_B = 0;
uint32_t u32_VibraParam = 0;
uint32_t StandyTime = 0;
uint8_t CompleteFlg = 0;
uint32_t Charge_Time = 0;

uint8_t UltraDuty = 0;
extern SCREENSTATE ScreenState;
Dev_Work_State DevWorkState = IDLE_STATE;

extern uint32_t MotorLevel;
extern uint16_t FreqOffset;
extern uint8_t SlaveFlg;

void UltraParam_Init(void)
{
		uint8_t tag_i = 0;
		DevFlash_Read(FLASH_SAVE_ADDR,FlashStoreBuff,17);
		DevFlash_Read(FLASH_LOWBATTERY,&Low_Battery_Flg,1);
	
		ParamChangeFlg[0] = (uint8_t)FlashStoreBuff[0];
		ParamChangeFlg[1] = (uint8_t)FlashStoreBuff[1];
		ParamChangeFlg[2] = (uint8_t)FlashStoreBuff[2];
	
		if((ParamChangeFlg[0] == 0xdd) && (ParamChangeFlg[1] == 0xee) && (ParamChangeFlg[2] == 0xff))
		{
				FreqParam_A	= (uint8_t)FlashStoreBuff[3];
				FreqParam_B = (uint8_t)FlashStoreBuff[4];
				VibraParam  = (uint8_t)FlashStoreBuff[5];
					
				u32_FreqParam_A = 2000 * (551+FreqParam_A);
				u32_FreqParam_B = 2000 * (551+FreqParam_B);
			  u32_VibraParam = VibraParam * 212;
		}else
		{
				FreqParam_A = 0x54;
				FreqParam_B = 0x54;
				VibraParam = 0x0A;
				
				u32_FreqParam_A = 2000 * (551+FreqParam_A);
				u32_FreqParam_B = 2000 * (551+FreqParam_B);
			  u32_VibraParam = VibraParam * 212;
		}
		
		LightLevel = FlashStoreBuff[7];
		
		for(tag_i = 8;tag_i < 17;tag_i++)
		{
				DevicesParam.DevTempBuff[tag_i - 8] = FlashStoreBuff[tag_i];
		}
		
		if(LightLevel == 0xFFFF)
		{
				LightLevel = 50;
		}
		
		MotorLevel = VibraParam;
		FreqOffset = FreqParam_A;
}

static void DevPWM_Init(void)
{
		
		__HAL_TIM_SetCompare(MOTOR_HANDLE,MOTOR_CHB,0);
		__HAL_TIM_SetCompare(MOTOR_HANDLE,MOTOR_CHA,0);
		__HAL_TIM_SetCompare(ULTRA_HANDLE,ULTRA_CHB,0);
		__HAL_TIM_SetCompare(ULTRA_HANDLE,ULTRA_CHA,0);

}

void DevSystem_Init(void)
{
		DevGpio_Init();
		DevPWM_Init();
		AD9833_InitIo(AD9833_CH_A);
		AD9833_InitIo(AD9833_CH_B);
	
		AD9833_SetPara(AD9833_CH_A,AD9833_REG_FREQ0,u32_FreqParam_A,AD9833_REG_PHASE1,2048,AD9833_OUT_TRIANGLE);
		AD9833_SetPara(AD9833_CH_B,AD9833_REG_FREQ0,u32_FreqParam_B,AD9833_REG_PHASE1,2048,AD9833_OUT_TRIANGLE);
}

void DevAPP_MainFunc(void)
{
		static uint8_t BatteryChFlg = 0;
		static uint32_t old_tick = 0;
		uint32_t new_tick = 0;
		uint16_t ultra_pluse = 0;
	
		if(SendBatteryStateData < Boost_Level1)
		{
				DevWorkState = CHARGE_STATE;
				new_tick = HAL_GetTick();
				if((new_tick - old_tick) > 1000)
				{
					old_tick = new_tick;
					BatteryChFlg = 1;
				}
		}else
		{
				if(BatteryChFlg == 0x01)
				{
					DevWorkState = CLOSE_STATE;
				}
				new_tick = HAL_GetTick();
				old_tick = new_tick;
		}
		
		ultra_pluse = UltraDuty * 100;
		
		switch(DevWorkState)
		{
			case IDLE_STATE:
				if(StandyTime > 45000)
				{
						DevWorkState = CLOSE_STATE;
					  StandyTime = 0;
				}
				
				DevGpio_SetOutSta(LTDCDC_EN,GPIO_PIN_RESET);			//关闭 45V DCDC
				DevGpio_SetOutSta(MOTOR_GATE,GPIO_PIN_RESET);
				DevGpio_SetOutSta(ULTRA_A_EN,GPIO_PIN_RESET);
				DevGpio_SetOutSta(ULTRA_B_EN,GPIO_PIN_RESET);
				
				__HAL_TIM_SetCompare(MOTOR_HANDLE,MOTOR_CHB,0);
				__HAL_TIM_SetCompare(MOTOR_HANDLE,MOTOR_CHA,0);
				__HAL_TIM_SetCompare(ULTRA_HANDLE,ULTRA_CHB,0);
				__HAL_TIM_SetCompare(ULTRA_HANDLE,ULTRA_CHA,0);
				
				break;
				
			case PASUE_STATE:
				
				if(WorkStartFlg == 1)
				{
						WorkFinish = 1;
				}
				StandyTime = 0;
				
				DevGpio_SetOutSta(LTDCDC_EN,GPIO_PIN_RESET);			//关闭 45V DCDC
				DevGpio_SetOutSta(MOTOR_GATE,GPIO_PIN_RESET);
				DevGpio_SetOutSta(ULTRA_A_EN,GPIO_PIN_RESET);
				DevGpio_SetOutSta(ULTRA_B_EN,GPIO_PIN_RESET);
				
				__HAL_TIM_SetCompare(MOTOR_HANDLE,MOTOR_CHB,0);
				__HAL_TIM_SetCompare(MOTOR_HANDLE,MOTOR_CHA,0);
				__HAL_TIM_SetCompare(ULTRA_HANDLE,ULTRA_CHB,0);
				__HAL_TIM_SetCompare(ULTRA_HANDLE,ULTRA_CHA,0);
				
				break;
			
			case CHARGE_STATE:
				StandyTime = 0;
				DevGpio_Init();
				break;
			
			case WORK_STATE:
				
					WorkStartFlg = 1;
					StandyTime = 0;

					DevGpio_SetOutSta(LTDCDC_EN,GPIO_PIN_SET);			
					DevGpio_SetOutSta(MOTOR_GATE,GPIO_PIN_SET);
					DevGpio_SetOutSta(ULTRA_B_EN,GPIO_PIN_SET);

					__HAL_TIM_SetCompare(ULTRA_HANDLE,ULTRA_CHB,ultra_pluse);
					__HAL_TIM_SetCompare(MOTOR_HANDLE,MOTOR_CHB,u32_VibraParam);
					
				break;
			
			case CLOSE_STATE:
				
					DevGpio_SetOutSta(CONTROL_CLOSE,GPIO_PIN_SET);
			break;
			
			default:
				break;
		}
}

void UltraParam_Set(void)
{
		uint8_t tag_i = 0;
	
		if(SlaveFlg == 1)
		{
				SlaveFlg = 0;
				
				FreqParam_A = (uint8_t)FreqOffset;
				FreqParam_B = FreqParam_A;
				VibraParam = (uint8_t)MotorLevel;
			
				u32_FreqParam_A = 2000 * (FreqParam_A + 551);
				u32_FreqParam_B = 2000 * (FreqParam_B + 551);
				u32_VibraParam = VibraParam * 212;
			
				ParamChangeFlg[0] = 0xdd;
				ParamChangeFlg[1] = 0xee;
				ParamChangeFlg[2] = 0xff;
			
				AD9833_SetPara(AD9833_CH_A,AD9833_REG_FREQ0,u32_FreqParam_A,AD9833_REG_PHASE1,2048,AD9833_OUT_TRIANGLE);
				AD9833_SetPara(AD9833_CH_B,AD9833_REG_FREQ0,u32_FreqParam_B,AD9833_REG_PHASE1,2048,AD9833_OUT_TRIANGLE);
			
				FlashStoreBuff[0] = (uint16_t)ParamChangeFlg[0];
				FlashStoreBuff[1] = (uint16_t)ParamChangeFlg[1];
				FlashStoreBuff[2] = (uint16_t)ParamChangeFlg[2];
				FlashStoreBuff[3] = (uint16_t)FreqParam_A;
				FlashStoreBuff[4] = (uint16_t)FreqParam_B;
				FlashStoreBuff[5] = (uint16_t)VibraParam;
				FlashStoreBuff[6] = 0;
				FlashStoreBuff[7] = (uint16_t)LightLevel;
				
				for(tag_i = 8;tag_i < 17;tag_i++)
				{
						FlashStoreBuff[tag_i] = DevicesParam.DevTempBuff[tag_i - 8];
				}
				
				DevFlash_Write(FLASH_SAVE_ADDR,FlashStoreBuff,17);
		}else
		{
		}
}

void Low_Battery_Warning(void)
{
		//从工作到结束，并且电量低于2格时低电量关机
	if((CompleteFlg == 1) && ((SendBatteryStateData == Boost_Level2) || (SendBatteryStateData == Boost_Level1)))
	{
		if(Low_Battery_Flg == 1)
		{

		}else
		{
			Low_Battery_Flg = 1;
			DevFlash_Write(FLASH_LOWBATTERY,&Low_Battery_Flg,1);
		}

	}

	if(SendBatteryStateData > Boost_Level2)
	{
		Low_Battery_Flg = 0;
	}

	if(Charge_Time > 120000)
	{
		Charge_Time = 0;
		Low_Battery_Flg = 0;

		DevFlash_Write(FLASH_LOWBATTERY,&Low_Battery_Flg,1);
	}

}



