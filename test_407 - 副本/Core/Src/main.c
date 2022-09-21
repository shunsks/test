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
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h"
//#include "key.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "delay.h"
#include "gt30l32.h"
#include "menu.h"
#include "pid.h"
#include "stmflash.h"
#include "SHT30.h"
#include "sht30_i2c_drv.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

const u8 TEXT_Buffer_1[]={" STM32 FLASH TEST_1"};//要写入到STM32 FLASH的字符串数组
const u8 TEXT_Buffer_2[]={"STM32 FLASH TEST_2"};//要写入到STM32 FLASH的字符串数组
#define SIZE sizeof(TEXT_Buffer_1)	 	//数组长度
    
float data[2];
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

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
    uint8_t Menu_options = 0,Menu_options_run = 0;
    uint8_t menu_set = 0;
    uint8_t cnt = 0,i=0;
    uint32_t ad_value[2];
    uint8_t strbuf[32];
    
    u8 len;
    u16 times=0;
        
    u8 datatemp[SIZE];  //Flash读取缓存数组
    u8 *p=datatemp;	    //数组指针

    uint8_t recv_dat[6] = {0};
    float temperature = 0.0;
    float humidity = 0.0;    
    
    char tempstr[6] = {0};
    char humistr[6] = {0};
    
    
    uint8_t t = 0;
    uint8_t tbuf[40];
    RTC_DateTypeDef RTC_DateStruct;
    RTC_TimeTypeDef RTC_TimeStruct;

    
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
  MX_I2C3_Init();
  MX_SPI3_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
  delay_init(168);
  PID_init();
  OLED_Init();
//  SHT30_Init();
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_Delay(200);
  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,GPIO_PIN_SET);

  HAL_UART_Receive_IT(&huart1, (u8 *)aRxBuffer, RXBUFFERSIZE);
  
//  SHT30_reset();
//    if(SHT30_Init() == HAL_OK)
//        printf("sht30 init ok.\n");
//    else
//        printf("sht30 init fail.\n");
//  STMFLASH_Write(ADDR_FLASH_SECTOR_11,(uint32_t*)TEXT_Buffer_1,SIZE);//第一次写读
//  STMFLASH_Read(ADDR_FLASH_SECTOR_11,(uint32_t*)datatemp,SIZE);
////  
//  OLED_ShowAscilString(0,4,p);
    
    RTC_TimeStruct.Hours = 20;
    HAL_RTC_SetTime(&hrtc, &RTC_TimeStruct, RTC_FORMAT_BIN);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  TIM1->CCR1 = 10;
//  Disp_Snow(0x55,0xaa);
  while (1)
  {
          
      
//      if(USART_RX_STA&0x8000)
//		{					   
//			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
//            ReceiveData = USARTBufferToD_data(USART_RX_BUF);
//            printf("PMTSP:%d",ReceiveData.PMTSP);
////			HAL_UART_Transmit(&huart1,(uint8_t *)USART_RX_BUF,len,1000);	//发送接收到的数据
////			while(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TC)!=SET);		//等待发送结束
//			USART_RX_STA=0;  
//		}
//    for(i=0;i<2;i++)
//    {
//        ad_value[i]=ADC_Get_Average(i,10);
//    }
//    
//    sprintf(strbuf,"adc0:%d;adc1:%d;       ",ad_value[0],ad_value[1]);
//    OLED_ShowAscilString(0,0,strbuf);
//    ad_value[1] = PID_realize(3600,ad_value[0]);
//    TIM1->CCR1 = 10;
//    sprintf(strbuf,"PID:%d       ",ad_value[1]);
//    OLED_ShowAscilString(0,2,strbuf);
//    HAL_Delay(500);
//    
//    if(SHT30_Read_Dat(recv_dat) == HAL_OK)
//		{
//			if(SHT30_Dat_To_Float(recv_dat, &temperature, &humidity)==0)
//			{
//				printf("temperature = %f, humidity = %f\n", temperature, humidity);
//			}
//			else
//			{
//				printf("crc check fail.\n");
//			}
//		}
//		else
//		{
//			printf("read data from sht30 fail.\n");
//		}
    
    
    
    
    
//    HAL_RTC_GetTime(&hrtc,&RTC_TimeStruct,RTC_FORMAT_BIN);
//    printf("Time:%02d:%02d:%02d",RTC_TimeStruct.Hours,RTC_TimeStruct.Minutes,RTC_TimeStruct.Seconds); 
//    HAL_RTC_GetDate(&hrtc,&RTC_DateStruct,RTC_FORMAT_BIN);
//    printf("Date:20%02d-%02d-%02d",RTC_DateStruct.Year,RTC_DateStruct.Month,RTC_DateStruct.Date); 	
//    printf("Week:%d\r\n",RTC_DateStruct.WeekDay); 
      menu_run();
//    sprintf(strbuf,"KEY_NUM:%d",key);
//    OLED_ShowAscilString(0,6,strbuf);
		

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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_5)
    {
        
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
