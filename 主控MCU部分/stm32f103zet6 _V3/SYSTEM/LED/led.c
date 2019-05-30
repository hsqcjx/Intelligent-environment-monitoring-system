
#include "led.h"



/***********************************************
	函数功能：LED灯初始化
	硬件接口：PF7->led1
						PB5->led2
						PB8->led3
						PA1->led4
	硬件特性：低电平点亮，高电平复位
************************************************/
void LED_Init(void)
{
	/*开启时钟*/
	RCC->APB2ENR|=1<<3;
	RCC->APB2ENR|=1<<6;
	/*配置gpio模式*/
	GPIOE->CRL&=0xFF0FFFFF;
	GPIOE->CRL|=0x00300000;
	
	GPIOB->CRL&=0xFF0FFFFF;
	GPIOB->CRL|=0x00300000;
	
	//初始化LED熄灭
	LED1=1;
	LED2=1;
}


/************************************************
	函数功能：让led流水并且每个led亮灭都实现呼吸灯的效果
	函数参数：延时时间  参考时间：500
************************************************/
void LED_Show(int time)
{
	int j;
	for(j=0;j<time;j=j+1)
	{
		LED1=1;
		LED2=1;
		DelayUs(j);
		LED1=0;
		LED2=0;
		DelayUs(time-j);
	}
	for(j=time;j>0;j=j-1)
	{
		LED1=1;
		LED2=1;
		DelayUs(j);
		LED1=0;
		LED2=0;
		DelayUs(time-j);
	}
}

