#ifndef __SHT30_H
#define __SHT30_H

#include "sys.h"
#include "stdio.h"
#include "main.h"
#include "string.h"
#include "sys.h"
 
#define addr  0x44      //SHT30的IIC地址  0x44
 
//IIC总线地址接口定义
#define SCL         PBout(6)
#define SDA_OUT     PBout(7)
#define SDA_IN      PBin(7)
#define IIC_INPUT_MODE_SET()    {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=0<<7*2;}	
#define IIC_OUTPUT_MODE_SET()   {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=1<<7*2;} 
 
//void SHT30_Init(void);    //SHT30初始化
void IIC_ACK(void);       //iic应答
void IIC_NACK(void);      
u8 IIC_wait_ACK(void);    //等待应答
void IIC_Start(void);     //开始信号
void IIC_Stop(void);      //结束信号
void IIC_SendByte(u8 byte); //发送一个字节
u8 IIC_RcvByte(void);       //读取一个字节
void SHT30_read_result(float *P);   //读取温湿度数据

#endif




