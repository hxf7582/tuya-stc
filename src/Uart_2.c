//微信公众号：物联网零妖
//串口2  115200bps 22.1184MHZ
#define	USER_UART_GLOBALS
//#include<Uart_2.h>
#include "include.h"
#include "wifi.h"
#define S2RI  0x01              //S2CON.0
#define S2TI  0x02              //S2CON.1
static bit busy2=0;//COM2用到的发送忙标志


void INT_Uart2(void) interrupt 8//串口2中断处理程序
{
 	
   if (S2CON & 0x02)
    {
        S2CON &= ~0x02;
        busy2 = 0;
    }
    if (S2CON & 0x01)
    {
        S2CON &= ~0x01;			
			  uart_receive_input(S2BUF);             //测试端口      
    }
}
// 描述: 串口初始化程序.
void Init_Uart2(void)
{
	S2CON = 0x10;		//8位数据,可变波特率
	busy2 = 0;
	IE2 = 0x01;    //使能串口2中断	
	
	
}
//COM2发送一个字节
void Send_Data2(unsigned char dat)
{
	
	while (busy2);
  busy2 = 1;
	S2BUF = dat;
}
//COM2发送一个字符串
void Send_Str2(unsigned char *s)
{
	do
		Send_Data2(*s++);
	while(*s);
}



