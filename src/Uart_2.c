//΢�Ź��ںţ�����������
//����2  115200bps 22.1184MHZ
#define	USER_UART_GLOBALS
//#include<Uart_2.h>
#include "include.h"
#include "wifi.h"
#define S2RI  0x01              //S2CON.0
#define S2TI  0x02              //S2CON.1
static bit busy2=0;//COM2�õ��ķ���æ��־


void INT_Uart2(void) interrupt 8//����2�жϴ������
{
 	
   if (S2CON & 0x02)
    {
        S2CON &= ~0x02;
        busy2 = 0;
    }
    if (S2CON & 0x01)
    {
        S2CON &= ~0x01;			
			  uart_receive_input(S2BUF);             //���Զ˿�      
    }
}
// ����: ���ڳ�ʼ������.
void Init_Uart2(void)
{
	S2CON = 0x10;		//8λ����,�ɱ䲨����
	busy2 = 0;
	IE2 = 0x01;    //ʹ�ܴ���2�ж�	
	
	
}
//COM2����һ���ֽ�
void Send_Data2(unsigned char dat)
{
	
	while (busy2);
  busy2 = 1;
	S2BUF = dat;
}
//COM2����һ���ַ���
void Send_Str2(unsigned char *s)
{
	do
		Send_Data2(*s++);
	while(*s);
}



