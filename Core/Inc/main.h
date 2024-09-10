/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CHARGE_STATE_Pin GPIO_PIN_0
#define CHARGE_STATE_GPIO_Port GPIOC
#define CHARGE_STATE_EXTI_IRQn EXTI0_IRQn
#define B_SCLK_Pin GPIO_PIN_15
#define B_SCLK_GPIO_Port GPIOA
#define B_DATA_Pin GPIO_PIN_10
#define B_DATA_GPIO_Port GPIOC
#define B_FSYNC_Pin GPIO_PIN_11
#define B_FSYNC_GPIO_Port GPIOC
#define A_SCLK_Pin GPIO_PIN_3
#define A_SCLK_GPIO_Port GPIOB
#define A_DATA_Pin GPIO_PIN_5
#define A_DATA_GPIO_Port GPIOB
#define A_FSYNC_Pin GPIO_PIN_6
#define A_FSYNC_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
