#include "dev_app.h"
#include "lv_mainstart.h"

#define ULTRA_BASE 540
#define ULTRA_DUTY 36

static uint16_t FlashStoreBuff[34] = {0}; // 参数配置存储缓存
static uint8_t ParamChangeFlg[3] = {0};	  // 超声参数修改标志位
static uint8_t FreqParam_A = 0;			  // A通道频率参数
static uint8_t FreqParam_B = 0;			  // B通道频率参数
static uint8_t VibraParam = 0;			  // 马达震动参数
static uint32_t u32_FreqParam_A = 0;	  // A通道驱动频率
static uint32_t u32_FreqParam_B = 0;	  // B通道驱动频率
static uint32_t u32_VibraParam = 0;		  // PWM驱动参数
static uint16_t PowerFlg = 0;			  // 充电自动关机
static uint16_t ReadBattery = 0;

Dev_Work_State DevWorkState = IDLE_STATE; // 设备工作状态
extern SCREENSTATE ScreenState;

/*
 * @函数名称：UltraParam_Init
 * @函数功能：初始化超声波参数
 * @输入参数：无
 * @返回参数：无
 * @函数说明：读取FLASH中的参数配置，并初始化超声波参数
 */
void UltraParam_Init(void)
{
	uint8_t tag_i = 0;
	DevFlash_Read(FLASH_SAVE_ADDR, FlashStoreBuff, 34); // 读取参数配置
	DevFlash_Read(FLASH_BATTERYLEVEL, &ReadBattery, 1); // 读取历史电量
	DevFlash_Read(FLASH_SHUNTDOWN, &PowerFlg, 1);		// 读取充电自动关机标志位

	ParamChangeFlg[0] = (uint8_t)FlashStoreBuff[0];
	ParamChangeFlg[1] = (uint8_t)FlashStoreBuff[1];
	ParamChangeFlg[2] = (uint8_t)FlashStoreBuff[2];

	if ((ParamChangeFlg[0] == 0xdd) && (ParamChangeFlg[1] == 0xee) && (ParamChangeFlg[2] == 0xff)) // 参数修改标志位
	{
		FreqParam_A = (uint8_t)FlashStoreBuff[3];
		FreqParam_B = (uint8_t)FlashStoreBuff[4];
		VibraParam = (uint8_t)FlashStoreBuff[5];

		u32_FreqParam_A = 2000 * (ULTRA_BASE + FreqParam_A);
		u32_FreqParam_B = 2000 * (ULTRA_BASE + FreqParam_B);
		u32_VibraParam = VibraParam * 212;
	}
	else
	{
		FreqParam_A = 0x3C;
		FreqParam_B = 0x3C;
		VibraParam = 0x05;

		u32_FreqParam_A = 2000 * (ULTRA_BASE + FreqParam_A);
		u32_FreqParam_B = 2000 * (ULTRA_BASE + FreqParam_B);
		u32_VibraParam = VibraParam * 212;
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

	if (ReadBattery == 0xFFFF)
	{
		ReadBattery = Battery_Level5;
		BatLevel_old = ReadBattery;
	}
	else
	{
		BatLevel_old = ReadBattery;
	}

	MotorLevel = VibraParam;
	FreqOffset = FreqParam_B;
}

/*
 * @函数名称：DevPWM_Init
 * @函数功能：初始化PWM驱动器
 * @输入参数：无
 * @返回参数：无
 * @函数说明：初始化PWM驱动器，设置马达震动初始值为0，超声脉冲频率初始值为0
 */
static void DevPWM_Init(void)
{
	__HAL_TIM_SetCompare(MOTOR_HANDLE, MOTOR_CHB, 0);
	__HAL_TIM_SetCompare(ULTRA_HANDLE, ULTRA_CHB, 0);
}

/*
 * @函数名称：DevSystem_Init
 * @函数功能：初始化系统
 * @输入参数：无
 * @返回参数：无
 * @函数说明：初始化系统，包括GPIO，PWM，ADC，超声波等
 */
void DevSystem_Init(void)
{
	DevGpio_Init();				// 初始化GPIO
	DevPWM_Init();				// 初始化PWM
								//	AD9833_InitIo(AD9833_CH_A); 	// 初始化A通道
	AD9833_InitIo(AD9833_CH_B); // 初始化B通道

	//	AD9833_SetPara(AD9833_CH_A, AD9833_REG_FREQ0, u32_FreqParam_A, AD9833_REG_PHASE1, 2048, AD9833_OUT_TRIANGLE);
	AD9833_SetPara(AD9833_CH_B, AD9833_REG_FREQ0, u32_FreqParam_B, AD9833_REG_PHASE1, 2048, AD9833_OUT_TRIANGLE); // 设置B通道三角波输出频率
}

/*
 * @函数名称：DevAPP_MainFunc
 * @函数功能：设备主函数
 * @输入参数：无
 * @返回参数：无
 * @函数说明：设备主函数，根据设备工作状态执行相应的操作
 * 1. IDLE_STATE：空闲状态，设备处于待机状态，等待用户操作
 * 2. ADMIN_STATE：管理状态，设备处于管理状态，可进行参数配置
 * 3. PASUE_STATE：暂停状态，设备处于暂停状态，超声波输出停止，马达震动停止，
 * 4. CHARGE_STATE：充电状态，设备处于充电状态，超声波输出停止，马达震动停止
 * 5. WORK_STATE：工作状态，可进行控制超声波输出以及马达震动
 * 6. CLOSE_STATE：关机状态，持续拉低相应的IO口，使设备进入待机状态
 */
void DevAPP_MainFunc(void)
{
	static uint8_t BatteryChFlg = 0;
	static uint32_t old_tick = 0;
	uint16_t clear_flg = 0;
	uint32_t new_tick = 0;
	uint16_t ultra_pluse = 0;

	/*充放电状态切换检测，检测到充电状态切换时，将充电自动关机标志位写入FLASH。并关机设备*/
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
	/*设置超声波脉冲占空比为36%*/
	ultra_pluse = UltraDuty * ULTRA_DUTY;

	switch (DevWorkState)
	{
	case IDLE_STATE:
		/*处于待机状态2min，进入关机状态 */
		if (StandyTime > 120000)
		{
			DevWorkState = CLOSE_STATE;
			StandyTime = 0;
		}

		DevGpio_SetOutSta(LTDCDC_EN, GPIO_PIN_RESET);	  //  关闭45V DCDC
		DevGpio_SetOutSta(MOTOR_GATE, GPIO_PIN_RESET);	  //  关闭马达驱动
		DevGpio_SetOutSta(PWM_WAVE_B_EN, GPIO_PIN_RESET); //  关闭超声输出

		__HAL_TIM_SetCompare(MOTOR_HANDLE, MOTOR_CHB, 0);
		__HAL_TIM_SetCompare(ULTRA_HANDLE, ULTRA_CHB, 0);

		break;

	case ADMIN_STATE:
		/*进入管理员模式，10分钟未进行操作进入关机状态*/
		if (StandyTime > 600000)
		{
			StandyTime = 0;
			DevWorkState = CLOSE_STATE;
		}
		DevGpio_SetOutSta(LTDCDC_EN, GPIO_PIN_RESET); // 关闭 45V DCDC
		DevGpio_SetOutSta(PWM_WAVE_B_EN, GPIO_PIN_RESET);

		__HAL_TIM_SetCompare(ULTRA_HANDLE, ULTRA_CHB, 0);
		break;
	case PASUE_STATE:

		/*暂停状态超声波停止输出*/
		StandyTime = 0;

		DevGpio_SetOutSta(LTDCDC_EN, GPIO_PIN_RESET); // 关闭 45V DCDC
		DevGpio_SetOutSta(MOTOR_GATE, GPIO_PIN_RESET);
		DevGpio_SetOutSta(PWM_WAVE_B_EN, GPIO_PIN_RESET);

		__HAL_TIM_SetCompare(MOTOR_HANDLE, MOTOR_CHB, 0);
		__HAL_TIM_SetCompare(ULTRA_HANDLE, ULTRA_CHB, 0);

		break;

	case CHARGE_STATE:
		/*充电中不会进入关机状态 */
		StandyTime = 0;
		DevGpio_Init();
		break;

	case WORK_STATE:
		/*工作状态，超声波输出，马达震动*/
		StandyTime = 0;

		DevGpio_SetOutSta(LTDCDC_EN, GPIO_PIN_SET);
		DevGpio_SetOutSta(MOTOR_GATE, GPIO_PIN_SET);

		DevGpio_SetOutSta(PWM_WAVE_B_EN, GPIO_PIN_SET);
		__HAL_TIM_SetCompare(ULTRA_HANDLE, ULTRA_CHB, ultra_pluse);

		if ((VibraEnableFlg == 0) && (ParamLockFlg == 1))
		{
			__HAL_TIM_SetCompare(MOTOR_HANDLE, MOTOR_CHB, 0);
		}
		else
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
		/*关机状态，持续拉低相应的IO口，使设备进入待机状态*/
		DevWorkState = CLOSE_STATE;
		if (PowerFlg == 1)
		{
			if (ShuntDownCount > 1000)
			{
				if (DevFlash_Write(FLASH_SHUNTDOWN, &clear_flg, 1) == HAL_OK)
				{
					PowerFlg = 0;
				}
			}
		}
		else
		{
			DevGpio_SetOutSta(KEY_CONTROL, GPIO_PIN_SET);
			DevGpio_SetOutSta(CONTROL_CLOSE, GPIO_PIN_SET);
		}
		break;

	default:
		break;
	}
}

/*
 * @函数名称：UltraParam_Set
 * @函数功能：设置超声波参数	
 * @输入参数：无
 * @返回参数：无	
 * @函数说明：设置超声波参数，并将参数写入FLASH
 */
void UltraParam_Set(void)
{
	uint8_t tag_i = 0;

	/*保存标志位为1开始对参数进行保存 */
	if (SlaveFlg == 1)
	{
		FreqParam_A = (uint8_t)FreqOffset;
		FreqParam_B = FreqOffset;
		VibraParam = MotorLevel;

		u32_FreqParam_A = 2000 * (FreqParam_A + ULTRA_BASE);
		u32_FreqParam_B = 2000 * (FreqParam_B + ULTRA_BASE);
		u32_VibraParam = VibraParam * 212;

		ParamChangeFlg[0] = 0xdd;
		ParamChangeFlg[1] = 0xee;
		ParamChangeFlg[2] = 0xff;

//		AD9833_SetPara(AD9833_CH_A, AD9833_REG_FREQ0, u32_FreqParam_A, AD9833_REG_PHASE1, 2048, AD9833_OUT_TRIANGLE);
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

		/*判断数据是否保存成功*/
		if (DevFlash_Write(FLASH_SAVE_ADDR, FlashStoreBuff, 34) == HAL_OK)
		{
			SlaveFlg = 0;
		}
	}
	else
	{
	}
}
