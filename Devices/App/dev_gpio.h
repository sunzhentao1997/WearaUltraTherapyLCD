#ifndef __DEV_GPIO_H
#define __DEV_GPIO_H

#include "main.h"

typedef enum
{
		MOTOR_GATE,			//马达控制
		ULTRA_A_EN,			//A通道超声使能
		ULTRA_B_EN,			//B通道超声使能
		PWM_WAVE_A_EN,  //A通道PWM输出使能
		PWM_WAVE_B_EN,	//B通道PWM输出使能
		LTDCDC_EN,			//12V电压使能
		MPDCDC_EN,			//45V电压使能
		CONTROL_CLOSE,  //关机
		KEY_CONTROL,		//按键开关
		DevGpioMaxChannlLab,
}DevGPIOChannleLabType;

void DevGpio_SetOutSta(uint8_t ch,GPIO_PinState PinState);
void DevGpio_Init(void);

#endif
