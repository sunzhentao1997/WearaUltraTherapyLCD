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
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void ScreenRGBTask(void *argument);

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
	uint8_t mode = 0x01;
	lv_mainstart();                 /* 测试的demo */;
  /* Infinite loop */
  for(;;)
  {
		lv_timer_handler();         /* LVGL计时�? */
    osDelay(5);
  }
  /* USER CODE END ScreenRGBTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

