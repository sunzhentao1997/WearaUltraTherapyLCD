#include "dev_app.h"

typedef struct
{
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
}DevGpioHandleType;

#define GPIO1		MOTOR_GATE_GPIO_Port,MOTOR_GATE_Pin
#define GPIO2		WAVE_A_EN_GPIO_Port,WAVE_A_EN_Pin
#define GPIO3		WAVE_B_EN_GPIO_Port,WAVE_B_EN_Pin
#define GPIO4		PWM_WAVE_A_EN_GPIO_Port,PWM_WAVE_A_EN_Pin
#define GPIO5		PWM_WAVE_B_EN_GPIO_Port,PWM_WAVE_B_EN_Pin
#define GPIO6		LTDCDC_EN_GPIO_Port,LTDCDC_EN_Pin
#define GPIO7		MPDCDC_EN_GPIO_Port,MPDCDC_EN_Pin
#define GPIO8		CONTROL_CLOSE_GPIO_Port,CONTROL_CLOSE_Pin
#define GPIO9		KEY_CONTROL_GPIO_Port,KEY_CONTROL_Pin

const static DevGpioHandleType dev_gpio_handle[DevGpioMaxChannlLab] = 
{
		[MOTOR_GATE] 			= {GPIO1},
		[ULTRA_A_EN] 			= {GPIO2},
		[ULTRA_B_EN] 			= {GPIO3},
		[PWM_WAVE_A_EN] 	= {GPIO4},
		[PWM_WAVE_B_EN] 	= {GPIO5},
		[LTDCDC_EN] 			= {GPIO6},
		[MPDCDC_EN] 			= {GPIO7},
		[CONTROL_CLOSE] 	= {GPIO8},
		[KEY_CONTROL] 		= {GPIO9},
};

void DevGpio_SetOutSta(uint8_t ch,GPIO_PinState PinState)
{
		GPIO_TypeDef* gpio;
		uint16_t pin;
	
		gpio = dev_gpio_handle[ch].GPIOx;
		pin = dev_gpio_handle[ch].GPIO_Pin;
	
		HAL_GPIO_WritePin(gpio,pin,PinState);
}

void DevGpio_Init(void)
{
		DevGpio_SetOutSta(CONTROL_CLOSE,GPIO_PIN_RESET);
		DevGpio_SetOutSta(MPDCDC_EN,GPIO_PIN_SET);
		DevGpio_SetOutSta(LTDCDC_EN,GPIO_PIN_RESET);
		DevGpio_SetOutSta(MOTOR_GATE,GPIO_PIN_RESET);
	
		DevGpio_SetOutSta(PWM_WAVE_A_EN,GPIO_PIN_RESET);
		DevGpio_SetOutSta(PWM_WAVE_B_EN,GPIO_PIN_RESET);
		DevGpio_SetOutSta(KEY_CONTROL,GPIO_PIN_RESET);
		DevGpio_SetOutSta(ULTRA_A_EN,GPIO_PIN_RESET);
		DevGpio_SetOutSta(ULTRA_B_EN,GPIO_PIN_RESET);
	
}
