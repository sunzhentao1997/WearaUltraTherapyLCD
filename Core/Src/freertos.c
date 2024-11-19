/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lv_mainstart.h"
#include "lvgl.h"
#include "dev_gt911.h"
#include "dev_ltdc.h"
#include "dev_beep.h"
#include "custom.h"
#include "tim.h"
#include "dev_app.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern uint32_t BackLedTime;


/* USER CODE END Variables */
/* Definitions for ScreenRGB */
osThreadId_t ScreenRGBHandle;
uint32_t ScreenRGBBuffer[ 1024 ];
osStaticThreadDef_t ScreenRGBControlBlock;
const osThreadAttr_t ScreenRGB_attributes = {
  .name = "ScreenRGB",
  .cb_mem = &ScreenRGBControlBlock,
  .cb_size = sizeof(ScreenRGBControlBlock),
  .stack_mem = &ScreenRGBBuffer[0],
  .stack_size = sizeof(ScreenRGBBuffer),
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for UltraApp */
osThreadId_t UltraAppHandle;
uint32_t UltraAppBuffer[ 256 ];
osStaticThreadDef_t UltraAppControlBlock;
const osThreadAttr_t UltraApp_attributes = {
  .name = "UltraApp",
  .cb_mem = &UltraAppControlBlock,
  .cb_size = sizeof(UltraAppControlBlock),
  .stack_mem = &UltraAppBuffer[0],
  .stack_size = sizeof(UltraAppBuffer),
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void ScreenRGBTask(void *argument);
void UltraAppTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of ScreenRGB */
  ScreenRGBHandle = osThreadNew(ScreenRGBTask, NULL, &ScreenRGB_attributes);

  /* creation of UltraApp */
  UltraAppHandle = osThreadNew(UltraAppTask, NULL, &UltraApp_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_ScreenRGBTask */
/**
  * @brief  Function implementing the ScreenRGB thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_ScreenRGBTask */
void ScreenRGBTask(void *argument)
{
  /* USER CODE BEGIN ScreenRGBTask */
	static uint32_t old_tick = 0;
	uint32_t tick = 0;
	static uint8_t StartFlg = 0;
	static uint16_t tag_i = 100;
	static uint16_t tag_j = 150;
	uint16_t tempval = 0;
	lv_mainstart();
  /* Infinite loop */
  for(;;)
  {
		if((StartFlg == 0) && (BackLedTime < 3500))
		{
			  tempval = LightLevel * 10;
								
				if(BackLedTime > 1500)
				{
					__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,1000);
				}
				if(BackLedTime > 3450)
				{
					  ui_load_scr_animation(&guider_ui, &guider_ui.main, guider_ui.main_del, &guider_ui.boot_del, setup_scr_main, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, true);
						StartFlg = 1;
				}
		}else if(StartFlg == 1)
		{
				ScreenFunc();
//				tick = HAL_GetTick();
//				if((tick - old_tick) > 100)
//				{
//					old_tick = tick;
//					if(tag_i == 50)
//					{
//						lv_obj_set_size(guider_ui.main_label_14, 50, 50);
//						lv_obj_set_pos(guider_ui.main_label_14, (191+25), (497+25));
//						tag_i = 60;	
//					}else if(tag_i == 60)
//					{
//						lv_obj_set_size(guider_ui.main_label_14, 60, 60);
//						lv_obj_set_pos(guider_ui.main_label_14, (191+20), (497+20));
//						tag_i = 70;
//					}else if(tag_i == 70)
//					{
//						lv_obj_set_size(guider_ui.main_label_14, 70, 70);
//						lv_obj_set_pos(guider_ui.main_label_14, (191+15), (497+15));
//						tag_i = 80;
//					}else if(tag_i == 80)
//					{
//						lv_obj_set_size(guider_ui.main_label_14, 80, 80);
//						lv_obj_set_pos(guider_ui.main_label_14, (191+10), (497+10));
//						tag_i = 90;
//					}else if(tag_i == 90)
//					{
//						lv_obj_set_size(guider_ui.main_label_14, 90, 90);
//						lv_obj_set_pos(guider_ui.main_label_14, (191+5), (497+5));
//						tag_i = 100;
//					}else if(tag_i == 100)
//					{
//						lv_obj_set_size(guider_ui.main_label_14, 100, 100);
//						lv_obj_set_pos(guider_ui.main_label_14, (191), (497));
//						tag_i = 50;
//					}
//				}
		}
		Beep_MainFunc();
		lv_timer_handler();
    osDelay(5);
  }
  /* USER CODE END ScreenRGBTask */
}

/* USER CODE BEGIN Header_UltraAppTask */
/**
* @brief Function implementing the UltraApp thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_UltraAppTask */
void UltraAppTask(void *argument)
{
  /* USER CODE BEGIN UltraAppTask */
//	static uint8_t count = 0;
	
	DevSystem_Init();
	DevAdc_Init();
  /* Infinite loop */
  for(;;)
  {
		DevAdc_MainFunc();
		DevAPP_MainFunc();
		DevMPC5043_MainFunc();
		UltraParam_Set();
		Low_Battery_Warning();
				
    osDelay(20);
  }
  /* USER CODE END UltraAppTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

