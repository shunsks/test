#ifndef _KEY_H
#define _KEY_H
#include "sys.h"

#define KEY1        HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_12)  
#define KEY2        HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_15) 
#define KEY3        HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2) 	
#define KEY4        HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_7)  
#define KEY5        HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_8) 
#define KEY6        HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_10) 	
#define KEY7        HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_11)  
#define KEY8        HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_13) 
#define KEY9        HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_14) 	


#define KEY1_PRES 	1
#define KEY2_PRES	2
#define KEY3_PRES	3
#define KEY4_PRES 	4
#define KEY5_PRES	5
#define KEY6_PRES	6
#define KEY7_PRES 	7
#define KEY8_PRES	8
#define KEY9_PRES	9


u8 KEY_Scan(u8 mode);
#endif
