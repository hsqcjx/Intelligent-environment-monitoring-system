
#include "delay.h"




///*
//函数功能：延时函数初始化
//*/
//void DelayInit(void)
//{
//	/*1. 开时钟*/
//	RCC->APB1ENR|=1<<4;    //开启定时器6的时钟
//	RCC->APB1RSTR|=1<<4;   //开启复位时钟  
//	RCC->APB1RSTR&=~(1<<4);//关闭
//}


///*
//函数功能：延时毫秒的函数
//函数参数：毫秒的时间
//*/
//void DelayMs(int ms)
//{
//	/*1. 配置定时器的核心寄存器*/
//	TIM6->PSC=7200-1;     //预分频  0.1ms
//	/*2. 计数器的时钟频率CK_CNT等于fCK_PSC/(PSC[15:0]+1)*/
//	TIM6->ARR=ms*10;    //重装载寄存器
//	TIM6->CNT=0;
//	TIM6->CR1|=1<<0;      //使能计数器
//	while(!(TIM6->SR&1<<0)){} //等待时间到达
//	TIM6->CR1&=~(1<<0);       //关闭定时器
//	TIM6->SR=0x0;             //清除状态位
//}

///*
//函数功能：延时微秒的函数
//函数参数：微秒的时间
//*/
//void DelayUs(int us)
//{
//	/*1. 配置定时器的核心寄存器*/
//	TIM6->PSC=72-1;     //预分频  0.1ms
//	/*2. 计数器的时钟频率CK_CNT等于fCK_PSC/(PSC[15:0]+1)*/
//	TIM6->ARR=us;         //重装载寄存器
//	TIM6->CNT=0;
//	TIM6->CR1|=1<<0;         //使能计数器
//	while(!(TIM6->SR&1<<0)){}
//	TIM6->CR1&=~(1<<0);
//	TIM6->SR=0x0;
//}



/*
函数功能: 延时ms单位
最大值: 16777215
最大填入的ms单位: 1864ms
*/
void DelayMs(int ms)
{
	int i,j,n;
	for(i=0;i<ms;i++)
		for(j=0;j<10;j++)
			for(n=0;n<797;n++);
//#ifdef	_SYSTICK_IRQ_
//	int i,j,n;
//	for(i=0;i<ms;i++)
//		for(j=0;j<100;j++)
//			for(n=0;n<100;n++);
//#else
//	u32 tmp;
//	SysTick->VAL=0;         //CNT计数器值	
//	SysTick->LOAD=9000*ms;  //9000表示1ms
//	SysTick->CTRL|=1<<0;    //开启定时器	
//	do
//	{
//			tmp=SysTick->CTRL; //读取状态
//	}while((!(tmp&1<<16))&&(tmp&1<<0));
//	SysTick->VAL=0;         //CNT计数器值	
//	SysTick->CTRL&=~(1<<0); //关闭定时器	
//#endif	
}


/*
函数功能: 延时us单位
*/
void DelayUs(int us)
{
	int i,j;
	for(i=0;i<us;i++)
		for(j=0;j<10;j++);
//#ifdef	_SYSTICK_IRQ_
//	int i,j;
//	for(i=0;i<us;i++)
//		for(j=0;j<72;j++);
//#else
//	u32 tmp;
//	SysTick->VAL=0;         //CNT计数器值	
//	SysTick->LOAD=9*us;     //9表示1us
//	SysTick->CTRL|=1<<0;    //开启定时器	
//	do
//	{
//			tmp=SysTick->CTRL; //读取状态
//	}while((!(tmp&1<<16))&&(tmp&1<<0));
//	SysTick->VAL=0;         //CNT计数器值	
//	SysTick->CTRL&=~(1<<0); //关闭定时器	
//#endif	
}



