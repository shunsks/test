#include "SHT30.h" 	
#include "delay.h" 	
 



///**
// * �������� : ��ʼ��SHT30
// * ˵    �� : ��
// * ������� : ��
// * �� �� ֵ : ��
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


 /*��������ACK*/
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


 /*����������ACK*/
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


 /*�����ȴ��ӻ���ACK*/
u8 IIC_wait_ACK(void)
{
    u8 t = 200;
    IIC_OUTPUT_MODE_SET();
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_SET);//8λ��������ͷ������ߣ�׼������Ӧ��λ 
    delay_us(1);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_RESET);
    delay_us(1); 
    IIC_INPUT_MODE_SET();
    delay_us(1); 
    while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7))//�ȴ�SHT30Ӧ��
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
����:����I2C����,������I2C��ʼ����.  
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
����:����I2C����,������I2C��������.  
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
�ֽ����ݷ��ͺ���               
����ԭ��: void  SendByte(UCHAR c);
����:������c���ͳ�ȥ,�����ǵ�ַ,Ҳ����������
********************************************************************/
void  IIC_SendByte(u8 byte)
{
	u8  BitCnt;
	IIC_OUTPUT_MODE_SET();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_RESET);
	for(BitCnt=0;BitCnt<8;BitCnt++)//Ҫ���͵����ݳ���Ϊ8λ
	{
		if(byte&0x80) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_SET);//�жϷ���λ
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
 �ֽ����ݽ��պ���               
����ԭ��: UCHAR  RcvByte();
����: �������մ���������������  
********************************************************************/    
u8 IIC_RcvByte(void)
{
  u8 retc;
  u8 BitCnt;
  retc=0; 
  IIC_INPUT_MODE_SET();//��������Ϊ���뷽ʽ
  delay_us(1);                    
  for(BitCnt=0;BitCnt<8;BitCnt++)
  {  
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_RESET);//��ʱ����Ϊ�ͣ�׼����������λ
	delay_us(2);               
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_SET);//��ʱ����Ϊ��ʹ��������������Ч                
	retc=retc<<1;
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7)) retc |=1;//������λ,���յ�����λ����retc�� 
	delay_us(1);
  }
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,GPIO_PIN_RESET);    
  return(retc);
}


/*******************************************************************
 ��ʪ�Ȼ�ȡ����               
����ԭ��: SHT30_read_result(float *P);
����: �������մ������ɼ����ϳ���ʪ��
********************************************************************/ 
void SHT30_read_result(float *P)
{
	u16 tem,hum;
	u16 buff[6];
	float Temperature=0;
	float Humidity=0;
	
	IIC_Start();
	IIC_SendByte(addr<<1 | 0);//д7λI2C�豸��ַ��0��Ϊдȡλ,1Ϊ��ȡλ
	IIC_wait_ACK();
	IIC_SendByte(0x2C);
	IIC_wait_ACK();
	IIC_SendByte(0x06);
	IIC_wait_ACK();
	IIC_Stop();
	delay_us(60);
	IIC_Start();
	IIC_SendByte(addr<<1 | 1);//д7λI2C�豸��ַ��0��Ϊдȡλ,1Ϊ��ȡλ
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
	
	tem = ((buff[0]<<8) | buff[1]);//�¶�ƴ��
	hum = ((buff[3]<<8) | buff[4]);//ʪ��ƴ��
	
	/*ת��ʵ���¶�*/
	Temperature= (float)(175.0*(float)tem/65535.0-45.0) ;// T = -45 + 175 * tem / (2^16-1)
	Humidity= (float)(100.0*(float)hum/65535.0);// RH = hum*100 /(2^16-1)

// printf("Temp  : %0.2f    ,    Hum  : %0.2f%%\r\n ",Temperature,Humidity);
  
	hum=0;
	tem=0;
  P[0]=Temperature;
  P[1]=Humidity;
}






