#ifndef __SI7021_H_
#define __SI7021_H_

#include "i2c.h"
#include "stdio.h"
#include "stdlib.h"


#define MEAN_NUM  10

#define	SLAVE_ADDR		      0x40	//7 BIT ADDR
#define	TEMP_HOLD_MASTER	   0xE3
#define	HUMI_NOHOLD_MASTER	0xF5
#define	TEMP_NOHOLD_MASTER	0xF3
#define  Si7021_RST			   0xFE
#define  Write_UserReg		   0xE6
#define  Read_UserReg		   0xE7


typedef	struct
{
	float temp;
	float humi;
	uint8_t crc;
}_si7021_value;
// Data Define for Filter
typedef struct
{
	uint8_t curI;
	uint8_t thAmount;
	float tBufs[10];
	float hBufs[10];
}_si7021_filter;

void measure_Si7021(void);

#endif
