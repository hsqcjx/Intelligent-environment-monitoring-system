#ifndef _USART1_H
#define _USART1_H
#include "stm32f10x.h"
#include <stdio.h>
#include "sys.h"
#include "string.h"
#include "led.h"
#define USART_RX_MAX_LEN 1024
//各个串口接收数据的buff
extern char USART1_RX_BUFF[USART_RX_MAX_LEN];
extern char USART2_RX_BUFF[USART_RX_MAX_LEN];
extern char USART3_RX_BUFF[USART_RX_MAX_LEN];
//记录当前接收数据的位置
extern int USART1_RX_CURRENT;
extern int USART2_RX_CURRENT;
extern int USART3_RX_CURRENT;
//标志接收状态 1 表示对应的串口接收到数据  0 表示对应的串口没有数据
extern u8 USART1_RX_STATE;
extern u8 USART2_RX_STATE;
extern u8 USART3_RX_STATE;

void USARTX_Init(USART_TypeDef *USARTx,int clock,u32 baud);
void USARTX_SendString(USART_TypeDef *USARTx,char *str);
void USARTX_SendData(USART_TypeDef *USARTx,char *str,u32 len);

//	USARTX_Init(USART1,72,115200);  //常用波特率 115200 9600
//	USARTX_Init(USART2,36,9600);  //常用波特率 115200 9600
//	USARTX_Init(USART3,36,115200);  //常用波特率 115200 9600
#endif
