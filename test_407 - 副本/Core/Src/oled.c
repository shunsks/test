#include "oled.h"
#include "oledfont.h"
#include "gt30l32.h"
#include "delay.h"
void delay(uint8_t i)
{
		while(i--);
}

void ChangeOneBlock(unsigned char *pSrc, unsigned char *pDst, unsigned char step)
{
    unsigned char x;

    for (x = 0; x < 8; ++x)
    {
        *pDst = 0;

        if (*(pSrc + 0 * step) & (1 << (7 - x)))
        {
            *pDst = *pDst | 0x1;
        }

        if (*(pSrc + 1 * step) & (1 << (7 - x)))
        {
            *pDst = *pDst | 0x2;
        }

        if (*(pSrc + 2 * step) & (1 << (7 - x)))
        {
            *pDst = *pDst | 0x4;
        }

        if (*(pSrc + 3 * step) & (1 << (7 - x)))
        {
            *pDst = *pDst | 0x8;
        }

        if (*(pSrc + 4 * step) & (1 << (7 - x)))
        {
            *pDst = *pDst | 0x10;
        }

        if (*(pSrc + 5 * step) & (1 << (7 - x)))
        {
            *pDst = *pDst | 0x20;
        }

        if (*(pSrc + 6 * step) & (1 << (7 - x)))
        {
            *pDst = *pDst | 0x40;
        }

        if (*(pSrc + 7 * step) & (1 << (7 - x)))
        {
            *pDst = *pDst | 0x80;
        }

        pDst++;
    }
}

void ChangeOneHaltBlock(unsigned char *pSrc, unsigned char *pDst, unsigned char step)
{
    unsigned char x;

    for (x = 0; x < 8; ++x)
    {
        *pDst = 0;

        if (*(pSrc + 0 * step) & (1 << (7 - x)))
        {
            *pDst = *pDst | 0x1;
        }

        if (*(pSrc + 1 * step) & (1 << (7 - x)))
        {
            *pDst = *pDst | 0x2;
        }

        if (*(pSrc + 2 * step) & (1 << (7 - x)))
        {
            *pDst = *pDst | 0x4;
        }

        if (*(pSrc + 3 * step) & (1 << (7 - x)))
        {
            *pDst = *pDst | 0x8;
        }

        pDst++;
    }
}

void RowModeToColumMode(Char_Mode_e eMode, unsigned char *pSrc, unsigned char *pDst)
{
    switch (eMode)
    {
        case CHAR_MODE_8x16:   /*1 Byte x 16*/
        {
            unsigned char y;

            for (y = 0; y < 2; ++y)
            {
                ChangeOneBlock(pSrc, pDst, 1);
                pDst += 8;
                pSrc += 8;
            }
        }
        break;

        case CHAR_MODE_16x16:
        {
            unsigned char y; /*2 Byte x 16*/

            for (y = 0; y < 2; ++y)
            {
                ChangeOneBlock(pSrc, pDst, 2);
                pDst += 8;
                pSrc += 1;

                ChangeOneBlock(pSrc, pDst, 2);
                pDst += 8;
                pSrc += 2 * 8 - 1;
            }
        }
        break;

        case CHAR_MODE_32x32: /*4 Byte x 32*/
        {
            unsigned char y;

            for (y = 0; y < 4; ++y)
            {
                ChangeOneBlock(pSrc, pDst, 4);
                pDst += 8;
                pSrc += 1;

                ChangeOneBlock(pSrc, pDst, 4);
                pDst += 8;
                pSrc += 1;

                ChangeOneBlock(pSrc, pDst, 4);
                pDst += 8;
                pSrc += 1;

                ChangeOneBlock(pSrc, pDst, 4);
                pDst += 8;
                pSrc += 4 * 8 - 3;
            }
        }
        break;

        case CHAR_MODE_12x12: /*2 Byte x 12*/
        {
            ChangeOneBlock(pSrc, pDst, 2);
            pDst += 8;
            pSrc += 1;

            ChangeOneBlock(pSrc, pDst, 2);
            pDst += 8;
            pSrc += 2 * 8 - 1;

            ChangeOneHaltBlock(pSrc, pDst, 2);
            pDst += 8;
            pSrc += 1;

            ChangeOneHaltBlock(pSrc, pDst, 2);
        }
        break;

        default:
            break;
    }
}

void Write_4spi_OLED_CMD(uint8_t Dat)
{
	uint8_t i;
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_RESET);
	for(i=0;i<8;i++)
	{
        
		if(Dat&0x80)
		{
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);
		}
		else
		{
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);
		}delay_us(1);
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
        delay_us(1);
        //HAL_Delay(1);
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);

        Dat<<=1;
	}
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_SET);
}


void Write_4spi_OLED_DATA(uint8_t Dat)
{
	uint8_t i;
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_SET);
	for(i=0;i<8;i++)
	{
        
		if(Dat&0x80)
		{
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);
		}
		else
		{
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);
		}delay_us(1);    
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
        delay_us(1);
        //HAL_Delay(1);
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);

        Dat<<=1;
	}
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_SET);
}


void clealddram()
{
	int i,j;
	Write_4spi_OLED_CMD(0x30);
	Write_4spi_OLED_CMD(0x15);
	Write_4spi_OLED_DATA(0x00);
	Write_4spi_OLED_DATA(0xff);
	Write_4spi_OLED_CMD(0x75);
	Write_4spi_OLED_DATA(0x00);	
	Write_4spi_OLED_DATA(0x3f);
	Write_4spi_OLED_CMD(0x5c);	
	for(i=0;i<8;i++)
	{
	for(j=0;j<256;j++)	
	{
	Write_4spi_OLED_DATA(0x00);
	}
	}
}



void OLED_Init()
{
//    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);
//    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_SET);
//    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_SET);
	
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);
  HAL_Delay(20);
  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET);
  HAL_Delay(20);
  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);
  HAL_Delay(200);
    
    Write_4spi_OLED_CMD(0x30);//Extension Command1
    Write_4spi_OLED_CMD(0x6e);//Enable Master
    
    Write_4spi_OLED_CMD(0x31);//Extension Command2
    Write_4spi_OLED_CMD(0xd7);//Disable Auto Read
    Write_4spi_OLED_DATA(0x9f);//Extension Command
    Write_4spi_OLED_CMD(0xe0);
    Write_4spi_OLED_DATA(0x00);
    HAL_Delay(20);
    Write_4spi_OLED_CMD(0xe3);
    HAL_Delay(20);
    Write_4spi_OLED_CMD(0xe1);
    
    
    
    Write_4spi_OLED_CMD(0x30);   //Extension Command1
    Write_4spi_OLED_CMD(0x94);   //Sleep Out
    Write_4spi_OLED_CMD(0xae);   //Display off
    HAL_Delay(50);            
                             
    Write_4spi_OLED_CMD(0x20);   //Power Control
    Write_4spi_OLED_DATA(0x0b);  //VB,VR,VF AllON
    Write_4spi_OLED_CMD(0x81);   //Set VOP
    Write_4spi_OLED_DATA(0x1f);  //0x03/0x3f=13.8V 0x2b=13.0 ;0x1d/0x04=15.0V
    Write_4spi_OLED_DATA(0x02);  //	
                             
    Write_4spi_OLED_CMD(0x31);   	// Extension Command 2	
    Write_4spi_OLED_CMD(0x32);   //Analog Circuit Set	
    Write_4spi_OLED_DATA(0x00);  //
    Write_4spi_OLED_DATA(0x01);  //Booster Efficiency-6KHz
    Write_4spi_OLED_DATA(0x05);  //0x05=Bias=1/9	0x02=1/12
                             
    Write_4spi_OLED_CMD(0x51);   //Booster Level 	
    Write_4spi_OLED_DATA(0xfb);  //*10		
                             
    Write_4spi_OLED_CMD(0x30);   //Extension Command1	
                             
    Write_4spi_OLED_CMD(0xf0);   //Display Mode
    Write_4spi_OLED_DATA(0x10);  //Mono Mode
                             
    Write_4spi_OLED_CMD(0xca);   //Display Control
    Write_4spi_OLED_DATA(0x00);  //CL Dividing Ratio---Not Divide
    Write_4spi_OLED_DATA(0x3f);  //Duty Set---- 1/64		
    Write_4spi_OLED_DATA(0x00);  //Frame Inversion
                             
    Write_4spi_OLED_CMD(0x31);   	// Extension Command 2
                             
    Write_4spi_OLED_CMD(0xf2);   //Temperature Range
    Write_4spi_OLED_DATA(0x1E);  // TA=-10
    Write_4spi_OLED_DATA(0x28);  // TB=0
    Write_4spi_OLED_DATA(0x32);  // TC=10
                             
    Write_4spi_OLED_CMD(0xf0);   //Frame rate
    Write_4spi_OLED_DATA(0x16);  //
    Write_4spi_OLED_DATA(0x16);  //
    Write_4spi_OLED_DATA(0x16);  // 0X18
    Write_4spi_OLED_DATA(0x16);  //102Hz
                             
    Write_4spi_OLED_CMD(0x30);   //Extension Command1	
    Write_4spi_OLED_CMD(0xbc);   //Data Scan Direction
    Write_4spi_OLED_DATA(0x00);  //Address direction
                             
    Write_4spi_OLED_CMD(0xa6);  //Normal display
                             
    Write_4spi_OLED_CMD(0x31);   //Extension Command2
    Write_4spi_OLED_CMD(0x40);   //Internal Power Supply
                             
    clealddram();            
                             
    Write_4spi_OLED_CMD(0xaf);  //Display ON
    
    
    
//    Write_4spi(0xaf,0);//display on
//	Write_4spi(0xa6,0);//normal display,0xa7:inverse display
//                        //Write_4spi(0,0x23);//all pixel display on
//	               
//	Write_4spi(0xca,0);//display control
//	Write_4spi(0x00,1);//cld =0;not divide
//	Write_4spi(0x4F,1);//set 1/80duty
//	Write_4spi(0x0e,1);//LF
//	               
//	Write_4spi(0x94,0);//SLP,Sleep out mode
//	               
//	Write_4spi(0x75,0);//Set page address
//	Write_4spi(0x00,1);//starting page address 00~28h//14h 
//	Write_4spi(0x0A,1);//Ending page address
//	               
//	Write_4spi(0x15,0);//Set Column address
//	Write_4spi(0x00,1);//Set Column address
//	Write_4spi(0xef,1);//Set Column address
//                   
//	Write_4spi(0xBC,0);//Set DATA scan direction
//	Write_4spi(0x00,1);//从左到右，从上到下	
//	               
//	Write_4spi(0xA3,0);//Set Start Line
//	Write_4spi(0x00,1);//
//                   
//	Write_4spi(0xD1,0);//Set OSC ON
//	               
//	Write_4spi(0x20,0);//Set Power control
//	Write_4spi(0x0B,1);//VB,VF,VR =1;
//	               
//	Write_4spi(0x81,0);//Set VOP
//	Write_4spi(0x1f,1);//Set VOP543210
//	Write_4spi(0x03,1);//Set VOP876
//	               
//	Write_4spi(0xD6,0);//Set VOP Increase one step
//	               
//	Write_4spi(0x08,0);//Set DO=0,Data Format select,LSB on bottom
//	               
//	Write_4spi(0xf0,0);//Set display mode
//	Write_4spi(0x10,1);//DM=0,Mono mode
//	               
//	Write_4spi(0x6e,0);//Set master 
//	               
//	Write_4spi(0x76,0);//Set ICON RAM disable
//	               
//	Write_4spi(0x32,0);//Set analog circuit 
//	Write_4spi(0x00,1);//
//	Write_4spi(0x01,1);//booster efficiency level:1
//	Write_4spi(0x04,1);//1/10 lcd bias
//	               
//	Write_4spi(0x51,0);//Set booster level
//	Write_4spi(0xfb,1);//Set x10
//	               
//	Write_4spi(0x40,0);//Set Driving select  internal
//	               
//                   
//	               
//	               
//    Write_4spi(0x5C,0);//Write_4spi Data To DDRAM
}

void Disp_Snow(uint8_t Dat1,uint8_t Dat2)
{
	uint8_t i,j;
	Write_4spi_OLED_CMD(0x30);
	Write_4spi_OLED_CMD(0x15);
	Write_4spi_OLED_DATA(0x00);
	Write_4spi_OLED_DATA(0xff);
	Write_4spi_OLED_CMD(0x75);
	Write_4spi_OLED_DATA(0x00);	
	Write_4spi_OLED_DATA(0x3f);
	Write_4spi_OLED_CMD(0x5C);
	for(i=0;i<8;i++)
	{
	for(j=0;j<=255;j++)
		{
			Write_4spi_OLED_DATA(Dat1);Write_4spi_OLED_DATA(Dat2);
		}
	}
	
}
void Disp_Pic(uint8_t *p)
{
	uint8_t i,j;
	Write_4spi_OLED_CMD(0x75);//Set page address
	Write_4spi_OLED_DATA(0x00);//starting page address 00~28h//14h 
	Write_4spi_OLED_DATA(0x0A);//Ending page address
	               
	Write_4spi_OLED_CMD(0x15);//Set Column address
	Write_4spi_OLED_DATA(0x00);//Set Column address
	Write_4spi_OLED_DATA(0xff);//Set Column address
	Write_4spi_OLED_CMD(0x5C);
//	for(i=0;i<10;i++)
//	{
        for(j=0;j<255;j++)
		{
			Write_4spi_OLED_DATA(0xff);
		}
//	}
}

void OLED_SetPoint(uint8_t x,uint8_t y)
{
    Write_4spi_OLED_CMD(0x75);//Set page address
	Write_4spi_OLED_DATA(7-y);//starting page address 00~28h//14h 
	Write_4spi_OLED_DATA(0x0A);//Ending page address
	               
	Write_4spi_OLED_CMD(0x15);//Set Column address
	Write_4spi_OLED_DATA(x);//Set Column address
	Write_4spi_OLED_DATA(0xff);//Set Column address
	Write_4spi_OLED_CMD(0x5C);
}



void OLED_Show_Char(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1)
{
	uint8_t i,m,temp,size2,chr1;
	uint8_t x0=x;
	size2=(size1/8+((size1%8)?1:0))*(size1/2); 
	chr1=chr-' ';
//    OLED_SetPoint(x,y);
//    Write_4spi_OLED_DATA(chr);
    
    for(i=0;i<size2;i++)
	{
		if(size1==12)
        {temp = asc2_1206[chr1][i];}
		else if(size1==16)
        {temp = asc2_1608[chr1][i];} 
		else if(size1==24)
        {temp = asc2_2412[chr1][i];} 
		else return;
        
        OLED_SetPoint(x,y);
        Write_4spi_OLED_DATA(temp);
        x++;
        if((x-x0)==size1/2)
        {
            x=x0;
            y++;
        }
        
    }
}

void OLED_Show_Chinese(uint8_t x,uint8_t y,uint8_t chr)
{
    uint8_t i,m,temp,size2,chr1;
    uint8_t x0=x;
    for(i = 0;i<32;i++)
    {
        temp = GB_16X16[0][i];
        OLED_SetPoint(x,y);
        Write_4spi_OLED_DATA(temp);
        x++;
        if((x-x0)==16)
        {
            x=x0;
            y++;
        }
    }
    
    
}
void OLED_Show_Ascil(uint8_t x,uint8_t y,char *chr)
{
    uint8_t temp,i;
    uint8_t x0=x;
    uint8_t BUF[16],BUF_ROW[16];
    ASCII_8X16(chr,BUF);
    RowModeToColumMode(CHAR_MODE_8x16,BUF,BUF_ROW);
    for(i=0;i<16;i++)
	{

        temp = BUF_ROW[i];
        OLED_SetPoint(x,y);
        Write_4spi_OLED_DATA(temp);
        x++;
        if((x-x0)==16/2)
        {
            x=x0;
            y++;
        }
        
    }
    
}

void OLED_Show_GB2312(uint8_t x,uint8_t y,char *chr)
{
    uint8_t temp,i;
    uint8_t x0=x;
    uint8_t BUF[32],BUF_ROW[32];
    GB2312_16X16(chr,BUF);
    RowModeToColumMode(CHAR_MODE_16x16,BUF,BUF_ROW);
    for(i=0;i<32;i++)
	{

        temp = BUF_ROW[i];
        OLED_SetPoint(x,y);
        Write_4spi_OLED_DATA(temp);
        x++;
        if((x-x0)==16)
        {
            x=x0;
            y++;
        }
        
    }
}

void OLED_ShowAscilString(uint8_t x,uint8_t y,uint8_t *chr)
{
	while((*chr>=' ')&&(*chr<='~'))
	{
		OLED_Show_Ascil(x,y,chr);
		x+=8;
		if(x>256-8) 
		{
			x=0;
			y+=2;
        }
        chr++;
    }
}

void OLED_ShowGB2312String(uint8_t x,uint8_t y,uint8_t *chr)
{
	while(*chr !='\0')
	{
        if(*chr != ' ')
            OLED_Show_GB2312(x,y,chr);
        else
        {
            OLED_Show_Ascil(x,y," ");
            OLED_Show_Ascil(x+8,y," ");
        }
		x+=16;
		if(x>256-16) 
		{
			x=0;
			y+=2;
        }
        chr+=2;
    }
}

void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t size1)
{
	while((*chr>=' ')&&(*chr<='~'))
	{
		OLED_Show_Char(x,y,*chr,size1);
		x+=size1/2;
		if(x>256-size1) 
		{
			x=0;
			y+=2;
    }
		chr++;
  }
}

void font2()
{
	int i,j;
    Write_4spi_OLED_CMD(0x30);
    Write_4spi_OLED_CMD(0x15);
    Write_4spi_OLED_DATA(0x00); 
    Write_4spi_OLED_DATA(0xFf); 
    Write_4spi_OLED_CMD(0x75);
    Write_4spi_OLED_DATA(0x00); 
    Write_4spi_OLED_DATA(0x3f); 
    Write_4spi_OLED_CMD(0x5c);

	for(i=0;i<8;i++)
	{
	for(j=0;j<256;j++)	
	{
        Write_4spi_OLED_DATA(0x55); 
	}
	}
}
