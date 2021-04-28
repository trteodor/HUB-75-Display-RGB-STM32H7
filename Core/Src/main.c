/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "iwdg.h"
#include "mdma.h"
#include "quadspi.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "HUB_75.h"
#include "stm32h7xx_it.h"
#include "PIXEL_MAPS.h"
#include "stm32h7xx_hal.h"
#include "Napisy.h"
#include "LL_UART_TEO.h"
#include "String_From_UART.h"
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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE BEGIN PV */
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

/* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_MDMA_Init();
  MX_TIM2_Init();
  MX_QUADSPI_Init();
  MX_TIM3_Init();
  MX_TIM5_Init();
  MX_USART3_UART_Init();
  MX_TIM4_Init();
  MX_SPI2_Init();
  MX_IWDG1_Init();
  /* USER CODE BEGIN 2 */

  //HAL_Delay(2);  //WatchDOG!!!!! na 20 MS
  HAL_IWDG_Refresh(&hiwdg1);
HUB_75_INIT();

INIT_UART3();

uint8_t Proces_num=0 ;

uint8_t Pozdr_widzow[10000]={0};

uint8_t B1[]= "tel. 885015433";
int Size=sizeof(B1)-1;
Create_String_buffer (B1, Size, 0 , Pozdr_widzow,Azure);
uint8_t B2[]= "POZDRAWIAMY";
Size=sizeof(B2)-1;
Create_String_buffer (B2, Size, 1 , Pozdr_widzow,Green);

HAL_IWDG_Refresh(&hiwdg1);

uint8_t ZaprDoSalonuFryzStudio[10000]={0};
uint8_t S1[]= " ZAPRASZAMY";
uint8_t S2[]= "  DO SALONU ";
uint8_t S3[]= "FRYZJESKIEGO";
uint8_t S4[]= " ORAZ STUDIA";
uint8_t S5[]= "  PAZNOKCI!";
 Size=sizeof(S1)-1;
Create_String_buffer (S1, Size, 0 , ZaprDoSalonuFryzStudio,Azure);
 Size=sizeof(S2)-1;
Create_String_buffer (S2, Size, 1 , ZaprDoSalonuFryzStudio,Green);
 Size=sizeof(S3)-1;

 HAL_IWDG_Refresh(&hiwdg1);

Create_String_buffer (S3, Size, 2 , ZaprDoSalonuFryzStudio,Yellow);
 Size=sizeof(S4)-1;
Create_String_buffer (S4, Size, 3 , ZaprDoSalonuFryzStudio,Purple);
Size=sizeof(S5)-1;
Create_String_buffer (S5, Size, 4 , ZaprDoSalonuFryzStudio,White);
int ZaprDoSalonuFryzStudioRow=4+1;


/*
uint8_t ZaprDoSalonuFryzStudio2[10000]={0};
uint8_t S12[]= "ZAPRASZAMY";
uint8_t S22[]= "DO SALONU ";
uint8_t S32[]= "FRYZJESKIEGO";
uint8_t S42[]= " ORAZ STUDIA";
uint8_t S52[]= "  PAZNKOCI";
 Size=sizeof(S1)-1;
Create_String_buffer (S1, Size, 0 , ZaprDoSalonuFryzStudio2,Azure);
 Size=sizeof(S2)-1;
Create_String_buffer (S2, Size, 1 , ZaprDoSalonuFryzStudio2,Green);
 Size=sizeof(S3)-1;
Create_String_buffer (S3, Size, 2 , ZaprDoSalonuFryzStudio2,Yellow);
 Size=sizeof(S4)-1;
Create_String_buffer (S4, Size, 3 , ZaprDoSalonuFryzStudio2,Purple);
Size=sizeof(S5)-1;
Create_String_buffer (S5, Size, 4 , ZaprDoSalonuFryzStudio,Purple);
int ZaprDoSalonuFryzStudioRow2=4+1;
*/


SedingBufor_Adr=OUT_B1;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  HAL_IWDG_Refresh(&hiwdg1);
	  HandleEcho(&Thuart3);

	  switch( Proces_num )
	  {
	  case 0:
	  	Verical_Scroll_Flow_withHOLD(ZaprDoSalonuFryzStudio, ZaprDoSalonuFryzStudioRow*16, 50, 800,300, 0);  //this fucion execution maks 550us
	   if(SCR_PROCESS==SCR_VIEWING_PROCESS_DONE)
	   {
	  	 Proces_num++;
	   }
	  break;
	  case 1:

	  	Verical_Scroll_Flow_withHOLD(ZaprDoSalonuFryzStudio, (ZaprDoSalonuFryzStudioRow*16) +16 , 50, 300,800, 1);
	  	 if(SCR_PROCESS==SCR_VIEWING_PROCESS_DONE)
	  	 {
	  		 Proces_num++;
	  	 }
	  	break;
	  case 2:

	  	Viewing_BitMapBy_Time(Pozdr_widzow, 2000);
	  	 if(SCR_PROCESS==SCR_VIEWING_PROCESS_DONE)
	  	 {
	  		 Proces_num++;
	  	 }

	  	break;
	  case 3:

	  	Viewing_BitMapBy_Time(Pozdr_widzow, 1000);
	  	 if(SCR_PROCESS==SCR_VIEWING_PROCESS_DONE)
	  	 {
	  		 Proces_num++;
	  	 }

	  	break;

	  case 4:
		  	 Horizontal_SCROLL( Pozdr_wsz, 1300 , 1300, 23);  //Pozdr_wsz
		  	 if(SCR_PROCESS==SCR_VIEWING_PROCESS_DONE)
		  	 {
		  		 Proces_num++;
		  	 }


	  	break;
	  case 5:
		  	  	  	  //Napisy z UARTU czyli bluetootha
		  if(Ilosc_Lini_tesktu>0)
		  {

			  if(Ilosc_Lini_tesktu==1 || Ilosc_Lini_tesktu==2)
			  {
				  	Viewing_BitMapBy_Time( Created_By_UART_BMP , 6000);

						  	 if(SCR_PROCESS==SCR_VIEWING_PROCESS_DONE)
						  	 {
						  		Proces_num++;
						  		break;
						  	 }
			  }


			  else if(Ilosc_Lini_tesktu==3 || Ilosc_Lini_tesktu==4)
			  {
				  Verical_Scroll_Flow_withHOLD(Created_By_UART_BMP, 64, 80, 3200,3200, 1);
				  	 if(SCR_PROCESS==SCR_VIEWING_PROCESS_DONE)
				  	 {
				  		Proces_num++;
				  		break;
				  	 }
			  }
			  else
			  {
				  SCR_PROCESS=SCR_VIEWING_PROCESS_DONE;
				  Proces_num++;
				  break;
			  }

			  if(  (HAL_GetTick() - Z_czasOtrzymania_tekstu) > (1000*60*1) )
			  {
				  SCR_PROCESS=SCR_VIEWING_PROCESS_DONE;
				  Ilosc_Lini_tesktu=0;
				  f_start_view=1;
				  Proces_num++;
				  break;
			  }

		  }

		  else
		  {
			  SCR_PROCESS=SCR_VIEWING_PROCESS_DONE;
			  Proces_num++;
			  break;
		  }
	  	break;

	  default :
	  	Proces_num=0;

	  	break;
	  }


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

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_CSI);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_CSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.CSIState = RCC_CSI_ON;
  RCC_OscInitStruct.CSICalibrationValue = RCC_CSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_CSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 240;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 120;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_QSPI|RCC_PERIPHCLK_SPI2;
  PeriphClkInitStruct.PLL2.PLL2M = 1;
  PeriphClkInitStruct.PLL2.PLL2N = 60;
  PeriphClkInitStruct.PLL2.PLL2P = 120;
  PeriphClkInitStruct.PLL2.PLL2Q = 120;
  PeriphClkInitStruct.PLL2.PLL2R = 5;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_2;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
  PeriphClkInitStruct.QspiClockSelection = RCC_QSPICLKSOURCE_PLL2;
  PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
