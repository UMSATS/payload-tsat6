/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "adc.h"
#include "can.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lowlevel/max7300.h" 		// I/O Expander (I2C)
#include "lowlevel/tlv2553.h" 		// ADC (SPI)
#include "lowlevel/max6822.h"		// Watchdog/supervisor
#include "thermostats.h" 			// Well temperature readings
#include "heaters.h" 				// Well heater system
#include "leds.h"					// LEDs
#include "temperatures.h"			// Well temperature monitoring system

#include "can_message_queue.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define HIGH	1 // for GPIO
#define LOW		0
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t secondsCounter = 0;

// function to get temperature data, package it and send it through CAN
void TEMP_transmitTemperatureData(uint8_t wellID) {
	uint16_t temperatureReading = TEMP_getWellTemperatureReading(wellID);

	CANMessage_t message;

	message.SenderID = 0x3;
	message.DestinationID = 0x1;
	message.command = 0x34;
	message.priority = 0b0000011;

	message.data[0] = wellID;
	message.data[1] = wellID;
	message.data[2] = (temperatureReading & 0xFF00) >> 8;
	message.data[3] = temperatureReading & 0xFF;

	CAN_Transmit_Message(message);

}

// Interrupt handler for new CAN message
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan) {
	CAN_Message_Received(); // no error handling right now
}

// this SHOULD happen once per second. System clock = 4MHz, timer interval is 4000000.
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
	secondsCounter++;
	if (secondsCounter >= 60) {
		secondsCounter = 0;

		for (int i = 1; i < 11; i++) {
			TEMP_transmitTemperatureData(i);
		}

	}

}

CANQueue_t can_queue; // CAN Queue object

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
  MX_ADC1_Init();
  MX_CAN1_Init();
  MX_I2C1_Init();
  MX_SPI3_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  MAX7300_Init();
  CAN_Queue_Init(&can_queue);

  HAL_StatusTypeDef can_operation_status;
  can_operation_status = CAN_Init(); 		// defined in the custom can_driver file
  // if (can_operation_status != HAL_OK) goto error;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  MAX6822_Toggle_WDI();

	  if (!CAN_Queue_IsEmpty(&can_queue)) {
		  CANMessage_t can_message;
		  CAN_Queue_Dequeue(&can_queue, &can_message);

		  CANMessage_t response;

		  // these will be the same for every command
		  response.SenderID = 0x3; // PLD
		  response.DestinationID = 0x1; // CDH
		  response.command = 0x01; // ACK command code

		  uint8_t led_id, therm_id, heater_id;

		  switch (can_message.command) {
		      case 0xA0: // RESET command

		    	  CAN_Send_Default_ACK(can_message);

		          response.priority = 0x0;
		          response.data[0] = 0xA0;
		          CAN_Transmit_Message(response);

		          MAX6822_Manual_Reset();

		          break;

		      case 0xA1: // LED ON command

		    	  CAN_Send_Default_ACK(can_message);

		    	  led_id = can_message.data[0];

		    	  LED_enableLED(led_id);

		    	  response.priority = 0b0001111;
		    	  response.data[0] = 0xA1;
		    	  response.data[1] = led_id;
		    	  CAN_Transmit_Message(response);

				  break;

		      case 0xA2: // LED OFF command

		    	  CAN_Send_Default_ACK(can_message);

		    	  led_id = can_message.data[0];

		    	  LED_disableLED(led_id);

		    	  response.priority = 0b0000111;
		    	  response.data[0] = 0xA2;
		    	  response.data[1] = led_id;
		    	  CAN_Transmit_Message(response);

		          break;

		      case 0xA3: // THERMOREGULATION ON command

		    	  CAN_Send_Default_ACK(can_message);

		    	  therm_id = can_message.data[0];

		    	  THERM_enableThermostat(therm_id);

		    	  response.priority = 0b0000011;
		    	  response.data[0] = 0xA3;
		    	  response.data[1] = therm_id;
		    	  CAN_Transmit_Message(response);

		          break;

		      case 0xA4: // THERMOREGULATION OFF COMMAND

		    	  CAN_Send_Default_ACK(can_message);

		    	  therm_id = can_message.data[0];

		    	  THERM_disableThermostat(therm_id);

		    	  response.priority = 0b0000001;
		    	  response.data[0] = 0xA4;
		    	  response.data[1] = therm_id;
		    	  CAN_Transmit_Message(response);

		          break;

		      case 0xA5: // HEAT ON command

		    	  CAN_Send_Default_ACK(can_message);

		    	  heater_id = can_message.data[0];

		    	  HEAT_enableHeater(heater_id);

		    	  response.priority = 0b0000011;
		    	  response.data[0] = 0xA5;
		    	  response.data[1] = heater_id;
		    	  CAN_Transmit_Message(response);

		          break;

		      case 0xA6: // HEATER OFF command

		    	  CAN_Send_Default_ACK(can_message);

		    	  heater_id = can_message.data[0];

		    	  HEAT_disableHeater(heater_id);

		    	  response.priority = 0b0000001;
		    	  response.data[0] = 0xA6;
		    	  response.data[1] = heater_id;
		    	  CAN_Transmit_Message(response);

		          break;

		      default:
		          break;
		  }


	  }

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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 16;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV8;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
