/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//Testing Push by Sriharsha
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DEBOUNCE_THRESHOLD 50  // Debounce time in ms

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_UART4_Init(void);
static void MX_UART5_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
volatile uint32_t lastButtonPressTime[8];

uint8_t buttonStates;

uint16_t button_press_init;

uint32_t previousTimes[] = {0,0,0,0,0,0,0,0};
uint32_t currentTime = 0;

uint8_t buttonPressEvents;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
  for(int i = 0; i<8; i++){
	  lastButtonPressTime[i] = 0;
  }

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
  MX_UART4_Init();
  MX_UART5_Init();
  /* USER CODE BEGIN 2 */
  buttonStates = 0b01000000;
  HAL_GPIO_WritePin(BUTTON7_LED_GPIO_Port, BUTTON7_LED_Pin, GPIO_PIN_SET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	HAL_GPIO_TogglePin(OK_LED_GPIO_Port, OK_LED_Pin);

	if(!HAL_GPIO_ReadPin(BUTTON6_GPIO_Port, BUTTON6_Pin)){
		buttonStates |= 0b00100000;
    HAL_GPIO_WritePin(BUTTON6_LED_GPIO_Port, BUTTON6_LED_Pin, GPIO_PIN_SET);
	}else{
		buttonStates &= 0b11011111;
    HAL_GPIO_WritePin(BUTTON6_LED_GPIO_Port, BUTTON6_LED_Pin, GPIO_PIN_RESET);
	}

  if (!HAL_GPIO_ReadPin(BUTTON5_GPIO_Port, BUTTON5_Pin)) { // make ptt / brake debug button a hold
    buttonStates |= 0b00010000;
    HAL_GPIO_WritePin(BUTTON5_LED_GPIO_Port, BUTTON5_LED_Pin, GPIO_PIN_SET);
  } else {
    buttonStates &= 0b11101111;
    HAL_GPIO_WritePin(BUTTON5_LED_GPIO_Port, BUTTON5_LED_Pin, GPIO_PIN_RESET);
  }


	if(HAL_UART_Transmit(&huart4, &buttonStates, 1, 1000) != HAL_OK){
		HAL_GPIO_WritePin(ERROR_LED_GPIO_Port, ERROR_LED_Pin, SET);
	}
	else{
		HAL_GPIO_WritePin(ERROR_LED_GPIO_Port, ERROR_LED_Pin, RESET);
	}

	HAL_Delay(500);
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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 9600;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief UART5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART5_Init(void)
{

  /* USER CODE BEGIN UART5_Init 0 */

  /* USER CODE END UART5_Init 0 */

  /* USER CODE BEGIN UART5_Init 1 */

  /* USER CODE END UART5_Init 1 */
  huart5.Instance = UART5;
  huart5.Init.BaudRate = 115200;
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  huart5.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart5.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART5_Init 2 */

  /* USER CODE END UART5_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BUTTON8_LED_GPIO_Port, BUTTON8_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, BUTTON7_LED_Pin|BUTTON3_LED_Pin|BUTTON4_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, BUTTON6_LED_Pin|BUTTON5_LED_Pin|BUTTON1_LED_Pin|BUTTON2_LED_Pin
                          |OK_LED_Pin|ERROR_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : BUTTON8_Pin BUTTON7_Pin */
  GPIO_InitStruct.Pin = BUTTON8_Pin|BUTTON7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON8_LED_Pin */
  GPIO_InitStruct.Pin = BUTTON8_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(BUTTON8_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BUTTON7_LED_Pin BUTTON3_LED_Pin BUTTON4_LED_Pin */
  GPIO_InitStruct.Pin = BUTTON7_LED_Pin|BUTTON3_LED_Pin|BUTTON4_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON6_Pin */
  GPIO_InitStruct.Pin = BUTTON6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BUTTON6_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BUTTON6_LED_Pin BUTTON5_LED_Pin BUTTON1_LED_Pin BUTTON2_LED_Pin
                           OK_LED_Pin ERROR_LED_Pin */
  GPIO_InitStruct.Pin = BUTTON6_LED_Pin|BUTTON5_LED_Pin|BUTTON1_LED_Pin|BUTTON2_LED_Pin
                          |OK_LED_Pin|ERROR_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : BUTTON5_Pin BUTTON1_Pin BUTTON2_Pin */
  GPIO_InitStruct.Pin = BUTTON5_Pin|BUTTON1_Pin|BUTTON2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : BUTTON3_Pin BUTTON4_Pin */
  GPIO_InitStruct.Pin = BUTTON3_Pin|BUTTON4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	uint32_t currentTime;

	if (GPIO_Pin == BUTTON1_Pin) { /// fan
		currentTime = HAL_GetTick();

	    if ((currentTime - lastButtonPressTime[0]) > DEBOUNCE_THRESHOLD) {
	    	lastButtonPressTime[0] = currentTime;  // Update last press time

	        if (HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin) == GPIO_PIN_RESET) {
	          buttonStates ^= 0b00000001;
	        }

          if (buttonStates & 0b00000001) 
        	  HAL_GPIO_WritePin(BUTTON1_LED_GPIO_Port, BUTTON1_LED_Pin, GPIO_PIN_SET);
          else 
        	  HAL_GPIO_WritePin(BUTTON1_LED_GPIO_Port, BUTTON1_LED_Pin, GPIO_PIN_RESET);
          
	    }
	}
	if (GPIO_Pin == BUTTON2_Pin) { // display
		currentTime = HAL_GetTick();

		if ((currentTime - lastButtonPressTime[1]) > DEBOUNCE_THRESHOLD) {
			lastButtonPressTime[1] = currentTime;  // Update last press time

		    if (HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin) == GPIO_PIN_RESET) {
		    	buttonStates ^= 0b00000010;
		    }

          if (buttonStates & 0b00000010) 
        	  HAL_GPIO_WritePin(BUTTON2_LED_GPIO_Port, BUTTON2_LED_Pin, GPIO_PIN_SET);
          else 
        	  HAL_GPIO_WritePin(BUTTON2_LED_GPIO_Port, BUTTON2_LED_Pin, GPIO_PIN_RESET);
		}
	}

	if (GPIO_Pin == BUTTON3_Pin) { // hazards
		currentTime = HAL_GetTick();

		if ((currentTime - lastButtonPressTime[2]) > DEBOUNCE_THRESHOLD) {
			lastButtonPressTime[2] = currentTime;  // Update last press time

			if (HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin) == GPIO_PIN_RESET) {
				buttonStates ^= 0b00000100;
        buttonStates &= 0b11110111; // turn off left turn
        buttonStates &= 0b01111111; // turn off right turn
			}

          if (buttonStates & 0b00000100) {
        	  HAL_GPIO_WritePin(BUTTON3_LED_GPIO_Port, BUTTON3_LED_Pin, GPIO_PIN_SET);
            // turn off left and right turn lights
            HAL_GPIO_WritePin(BUTTON4_LED_GPIO_Port, BUTTON4_LED_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(BUTTON8_LED_GPIO_Port, BUTTON8_LED_Pin, GPIO_PIN_RESET);
          }
          else 
        	  HAL_GPIO_WritePin(BUTTON3_LED_GPIO_Port, BUTTON3_LED_Pin, GPIO_PIN_RESET);
		}
	}

	if (GPIO_Pin == BUTTON4_Pin) { // left turn
		currentTime = HAL_GetTick();

		if ((currentTime - lastButtonPressTime[3]) > DEBOUNCE_THRESHOLD) {
			lastButtonPressTime[3] = currentTime;  // Update last press time

			if (HAL_GPIO_ReadPin(BUTTON4_GPIO_Port, BUTTON4_Pin) == GPIO_PIN_RESET) {
				buttonStates ^= 0b00001000;
				buttonStates &= 0b01111111; // turn off right turn
        buttonStates &= 0b11111011; // turn off hazards
			}

          if (buttonStates & 0b00001000) {
        	  HAL_GPIO_WritePin(BUTTON4_LED_GPIO_Port, BUTTON4_LED_Pin, GPIO_PIN_SET);
            // turn off right turn light
            HAL_GPIO_WritePin(BUTTON8_LED_GPIO_Port, BUTTON8_LED_Pin, GPIO_PIN_RESET);
            // turn off hazards
            HAL_GPIO_WritePin(BUTTON3_LED_GPIO_Port, BUTTON3_LED_Pin, GPIO_PIN_RESET);
          }
          else 
        	  HAL_GPIO_WritePin(BUTTON4_LED_GPIO_Port, BUTTON4_LED_Pin, GPIO_PIN_RESET);
		}
	}

	if (GPIO_Pin == BUTTON7_Pin) { // headlights
		currentTime = HAL_GetTick();

		if ((currentTime - lastButtonPressTime[6]) > DEBOUNCE_THRESHOLD) {
			lastButtonPressTime[6] = currentTime;  // Update last press time

			if (HAL_GPIO_ReadPin(BUTTON7_GPIO_Port, BUTTON7_Pin) == GPIO_PIN_RESET) {
				buttonStates ^= 0b01000000;

			}
          if (buttonStates & 0b01000000) 
        	  HAL_GPIO_WritePin(BUTTON7_LED_GPIO_Port, BUTTON7_LED_Pin, GPIO_PIN_SET);
          else 
        	  HAL_GPIO_WritePin(BUTTON7_LED_GPIO_Port, BUTTON7_LED_Pin, GPIO_PIN_RESET);
		}
	}

	if (GPIO_Pin == BUTTON8_Pin) { // right turn
		currentTime = HAL_GetTick();

		if ((currentTime - lastButtonPressTime[7]) > DEBOUNCE_THRESHOLD) {
			lastButtonPressTime[7] = currentTime;  // Update last press time

			if (HAL_GPIO_ReadPin(BUTTON8_GPIO_Port, BUTTON8_Pin) == GPIO_PIN_RESET) {
				buttonStates ^= 0b10000000;
				buttonStates &= 0b11110111; // turn of left turn
        buttonStates &= 0b11111011; // turn off hazards
			}
          if (buttonStates & 0b10000000) {
        	  HAL_GPIO_WritePin(BUTTON8_LED_GPIO_Port, BUTTON8_LED_Pin, GPIO_PIN_SET);
            // turn off left turn light
            HAL_GPIO_WritePin(BUTTON4_LED_GPIO_Port, BUTTON4_LED_Pin, GPIO_PIN_RESET);
            // turn off hazards
            HAL_GPIO_WritePin(BUTTON3_LED_GPIO_Port, BUTTON3_LED_Pin, GPIO_PIN_RESET);
          }
          else 
        	  HAL_GPIO_WritePin(BUTTON8_LED_GPIO_Port, BUTTON8_LED_Pin, GPIO_PIN_RESET);
		}
	}





}
/* USER CODE END 4 */

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
