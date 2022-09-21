
#include "menu.h"
#include "sht30_i2c_drv.h"

uint8_t key;
u8 main_menu = 0;
u8 user_menu = 0;
u16 rxlen;
D_data ReceiveData;

uint8_t recv_dat[6] = {0};

D_data USARTBufferToD_data(u8 *RxBuffer)
{
    D_data USARTBuffer;
    
    
     
    
    USARTBuffer.PMTSP   = (RxBuffer[2]<<8)+RxBuffer[1];
    USARTBuffer.PM10    = (RxBuffer[4]<<8)+RxBuffer[3];
    USARTBuffer.PM5     = (RxBuffer[6]<<8)+RxBuffer[5];
    USARTBuffer.PM2_5   = (RxBuffer[8]<<8)+RxBuffer[7];
    USARTBuffer.PM1     = (RxBuffer[10]<<8)+RxBuffer[9];
    USARTBuffer.PMc     = (RxBuffer[12]<<8)+RxBuffer[11];
    USARTBuffer.Pmax    = (RxBuffer[14]<<8)+RxBuffer[13];
    USARTBuffer.ALM     = (RxBuffer[16]<<8)+RxBuffer[15];
    USARTBuffer.LPDV    = (RxBuffer[18]<<8)+RxBuffer[17];
    USARTBuffer.Ver     = (RxBuffer[20]<<8)+RxBuffer[19];
    USARTBuffer.Pmin    = (RxBuffer[22]<<8)+RxBuffer[21];
    USARTBuffer.SUM     = (RxBuffer[24]<<8)+RxBuffer[23];
    
    return USARTBuffer;
}

void GetUsartBuf()
{
    if(SHT30_Read_Dat(recv_dat) == HAL_OK)
    {
        if(SHT30_Dat_To_Float(recv_dat, &ReceiveData.temperature, &ReceiveData.humidity)==0)
        {
//				printf("temperature = %f, humidity = %f\n", temperature, humidity);
        }
        else
        {
//				printf("crc check fail.\n");
        }
    }
    if(USART_RX_STA&0x8000)
    {					   
        rxlen=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
        ReceiveData = USARTBufferToD_data(USART_RX_BUF);
        USART_RX_STA=0;  
    }
}

void Accessibility_Menu()
{
    u8 accessibility_menu = 0;
    uint8_t strbuf[32];
    static u8 menu_x = 14*8,menu_y = 2;
    while(1)
    {
        OLED_ShowGB2312String(0,0,"            辅助功能              ");
        OLED_ShowGB2312String(0,2,"  滤膜称重校准                    ");
        OLED_ShowGB2312String(0,4,"  流量校准                        ");
        OLED_ShowGB2312String(0,6,"                                 ");
        key=KEY_Scan(0);
        if(key == KEY5_PRES)
        {
            accessibility_menu++;
            menu_y+=2;
//            if(menu_y>4)
//            {
                if(accessibility_menu>1)
                {
                    accessibility_menu = 0;
                    menu_x = 14*8;
                    menu_y = 2;
                }
                else
                {

                }
//            }
        }
        else if(key == KEY6_PRES)
        {
            if(accessibility_menu != 0)
                accessibility_menu--;
            else
                accessibility_menu = 1;
            menu_y-=2;
            if(menu_y<2)
            {
                if(accessibility_menu<2)
                {
                    menu_x = 14*8;
                    menu_y = 4;
                }
                else
                {
                    menu_y = 4;
                    menu_x = 28*8;
                }
            }
        }
        else if(key == KEY7_PRES)
            break;
        else if(key == KEY8_PRES)
        {
            clealddram();
            switch(accessibility_menu)
            {
                case 0:break;
                case 1:break;
            }
        }
        sprintf(strbuf,"%d",key);
        OLED_ShowAscilString(menu_x,menu_y,"<");
    }
}

void DiffMass_Menu()
{
    u8 diffmass_menu = 0;
    uint8_t strbuf[32];
    static u8 menu_x = 14*8,menu_y = 2;
    while(1)
    {
        GetUsartBuf();
        OLED_ShowGB2312String(0,0,"          差分质量浓度            ");
        sprintf(strbuf," M  c:%5d   M5.0:%5d         ",ReceiveData.PMc,ReceiveData.PM5);
        OLED_ShowAscilString (0,2,strbuf);
        sprintf(strbuf," M1.0:%5d   M 10:%5d  %2.f%RH  ",ReceiveData.PM1,ReceiveData.PM10,ReceiveData.humidity);
        OLED_ShowAscilString (0,4,strbuf);
        sprintf(strbuf," M2.5:%5d   TSP :%5d   %2.f",ReceiveData.PM2_5,ReceiveData.PMTSP,ReceiveData.temperature);
        OLED_ShowAscilString (0,6,strbuf);
        OLED_ShowGB2312String(29*8,6,"℃");
        key=KEY_Scan(0);
        if(key == KEY5_PRES)
        {

        }
        else if(key == KEY6_PRES)
        {

        }
        else if(key == KEY7_PRES)
            break;
        else if(key == KEY8_PRES)
        {

        }
//        sprintf(strbuf,"%d",key);
//        OLED_ShowAscilString(menu_x,menu_y,"<");
    }
}

void DiffPart_Menu()
{
    uint8_t strbuf[32];
    static u8 menu_x = 14*8,menu_y = 2;
    while(1)
    {
        OLED_ShowGB2312String(0,0,"        差分粒子数浓度            ");
        OLED_ShowAscilString (0,2," M  c: 20     M5.0:7526          ");
        OLED_ShowAscilString (0,4," M1.0: 20     M 10:12345  66%RH  ");
        OLED_ShowAscilString (0,6," M2.5: 20     TSP:123123   26");
        OLED_ShowGB2312String(29*8,6,"℃");
        key=KEY_Scan(0);
        if(key == KEY5_PRES)
        {

        }
        else if(key == KEY6_PRES)
        {

        }
        else if(key == KEY7_PRES)
            break;
        else if(key == KEY8_PRES)
        {

        }
//        sprintf(strbuf,"%d",key);
//        OLED_ShowAscilString(menu_x,menu_y,"<");
    }
}

void CumuMass_Menu()
{
    u8 diffmass_menu = 0;
    uint8_t strbuf[32];
    static u8 menu_x = 14*8,menu_y = 2;
    while(1)
    {
        OLED_ShowGB2312String(0,0,"          累加质量浓度            ");
        OLED_ShowAscilString (0,2," M  c: 20     M5.0:7526          ");
        OLED_ShowAscilString (0,4," M1.0: 20     M 10:12345  66%RH  ");
        OLED_ShowAscilString (0,6," M2.5: 20     TSP:123123   26");
        OLED_ShowGB2312String(29*8,6,"℃");
        key=KEY_Scan(0);
        if(key == KEY5_PRES)
        {

        }
        else if(key == KEY6_PRES)
        {

        }
        else if(key == KEY7_PRES)
            break;
        else if(key == KEY8_PRES)
        {

        }
//        sprintf(strbuf,"%d",key);
//        OLED_ShowAscilString(menu_x,menu_y,"<");
    }
}

void CumuPart_Menu()
{
    u8 diffmass_menu = 0;
    uint8_t strbuf[32];
    static u8 menu_x = 14*8,menu_y = 2;
    while(1)
    {
        OLED_ShowGB2312String(0,0,"        累加粒子数浓度            ");
        OLED_ShowAscilString (0,2," M  c: 20     M5.0:7526          ");
        OLED_ShowAscilString (0,4," M1.0: 20     M 10:12345  66%RH  ");
        OLED_ShowAscilString (0,6," M2.5: 20     TSP:123123   26");
        OLED_ShowGB2312String(29*8,6,"℃");
        key=KEY_Scan(0);
        if(key == KEY5_PRES)
        {

        }
        else if(key == KEY6_PRES)
        {

        }
        else if(key == KEY7_PRES)
            break;
        else if(key == KEY8_PRES)
        {

        }
//        sprintf(strbuf,"%d",key);
//        OLED_ShowAscilString(menu_x,menu_y,"<");
    }
}

void MeaValue_Menu()
{
    u8 meavalue_menu = 0; 
    uint8_t strbuf[32];
    static u8 menu_x = 16*8,menu_y = 2;
    while(1)
    {
        OLED_ShowGB2312String(0,0,"          测量值显示            ");
        OLED_ShowGB2312String(0,2,"  差分粒子数浓度  差分质量浓度  ");
        OLED_ShowGB2312String(0,4,"  累加粒子数浓度  累加质量浓度  ");
        OLED_ShowGB2312String(0,6,"                               ");
        key=KEY_Scan(0);
        if(key == KEY5_PRES)
        {
            meavalue_menu++;
            menu_y+=2;
            if(menu_y>4)
            {
                if(meavalue_menu>2)
                {
                    meavalue_menu = 0;
                    menu_x = 16*8;
                    menu_y = 2;
                }
                else
                {
                    menu_y = 2;
                    menu_x = 16*15;
                }
            }
        }
        else if(key == KEY6_PRES)
        {
            if(meavalue_menu != 0)
                meavalue_menu--;
            else
                meavalue_menu = 3;
            menu_y-=2;
            if(menu_y<2)
            {
                if(meavalue_menu<2)
                {
                    menu_x = 16*8;
                    menu_y = 4;
                }
                else
                {
                    menu_y = 4;
                    menu_x = 16*15;
                }
            }
        }
        else if(key == KEY7_PRES)
            break;
        else if(key == KEY8_PRES)
        {
            switch(meavalue_menu)
            {
                case 0:DiffPart_Menu();break;
                case 1:CumuPart_Menu();break;
                case 2:DiffMass_Menu();break;
                case 3:CumuMass_Menu();break;
            }
        }
        sprintf(strbuf,"%d",key);
        OLED_ShowAscilString(menu_x,menu_y,"<");
    }
}

void SysState_Menu()
{
    u8 sysstate_menu = 0;
    uint8_t strbuf[32];
    static u8 menu_x = 14*8,menu_y = 2;
    RTC_DateTypeDef rdata;
    RTC_TimeTypeDef rtime;
    while(1)
    {
        GetUsartBuf();
        OLED_ShowGB2312String(0,0,"            系统状态              ");
        OLED_ShowGB2312String(16,2,"版本号：");
        OLED_ShowGB2312String(8*16,2,"运行时间：");
        OLED_ShowGB2312String(16,4,"采样流量：");
        OLED_ShowGB2312String(8*16,4,"电池电量：");
        OLED_ShowGB2312String(16,6,"日期时间：");
        
        sprintf(strbuf,"%d",ReceiveData.Ver);
        OLED_ShowAscilString(5*16,2,strbuf);
        OLED_ShowAscilString(13*16,2,"10S");
        OLED_ShowAscilString(6*16,4,"    ");
        OLED_ShowAscilString(13*16,4,"100%");

        HAL_RTC_GetTime(&hrtc,&rtime,RTC_FORMAT_BIN);
        HAL_RTC_GetDate(&hrtc,&rdata,RTC_FORMAT_BIN);

        sprintf(strbuf,"20%02d-%02d-%02d-%02d:%02d:%02d  ",rdata.Year,rdata.Month,rdata.Date,rtime.Hours,rtime.Minutes,rtime.Seconds);
        OLED_ShowAscilString (6*16,6,strbuf);
        key=KEY_Scan(0);
        if(key == KEY5_PRES)
        {
            sysstate_menu++;
            menu_y+=2;
//            if(menu_y>4)
//            {
                if(sysstate_menu>1)
                {
                    sysstate_menu = 0;
                    menu_x = 14*8;
                    menu_y = 2;
                }
                else
                {

                }
//            }
        }
        else if(key == KEY6_PRES)
        {
            if(sysstate_menu != 0)
                sysstate_menu--;
            else
                sysstate_menu = 1;
            menu_y-=2;
            if(menu_y<2)
            {
                if(sysstate_menu<2)
                {
                    menu_x = 14*8;
                    menu_y = 4;
                }
                else
                {
                    menu_y = 4;
                    menu_x = 28*8;
                }
            }
        }
        else if(key == KEY7_PRES)
            break;
        else if(key == KEY8_PRES)
        {
            switch(sysstate_menu)
            {
                case 0:break;
                case 1:break;
                case 2:break;
                case 3:break;
            }
        }
//        sprintf(strbuf,"%d",key);
//        OLED_ShowAscilString(menu_x,menu_y,"<");
    }
}

void State_Menu()
{
    u8 state_menu = 0;
    uint8_t strbuf[32];
    static u8 menu_x = 14*8,menu_y = 2;
    while(1)
    {
        OLED_ShowGB2312String(0,0,"            状态显示              ");
        OLED_ShowGB2312String(0,2,"    测量值显示                    ");
        OLED_ShowGB2312String(0,4,"    系统状态                      ");
        OLED_ShowGB2312String(0,6,"                                 ");
        key=KEY_Scan(0);
        if(key == KEY5_PRES)
        {
            state_menu++;
            menu_y+=2;
//            if(menu_y>4)
//            {
                if(state_menu>1)
                {
                    state_menu = 0;
                    menu_x = 14*8;
                    menu_y = 2;
                }
                else
                {

                }
//            }
        }
        else if(key == KEY6_PRES)
        {
            if(state_menu != 0)
                state_menu--;
            else
                state_menu = 1;
            menu_y-=2;
            if(menu_y<2)
            {
                if(state_menu<2)
                {
                    menu_x = 14*8;
                    menu_y = 4;
                }
                else
                {
                    menu_y = 4;
                    menu_x = 28*8;
                }
            }
        }
        else if(key == KEY7_PRES)
            break;
        else if(key == KEY8_PRES)
        {
            clealddram();
            switch(state_menu)
            {
                case 0:MeaValue_Menu();break;
                case 1:SysState_Menu();break;
            }
        }
        sprintf(strbuf,"%d",key);
        OLED_ShowAscilString(menu_x,menu_y,"<");
    }
}

void TimeSet_Menu()
{
    u8 rtc_cnt = 0;
    u8 timset_menu = 0;
    uint8_t strbuf[32];
    static u8 menu_x = 14*8,menu_y = 2;
    RTC_DateTypeDef rdata;
    RTC_TimeTypeDef rtime;
    while(1)
    {
        OLED_ShowGB2312String(0,0,"          日期时间设置            ");
        sprintf(strbuf,"      20%02d-%02d-%02d-%02d:%02d:%02d        ",rdata.Year,rdata.Month,rdata.Date,rtime.Hours,rtime.Minutes,rtime.Seconds);
        OLED_ShowAscilString (0,2,strbuf);
        OLED_ShowGB2312String(0,4,"                                 ");
        OLED_ShowGB2312String(0,6,"                                 ");
        key=KEY_Scan(0);
        
        OLED_ShowAscilString(56+24*rtc_cnt,2,"  ");
        if(key == KEY5_PRES)
        {
            switch(rtc_cnt)
            {
                case 0:if(rdata.Year<99)rdata.Year++;break;
                case 1:if(rdata.Month<11)rdata.Month++;break;
                case 2:if(rdata.Date<30)rdata.Date++;break;
                case 3:if(rtime.Hours<23)rtime.Hours++;break;
                case 4:if(rtime.Minutes<59)rtime.Minutes++;break;
                case 5:if(rtime.Seconds<59)rtime.Seconds++;break;
            }
        }
        else if(key == KEY6_PRES)
        {
            switch(rtc_cnt)
            {
                case 0:if(rdata.Year!=0)rdata.Year--;break;
                case 1:if(rdata.Month!=0)rdata.Month--;break;
                case 2:if(rdata.Date!=0)rdata.Date--;break;
                case 3:if(rtime.Hours!=0)rtime.Hours--;break;
                case 4:if(rtime.Minutes!=0)rtime.Minutes--;break;
                case 5:if(rtime.Seconds!=0)rtime.Seconds--;break;
            }
        }
        else if(key == KEY7_PRES)
        {
            HAL_RTC_SetTime(&hrtc, &rtime, RTC_FORMAT_BIN);
            HAL_RTC_SetDate(&hrtc, &rdata, RTC_FORMAT_BCD);
            break;
        }
        else if(key == KEY8_PRES)
        {
            rtc_cnt++;
            if(rtc_cnt == 6)
            {
                rtc_cnt = 0;
            }
        }
//        sprintf(strbuf,"%d",key);
//        OLED_ShowAscilString(menu_x,menu_y,"<");
    }
}

void CommunData_Menu()
{
    
    uint8_t strbuf[32];
    static u8 menu_x = 14*8,menu_y = 2;
    while(1)
    {
        OLED_ShowGB2312String(0,0,"              通信数据            ");
        OLED_ShowGB2312String(16,2,"仪器地址：");
        OLED_ShowGB2312String(9*16,2,"波特率："); 
        OLED_ShowGB2312String(16,4,"校验方式：无");
        
        OLED_ShowAscilString(6*16,2,"255");
        OLED_ShowAscilString(13*16,2,"115200");
        key=KEY_Scan(0);
        if(key == KEY5_PRES)
        {

        }
        else if(key == KEY6_PRES)
        {

        }
        else if(key == KEY7_PRES)
            break;
        else if(key == KEY8_PRES)
        {

        }
//        sprintf(strbuf,"%d",key);
//        OLED_ShowAscilString(menu_x,menu_y,"<");
    }
}

void SaveTime_Menu()
{
    uint8_t strbuf[32];
    static u8 menu_x = 14*8,menu_y = 2;
    while(1)
    {
        OLED_ShowGB2312String(0,0,"          数据存贮间隔            ");
        OLED_ShowAscilString (0,2,"                                 ");
        OLED_ShowGB2312String(0,4,"                                 ");
        OLED_ShowGB2312String(0,6,"                                 ");
        key=KEY_Scan(0);
        if(key == KEY5_PRES)
        {

        }
        else if(key == KEY6_PRES)
        {

        }
        else if(key == KEY7_PRES)
            break;
        else if(key == KEY8_PRES)
        {

        }
//        sprintf(strbuf,"%d",key);
//        OLED_ShowAscilString(menu_x,menu_y,"<");
    }
}

void BatteryLevel_Menu()
{
    uint8_t strbuf[32];
    static u8 menu_x = 14*8,menu_y = 2;
    while(1)
    {
        OLED_ShowGB2312String(0,0,"          电池电量阈值            ");
        
        OLED_ShowGB2312String(16,2,"电池电量低于：");
        OLED_ShowAscilString(16*8,2,"20%");
        
        key=KEY_Scan(0);
        if(key == KEY5_PRES)
        {

        }
        else if(key == KEY6_PRES)
        {

        }
        else if(key == KEY7_PRES)
            break;
        else if(key == KEY8_PRES)
        {

        }
//        sprintf(strbuf,"%d",key);
//        OLED_ShowAscilString(menu_x,menu_y,"<");
    }
}

void PumpSpeed_Menu()
{
    uint8_t strbuf[32];
    static u8 menu_x = 14*8,menu_y = 2;
    while(1)
    {
        OLED_ShowGB2312String(0,0,"          泵速高低阈值            ");
        
        OLED_ShowGB2312String(16,2,"泵控制脉宽超过上限：");
        OLED_ShowAscilString(16*11,2,"80%");
        
        OLED_ShowGB2312String(16,4,"泵控制脉宽超过下限：");
        OLED_ShowAscilString(16*11,4,"20%");
        
        key=KEY_Scan(0);
        if(key == KEY5_PRES)
        {

        }
        else if(key == KEY6_PRES)
        {

        }
        else if(key == KEY7_PRES)
            break;
        else if(key == KEY8_PRES)
        {

        }
//        sprintf(strbuf,"%d",key);
//        OLED_ShowAscilString(menu_x,menu_y,"<");
    }
}

void BaselineLevel_Menu()
{
    uint8_t strbuf[32];
    static u8 menu_x = 14*8,menu_y = 2;
    while(1)
    {
        OLED_ShowGB2312String(0,0,"          基线电平阈值            ");
        
        OLED_ShowGB2312String(16,2,"基线电平超过上限：");
        OLED_ShowAscilString(16*10,2,"1000mV");
        
        OLED_ShowGB2312String(16,4,"基线电平超过下限：");
        OLED_ShowAscilString(16*10,4,"20mV");
        
        key=KEY_Scan(0);
        if(key == KEY5_PRES)
        {

        }
        else if(key == KEY6_PRES)
        {

        }
        else if(key == KEY7_PRES)
            break;
        else if(key == KEY8_PRES)
        {

        }
//        sprintf(strbuf,"%d",key);
//        OLED_ShowAscilString(menu_x,menu_y,"<");
    }
}

void Laser_Menu()
{
    uint8_t strbuf[32];
    static u8 menu_x = 14*8,menu_y = 2;
    while(1)
    {
        OLED_ShowGB2312String(0,0,"            激光异常              ");
        
        
        key=KEY_Scan(0);
        if(key == KEY5_PRES)
        {

        }
        else if(key == KEY6_PRES)
        {

        }
        else if(key == KEY7_PRES)
            break;
        else if(key == KEY8_PRES)
        {

        }
//        sprintf(strbuf,"%d",key);
//        OLED_ShowAscilString(menu_x,menu_y,"<");
    }
}

void WarnningSet_Menu()
{
    u8 warnningset_menu = 0;
    uint8_t strbuf[32];
    static u8 menu_x = 16*5,menu_y = 2;
    while(1)
    {
        OLED_ShowGB2312String(0,0,"        报警阈值设定            ");
        OLED_ShowGB2312String(0,2,"  电池电量        激光异常      ");
        OLED_ShowGB2312String(0,4,"  基线电平        泵速高低      ");
        OLED_ShowGB2312String(0,6,"                               ");
        key=KEY_Scan(0);
        if(key == KEY5_PRES)
        {
            warnningset_menu++;
            menu_y+=2;
            if(menu_y>4)
            {
                if(warnningset_menu>2)
                {
                    warnningset_menu = 0;
                    menu_x = 16*5;
                    menu_y = 2;
                }
                else
                {
                    menu_y = 2;
                    menu_x = 16*13;
                }
            }
        }
        else if(key == KEY6_PRES)
        {
            if(warnningset_menu != 0)
                warnningset_menu--;
            else
                warnningset_menu = 3;
            menu_y-=2;
            if(menu_y<2)
            {
                if(warnningset_menu<2)
                {
                    menu_x = 16*5;
                    menu_y = 4;
                }
                else
                {
                    menu_y = 4;
                    menu_x = 16*13;
                }
            }
        }
        else if(key == KEY7_PRES)
            break;
        else if(key == KEY8_PRES)
        {
            clealddram();
            switch(warnningset_menu)
            {
                case 0:BatteryLevel_Menu();break;
                case 1:BaselineLevel_Menu();break;
                case 2:Laser_Menu();break;
                case 3:PumpSpeed_Menu();break;
            }
        }
        sprintf(strbuf,"%d",key);
        OLED_ShowAscilString(menu_x,menu_y,"<");
    }
}

void DefaultShow_Menu()
{
    uint8_t strbuf[32];
    static u8 menu_x = 14*8,menu_y = 2;
    while(1)
    {
        OLED_ShowGB2312String(0,0,"        默认测量显示格式          ");
        OLED_ShowAscilString (0,2,"                                 ");
        OLED_ShowGB2312String(0,4,"                                 ");
        OLED_ShowGB2312String(0,6,"                                 ");
        key=KEY_Scan(0);
        if(key == KEY5_PRES)
        {

        }
        else if(key == KEY6_PRES)
        {

        }
        else if(key == KEY7_PRES)
            break;
        else if(key == KEY8_PRES)
        {

        }
//        sprintf(strbuf,"%d",key);
//        OLED_ShowAscilString(menu_x,menu_y,"<");
    }
}


void User_Menu()
{
    
    uint8_t strbuf[32];
    static u8 menu_x = 14*8,menu_y = 2;
    while(1)
    {
        OLED_ShowGB2312String(0,0,"            用户参数            ");
        OLED_ShowGB2312String(0,2,"  日期时间设置  数据存贮间隔    ");
        OLED_ShowGB2312String(0,4,"  报警阈值设定  默认显示格式    ");
        OLED_ShowGB2312String(0,6,"                               ");
        key=KEY_Scan(0);
        if(key == KEY5_PRES)
        {
            user_menu++;
            menu_y+=2;
            if(menu_y>4)
            {
                if(user_menu>2)
                {
                    user_menu = 0;
                    menu_x = 14*8;
                    menu_y = 2;
                }
                else
                {
                    menu_y = 2;
                    menu_x = 28*8;
                }
            }
        }
        else if(key == KEY6_PRES)
        {
            if(user_menu != 0)
                user_menu--;
            else
                user_menu = 3;
            menu_y-=2;
            if(menu_y<2)
            {
                if(user_menu<2)
                {
                    menu_x = 14*8;
                    menu_y = 4;
                }
                else
                {
                    menu_y = 4;
                    menu_x = 28*8;
                }
            }
        }
        else if(key == KEY7_PRES)
            break;
        else if(key == KEY8_PRES)
        {
            switch(user_menu)
            {
                case 0:TimeSet_Menu();break;
                case 1:WarnningSet_Menu();break;
                case 2:SaveTime_Menu();break;
                case 3:DefaultShow_Menu();break;
            }
        }
        sprintf(strbuf,"%d",key);
        OLED_ShowAscilString(menu_x,menu_y,"<");
    }
}





void menu_run()
{
    uint8_t strbuf[32];
    static u8 main_x = 12*8,main_y = 2;
    OLED_ShowGB2312String(0,0,"            郎亿机电            ");
    OLED_ShowGB2312String(0,2,"    状态显示        用户参数    ");
    OLED_ShowGB2312String(0,4,"    通信数据        辅助功能    ");
    OLED_ShowGB2312String(0,6,"    报警状态        系统参数    ");
    key=KEY_Scan(0);
    if(key == KEY5_PRES)
    {
        main_menu++;
        main_y+=2;
        if(main_y>6)
        {
            if(main_menu>3)
            {
                main_menu = 0;
                main_x = 12*8;
                main_y = 2;
            }
            else
            {
                main_y = 2;
                main_x = 28*8;
            }
        }
    }
    else if(key == KEY6_PRES)
    {
        if(main_menu != 0)
            main_menu--;
        else
            main_menu = 5;
        main_y-=2;
        if(main_y<2)
        {
            if(main_menu<4)
            {
                main_x = 12*8;
                main_y = 6;
            }
            else
            {
                main_y = 6;
                main_x = 28*8;
            }
        }
    }
    else if(key == KEY8_PRES)
    {
        clealddram();
        switch(main_menu)
        {
            case 0:State_Menu();break;
            case 1:CommunData_Menu();break;
            case 2:break;
            case 3:User_Menu();break;
            case 4:Accessibility_Menu();break;
            case 5:break;
        }
    }
    sprintf(strbuf,"%d",key);
    OLED_ShowAscilString(main_x,main_y,"<");
}