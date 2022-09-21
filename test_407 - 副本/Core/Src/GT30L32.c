#include "gt30l32.h"
#include "spi.h"

uint8_t SPI3_ReadWriteByte(uint8_t TxData)//发送一个字节，并从寄存器返回一个字节
{
	uint8_t Rxdata;
	HAL_SPI_TransmitReceive(&hspi3, &TxData, &Rxdata, 1, 1000);       
 	return Rxdata;          		    
}

void GenitopZk_Address(u32 Address) 
{
	u8 AddH, AddM, AddL;
	
	AddH = Address >> 16;
	AddM = Address >> 8;
	AddL = Address;
	
	SPI3_ReadWriteByte(0x03);	//一般读取
	SPI3_ReadWriteByte(AddH);
	SPI3_ReadWriteByte(AddM);
	SPI3_ReadWriteByte(AddL);
	
//	SPI3_ReadWriteByte(0x0B);	//快速读取
//	SPI3_ReadWriteByte(AddH);
//	SPI3_ReadWriteByte(AddM);
//	SPI3_ReadWriteByte(AddL);
//	SPI3_ReadWriteByte(0xff);
}

void ASCII_8X16(char *ASCIICode, u8 *BUF)
{
	u8 i;
	u32 BaseAdd;
	u32 Address;
	
	BaseAdd = 0x1DD780;
	
	if(*ASCIICode >= 0x20 && *ASCIICode <= 0x7E){
		Address = (*ASCIICode - 0x20) * 16 + 0x1DD780;
	}

	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET);

	GenitopZk_Address(Address);
	for(i = 0; i < 16 ; i++){
		BUF[i] = SPI3_ReadWriteByte(0xFF);
//		printf("%c", BUF[i]);
	}
	
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);

}

void GB2312_16X16(char *GBCode, u8 *BUF)
{
	u8 i;
    u8 MSB;			//汉字内码高八位
	u8 LSB;			//汉字内码低八位
    
	u32 BaseAdd;
	u32 Address;
	    
	BaseAdd = 0x2C9D0;
	
    MSB = *GBCode;
	LSB = *(++GBCode);
    
	if(MSB >= 0xA1 && MSB <= 0xA9 && LSB >= 0xA1){
		Address = ((MSB - 0xA1) * 94 + (LSB - 0xA1)) * 32 + BaseAdd;
	}
	else if(MSB >= 0xB0 && MSB <= 0xF7 && LSB >= 0xA1){
		Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1) + 846) * 32 + BaseAdd;
	}

	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET);

	GenitopZk_Address(Address);
	for(i = 0; i < 32 ; i++){
		BUF[i] = SPI3_ReadWriteByte(0xFF);
//		printf("%c", BUF[i]);
	}
	
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);

}







