#include "si7021.h"

_si7021_value si7021;//
_si7021_filter si7021_filter;//

void Multiple_read_Si7021(uint8_t REG_address, uint16_t *value)
{
	uint8_t Si7021_BUF[2]={0};
    
    
    HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)((SLAVE_ADDR<<1)|0), (uint8_t*)REG_address, 1, 10000);
    
    HAL_I2C_Master_Receive(&hi2c1, (uint16_t)((SLAVE_ADDR<<1)|0), (uint8_t *)Si7021_BUF, 2, 10000);
    
	*value=((Si7021_BUF[0]<<8)+Si7021_BUF[1]);
}

void measure_Si7021(void)
{
	uint16_t TEMP,HUMI;
	uint8_t curI;
	Multiple_read_Si7021(TEMP_NOHOLD_MASTER,&TEMP);//NOHOLD_MASTER
	si7021.temp=(((((float)TEMP)*175.72f)/65536.0f) - 46.85f);
	Multiple_read_Si7021(HUMI_NOHOLD_MASTER,&HUMI);//NOHOLD_MASTER
	si7021.humi=(((((float)HUMI)*125.0f)/65535.0f) - 6.0f);
 
	if(MEAN_NUM > si7021_filter.curI)
	{
		si7021_filter.tBufs[si7021_filter.curI] = si7021.temp;
		si7021_filter.hBufs[si7021_filter.curI] = si7021.humi;
		si7021_filter.curI++;
	}
	else
	{
		si7021_filter.curI = 0;
		si7021_filter.tBufs[si7021_filter.curI] = si7021.temp;
		si7021_filter.hBufs[si7021_filter.curI] = si7021.humi;
		si7021_filter.curI++;
	}
	if(MEAN_NUM <= si7021_filter.curI) 
    {
        si7021_filter.thAmount = MEAN_NUM;
    }
    if(0 == si7021_filter.thAmount) 
    {
        for(curI = 0; curI < si7021_filter.curI; curI++)
        {
            si7021.temp += si7021_filter.tBufs[curI];
            si7021.humi += si7021_filter.hBufs[curI];
        }
        si7021.temp = si7021.temp / si7021_filter.curI;
        si7021.humi = si7021.humi / si7021_filter.curI; 
//        TEMP_buf = si7021.temp;
//        Humi_buf = si7021.humi;
    }
    else if(MEAN_NUM == si7021_filter.thAmount) 
    {
        for(curI = 0; curI < si7021_filter.thAmount; curI++) 
        {
            si7021.temp += si7021_filter.tBufs[curI];
            si7021.humi += si7021_filter.hBufs[curI];
        }
        si7021.temp = si7021.temp / si7021_filter.thAmount; 
        si7021.humi = si7021.humi / si7021_filter.thAmount; 
//        TEMP_buf = si7021.temp; 
//        Humi_buf = si7021.humi; 
    }
 
}
 