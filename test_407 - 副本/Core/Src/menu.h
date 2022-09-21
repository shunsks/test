#ifndef __MENU_H_
#define __MENU_H_

#include "oled.h"
#include "stdio.h"
#include "stdlib.h"
#include "key.h"
#include "usart.h"
#include "rtc.h"

typedef struct{
    uint16_t PMTSP;
    uint16_t PM10;
    uint16_t PM5;
    uint16_t PM2_5;
    uint16_t PM1;
    uint16_t PMc;
    uint16_t Pmax;
    uint16_t ALM;
    uint16_t LPDV;
    uint16_t Ver;
    uint16_t Pmin;
    uint16_t SUM;
    float temperature;
    float humidity;    


}D_data;  



D_data USARTBufferToD_data(u8 *RxBuffer);
void menu_run();

#endif
