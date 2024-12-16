#include "dev_app.h"
#include "lv_mainstart.h"

static uint16_t FlashStoreBuff[34] = {0}; // 参数配置存储缓存
static uint8_t ParamChangeFlg[3] = {0};	  // 超声参数修改标志位
static uint8_t FreqParam_A = 0;			  // A通道频率参数
static uint8_t FreqParam_B = 0;			  // B通道频率参数
static uint8_t VibraParam = 0;			  // 马达震动参数
static uint32_t u32_FreqParam_A = 0;	  // A通道驱动频率
static uint32_t u32_FreqParam_B = 0;	  // B通道驱动频率
static uint32_t u32_VibraParam = 0;		  // PWM驱动参数
static uint8_t WorkStartFlg = 0;		  // 工作开始标志
static uint8_t WorkFinFlg = 0;			  // 工作结束标志
static uint16_t PowerFlg = 0;			  // 充电自动关机
static uint16_t ReadBattery = 0;

Dev_Work_State DevWorkState = IDLE_STATE; // 设备工作状态

extern SCREENSTATE ScreenState;

void UltraParam_Init(void)
{
	uint8_t tag_i = 0;
	DevFlash_Read(FLASH_SAVE_ADDR, FlashStoreBuff, 34);
	DevFlash_Read(FLASH_BATTERYLEVEL, &ReadBattery, 1);
	DevFlash_Read(FLASH_SHUNTDOWN, &PowerFlg, 1);

	ParamChangeFlg[0] = (uint8_t)FlashStoreBuff[0];
	ParamChangeFlg[1] = (uint8_t)FlashStoreBuff[1];
	ParamChangeFlg[2] = (uint8_t)FlashStoreBuff[2];

	if ((ParamChangeFlg[0] == 0xdd) && (ParamChangeFlg[1] == 0xee) && (ParamChangeFlg[2] == 0xff))
	{
		FreqParam_A = (uint8_t)FlashStoreBuff[3];
		FreqParam_B = (uint8_t)FlashStoreBuff[4];
		VibraParam = (uint8_t)FlashStoreBuff[5];

		u32_FreqParam_A = 2000 * (580 + FreqParam_A);
		u32_FreqParam_B = 2000 * (580 + FreqParam_B);
		u32_VibraParam = VibraParam * 106;
	}
	else
	{
		FreqParam_A = 0x54;
		FreqParam_B = 0x54;
		VibraParam = 0x0A;

		u32_FreqParam_A = 2000 * (580 + FreqParam_A);
		u32_FreqParam_B = 2000 * (580 + FreqParam_B);
		u32_VibraParam = VibraParam * 106;
	}

	LightLevel = FlashStoreBuff[7];

	for (tag_i = 8; tag_i < 32; tag_i++)
	{
		DevicesParam.DevTempBuff[tag_i - 8] = FlashStoreBuff[tag_i];
	}

	VibraEnableFlg = (uint8_t)FlashStoreBuff[32];
	ParamLockFlg = (uint8_t)FlashStoreBuff[33];
	
	if (VibraEnableFlg == 0xFF)
	{
		VibraEnableFlg = 1;
	}
	VibraEnableFlg_old = VibraEnableFlg;

	if (LightLevel == 0xFFFF)
	{
		LightLevel = 100;
	}

	if (PowerFlg == 0x01)
	{
		DevWorkState = CLOSE_STATE;
	}
	else if (PowerFlg == 0xFFFF)
	{
		PowerFlg = 0;
	}
	else
	{
	}
	
	if(ReadBattery == 0xFFFF)
	{
			ReadBattery = Battery_Level5;
			SendBatteryStateData = ReadBattery;
	}else
	{
			SendBatteryStateData = ReadBattery;
	}

	MotorLevel = VibraParam;
	FreqOffset = FreqParam_B;
}

static void DevPWM_Init(void)
{

	__HAL_TIM_SetCompare(MOTOR_HANDLE, MOTOR_CHB, 0);
	__HAL_TIM_SetCompare(ULTRA_HANDLE, ULTRA_CHB, 0);

}

void DevSystem_Init(void)
{
	DevGpio_Init();
	DevPWM_Init();
	AD9833_InitIo(AD9833_CH_A);
	AD9833_InitIo(AD9833_CH_B);

	AD9833_SetPara(AD9833_CH_A, AD9833_REG_FREQ0, u32_FreqParam_A, AD9833_REG_PHASE1, 2048, AD9833_OUT_TRIANGLE);
	AD9833_SetPara(AD9833_CH_B, AD9833_REG_FREQ0, u32_FreqParam_B, AD9833_REG_PHASE1, 2048, AD9833_OUT_TRIANGLE);
}

void DevAPP_MainFunc(void)
{
	static uint8_t BatteryChFlg = 0;
	static uint32_t old_tick = 0;
	uint32_t new_tick = 0;
	uint16_t ultra_pluse = 0;

	if (BatteryState != BOOST)
	{
		DevWorkState = CHARGE_STATE;
		new_tick = HAL_GetTick();
		if ((new_tick - old_tick) > 1000)
		{
			old_tick = new_tick;
			BatteryChFlg = 1;
		}
		if ((BatteryChFlg == 1) && (PowerFlg == 0))
		{
			PowerFlg = 1;
			DevFlash_Write(FLASH_SHUNTDOWN, &PowerFlg, 1);
		}
	}
	else
	{
		if (BatteryChFlg == 0x01)
		{
			DevWorkState = CLOSE_STATE;
		}
		new_tick = HAL_GetTick();
		old_tick = new_tick;
	}

	ultra_pluse = UltraDuty * 25;

	switch (DevWorkState)
	{
	case IDLE_STATE:
		if (StandyTime > 120000)
		{
			DevWorkState = CLOSE_STATE;
			StandyTime = 0;
		}

		DevGpio_SetOutSta(LTDCDC_EN, GPIO_PIN_SET); // 关闭 45V DCDC
		DevGpio_SetOutSta(MOTOR_GATE, GPIO_PIN_RESET);
		DevGpio_SetOutSta(PWM_WAVE_B_EN, GPIO_PIN_RESET);

		__HAL_TIM_SetCompare(MOTOR_HANDLE, MOTOR_CHB, 0);
		__HAL_TIM_SetCompare(ULTRA_HANDLE, ULTRA_CHB, 0);

		break;

	case ADMIN_STATE:
		if (WorkStartFlg == 1)
		{
			WorkFinFlg = 1;
		}

		if(StandyTime > 600000)
		{
			StandyTime = 0;
			DevWorkState = CLOSE_STATE;
		}
		DevGpio_SetOutSta(LTDCDC_EN, GPIO_PIN_SET); // 关闭 45V DCDC
		DevGpio_SetOutSta(PWM_WAVE_B_EN, GPIO_PIN_RESET);

		__HAL_TIM_SetCompare(ULTRA_HANDLE, ULTRA_CHB, 0);
		break;
	case PASUE_STATE:

		if (WorkStartFlg == 1)
		{
			WorkFinFlg = 1;
		}
		StandyTime = 0;

		DevGpio_SetOutSta(LTDCDC_EN, GPIO_PIN_SET); // 关闭 45V DCDC
		DevGpio_SetOutSta(MOTOR_GATE, GPIO_PIN_RESET);
		DevGpio_SetOutSta(PWM_WAVE_B_EN, GPIO_PIN_RESET);

		__HAL_TIM_SetCompare(MOTOR_HANDLE, MOTOR_CHB, 0);
		__HAL_TIM_SetCompare(ULTRA_HANDLE, ULTRA_CHB, 0);

		break;

	case CHARGE_STATE:
		StandyTime = 0;
		DevGpio_Init();
		break;

	case WORK_STATE:

		WorkStartFlg = 1;
		StandyTime = 0;

		DevGpio_SetOutSta(LTDCDC_EN, GPIO_PIN_SET);
		DevGpio_SetOutSta(MOTOR_GATE, GPIO_PIN_SET);

		__HAL_TIM_SetCompare(ULTRA_HANDLE, ULTRA_CHB, ultra_pluse);
		DevGpio_SetOutSta(PWM_WAVE_B_EN, GPIO_PIN_SET);

		if((VibraEnableFlg == 0) && (ParamLockFlg == 1))
		{
				__HAL_TIM_SetCompare(MOTOR_HANDLE, MOTOR_CHB, 0);
		}else
		{
			if (MotorTime < 500)
			{
				__HAL_TIM_SetCompare(MOTOR_HANDLE, MOTOR_CHB, u32_VibraParam);
			}
			else if ((MotorTime >= 500) && (MotorTime < 2000))
			{
				__HAL_TIM_SetCompare(MOTOR_HANDLE, MOTOR_CHB, 0);
			}
			else
			{
				MotorTime = 0;
			}
		}

		break;

	case CLOSE_STATE:

		if ((ShuntDownCount > 1300) && (PowerFlg == 1))
		{
			PowerFlg = 0;
			DevFlash_Write(FLASH_SHUNTDOWN, &PowerFlg, 1);
		}

		DevGpio_SetOutSta(KEY_CONTROL, GPIO_PIN_SET);
		DevGpio_SetOutSta(CONTROL_CLOSE, GPIO_PIN_SET);
		break;

	default:
		break;
	}
}

void UltraParam_Set(void)
{
	uint8_t tag_i = 0;

	if (SlaveFlg == 1)
	{
		SlaveFlg = 0;

		FreqParam_A = (uint8_t)FreqOffset;
		FreqParam_B = FreqOffset;
		VibraParam = MotorLevel;

		u32_FreqParam_A = 2000 * (FreqParam_A + 580);
		u32_FreqParam_B = 2000 * (FreqParam_B + 580);
		u32_VibraParam = VibraParam * 106;

		ParamChangeFlg[0] = 0xdd;
		ParamChangeFlg[1] = 0xee;
		ParamChangeFlg[2] = 0xff;

		AD9833_SetPara(AD9833_CH_A, AD9833_REG_FREQ0, u32_FreqParam_A, AD9833_REG_PHASE1, 2048, AD9833_OUT_TRIANGLE);
		AD9833_SetPara(AD9833_CH_B, AD9833_REG_FREQ0, u32_FreqParam_B, AD9833_REG_PHASE1, 2048, AD9833_OUT_TRIANGLE);

		FlashStoreBuff[0] = (uint16_t)ParamChangeFlg[0];
		FlashStoreBuff[1] = (uint16_t)ParamChangeFlg[1];
		FlashStoreBuff[2] = (uint16_t)ParamChangeFlg[2];
		FlashStoreBuff[3] = (uint16_t)FreqParam_A;
		FlashStoreBuff[4] = (uint16_t)FreqParam_B;
		FlashStoreBuff[5] = (uint16_t)VibraParam;
		FlashStoreBuff[6] = 0;
		FlashStoreBuff[7] = (uint16_t)LightLevel;

		for (tag_i = 8; tag_i < 32; tag_i++)
		{
			FlashStoreBuff[tag_i] = DevicesParam.DevTempBuff[tag_i - 8];
		}

		FlashStoreBuff[32] = (uint16_t)VibraEnableFlg;
		FlashStoreBuff[33] = (uint16_t)ParamLockFlg;

		DevFlash_Write(FLASH_SAVE_ADDR, FlashStoreBuff, 34);
	}
	else
	{
	}
}
