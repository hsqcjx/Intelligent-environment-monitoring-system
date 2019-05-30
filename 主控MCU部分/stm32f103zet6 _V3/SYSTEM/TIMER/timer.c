#include "timer.h"
u8 UsartRxState=0;

/*
	函数功能：初始化指定定时器
	函数参数：
						psc：预分频数再给psc寄存器进行赋值是需要将预分频数减一再赋值
						arr：自动重装值
						open:是否打开定时器  0 关闭定时器  1 打开定时器
*/

void TIMERx_Init(TIM_TypeDef *tim,u32 psc,u32 arr,u8 open)
{
	if(tim==TIM2)
	{
		//开时钟
		RCC->APB1ENR|=1<<0;
		//复位定时器
		RCC->APB1RSTR|=1<<0;
		RCC->APB1RSTR&=~(1<<0);
#ifdef TIM2_IRQ	
		tim->DIER|=1<<0;
		STM32_NVIC_SetPriority(TIM2_IRQn,1,1);
#endif
	}
	else if(tim==TIM3)
	{
		//开时钟
		RCC->APB1ENR|=1<<1;
		//复位定时器
		RCC->APB1RSTR|=1<<1;
		RCC->APB1RSTR&=~(1<<1);
#ifdef TIM3_IRQ	
		tim->DIER|=1<<0;
		STM32_NVIC_SetPriority(TIM3_IRQn,1,1);
#endif
	}
	else if(tim==TIM4)
	{
		//开时钟
		RCC->APB1ENR|=1<<2;
		//复位定时器
		RCC->APB1RSTR|=1<<2;
		RCC->APB1RSTR&=~(1<<2);
#ifdef TIM4_IRQ	
		tim->DIER|=1<<0;
		STM32_NVIC_SetPriority(TIM4_IRQn,1,1);
#endif
	}
	else return ;
	
	
	//配置定时器的核心寄存器
	tim->PSC=psc-1;    //设置预分屏
	tim->ARR=arr;     //设置自动重装载值  即当计数到这个值是会将cnt复位
	tim->CR1|=1<<7;   //开启缓冲功能
	if(open)
	{
		tim->CR1|=1<<0;   //开启定时器
	}
	else
	{
		tim->CR1&=~(1<<0);  //关闭定时器
	}
	
}

/*
	函数功能：定时器中断处理函数
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

