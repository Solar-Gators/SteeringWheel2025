/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32l4xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUTTON8_Pin GPIO_PIN_5
#define BUTTON8_GPIO_Port GPIOA
#define BUTTON8_LED_Pin GPIO_PIN_6
#define BUTTON8_LED_GPIO_Port GPIOA
#define BUTTON7_Pin GPIO_PIN_7
#define BUTTON7_GPIO_Port GPIOA
#define BUTTON7_LED_Pin GPIO_PIN_4
#define BUTTON7_LED_GPIO_Port GPIOC
#define BUTTON6_Pin GPIO_PIN_5
#define BUTTON6_GPIO_Port GPIOC
#define BUTTON6_LED_Pin GPIO_PIN_0
#define BUTTON6_LED_GPIO_Port GPIOB
#define BUTTON5_Pin GPIO_PIN_1
#define BUTTON5_GPIO_Port GPIOB
#define BUTTON5_LED_Pin GPIO_PIN_2
#define BUTTON5_LED_GPIO_Port GPIOB
#define BUTTON1_Pin GPIO_PIN_12
#define BUTTON1_GPIO_Port GPIOB
#define BUTTON1_LED_Pin GPIO_PIN_13
#define BUTTON1_LED_GPIO_Port GPIOB
#define BUTTON2_Pin GPIO_PIN_14
#define BUTTON2_GPIO_Port GPIOB
#define BUTTON2_LED_Pin GPIO_PIN_15
#define BUTTON2_LED_GPIO_Port GPIOB
#define BUTTON3_Pin GPIO_PIN_6
#define BUTTON3_GPIO_Port GPIOC
#define BUTTON3_LED_Pin GPIO_PIN_7
#define BUTTON3_LED_GPIO_Port GPIOC
#define BUTTON4_Pin GPIO_PIN_8
#define BUTTON4_GPIO_Port GPIOC
#define BUTTON4_EXTI_IRQn EXTI9_5_IRQn
#define BUTTON4_LED_Pin GPIO_PIN_9
#define BUTTON4_LED_GPIO_Port GPIOC
#define OK_LED_Pin GPIO_PIN_4
#define OK_LED_GPIO_Port GPIOB
#define ERROR_LED_Pin GPIO_PIN_5
#define ERROR_LED_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
