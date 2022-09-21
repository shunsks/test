#ifndef __OLED_H_
#define __OLED_H_


//#include "i2c.h"
#include "main.h"
#include "gpio.h"

typedef enum {
  CHAR_MODE_8x16 = 0,
  CHAR_MODE_16x32,
  CHAR_MODE_12x12,
  CHAR_MODE_16x16,
  CHAR_MODE_24x24,
  CHAR_MODE_32x32,
  CHAR_MODE_MAX,
} Char_Mode_e;

#define OLED_CMD  1
#define OLED_DATA 0	

void OLED_WR_Byte(uint8_t dat,uint8_t mode);
void Write_4spi(uint8_t Dat,uint8_t Cd);
void OLED_Init(void);
void Disp_Snow(uint8_t Dat1,uint8_t Dat2);
void Disp_Pic(uint8_t *p);
void clealddram();
void font2(void);
void OLED_Show_Char(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1);
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t size1);

void OLED_Show_Chinese(uint8_t x,uint8_t y,uint8_t chr);

void OLED_Show_Ascil(uint8_t x,uint8_t y,char * chr);
void OLED_ShowAscilString(uint8_t x,uint8_t y,uint8_t *chr);

void OLED_Show_GB2312(uint8_t x,uint8_t y,char *chr);
void OLED_ShowGB2312String(uint8_t x,uint8_t y,uint8_t *chr);

#endif

