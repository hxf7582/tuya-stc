#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#ifdef MAINWORK_GLOBALS
#define MAINWORK_EXT
#else
#define MAINWORK_EXT extern 
#endif

//==============================================================================
typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

//==============================================================================
#include 		<intrins.h>
#include    <math.h>
#include        "STC8.H"
//#include        "user_uart.h"
#include 				"user_key.h"
#include 				"user_timer.h"
#include 				"user_I2C.h"
#include 				"user_OLED.h"
#include 				"user_SHT30.h"
//#include 				"user_ADC.h"
#include 				"Uart_2.h"
#include 				"Uart_1.h"
#include        "delay.h"
//==============================================================================
//�ܽŶ���
//==============================================================================
sbit K1 = P2^0;			//����1
sbit K2 = P2^1;			//����2
sbit K3 = P2^2;			//����3
sbit K4 = P2^3;			//����4
sbit LED1 = P0^0;			//LED1
sbit LED2 = P0^1;			//LED2
sbit LED3 = P0^2;			//LED3
sbit LED4 = P0^3;			//LED4
sbit LED5 = P0^4;			//LED5
sbit LED6 = P1^3;			//LED5
#define MAIN_Fosc		22118400UL	//������ʱ��

//**************I2C*************
#define	Speed		    100000UL	  //����I2Cʱ��Ƶ��
#define MSSPEED     (MAIN_Fosc/Speed/2-4)/2

#define OLED_Address 0x78
#define SHT30_Address 0x88

//*************����*************
#define	BaudRate		9600UL	//ѡ������
#define BRT         (65536-MAIN_Fosc/BaudRate/4)


//==============================================================================
//��������
//==============================================================================
typedef struct {
	
	signed int temper;                                        //�¶�
  uint8_t humidity;                                         //ʪ��
	uint32_t run_time;                                        //�ۼ�����ʱ��
	uint8_t Power;
	uint16_t SAMPLING;
	
} TYPE_BUFFER_S;

MAINWORK_EXT TYPE_BUFFER_S FlashBuffer;


#endif