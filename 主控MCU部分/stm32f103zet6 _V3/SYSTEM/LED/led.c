
#include "led.h"



/***********************************************
	�������ܣ�LED�Ƴ�ʼ��
	Ӳ���ӿڣ�PF7->led1
						PB5->led2
						PB8->led3
						PA1->led4
	Ӳ�����ԣ��͵�ƽ�������ߵ�ƽ��λ
************************************************/
void LED_Init(void)
{
	/*����ʱ��*/
	RCC->APB2ENR|=1<<3;
	RCC->APB2ENR|=1<<6;
	/*����gpioģʽ*/
	GPIOE->CRL&=0xFF0FFFFF;
	GPIOE->CRL|=0x00300000;
	
	GPIOB->CRL&=0xFF0FFFFF;
	GPIOB->CRL|=0x00300000;
	
	//��ʼ��LEDϨ��
	LED1=1;
	LED2=1;
}


/************************************************
	�������ܣ���led��ˮ����ÿ��led����ʵ�ֺ����Ƶ�Ч��
	������������ʱʱ��  �ο�ʱ�䣺500
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

