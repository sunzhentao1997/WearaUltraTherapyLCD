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
#include "dev_app.h"
#include "lv_mainstart.h"
#include "lvgl.h"
#include "dev_gt911.h"
#include "dev_ltdc.h"
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
/* Definitions for ScreenLCD */
osThreadId_t ScreenLCDHandle;
uint32_t ScreenLCDBuffer[ 1024 ];
osStaticThreadDef_t ScreenLCDControlBlock;
const osThreadAttr_t ScreenLCD_attributes = {
  .name = "ScreenLCD",
  .cb_mem = &ScreenLCDControlBlock,
  .cb_size = sizeof(ScreenLCDControlBlock),
  .stack_mem = &ScreenLCDBuffer[0],
  .stack_size = sizeof(ScreenLCDBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for UltraApp */
osThreadId_t UltraAppHandle;
uint32_t UltraAppBuffer[ 128 ];
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

void ScreenLCDTask(void *argument);
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
  /* creation of ScreenLCD */
  ScreenLCDHandle = osThreadNew(ScreenLCDTask, NULL, &ScreenLCD_attributes);

  /* creation of UltraApp */
  UltraAppHandle = osThreadNew(UltraAppTask, NULL, &UltraApp_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_ScreenLCDTask */
/**
  * @brief  Function implementing the ScreenLCD thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_ScreenLCDTask */
void ScreenLCDTask(void *argument)
{
  /* USER CODE BEGIN ScreenLCDTask */
  lv_mainstart();
	/* Infinite loop */
  for(;;)
  {
		lv_timer_handler();
    osDelay(5);
  }
  /* USER CODE END ScreenLCDTask */
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
	//DevAdc_Init();
	//DevSystem_Init();
  /* Infinite loop */
  for(;;)
  {
		DevAdc_MainFunc();
		DevMPC5043_MainFunc();
		
    osDelay(5);
  }
  /* USER CODE END UltraAppTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

