#ifndef _GT30L32_H
#define _GT30L32_H
#include "sys.h"


//extern SPI_HandleTypeDef hspi1;//DAC¾ä±ú

/************** GB2312×Ö¿â×Ö·û»ùµØÖ· *****************/
#define BaseAdd_12X12	0x00000
#define BaseAdd_16X16	0x2C9D0
#define BaseAdd_24X24	0x68190
#define BaseAdd_32X32	0xEDF00
/************** ASCII×Ö·û»ùµØÖ· *****************/
#define ASCIIAdd_5X7	0x1DDF80
#define ASCIIAdd_7X8	0x1DE280
#define ASCIIAdd_6X12	0x1DBE00
#define ASCIIAdd_8X16	0x1DD780
#define ASCIIAdd_12X24	0x1DFF00
#define ASCIIAdd_16X32	0x1E5A50

#define SPI_NSS PBout(4)

void GT30_Init(void);
void ASCII_5X7(char *ASCIICode, u8 *BUF);
void ASCII_7X8(char *ASCIICode, u8 *BUF);
void ASCII_6X12(char *ASCIICode, u8 *BUF);
void ASCII_8X16(char *ASCIICode, u8 *BUF);
void ASCII_12X24(char *ASCIICode, u8 *BUF);
void ASCII_16X32(char *ASCIICode, u8 *BUF);

void GB2312_12X12(char *GBCode, u8 *buf);
void GB2312_16X16(char *GBCode, u8 *buf);
void GB2312_24X24(char *GBCode, u8 *buf);
void GB2312_32X32(char *GBCode, u8 *buf);

#endif



