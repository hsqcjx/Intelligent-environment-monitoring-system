#ifndef _USART1_H
#define _USART1_H
#include "stm32f10x.h"
#include <stdio.h>
#include "sys.h"
#include "string.h"
#include "led.h"
#define USART_RX_MAX_LEN 1024
//�������ڽ������ݵ�buff
extern char USART1_RX_BUFF[USART_RX_MAX_LEN];
extern char USART2_RX_BUFF[USART_RX_MAX_LEN];
extern char USART3_RX_BUFF[USART_RX_MAX_LEN];
//��¼��ǰ�������ݵ�λ��
extern int USART1_RX_CURRENT;
extern int USART2_RX_CURRENT;
extern int USART3_RX_CURRENT;
//��־����״̬ 1 ��ʾ��Ӧ�Ĵ��ڽ��յ�����  0 ��ʾ��Ӧ�Ĵ���û������
extern u8 USART1_RX_STATE;
extern u8 USART2_RX_STATE;
extern u8 USART3_RX_STATE;

void USARTX_Init(USART_TypeDef *USARTx,int clock,u32 baud);
void USARTX_SendString(USART_TypeDef *USARTx,char *str);
void USARTX_SendData(USART_TypeDef *USARTx,char *str,u32 len);

//	USARTX_Init(USART1,72,115200);  //���ò����� 115200 9600
//	USARTX_Init(USART2,36,9600);  //���ò����� 115200 9600
//	USARTX_Init(USART3,36,115200);  //���ò����� 115200 9600
#endif
