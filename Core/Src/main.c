/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "dma.h"
#include "dma2d.h"
#include "iwdg.h"
#include "ltdc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "dev_malloc.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "dev_st7701.h"
#include "dev_app.h"
#include "lv_mainstart.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint32_t ScreenTime = 0;										//屝幕主界面数杮刷新时�?
uint32_t StandyTime = 0;										//待机时间
uint32_t ChargeRecvTime = 0;								//充电接收时间
uint32_t BatteryTime = 0;										//主界面电池刷新时�?
uint32_t BackLedTime = 0;			  						//背光启动时间
uint32_t PowerOnTime = 0;										//正式�?机时�?
uint32_t Charge_Time = 0;										//充电时长
uint32_t ShuntDownCount = 0;
uint32_t MotorTime = 0;
uint8_t CompleteFlg = 0;										//启动成功
uint32_t UltraWorkTim = 0;
uint32_t UnlockCount = 0;
uint32_t VibraFeedBackTime = 0;												//震动反馈时间
uint32_t DisplayTime = 0;
uint32_t BeatTime = 0;
uint32_t HintTime = 0;
uint8_t LongPressFlg = 0;
uint32_t LongPressTime = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_DMA2D_Init();
  MX_FMC_Init();
  MX_TIM2_Init();
  MX_LTDC_Init();
  MX_ADC1_Init();
  MX_TIM5_Init();
  MX_TIM9_Init();
  MX_TIM3_Init();
  MX_TIM12_Init();
  MX_TIM8_Init();
  MX_USART1_UART_Init();
  MX_IWDG_Init();
  /* USER CODE BEGIN 2 */
	HAL_IWDG_Refresh(&hiwdg);
	UltraParam_Init();
	st7701_init();
	my_mem_init(SRAMIN);                        				/* 初始化内部SRAM内存�? */
	my_mem_init(SRAMEX);                        				/* 初始化外部SRAM内存�? */
	lv_init();                                          /* lvgl系统初始�? */
	lv_port_disp_init();                                /* lvgl显示接口初始�?,放在lv_init()的后�?*/
	lv_port_indev_init();                               /* lvgl输入接口初始�?,放在lv_init()的后�?*/
	
	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_Base_Start(&htim5);
	HAL_TIM_Base_Start(&htim9);
	HAL_TIM_Base_Start(&htim12);
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim8);
	
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_1);
	
	HAL_IWDG_Refresh(&hiwdg);
	//HAL_Delay(500);
	//HAL_IWDG_Refresh(&hiwdg);

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* Call init function for freertos objects (in cmsis_os2.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM14 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */
	static uint8_t BeepTime = 0;

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM14) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
	//1ms周期
	if(htim->Instance == TIM8)
	{
		  BackLedTime++;
		  StandyTime++;
			ScreenTime++;
		  BatteryTime++;
			PowerOnTime++;
			MotorTime++;
			ShuntDownCount++;
			UltraWorkTim++;
			UnlockCount++;
      VibraFeedBackTime++;
      BeatTime++;
		
			if((ScreenState == STOP) || (ScreenState == COMPLETE))
			{
					HintTime++;
			}else
			{
				  HintTime = 0;
			}

      if (DisplayFlg == 1)
      {
         DisplayTime++;
      }
      
			if(PowerOnTime > 1500)
			{
					CompleteFlg = 1;
			}
			
			if(LongPressFlg == 1)
			{
				LongPressTime++;
			}else
			{
				LongPressTime = 0;
			}
			
			BeepTime++;
			if(BeepTime > 8)
			{
					Beep_MainFunc();
					BeepTime = 0;
			}
	}
	
	if(htim->Instance == TIM3)
	{
			ChargeRecvTime++;
	}
  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
