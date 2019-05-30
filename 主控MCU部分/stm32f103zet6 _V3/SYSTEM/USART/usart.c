#include "usart.h"
char USART1_RX_BUFF[USART_RX_MAX_LEN];
char USART2_RX_BUFF[USART_RX_MAX_LEN];
char USART3_RX_BUFF[USART_RX_MAX_LEN];
int USART1_RX_CURRENT=0;
int USART2_RX_CURRENT=0;
int USART3_RX_CURRENT=0;
u8 USART1_RX_STATE=0;
u8 USART2_RX_STATE=0;
u8 USART3_RX_STATE=0;
/*
	�������ܣ�
	Ӳ������
			TX-PA9    �����������
			RX-PA10   ����������
			״̬�Ĵ��� ֻ�������ж� �ж������Ƿ������
*/
void USARTX_Init(USART_TypeDef *USARTx,int clock,u32 baud)
{
	
/*----------------------------------����1------------------------------------------------------------*/
		if(USARTx==USART1)
		{	 
			USART1_RX_CURRENT=0;
			USART1_RX_STATE=0;
			//����GPIO�ڵ�ʱ�Ӳ�����ģʽ  TX:PA9  RX:PA10
			RCC->APB2ENR|=1<<2;
			GPIOA->CRH&=0xFFFFF00F;
			GPIOA->CRH|=0x000008B0;
		
			//��������ʱ�Ӳ����ô���ģʽ
			RCC->APB2ENR|=1<<14;
			RCC->APB2RSTR|=1<<14;    //������λ
			RCC->APB2RSTR&=~(1<<14); //ֹͣ��λ
		}
/*------------------------------------����2-------------------------------------------------------------------*/ 
		else if(USARTx==USART2)
		{
			//����GPIO�ڵ�ʱ�Ӳ�����ģʽ  TX:PA2  RX:PA3
			RCC->APB2ENR|=1<<2;  //PA
			GPIOA->CRL&=0xFFFF00FF;
			GPIOA->CRL|=0x00008B00; 
			

			/*2. ����GPIO�ڵ�ģʽ*/
			RCC->APB1ENR|=1<<17; //USART2
			RCC->APB1RSTR|=1<<17; //��λ����2
			RCC->APB1RSTR&=~(1<<17);
		}	
/*----------------------------------------����3------------------------------------------------------------------*/
		else if(USARTx==USART3)
		{
			//����GPIO�ڵ�ʱ�Ӳ�����ģʽ  TX:PA10  RX:PA11
			RCC->APB2ENR|=1<<3;
			GPIOB->CRH&=0xFFFF00FF;
			GPIOB->CRH|=0x00008B00;
			//��������ʱ�Ӳ����ô���ģʽ
			RCC->APB1ENR|=1<<18;
			RCC->APB1RSTR|=1<<18;    //������λ
			RCC->APB1RSTR&=~(1<<18); //ֹͣ��λ
		}
		else return ;  
	
#ifdef USATT1_INTERRUPT_RX
	//�����ж�
	USART1->CR1|=1<<5;
	STM32_NVIC_SetPriority(USART1_IRQn,2,2);
#endif
#ifdef USATT2_INTERRUPT_RX	
	USART2->CR1|=1<<5;  //�������ڽ����ж�
	STM32_NVIC_SetPriority(USART2_IRQn,1,1); //�����ж����ȼ�
#endif
#ifdef USATT3_INTERRUPT_RX	
	USART3->CR1|=1<<5;
	STM32_NVIC_SetPriority(USART3_IRQn,2,2);
#endif	
	USARTx->BRR=clock*1000000/baud;  //  ʱ��/������ ������1:72M����2��3Ϊ36M�����Ʒ���ÿһλ��ʱ����
	USARTx->CR1|=1<<2; //�������չ���
	USARTx->CR1|=1<<3; //�������͹���
	USARTx->CR1|=1<<13; //��������ģ�鹦��
	USART1->SR=0;
	
}

/*
	�������ܣ�ͨ������1�����ַ���
*/
void USARTX_SendString(USART_TypeDef *USARTx,char *str)
{
	  while(*str!='\0')
		{
				USARTx->DR=*str++; //��������
				while(!(USARTx->SR&1<<7)){} //�ȴ��������
		}
}


/*
	�������ܣ�ͨ������1�����ַ���
*/
void USARTX_SendData(USART_TypeDef *USARTx,char *str,u32 len)
{
		u32 i=0;
	  for(i=0;i<len;i++)
		{
				USARTx->DR=*str++; //��������
				while(!(USARTx->SR&1<<7)){} //�ȴ��������
		}
}



/*
	printf�����ض���
*/
int fputc(int c ,FILE *stream)
{
	USART1->DR=c;
	while(!(USART1->SR&1<<7)){}
	return c;
}	

/*
	scanf�����ض��򵽴���
*/
int fgetc(FILE *stream)
{
	while(!(USART1->SR&1<<5)){}
	return USART1->DR;
}



/*
	�������ܣ������жϺ���
	ʹ�ö�ʱ��  ���������ȰѶ�ʱ����cnt����ֵ����  �����ݽ������ʱ�Ͳ�������жϺ���
	����ʱ���ᳬʱ������붨ʱ���жϺ���  �ڶ�ʱ���жϺ�������ȥ����־λ��1��������ȥ�ж�
	��־λ��ֵ��������Ӧ�Ĳ���
*/
void USART1_IRQHandler(void)
{
		TIM2->CNT=0;
		TIM2->CR1|=1<<0;
		USART1_RX_STATE=0;
		if(USART1_RX_CURRENT<USART_RX_MAX_LEN)
		{
			USART1_RX_BUFF[USART1_RX_CURRENT++]=USART1->DR;
			USART1_RX_BUFF[USART1_RX_CURRENT]='\0';
		}
		USART1->SR=0;
}


void USART2_IRQHandler(void)
{
		TIM3->CNT=0;
		TIM3->CR1|=1<<0;
		if(USART2_RX_CURRENT<USART_RX_MAX_LEN)
		{
			USART2_RX_BUFF[USART2_RX_CURRENT++]=USART2->DR;
			USART2_RX_BUFF[USART2_RX_CURRENT]='\0';
		}
		USART2->SR=0;
}

void USART3_IRQHandler(void)
{
		TIM4->CNT=0;
		TIM4->CR1|=1<<0;
		if(USART3_RX_CURRENT<USART_RX_MAX_LEN)
		{
			USART3_RX_BUFF[USART3_RX_CURRENT++]=USART3->DR;
			USART3_RX_BUFF[USART3_RX_CURRENT]='\0';
		}
		USART3->SR=0;
}
