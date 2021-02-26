/******************************************************************************
�ļ�����: Main.c
�ļ���ʶ: STC8A8K64S4A12
ժ    Ҫ: ������
��ǰ�汾: V1.0	
�������: 2021.02.07
*******************************************************************************/
#define MAINWORK_GLOBALS
#include "include.h"
#include "wifi.h"
volatile uint8_t is_read_time = 0;
uint8_t wifi_state;
/*****************************************************************************
�������� : Bsp_Init
�������� : ��ʼ��Ӳ��
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
static void Bsp_Init(void)
{ 
	P0M1 = 0x00; P0M0 = 0x00; //P0
  P1M1 = 0x00; P1M0 = 0x48; //P1(00000000B,01001000B)
	LED6=0;  //���ع�
	Init_Uart2();
	Init_Uart1();//����1-2��ʼ��       
	wifi_protocol_init();//WiFiģ���ʼ��
	I2C_init();          //I2C��ʼ��	
	SHT_Init();          //SHT3X��ʼ��
	timer0_init();       //��ʱ����ʼ��	
	key_init();
	OLED_Init();         //OLED��ʼ��
	OLED_Clear();        //OLED����
}
/*****************************************************************************
�������� : Boot_animation
�������� : ��������
������� : ��
���ز��� : ��
ʹ��˵�� : ��
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
�������� : wifi_work_state_led
�������� : wifi״̬��ѯ
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void wifi_work_state_led(void)
{
  wifi_state = mcu_get_wifi_work_state();
	switch(wifi_state)
	{
	case SMART_CONFIG_STATE:            //smartconfig����״̬
	  OLED_ShowStr(110,0,"S!",8);	
	  OLED_ShowStr(122,0," ",8);
	  P0=0xFF;
	  LED1=0;
		break;
		
	case AP_STATE:                      //AP����״̬
	  OLED_ShowStr(110,0,"A!",8);
	  OLED_ShowStr(122,0," ",8);
	  P0=0xFF;
	  LED2=0;
		break;
		
	case WIFI_NOT_CONNECTED:            //WIFI���óɹ���δ����·����
		OLED_DrawBMP(0,0,24,1,UI1);
		//OLED_ShowStr(24,0,"  ",8);
		break;
		
	case WIFI_CONNECTED:                //WIFI���óɹ�������·����
		OLED_DrawBMP(0,0,24,1,UI2);
		OLED_ShowStr(24,0,"                 ",8);
	  P0=0xFF;
	  LED4=0;
		break;
		
	case WIFI_CONN_CLOUD:               //WIFI�Ѿ��������Ʒ�����
		OLED_DrawBMP(0,0,16,1,UI3);
		OLED_ShowStr(24,0,"              ",8);
	 
	  P0=0xFF;
	  LED4=0;
	  LED5=0;
		break;
		
	case WIFI_LOW_POWER:                //WIFI���ڵ͹���ģʽ
		OLED_DrawBMP(0,0,24,1,UI4);
		//OLED_ShowStr(24,0,"  ",8);
		break;
		
	case SMART_AND_AP_STATE:            //WIFI smartconfig&AP ģʽ
		OLED_ShowStr(110,0,"SA",8);
	  OLED_ShowStr(122,0," ",8);
	  P0=0xFF;
	  LED3=0;
		break;
		
	default:                            //δ֪״̬
    OLED_DrawBMP(0,0,24,1,UI1);
		//OLED_ShowStr(24,0,"  ",8);
		OLED_ShowStr(36,0,"WiFiStartr",8);
	  P0=0xFF;
	  LED3=0;
	 break;
	}
}
/*****************************************************************************
�������� : read_sensor
�������� : ��ȡ������
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
static void read_sensor(void)
{	
	//Get_Voltage();         //��ȡ��ص�ѹ
	sht30_read();          //��ȡ��ʪ��	
}
/*****************************************************************************
�������� : main
�������� : ������
������� : ��
���ز��� : ��
ʹ��˵�� : ��
*****************************************************************************/
void main(void)
{		
	Bsp_Init();//��ʼ��	
  Boot_animation();//��������		
	read_sensor();
	while(1)
	{	
		wifi_uart_service();	 //wifi���ݴ���		
		key_scan();            //����ɨ��		
		wifi_work_state_led(); //wifi״ָ̬ʾ��
		if(is_read_time == 1)  //15���ȡһ��
		{	
						
			LED5=1;	
			OLED_DrawBMP(0,0,24,1,UI3);
		  sht30_read();          //��ȡ��ʪ��                //��ȡ���������ϱ�   
		
			delay_ms(500);			
			OLED_ShowStr(18,0," ",8);
		  is_read_time = 0;
		}
	}
	
}