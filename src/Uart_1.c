//����1
//#include<Uart_1.h>
#define	USER_UART_GLOBALS
#include "wifi.h"
#include "include.h"
static bit busy1=0;//COM1�õ��ķ���æ��־
char wptr;
char rptr;
char buffer[16];

//����1�жϴ������
void INT_Uart1(void) interrupt 4
{
	
	if(TI)//��շ����жϱ�־λ
	{
		TI = 0;
		
	if (RI)
    {
        RI = 0;
        buffer[wptr++] = SBUF;
        wptr &= 0x0f;
			
    }	
	}
}
// ����: ���ڳ�ʼ������.
void Init_Uart1(void)
{
	SCON = 0x50;//
	AUXR |= 0x01;//��ʱ��2��1T
	AUXR |= 0x04;
	T2L = BRT;
  T2H = BRT >> 8;		//�趨��ʱ��ֵ  115200    22.1184MHZ
	AUXR |= 0x10;		//������ʱ��2
	ES = 1;//����COM1���п��ж�
	TI = 1;	
	EA = 1;		//����ȫ���ж�
	REN = 1;	//�������
	IE2 = ES2;  //ʹ�ܴ����ж�
	SBUF = 0x55; 
}
/*
//COM1����һ���ֽ�
void Send_Data1(unsigned char dat)
{
	
	
	while(!TI);           //��TI=0���ڴ˵ȴ�
    TI = 0;  
	SBUF = dat;
}
//����һ���ַ���
void Send_Str1(unsigned char *s)
{
	while(*s)
	{
		Send_Data1(*s++);
	}
}
void SendString(unsigned char *s)
{
	while(*s!='\0')
	{
		Send_Data1(*s);	//����SendData()�������η��͵��ֽ�����
		s++;					//ָ�����������ڷ�����һ������
	}
}
*/