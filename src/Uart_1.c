//串口1
//#include<Uart_1.h>
#define	USER_UART_GLOBALS
#include "wifi.h"
#include "include.h"
static bit busy1=0;//COM1用到的发送忙标志
char wptr;
char rptr;
char buffer[16];

//串口1中断处理程序
void INT_Uart1(void) interrupt 4
{
	
	if(TI)//清空发送中断标志位
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
// 描述: 串口初始化程序.
void Init_Uart1(void)
{
	SCON = 0x50;//
	AUXR |= 0x01;//定时器2，1T
	AUXR |= 0x04;
	T2L = BRT;
  T2H = BRT >> 8;		//设定定时初值  115200    22.1184MHZ
	AUXR |= 0x10;		//启动定时器2
	ES = 1;//允许COM1串行口中断
	TI = 1;	
	EA = 1;		//允许全局中断
	REN = 1;	//允许接收
	IE2 = ES2;  //使能串口中断
	SBUF = 0x55; 
}
/*
//COM1发送一个字节
void Send_Data1(unsigned char dat)
{
	
	
	while(!TI);           //若TI=0，在此等待
    TI = 0;  
	SBUF = dat;
}
//发送一个字符串
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
		Send_Data1(*s);	//调用SendData()函数依次发送单字节数据
		s++;					//指针自增，便于发送下一个数据
	}
}
*/