#include "timer.h"
u8 UsartRxState=0;

/*
	�������ܣ���ʼ��ָ����ʱ��
	����������
						psc��Ԥ��Ƶ���ٸ�psc�Ĵ������и�ֵ����Ҫ��Ԥ��Ƶ����һ�ٸ�ֵ
						arr���Զ���װֵ
						open:�Ƿ�򿪶�ʱ��  0 �رն�ʱ��  1 �򿪶�ʱ��
*/

void TIMERx_Init(TIM_TypeDef *tim,u32 psc,u32 arr,u8 open)
{
	if(tim==TIM2)
	{
		//��ʱ��
		RCC->APB1ENR|=1<<0;
		//��λ��ʱ��
		RCC->APB1RSTR|=1<<0;
		RCC->APB1RSTR&=~(1<<0);
#ifdef TIM2_IRQ	
		tim->DIER|=1<<0;
		STM32_NVIC_SetPriority(TIM2_IRQn,1,1);
#endif
	}
	else if(tim==TIM3)
	{
		//��ʱ��
		RCC->APB1ENR|=1<<1;
		//��λ��ʱ��
		RCC->APB1RSTR|=1<<1;
		RCC->APB1RSTR&=~(1<<1);
#ifdef TIM3_IRQ	
		tim->DIER|=1<<0;
		STM32_NVIC_SetPriority(TIM3_IRQn,1,1);
#endif
	}
	else if(tim==TIM4)
	{
		//��ʱ��
		RCC->APB1ENR|=1<<2;
		//��λ��ʱ��
		RCC->APB1RSTR|=1<<2;
		RCC->APB1RSTR&=~(1<<2);
#ifdef TIM4_IRQ	
		tim->DIER|=1<<0;
		STM32_NVIC_SetPriority(TIM4_IRQn,1,1);
#endif
	}
	else return ;
	
	
	//���ö�ʱ���ĺ��ļĴ���
	tim->PSC=psc-1;    //����Ԥ����
	tim->ARR=arr;     //�����Զ���װ��ֵ  �������������ֵ�ǻὫcnt��λ
	tim->CR1|=1<<7;   //�������幦��
	if(open)
	{
		tim->CR1|=1<<0;   //������ʱ��
	}
	else
	{
		tim->CR1&=~(1<<0);  //�رն�ʱ��
	}
	
}

/*
	�������ܣ���ʱ���жϴ�����
*/
void TIM2_IRQHandler(void )
{
	TIM2->SR=0;
	//LED1=!LED1;
	UsartRxState=1;
	USART1_RX_STATE=1;
	TIM2->CR1&=~(1<<0);
	USART1_RX_CURRENT=0;
}

void TIM3_IRQHandler(void )
{
	TIM3->SR=0;
	//LED2=!LED2;
	UsartRxState=2;
	USART2_RX_STATE=1;
	TIM3->CR1&=~(1<<0);
	USART2_RX_CURRENT=0;
}
void TIM4_IRQHandler(void )
{
	TIM4->SR=0;
	//LED3=!LED3;
	UsartRxState=3;
	USART3_RX_STATE=1;
	TIM4->CR1&=~(1<<0);
	USART3_RX_CURRENT=0;
}

