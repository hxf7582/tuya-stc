/******************************************************************************
文件名称: Main.c
文件标识: STC8A8K64S4A12
摘    要: 主函数
当前版本: V1.0	
完成日期: 2021.02.07
*******************************************************************************/
#define MAINWORK_GLOBALS
#include "include.h"
#include "wifi.h"
volatile uint8_t is_read_time = 0;
uint8_t wifi_state;
/*****************************************************************************
函数名称 : Bsp_Init
功能描述 : 初始化硬件
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
static void Bsp_Init(void)
{ 
	P0M1 = 0x00; P0M0 = 0x00; //P0
  P1M1 = 0x00; P1M0 = 0x48; //P1(00000000B,01001000B)
	LED6=0;  //开关关
	Init_Uart2();
	Init_Uart1();//串口1-2初始化       
	wifi_protocol_init();//WiFi模组初始化
	I2C_init();          //I2C初始化	
	SHT_Init();          //SHT3X初始化
	timer0_init();       //定时器初始化	
	key_init();
	OLED_Init();         //OLED初始化
	OLED_Clear();        //OLED清屏
}
/*****************************************************************************
函数名称 : Boot_animation
功能描述 : 开机画面
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void Boot_animation()
{
	OLED_DrawBMP(0,0,128,8,table);
  delay_ms(1000);		
	OLED_Clear();	
	OLED_DrawBMP(0,1,128,4,tableeda);
	OLED_ShowStr(32,5,"OSHWHub",16);
	delay_ms(1500);
	OLED_Clear();
		
	OLED_ShowCHinese(10,2,0);
	OLED_ShowCHinese(28,2,1);
	OLED_ShowCHinese(46,2,2);
	OLED_ShowCHinese(62,2,3);
	OLED_ShowCHinese(80,2,4);
  OLED_ShowCHinese(98,2,5);
	
	OLED_ShowCHinese(28,4,2);
  OLED_ShowCHinese(46,4,4);
	OLED_ShowStr(60,4,":",16);
	OLED_ShowStr(88,4,".",16);
	
	OLED_ShowCHinese(28,6,3);
	OLED_ShowCHinese(46,6,4);
  OLED_ShowStr(60,6,":",16);
}


/*****************************************************************************
函数名称 : wifi_work_state_led
功能描述 : wifi状态查询
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void wifi_work_state_led(void)
{
  wifi_state = mcu_get_wifi_work_state();
	switch(wifi_state)
	{
	case SMART_CONFIG_STATE:            //smartconfig配置状态
	  OLED_ShowStr(110,0,"S!",8);	
	  OLED_ShowStr(122,0," ",8);
	  P0=0xFF;
	  LED1=0;
		break;
		
	case AP_STATE:                      //AP配置状态
	  OLED_ShowStr(110,0,"A!",8);
	  OLED_ShowStr(122,0," ",8);
	  P0=0xFF;
	  LED2=0;
		break;
		
	case WIFI_NOT_CONNECTED:            //WIFI配置成功但未连上路由器
		OLED_DrawBMP(0,0,24,1,UI1);
		//OLED_ShowStr(24,0,"  ",8);
		break;
		
	case WIFI_CONNECTED:                //WIFI配置成功且连上路由器
		OLED_DrawBMP(0,0,24,1,UI2);
		OLED_ShowStr(24,0,"                 ",8);
	  P0=0xFF;
	  LED4=0;
		break;
		
	case WIFI_CONN_CLOUD:               //WIFI已经连接上云服务器
		OLED_DrawBMP(0,0,16,1,UI3);
		OLED_ShowStr(24,0,"              ",8);
	 
	  P0=0xFF;
	  LED4=0;
	  LED5=0;
		break;
		
	case WIFI_LOW_POWER:                //WIFI处于低功耗模式
		OLED_DrawBMP(0,0,24,1,UI4);
		//OLED_ShowStr(24,0,"  ",8);
		break;
		
	case SMART_AND_AP_STATE:            //WIFI smartconfig&AP 模式
		OLED_ShowStr(110,0,"SA",8);
	  OLED_ShowStr(122,0," ",8);
	  P0=0xFF;
	  LED3=0;
		break;
		
	default:                            //未知状态
    OLED_DrawBMP(0,0,24,1,UI1);
		//OLED_ShowStr(24,0,"  ",8);
		OLED_ShowStr(36,0,"WiFiStartr",8);
	  P0=0xFF;
	  LED3=0;
	 break;
	}
}
/*****************************************************************************
函数名称 : read_sensor
功能描述 : 读取传感器
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
static void read_sensor(void)
{	
	//Get_Voltage();         //读取电池电压
	sht30_read();          //读取温湿度	
}
/*****************************************************************************
函数名称 : main
功能描述 : 主函数
输入参数 : 无
返回参数 : 无
使用说明 : 无
*****************************************************************************/
void main(void)
{		
	Bsp_Init();//初始化	
  Boot_animation();//开机动画		
	read_sensor();
	while(1)
	{	
		wifi_uart_service();	 //wifi数据处理		
		key_scan();            //按键扫描		
		wifi_work_state_led(); //wifi状态指示灯
		if(is_read_time == 1)  //15秒读取一次
		{	
						
			LED5=1;	
			OLED_DrawBMP(0,0,24,1,UI3);
		  sht30_read();          //读取温湿度                //读取传感器并上报   
		
			delay_ms(500);			
			OLED_ShowStr(18,0," ",8);
		  is_read_time = 0;
		}
	}
	
}