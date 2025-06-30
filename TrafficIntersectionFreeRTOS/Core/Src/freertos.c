/* USER CODE BEGIN Header */
	/**
		******************************************************************************
		* File Name          : freertos.c
		* Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "gpio.h"
#include "trafficTypes.h"
#include "spiCommunication.h"
#include "intersection.h"
#include "../Inc/Logic/pedestrianLogic.h"
#include "../Inc/Logic/carLogic.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
/* USER CODE BEGIN Variables */
osMutexId_t pedestrianMutex;
osMutexId_t carSignalMutex;
osMutexId_t intersectionMutex;
IntersectionController intersection;
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
	.name = "defaultTask",
	.stack_size = 128 * 4,
	.priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for pedestrianTask */
osThreadId_t pedestrianTaskHandle;
const osThreadAttr_t pedestrianTask_attributes = {
	.name = "pedestrianTask",
	.stack_size = 128 * 4,
	.priority = (osPriority_t) osPriorityLow,
};
/* Definitions for carTask */
osThreadId_t carTaskHandle;
const osThreadAttr_t carTask_attributes = {
	.name = "carTask",
	.stack_size = 128 * 4,
	.priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void pedestrianLogicTask(void *argument);
void carLogicTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
	* @brief  FreeRTOS initialization
	* @param  None
	* @retval None
	*/
void MX_FREERTOS_Init(void) {
	/* USER CODE BEGIN Init */
		initializeRegisters();
		initIntersectionState(&intersection);
	/* USER CODE END Init */

	/* USER CODE BEGIN RTOS_MUTEX */
	intersectionMutex = osMutexNew(NULL);
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
	/* creation of defaultTask */
	defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

	/* creation of pedestrianTask */
	pedestrianTaskHandle = osThreadNew(pedestrianLogicTask, NULL, &pedestrianTask_attributes);

	/* creation of carTask */
	carTaskHandle = osThreadNew(carLogicTask, NULL, &carTask_attributes);

	/* USER CODE BEGIN RTOS_THREADS */
		/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* USER CODE BEGIN RTOS_EVENTS */
		/* add events, ... */
	/* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
	/**
		* @brief  Function implementing the defaultTask thread.
		* @param  argument: Not used
		* @retval None
		*/
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
	/* USER CODE BEGIN StartDefaultTask */
	/* Infinite loop */
	for(;;)
	{
	HAL_GPIO_TogglePin(GPIOB, LED26_Pin);
	osDelay(100);
	}
	/* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_pedestrianLogicTask */
/**
* @brief Function implementing the pedestrianTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_pedestrianLogicTask */
void pedestrianLogicTask(void *argument)
{
	/* USER CODE BEGIN pedestrianLogicTask */
	/* Infinite loop */
	for(;;)
	{
		osMutexAcquire(intersectionMutex, osWaitForever);
		pedestrianLogic(&intersection.pedestrianStateVertical,
			&intersection.pedestrianStateHorizontal,
			&intersection.carSignalState.currentState);
		osMutexRelease(intersectionMutex);
		osDelay(10);
	}
	/* USER CODE END pedestrianLogicTask */
}

/* USER CODE BEGIN Header_carLogicTask */
/**
* @brief Function implementing the carTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_carLogicTask */
void carLogicTask(void *argument)
{
	/* USER CODE BEGIN carLogicTask */
	/* Infinite loop */
	for(;;)
	{
		osMutexAcquire(intersectionMutex, osWaitForever);
		taskCarSignalLogic(&intersection.carSignalState, intersection.pedestrianStateVertical.currentState, intersection.pedestrianStateHorizontal.currentState);
		osMutexRelease(intersectionMutex);
		osDelay(10);
	}
	/* USER CODE END carLogicTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
