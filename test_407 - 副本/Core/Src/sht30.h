#ifndef __SHT30_H
#define __SHT30_H

#include "sys.h"
#include "stdio.h"
#include "main.h"
#include "string.h"
#include "sys.h"
 
#define addr  0x44      //SHT30��IIC��ַ  0x44
 
//IIC���ߵ�ַ�ӿڶ���
#define SCL         PBout(6)
#define SDA_OUT     PBout(7)
#define SDA_IN      PBin(7)
#define IIC_INPUT_MODE_SET()    {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=0<<7*2;}	
#define IIC_OUTPUT_MODE_SET()   {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=1<<7*2;} 
 
//void SHT30_Init(void);    //SHT30��ʼ��
void IIC_ACK(void);       //iicӦ��
void IIC_NACK(void);      
u8 IIC_wait_ACK(void);    //�ȴ�Ӧ��
void IIC_Start(void);     //��ʼ�ź�
void IIC_Stop(void);      //�����ź�
void IIC_SendByte(u8 byte); //����һ���ֽ�
u8 IIC_RcvByte(void);       //��ȡһ���ֽ�
void SHT30_read_result(float *P);   //��ȡ��ʪ������

#endif




