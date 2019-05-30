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
	函数功能：
	硬件连接
			TX-PA9    复用推挽输出
			RX-PA10   上下拉输入
			状态寄存器 只读用来判断 判断数据是否发送完成
*/
void USARTX_Init(USART_TypeDef *USARTx,int clock,u32 baud)
{
	
/*----------------------------------串口1------------------------------------------------------------*/
		if(USARTx==USART1)
		{	 
			USART1_RX_CURRENT=0;
			USART1_RX_STATE=0;
			//开启GPIO口的时钟并配置模式  TX:PA9  RX:PA10
			RCC->APB2ENR|=1<<2;
			GPIOA->CRH&=0xFFFFF00F;
			GPIOA->CRH|=0x000008B0;
		
			//开启串口时钟并配置串口模式
			RCC->APB2ENR|=1<<14;
			RCC->APB2RSTR|=1<<14;    //开启复位
			RCC->APB2RSTR&=~(1<<14); //停止复位
		}
/*------------------------------------串口2-------------------------------------------------------------------*/ 
		else if(USARTx==USART2)
		{
			//开启GPIO口的时钟并配置模式  TX:PA2  RX:PA3
			RCC->APB2ENR|=1<<2;  //PA
			GPIOA->CRL&=0xFFFF00FF;
			GPIOA->CRL|=0x00008B00; 
			

			/*2. 配置GPIO口的模式*/
			RCC->APB1ENR|=1<<17; //USART2
			RCC->APB1RSTR|=1<<17; //复位串口2
			RCC->APB1RSTR&=~(1<<17);
		}	
/*----------------------------------------串口3------------------------------------------------------------------*/
		else if(USARTx==USART3)
		{
			//开启GPIO口的时钟并配置模式  TX:PA10  RX:PA11
			RCC->APB2ENR|=1<<3;
			GPIOB->CRH&=0xFFFF00FF;
			GPIOB->CRH|=0x00008B00;
			//开启串口时钟并配置串口模式
			RCC->APB1ENR|=1<<18;
			RCC->APB1RSTR|=1<<18;    //开启复位
			RCC->APB1RSTR&=~(1<<18); //停止复位
		}
		else return ;  
	
#ifdef USATT1_INTERRUPT_RX
	//开启中断
	USART1->CR1|=1<<5;
	STM32_NVIC_SetPriority(USART1_IRQn,2,2);
#endif
#ifdef USATT2_INTERRUPT_RX	
	USART2->CR1|=1<<5;  //开启串口接收中断
	STM32_NVIC_SetPriority(USART2_IRQn,1,1); //设置中断优先级
#endif
#ifdef USATT3_INTERRUPT_RX	
	USART3->CR1|=1<<5;
	STM32_NVIC_SetPriority(USART3_IRQn,2,2);
#endif	
	USARTx->BRR=clock*1000000/baud;  //  时钟/波特率 （串口1:72M串口2和3为36M）控制发送每一位的时间间隔
	USARTx->CR1|=1<<2; //开启接收功能
	USARTx->CR1|=1<<3; //开启发送功能
	USARTx->CR1|=1<<13; //开启串口模块功能
	USART1->SR=0;
	
}

/*
	函数功能：通过串口1发送字符串
*/
void USARTX_SendString(USART_TypeDef *USARTx,char *str)
{
	  while(*str!='\0')
		{
				USARTx->DR=*str++; //发送数据
				while(!(USARTx->SR&1<<7)){} //等待发送完成
		}
}


/*
	函数功能：通过串口1发送字符串
*/
void USARTX_SendData(USART_TypeDef *USARTx,char *str,u32 len)
{
		u32 i=0;
	  for(i=0;i<len;i++)
		{
				USARTx->DR=*str++; //发送数据
				while(!(USARTx->SR&1<<7)){} //等待发送完成
		}
}



/*
	printf函数重定向
*/
int fputc(int c ,FILE *stream)
{
	USART1->DR=c;
	while(!(USART1->SR&1<<7)){}
	return c;
}	

/*
	scanf函数重定向到串口
*/
int fgetc(FILE *stream)
{
	while(!(USART1->SR&1<<5)){}
	return USART1->DR;
}



/*
	函数功能：串口中断函数
	使用定时器  当进来是先把定时器的cnt计数值清零  当数据接收完成时就不会进入中断函数
	即定时器会超时溢出进入定时器中断函数  在定时器中断函数里面去将标志位置1在主函数去判断
	标志位的值并作出相应的操作
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
