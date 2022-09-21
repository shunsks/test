#include "SHT30.h" 	
#include "delay.h" 	
 



///**
// * 函数功能 : 初始化SHT30
// * 说    明 : 无
// * 输入参数 : 无
// * 返 回 值 : 无
// *
//// **/
//void SHT30_Init(void)
//{
//  GPIO_InitTypeDef GPIO_InitStruct = {0};

//  __HAL_RCC_GPIOB_CLK_ENABLE();

//  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_SET);

//}	


 /*主机发送ACK*/
void IIC_ACK(void)
{
  IIC_OUTPUT_MODE_SET();
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_RESET);
  delay_us(2); 
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_RESET);
  delay_us(2);     
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_SET);
  delay_us(2);                  
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_RESET);                     
  delay_us(1);    
}


 /*主机不发送ACK*/
void IIC_NACK(void)
{
  IIC_OUTPUT_MODE_SET();
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_RESET);
  delay_us(2); 
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_SET);
  delay_us(2);      
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_SET);
  delay_us(2);                   
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_RESET);                     
  delay_us(1);    
}


 /*主机等待从机的ACK*/
u8 IIC_wait_ACK(void)
{
    u8 t = 200;
    IIC_OUTPUT_MODE_SET();
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_SET);//8位发送完后释放数据线，准备接收应答位 
    delay_us(1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_RESET);
    delay_us(1); 
    IIC_INPUT_MODE_SET();
    delay_us(1); 
    while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7))//等待SHT30应答
    {
	t--;
	delay_us(1); 
	if(t==0)
	{
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_RESET);
	  return 1;
	}
	delay_us(1); 
    }
    delay_us(1);      
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_SET);
    delay_us(1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_RESET);             
    delay_us(1);    
    return 0;	
}


/*******************************************************************
功能:启动I2C总线,即发送I2C起始条件.  
********************************************************************/
void IIC_Start(void)
{
  IIC_OUTPUT_MODE_SET();
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_SET);
  delay_us(4);	
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_RESET);
  delay_us(4); 
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_RESET);
}
 

/*******************************************************************
功能:结束I2C总线,即发送I2C结束条件.  
********************************************************************/
void IIC_Stop(void)
{
	IIC_OUTPUT_MODE_SET();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_RESET);  
	delay_us(4);	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_SET);
	delay_us(4);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_SET);
	delay_us(4);
}
 


/*******************************************************************
字节数据发送函数               
函数原型: void  SendByte(UCHAR c);
功能:将数据c发送出去,可以是地址,也可以是数据
********************************************************************/
void  IIC_SendByte(u8 byte)
{
	u8  BitCnt;
	IIC_OUTPUT_MODE_SET();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_RESET);
	for(BitCnt=0;BitCnt<8;BitCnt++)//要传送的数据长度为8位
	{
		if(byte&0x80) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_SET);//判断发送位
		else HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_RESET); 
		byte<<=1;
		delay_us(2); 
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_SET);
		delay_us(2);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_RESET);
		delay_us(2);
	}
}


/*******************************************************************
 字节数据接收函数               
函数原型: UCHAR  RcvByte();
功能: 用来接收从器件传来的数据  
********************************************************************/    
u8 IIC_RcvByte(void)
{
  u8 retc;
  u8 BitCnt;
  retc=0; 
  IIC_INPUT_MODE_SET();//置数据线为输入方式
  delay_us(1);                    
  for(BitCnt=0;BitCnt<8;BitCnt++)
  {  
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_RESET);//置时钟线为低，准备接收数据位
	delay_us(2);               
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_SET);//置时钟线为高使数据线上数据有效                
	retc=retc<<1;
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7)) retc |=1;//读数据位,接收的数据位放入retc中 
	delay_us(1);
  }
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_RESET);    
  return(retc);
}


/*******************************************************************
 温湿度获取函数               
函数原型: SHT30_read_result(float *P);
功能: 用来接收从器件采集并合成温湿度
********************************************************************/ 
void SHT30_read_result(float *P)
{
	u16 tem,hum;
	u16 buff[6];
	float Temperature=0;
	float Humidity=0;
	
	IIC_Start();
	IIC_SendByte(addr<<1 | 0);//写7位I2C设备地址加0作为写取位,1为读取位
	IIC_wait_ACK();
	IIC_SendByte(0x2C);
	IIC_wait_ACK();
	IIC_SendByte(0x06);
	IIC_wait_ACK();
	IIC_Stop();
	delay_us(60);
	IIC_Start();
	IIC_SendByte(addr<<1 | 1);//写7位I2C设备地址加0作为写取位,1为读取位
	if(IIC_wait_ACK()==0)
	{
		buff[0]=IIC_RcvByte();
		IIC_ACK();
		buff[1]=IIC_RcvByte();
		IIC_ACK();
		buff[2]=IIC_RcvByte();
		IIC_ACK();
		buff[3]=IIC_RcvByte();
		IIC_ACK();
		buff[4]=IIC_RcvByte();
		IIC_ACK();
		buff[5]=IIC_RcvByte();
		IIC_NACK();
		IIC_Stop();
	}
	
	tem = ((buff[0]<<8) | buff[1]);//温度拼接
	hum = ((buff[3]<<8) | buff[4]);//湿度拼接
	
	/*转换实际温度*/
	Temperature= (float)(175.0*(float)tem/65535.0-45.0) ;// T = -45 + 175 * tem / (2^16-1)
	Humidity= (float)(100.0*(float)hum/65535.0);// RH = hum*100 /(2^16-1)

// printf("Temp  : %0.2f    ,    Hum  : %0.2f%%\r\n ",Temperature,Humidity);
  
	hum=0;
	tem=0;
  P[0]=Temperature;
  P[1]=Humidity;
}






