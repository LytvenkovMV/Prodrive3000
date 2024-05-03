
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2020 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */

#include "period_config.h"
#include "input.h"
#include "button.h"
#include "encoder.h"
#include "hmi.h"
#include "display.h"
#include "motor.h"
#include "protection.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;
DMA_HandleTypeDef hdma_adc1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart3;
DMA_HandleTypeDef hdma_usart3_rx;

osThreadId HmiTaskHandle;
osThreadId MotorTaskHandle;
osMessageQId MotorDataQueueHandle;
osMessageQId MotorTargetQueueHandle;
osMessageQId CurrentsQueueHandle;
osMessageQId SettingQueueHandle;
osMessageQId PWMQueueHandle;
osMessageQId RXDataQueueHandle;
osSemaphoreId PhaseOverCurrentSemHandle;
osSemaphoreId PhaseCurrentRiseSemHandle;
osSemaphoreId DCOverCurrentSemHandle;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* Variables for current measure */
uint32_t glCurrentsSendingCnt = 0;
uint32_t const glCurrentsSendingPeriod = PERIOD_CONF_CURRENTS_SENDING_MS;
SENSOR_ADCvalues glADCvalues;
SENSOR_CurrentsStruct glCurrents;
SENSOR_InstCurrents glInstCurrents;
uint16_t glUpperThrdIL1 = 1;
uint16_t glUpperThrdIL3 = 1;

/* Variables for USART */
SENSOR_RXData glRXData;

/* Variables for PWM algorithm */
uint8_t glSectorNumber = 1;
float gltheta1 = 0;



/************************************** TEMP VARIABLES **************************************/
SENSOR_Values glSensorValues;
PROTECTION_Counters glProtCounters;
PROTECTION_ThermalData glThermalData;

MOTOR_State glMotorState;
MOTOR_PWMData glPWMData;





/********************************************************************************************/



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_TIM1_Init(void);
static void MX_ADC2_Init(void);
static void MX_TIM4_Init(void);
void Hmi(void const * argument);
void Motor(void const * argument);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
                                

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* External interrupt line detection callback */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

/* ADC conversion complete callback in non blocking mode */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);

/* Period elapsed callback in non blocking mode */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

/*Rx Transfer completed callback */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

/* UART error callback */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_ADC1_Init();
  MX_USART3_UART_Init();
  MX_TIM1_Init();
  MX_ADC2_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of PhaseOverCurrentSem */
  osSemaphoreDef(PhaseOverCurrentSem);
  PhaseOverCurrentSemHandle = osSemaphoreCreate(osSemaphore(PhaseOverCurrentSem), 1);

  /* definition and creation of PhaseCurrentRiseSem */
  osSemaphoreDef(PhaseCurrentRiseSem);
  PhaseCurrentRiseSemHandle = osSemaphoreCreate(osSemaphore(PhaseCurrentRiseSem), 1);

  /* definition and creation of DCOverCurrentSem */
  osSemaphoreDef(DCOverCurrentSem);
  DCOverCurrentSemHandle = osSemaphoreCreate(osSemaphore(DCOverCurrentSem), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of HmiTask */
  osThreadDef(HmiTask, Hmi, osPriorityNormal, 0, 512);
  HmiTaskHandle = osThreadCreate(osThread(HmiTask), NULL);

  /* definition and creation of MotorTask */
  osThreadDef(MotorTask, Motor, osPriorityHigh, 0, 1024);
  MotorTaskHandle = osThreadCreate(osThread(MotorTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the queue(s) */
  /* definition and creation of MotorDataQueue */
/* what about the sizeof here??? cd native code */
  osMessageQDef(MotorDataQueue, 1, MOTOR_Data);
  MotorDataQueueHandle = osMessageCreate(osMessageQ(MotorDataQueue), NULL);

  /* definition and creation of MotorTargetQueue */
/* what about the sizeof here??? cd native code */
  osMessageQDef(MotorTargetQueue, 1, MOTOR_Target);
  MotorTargetQueueHandle = osMessageCreate(osMessageQ(MotorTargetQueue), NULL);

  /* definition and creation of CurrentsQueue */
/* what about the sizeof here??? cd native code */
  osMessageQDef(CurrentsQueue, 1, SENSOR_InstCurrents);
  CurrentsQueueHandle = osMessageCreate(osMessageQ(CurrentsQueue), NULL);

  /* definition and creation of SettingQueue */
/* what about the sizeof here??? cd native code */
  osMessageQDef(SettingQueue, 1, SETTING_Values);
  SettingQueueHandle = osMessageCreate(osMessageQ(SettingQueue), NULL);

  /* definition and creation of PWMQueue */
/* what about the sizeof here??? cd native code */
  osMessageQDef(PWMQueue, 1, MOTOR_PWMData);
  PWMQueueHandle = osMessageCreate(osMessageQ(PWMQueue), NULL);

  /* definition and creation of RXDataQueue */
/* what about the sizeof here??? cd native code */
  osMessageQDef(RXDataQueue, 1, SENSOR_RXData);
  RXDataQueueHandle = osMessageCreate(osMessageQ(RXDataQueue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
 

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

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV2;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Enables the Clock Security System 
    */
  HAL_RCC_EnableCSS();

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

/* ADC1 init function */
static void MX_ADC1_Init(void)
{

  ADC_MultiModeTypeDef multimode;
  ADC_ChannelConfTypeDef sConfig;

    /**Common config 
    */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 2;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the ADC multi-mode 
    */
  multimode.Mode = ADC_DUALMODE_REGSIMULT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel 
    */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel 
    */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* ADC2 init function */
static void MX_ADC2_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;

    /**Common config 
    */
  hadc2.Instance = ADC2;
  hadc2.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.NbrOfConversion = 2;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel 
    */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure Regular Channel 
    */
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM1 init function */
static void MX_TIM1_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_CENTERALIGNED3;
  htim1.Init.Period = 0;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 1;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_LOW;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 72;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_TIM_MspPostInit(&htim1);

}

/* TIM4 init function */
static void MX_TIM4_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 0;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART3 init function */
static void MX_USART3_UART_Init(void)
{

  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 10, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  /* DMA1_Channel3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BO1_GPIO_Port, BO1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LE0_Pin|LE1_Pin|LE2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, OE2_Pin|OE1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : BO1_Pin */
  GPIO_InitStruct.Pin = BO1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(BO1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LE0_Pin LE1_Pin LE2_Pin */
  GPIO_InitStruct.Pin = LE0_Pin|LE1_Pin|LE2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : D4_Pin D3_Pin D2_Pin D5_Pin 
                           D6_Pin D7_Pin */
  GPIO_InitStruct.Pin = D4_Pin|D3_Pin|D2_Pin|D5_Pin 
                          |D6_Pin|D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : D0_Pin D1_Pin */
  GPIO_InitStruct.Pin = D0_Pin|D1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : OE2_Pin OE1_Pin */
  GPIO_InitStruct.Pin = OE2_Pin|OE1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	/* Private variables */
	static portBASE_TYPE xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;

	/* External over current protection */
	/* If interrupt from pin 12 */
	if (GPIO_Pin == GPIO_PIN_12)
	{


















		/* Stop modulator and give over current semaphore */
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////MOTOR_StopPWM(&htim1);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////xSemaphoreGiveFromISR(DCOverCurrentSemHandle, &xHigherPriorityTaskWoken);





















	}
}



void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	/* Private variables */
	static portBASE_TYPE xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;

	PROTECTION_State ProtectionState1 = PROTECTION_TRIPPED, ProtectionState2 = PROTECTION_TRIPPED, ProtectionState3 = PROTECTION_TRIPPED, ProtectionState4 = PROTECTION_TRIPPED;

	/* If ADC1 conversion complete */
	if (hadc->Instance == ADC1)
	{
		/* Stop ADC */
		SENSOR_StopADC(&hadc1, &hadc2);

		/* Calculate instantaneous currents */
		SENSOR_CalculateInstCurrents(&glADCvalues, &glCurrents);

		/* Perform over current protection function for phase L1 and L3 */
		ProtectionState1 = PROTECTION_OverCurrent(glCurrents.currIL1, glUpperThrdIL1);
		ProtectionState2 = PROTECTION_OverCurrent(glCurrents.currIL3, glUpperThrdIL3);

		/* If protection tripped */
		if ((ProtectionState1 == PROTECTION_TRIPPED) || (ProtectionState2 == PROTECTION_TRIPPED))
		{
			/* Stop PWM and give semaphore */
			MOTOR_StopPWM(&htim1);
			xSemaphoreGiveFromISR(PhaseOverCurrentSemHandle, &xHigherPriorityTaskWoken);
		}
		else
		{
			/* Perform current rise protection function for phase L1 and L3 */
			ProtectionState3 = PROTECTION_CurrentRise(glCurrents.currIL1, glCurrents.prevIL1, PROT_CONF_CURRENT_RISE_LIMIT);
			ProtectionState4 = PROTECTION_CurrentRise(glCurrents.currIL3, glCurrents.prevIL3, PROT_CONF_CURRENT_RISE_LIMIT);

			/* If protection tripped */
			if ((ProtectionState3 == PROTECTION_TRIPPED) || (ProtectionState4 == PROTECTION_TRIPPED))
			{
				/* Stop PWM and give semaphore */
				MOTOR_StopPWM(&htim1);
				xSemaphoreGiveFromISR(PhaseCurrentRiseSemHandle, &xHigherPriorityTaskWoken);
			}
			else
			{
				/* Shift instantaneous currents buffer */
				for (uint16_t i = 0; i < (SENSOR_INST_CURR_BUFFER_SIZE - 1); i ++)
				{
					glInstCurrents.bufferIL1[i] = glInstCurrents.bufferIL1[i + 1];
					glInstCurrents.bufferIL3[i] = glInstCurrents.bufferIL3[i + 1];
				}

				/* Fill in last buffers element */
				glInstCurrents.Status = glCurrents.Status;
				glInstCurrents.bufferIL1[SENSOR_INST_CURR_BUFFER_SIZE - 1] = glCurrents.currIL1;
				glInstCurrents.bufferIL3[SENSOR_INST_CURR_BUFFER_SIZE - 1] = glCurrents.currIL3;

				/* If currents sending time has elapsed */
				if (glCurrentsSendingCnt >= glCurrentsSendingPeriod)
				{
					/* Send instantaneous currents to the queue */
					xQueueOverwriteFromISR(CurrentsQueueHandle, &glInstCurrents, &xHigherPriorityTaskWoken);

					glCurrentsSendingCnt = 0;
				}
				else glCurrentsSendingCnt ++;
			}
		}
	}
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	/* Private variables */
	static portBASE_TYPE xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;

	/* Send RXData to the queue */
	xQueueOverwriteFromISR(RXDataQueueHandle, &glRXData, &xHigherPriorityTaskWoken);
}



void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	/* Enable UART again */
	HAL_UART_Receive_DMA(&huart3, (uint8_t *)&glRXData, 5);
}

/* USER CODE END 4 */

/* Hmi function */
void Hmi(void const * argument)
{

  /* USER CODE BEGIN 5 */

	/* Create variable needed for the system function vTaskDelayUntil() */
	portTickType xLastWakeTime;

	/* Create private variables */
	portBASE_TYPE xMotorStateQueueStatus;
	INPUT_States InputStates;
	BUTTON_States ButtonStates;
	BUTTON_Counters ButtonCounters;
	BUTTON_Settings ButtonSettings;
	BUTTON_SafetyState SafetyState = BUTTON_SAFETY_RELEASED;
	BUTTON_LimitState FwdLimitState = BUTTON_LIMIT_RELEASED, RevLimitState = BUTTON_LIMIT_RELEASED;
	BUTTON_Direction ButtonDirection = BUTTON_FORWARD;
	BUTTON_Command ButtonCommand;
	BUTTON_Status ButtonStatus = BUTTON_NOT_CHANGED;
	ENCODER_Data EncoderData;
	ENCODER_Command EncoderCommand;
	ENCODER_Status EncoderStatus = ENCODER_NOT_CHANGED;
	MOTOR_Data MotorData;
	MOTOR_Target MotorTarget;
	SETTING_Values SettingValues;
	HMI_Status HMIStatus;
	RELAY_Data RelayData;

	/* Clear screen */
	DISPLAY_ShowEmptyScreen();

	/* Load settings */
	SETTING_Load(&SettingValues);

	/* Initialize buttons and encoder */
	BUTTON_Init(&ButtonStates, &ButtonCounters, &ButtonSettings, &InputStates, &SettingValues);
	ENCODER_Init(&EncoderData, &InputStates);

	/* Initialize HMI */
	HMI_Init(&HMIStatus, &SettingValues, &MotorTarget);

	/* Initialize relay */
	RELAY_Init(&RelayData, &SettingValues, PERIOD_CONF_HMI_TASK_MS);

	/* Send setting values to the queue */
	xQueueOverwrite(SettingQueueHandle, &SettingValues);

	/* Send motor target to the queue */
	xQueueOverwrite(MotorTargetQueueHandle, &MotorTarget);

	/* Wait for the main board to load */
	osDelay(5000);


	/* !!!!! Start of code that contains a critical section !!!!! */
	/* Scan inputs */
	INPUT_Scan(&InputStates);
	/* !!!!! End of code that contains a critical section !!!!! */


	osDelay(PERIOD_CONF_HMI_TASK_MS);

	xLastWakeTime = xTaskGetTickCount();

	/* Infinite loop */
	for(;;)
	{
		/* If drive is OK */
		if (HMIStatus.DriveState == HMI_DRIVE_OK)
		{


			/* !!!!! Start of code that contains a critical section !!!!! */
			/* Scan inputs */
			INPUT_Scan(&InputStates);
			/* !!!!! End of code that contains a critical section !!!!! */


			/* If drive in working mode */
			if (HMIStatus.SetupMode == HMI_WORK)
			{
				/************************************************* HANDLE SAFETY CONTACT ************************************************/
				/* Update button states */
				BUTTON_UpdateStates(&ButtonStates, &InputStates);

				/* Get safety contact state */
				SafetyState = BUTTON_GetSafetyState(&ButtonStates, &ButtonSettings);

				/* If safety contact not released */
				if (SafetyState != BUTTON_SAFETY_RELEASED)
				{
					/* Prepare and send motor target */
					MotorTarget.Mode = MOTOR_STOP_FAST;
					MotorTarget.speed = 0;
					xQueueOverwrite(MotorTargetQueueHandle, &MotorTarget);

					/* Switch to failure state */
					HMI_SwitchToFailure(&HMIStatus, MESSAGE_01);
				}
				/************************************************************************************************************************/



				/*************************************************** HANDLE MOTOR DATA **************************************************/
				/* If motor data time has elapsed */
				if (HMIStatus.motorDataCnt >= HMIStatus.motorDataPeriod)
				{
					HMIStatus.motorDataCnt = 0;

					/* Receive motor data from the motor control process */
					xMotorStateQueueStatus = xQueueReceive(MotorDataQueueHandle, &MotorData, 5);

					/* If can't receive motor data */
					if (xMotorStateQueueStatus != pdPASS)
					{
						/* Prepare and send motor target */
						MotorTarget.Mode = MOTOR_STOP_FREERUN;
						MotorTarget.speed = 0;
						xQueueOverwrite(MotorTargetQueueHandle, &MotorTarget);

						/* Switch to failure state */
						HMI_SwitchToFailure(&HMIStatus, MESSAGE_21);
					}
					else
					{
						/* If data is received and there is motor failure switch to failure state */
						if (MotorData.HealthState != MOTOR_OK) HMI_SwitchToFailure(&HMIStatus, (MotorData.MessageID));
					}
				}
				else HMIStatus.motorDataCnt ++;
				/************************************************************************************************************************/



				/************************************************ GET LIMIT CONTACT STATES **********************************************/
				/* Get forward limit contact state */
				FwdLimitState = BUTTON_GetFwdLimitState(&ButtonStates, &ButtonSettings);

				/* Get reverse limit contact state */
				RevLimitState = BUTTON_GetRevLimitState(&ButtonStates, &ButtonSettings);
				/************************************************************************************************************************/
			}

			/* If drive is OK */
			if (HMIStatus.DriveState == HMI_DRIVE_OK)
			{
				/*************************************************** HANDLE BUTTONS *****************************************************/
				/* If drive in working mode */
				if (HMIStatus.SetupMode == HMI_WORK)
				{
					/* Update mechanism movement direction */
					if (MotorData.MotorDirection == MOTOR_REVERSE) ButtonDirection = BUTTON_REVERSE;
					else ButtonDirection = BUTTON_FORWARD;

					/* Get command from buttons and handle it */
					ButtonStatus = BUTTON_GetCommand(&ButtonCommand, &ButtonStates, &ButtonCounters, ButtonDirection, &ButtonSettings);
					if (ButtonStatus == BUTTON_CHANGED) HMI_HandleButtons(ButtonCommand, &HMIStatus, &SettingValues, &MotorTarget);
				}
				/************************************************************************************************************************/



				/*************************************************** HANDLE ENCODER *****************************************************/
				/* Get command from encoder and handle it */
				EncoderStatus = ENCODER_GetCommand(&EncoderCommand, &EncoderData, &InputStates);
				if (EncoderStatus == ENCODER_CHANGED) HMI_HandleEncoder(EncoderCommand, &HMIStatus, &SettingValues, MotorData, &MotorTarget);
				/************************************************************************************************************************/



				/* Prepare and send motor target if necessary */
				if (HMIStatus.MotorUpdate == HMI_UPDATE_REQUIRED)
				{
					/* Update target settings if necessary */
					if (HMIStatus.SettingStatus != HMI_SETTING_UP_TO_DATE)
					{
						MotorTarget.accTime = (uint16_t)SETTING_GetValue(SETTING_ARRAY_01, 1, &SettingValues);
						MotorTarget.decTime = (uint16_t)SETTING_GetValue(SETTING_ARRAY_01, 2, &SettingValues);

						HMIStatus.SettingStatus = HMI_SETTING_UP_TO_DATE;
					}

					/* Send motor target to the queue */
					xQueueOverwrite(MotorTargetQueueHandle, &MotorTarget);

					HMIStatus.MotorUpdate = HMI_UPDATE_NOT_REQUIRED;
				}
			}
		}



		/**************************************************** HANDLE RELAY ******************************************************/

		HMI_HandleRelay(&HMIStatus, &MotorData, SafetyState, FwdLimitState, RevLimitState, &RelayData, &SettingValues);

		/************************************************************************************************************************/



		/************************************************** UPDATE DISPLAY ***************************************************/
		/* If display time has elapsed */
		if (HMIStatus.displayCnt >= HMIStatus.displayPeriod)
		{
			HMIStatus.displayCnt = 0;

			/* If menu opened update display every cycle */
			if (HMIStatus.ScreenType == HMI_MENU_SCREEN) HMIStatus.DisplayUpdate = HMI_UPDATE_REQUIRED;

			/* Update display if necessary */
			if (HMIStatus.DisplayUpdate == HMI_UPDATE_REQUIRED)
			{
				DISPLAY_Update(&HMIStatus, &SettingValues, &(MotorData.SensorHMIValues));
				HMIStatus.DisplayUpdate = HMI_UPDATE_NOT_REQUIRED;
			}
		}
		else HMIStatus.displayCnt ++;
		/*********************************************************************************************************************/

		osDelayUntil(&xLastWakeTime, PERIOD_CONF_HMI_TASK_MS);
	}

  /* USER CODE END 5 */ 
}

/* Motor function */
void Motor(void const * argument)
{
  /* USER CODE BEGIN Motor */

	/* Create variable needed for the system function vTaskDelayUntil() */
	portTickType xLastWakeTime;

	/* Create private variables */
	portBASE_TYPE xPhaseOverCurrentSemStatus = pdPASS, xPhaseCurrentRiseSemStatus = pdPASS, xDCOverCurrentSemStatus = pdPASS;
	SETTING_Values SettingValues;
	SENSOR_Values SensorValues;
	MESSAGE_ID MessageID = MESSAGE_01;
	PROTECTION_Counters ProtectionCounters;
	PROTECTION_ThermalData ThermalData;
	PROTECTION_State ProtectionState = PROTECTION_TRIPPED;
	MOTOR_State MotorState;
	MOTOR_Data MotorData;
	MOTOR_Target MotorTarget;
	MOTOR_PWMData PWMData;
	MOTOR_UpdatingStatus UpdatingStatus = MOTOR_UPDATING_FAIL;
	uint8_t initCnt = 0;

	/* Get setting values */
	xQueuePeek(SettingQueueHandle, &SettingValues, portMAX_DELAY);

	/* Get motor target */
	xQueuePeek(MotorTargetQueueHandle, &MotorTarget, portMAX_DELAY);

	/* Initialize variables */
	MOTOR_Init(&MotorState, &MotorData, &MotorTarget, &PWMData, &SettingValues);
	PROTECTION_Init(&ProtectionCounters, &ThermalData, &SettingValues);

	/* Enable USART */
	HAL_UART_Receive_DMA(&huart3, (uint8_t *)&glRXData, 5);

	/* Initialize current upper threshold */
	glUpperThrdIL1 = MOTOR_CalcCurrentUpperThrd(&SettingValues, SENSOR_ADC1_COEFF);
	glUpperThrdIL3 = MOTOR_CalcCurrentUpperThrd(&SettingValues, SENSOR_ADC2_COEFF);

	/* Calibrate ADC */
	osDelay(500);
	SENSOR_CalibrateADC(&hadc1, &hadc2);
	osDelay(500);

	/* Initialize and start timer used to drive the ADC */
	MOTOR_InitADCTimer(&htim4);
	HAL_TIM_Base_Start_IT(&htim4);
	osDelay(PERIOD_CONF_MOTOR_TASK_MS);

	/* Initialize timer used for PWM */
	MOTOR_InitPWMTimer(&htim1, MotorState.arrRegister);

	/* Reset semaphores */
	xSemaphoreTake(PhaseOverCurrentSemHandle, portMAX_DELAY);
	xSemaphoreTake(PhaseCurrentRiseSemHandle, portMAX_DELAY);
	xSemaphoreTake(DCOverCurrentSemHandle, portMAX_DELAY);

	/* Wait for main board initialize */
	osDelay(500);

	/* Update sensor values 128 times in order to fill in buffers of instantaneous values */
	do
	{
		UpdatingStatus = MOTOR_UpdateSensorValues(&SensorValues, &MotorState, &MessageID, CurrentsQueueHandle, RXDataQueueHandle);

		if (UpdatingStatus == MOTOR_UPDATING_OK) initCnt ++;

		osDelay(PERIOD_CONF_MOTOR_TASK_MS);
	}
	while (initCnt < 128);

	xLastWakeTime = xTaskGetTickCount();

	for(;;)
	{
		/* If motor OK */
		if (MotorData.HealthState == MOTOR_OK)
		{
			/* Try to take current protection semaphores */
			xPhaseOverCurrentSemStatus = xSemaphoreTake(PhaseOverCurrentSemHandle, 0);
			xPhaseCurrentRiseSemStatus = xSemaphoreTake(PhaseCurrentRiseSemHandle, 0);
			xDCOverCurrentSemStatus = xSemaphoreTake(DCOverCurrentSemHandle, 0);

			/* If phase over current semaphore is taken */
			if (xPhaseOverCurrentSemStatus != pdFALSE)
			{
				/* Stop PWM immediately */
				MOTOR_StopPWM(&htim1);

				/* Switch to failure state */
				MotorState.HealthState = MOTOR_FAILURE;
				MotorState.MessageID = MESSAGE_02;

				/* Update motor data and send it to the queue */
				MOTOR_UpdateData(&MotorData, &MotorState, &SensorValues, ThermalData.TCU);
				xQueueOverwrite(MotorDataQueueHandle, &MotorData);
			}

			/* If phase current rise semaphore is taken */
			else if (xPhaseCurrentRiseSemStatus != pdFALSE)
			{
				/* Stop PWM immediately */
				MOTOR_StopPWM(&htim1);

				/* Switch to failure state */
				MotorState.HealthState = MOTOR_FAILURE;
				MotorState.MessageID = MESSAGE_03;

				/* Update motor data and send it to the queue */
				MOTOR_UpdateData(&MotorData, &MotorState, &SensorValues, ThermalData.TCU);
				xQueueOverwrite(MotorDataQueueHandle, &MotorData);
			}

			/* If DC current rise semaphore is taken */
			else if (xDCOverCurrentSemStatus != pdFALSE)
			{
				/* Stop PWM immediately */
				MOTOR_StopPWM(&htim1);

				/* Switch to failure state */
				MotorState.HealthState = MOTOR_FAILURE;
				MotorState.MessageID = MESSAGE_04;

				/* Update motor data and send it to the queue */
				MOTOR_UpdateData(&MotorData, &MotorState, &SensorValues, ThermalData.TCU);
				xQueueOverwrite(MotorDataQueueHandle, &MotorData);
			}

			/* If no one semaphore is taken */
			else
			{
				/* Update sensor values */
				UpdatingStatus = MOTOR_UpdateSensorValues(&SensorValues, &MotorState, &MessageID, CurrentsQueueHandle, RXDataQueueHandle);

				/* If updating fail */
				if (UpdatingStatus != MOTOR_UPDATING_OK)
				{
					/* Stop PWM immediately */
					MOTOR_StopPWM(&htim1);

					/* Switch to failure state */
					MotorState.HealthState = MOTOR_FAILURE;
					MotorState.MessageID = MessageID;

					/* Update motor data and send it to the queue */
					MOTOR_UpdateData(&MotorData, &MotorState, &SensorValues, ThermalData.TCU);
					xQueueOverwrite(MotorDataQueueHandle, &MotorData);
				}
				else
				{
					/* Execute protection function */
					ProtectionState = PROTECTION_MotorProt(&ProtectionCounters, &ThermalData, &MessageID, &SensorValues);

					/* If protection not released */
					if (ProtectionState != PROTECTION_RELEASED)
					{
						/* Stop PWM immediately */
						MOTOR_StopPWM(&htim1);

						/* Switch to failure state */
						MotorState.HealthState = MOTOR_FAILURE;
						MotorState.MessageID = MessageID;

						/* Update motor data and send it to the queue */
						MOTOR_UpdateData(&MotorData, &MotorState, &SensorValues, ThermalData.TCU);
						xQueueOverwrite(MotorDataQueueHandle, &MotorData);
					}
					else
					{
						/* Get target and handle it */
						xQueuePeek(MotorTargetQueueHandle, &MotorTarget, 0);
						MOTOR_HandleTarget(&MotorState, &MotorTarget, &htim1);

						/* Calculate and send PWM data to the queue */
						MOTOR_CalcPWMData(&MotorState, &PWMData, SensorValues.meanVoltageDCfloat);
						xQueueOverwrite(PWMQueueHandle, &PWMData);

						/* Update motor data and send it to the queue */
						MOTOR_UpdateData(&MotorData, &MotorState, &SensorValues, ThermalData.TCU);
						xQueueOverwrite(MotorDataQueueHandle, &MotorData);
					}
				}
			}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/* Fill in temporary variables */
			glSensorValues = SensorValues;
			glProtCounters = ProtectionCounters;
			glThermalData = ThermalData;

			glMotorState = MotorState;
			glPWMData = PWMData;
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



			osDelayUntil(&xLastWakeTime, PERIOD_CONF_MOTOR_TASK_MS);
		}
		else
		{
			osDelay(1000);
		}
	}

  /* USER CODE END Motor */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM2 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM2) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

	/* If TIM4 period elapsed */
  	if (htim->Instance == TIM4)
	{
  		/* Start ADC */
		SENSOR_StartADC(&glADCvalues, &hadc1, &hadc2);
	}

	/* If TIM1 period elapsed */
  	if (htim->Instance == TIM1)
	{
		MOTOR_PWMData PWMData;
		PWMData.Direction = MOTOR_FORWARD;
		PWMData.angleStep = 0;
		PWMData.amplitudeMulBy1000 = 0;
		uint16_t ccr1 = 0, ccr2 = 0, ccr3 = 0;

  		/* Receive PWM data */
  		xQueuePeekFromISR(PWMQueueHandle, &PWMData);

  		/* Calculate CCR values */
  		MOTOR_CalcCCR(&PWMData, &glSectorNumber, &gltheta1, &ccr1, &ccr2, &ccr3);

  		/* Set compare registers */
  		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, ccr1);
  		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, ccr2);
  		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, ccr3);
	}

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
