#include "dev_app.h"

#define BEEPONTIME 20
#define BEEPOFFTIME 24

int8_t BeepCount = 0;
uint8_t BeepFlg = 0;
static uint8_t BeepFlg_old = 0;

/* @函数名称：Beep_MainFunc
 * @功能描述：蜂鸣器的主函数，处理蜂鸣器的开启和关闭逻辑
 * @参数说明：无
 * @返回值：无
 */
void Beep_MainFunc(void)
{
	static uint8_t Beep_On = BEEPONTIME;      //蜂鸣器开启时间
	static uint8_t Beep_Off = BEEPOFFTIME;    //蜂鸣器关闭时间
	static uint8_t BeepTim = 0;

	if (BeepFlg == 1)                          //按键点击音效
	{
		BeepFlg_old = 1;
		if ((BeepCount % 2) == 0)
		{
			Beep_On--;
			BEEP_ON();

			if (Beep_On == 0)
			{
				BeepCount--;
				Beep_On = BEEPONTIME;
				Beep_Off = BEEPOFFTIME;
			}
		}
		else
		{
			Beep_Off--;
			BEEP_OFF();

			if (Beep_Off == 0)
			{
				BeepCount--;
				Beep_On = BEEPONTIME;
				Beep_Off = BEEPOFFTIME;
			}
		}

		if (BeepCount <= 0)
		{
			BEEP_OFF();
			BeepCount = 0;
			BeepFlg = 0;
			BeepFlg_old = 0;
			Beep_On = BEEPONTIME;
			Beep_Off = BEEPOFFTIME;
		}
	}
	else if ((BeepFlg == 2) && (BeepFlg_old == 1))  
	{
		BeepFlg_old = 0;
		BEEP_OFF();
	}
	else if (BeepFlg == 2)				//结束提示音
	{
		if (BeepCount % 6 == 0)
		{
			BeepTim++;
			if (BeepTim > 64)
			{
				if ((BeepCount % 2) == 0)
				{
					Beep_On--;
					BEEP_ON();

					if (Beep_On == 0)
					{
						BeepCount--;
						BeepTim = 0;
						Beep_On = BEEPONTIME;
						Beep_Off = BEEPOFFTIME;
					}
				}
				else
				{
					Beep_Off--;
					BEEP_OFF();

					if (Beep_Off == 0)
					{
						BeepCount--;
						Beep_On = BEEPONTIME;
						Beep_Off = BEEPOFFTIME;
					}
				}
			}
		}
		else
		{
			if ((BeepCount % 2) == 0)
			{
				Beep_On--;
				BEEP_ON();
				if (Beep_On == 0)
				{
					BeepCount--;
					Beep_On = BEEPONTIME;
					Beep_Off = BEEPOFFTIME;
				}
			}
			else
			{
				Beep_Off--;
				BEEP_OFF();

				if (Beep_Off == 0)
				{
					BeepCount--;
					Beep_On = BEEPONTIME;
					Beep_Off = BEEPOFFTIME;
				}
			}
		}

		if (BeepCount <= 0)
		{
			BEEP_OFF();

			BeepCount = 0;
			BeepFlg = 0;
			Beep_On = BEEPONTIME;
			Beep_Off = BEEPOFFTIME;
		}
	}
	else
	{
	}
}