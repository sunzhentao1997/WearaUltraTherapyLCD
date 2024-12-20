#include "dev_app.h"

#define BEEPONTIME 24
#define BEEPOFFTIME 32

int8_t BeepCount = 0;
uint8_t BeepFlg = 0;
static uint8_t BeepFlg_old = 0;

void Beep_MainFunc(void)
{
	static uint8_t Beep_On = BEEPONTIME;
	static uint8_t Beep_Off = BEEPOFFTIME;
	static uint8_t BeepTim = 0;

	if (BeepFlg == 1)
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
	else if (BeepFlg == 2)
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
