
#include "delay.h"




///*
//�������ܣ���ʱ������ʼ��
//*/
//void DelayInit(void)
//{
//	/*1. ��ʱ��*/
//	RCC->APB1ENR|=1<<4;    //������ʱ��6��ʱ��
//	RCC->APB1RSTR|=1<<4;   //������λʱ��  
//	RCC->APB1RSTR&=~(1<<4);//�ر�
//}


///*
//�������ܣ���ʱ����ĺ���
//���������������ʱ��
//*/
//void DelayMs(int ms)
//{
//	/*1. ���ö�ʱ���ĺ��ļĴ���*/
//	TIM6->PSC=7200-1;     //Ԥ��Ƶ  0.1ms
//	/*2. ��������ʱ��Ƶ��CK_CNT����fCK_PSC/(PSC[15:0]+1)*/
//	TIM6->ARR=ms*10;    //��װ�ؼĴ���
//	TIM6->CNT=0;
//	TIM6->CR1|=1<<0;      //ʹ�ܼ�����
//	while(!(TIM6->SR&1<<0)){} //�ȴ�ʱ�䵽��
//	TIM6->CR1&=~(1<<0);       //�رն�ʱ��
//	TIM6->SR=0x0;             //���״̬λ
//}

///*
//�������ܣ���ʱ΢��ĺ���
//����������΢���ʱ��
//*/
//void DelayUs(int us)
//{
//	/*1. ���ö�ʱ���ĺ��ļĴ���*/
//	TIM6->PSC=72-1;     //Ԥ��Ƶ  0.1ms
//	/*2. ��������ʱ��Ƶ��CK_CNT����fCK_PSC/(PSC[15:0]+1)*/
//	TIM6->ARR=us;         //��װ�ؼĴ���
//	TIM6->CNT=0;
//	TIM6->CR1|=1<<0;         //ʹ�ܼ�����
//	while(!(TIM6->SR&1<<0)){}
//	TIM6->CR1&=~(1<<0);
//	TIM6->SR=0x0;
//}



/*
��������: ��ʱms��λ
���ֵ: 16777215
��������ms��λ: 1864ms
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
//	SysTick->VAL=0;         //CNT������ֵ	
//	SysTick->LOAD=9000*ms;  //9000��ʾ1ms
//	SysTick->CTRL|=1<<0;    //������ʱ��	
//	do
//	{
//			tmp=SysTick->CTRL; //��ȡ״̬
//	}while((!(tmp&1<<16))&&(tmp&1<<0));
//	SysTick->VAL=0;         //CNT������ֵ	
//	SysTick->CTRL&=~(1<<0); //�رն�ʱ��	
//#endif	
}


/*
��������: ��ʱus��λ
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
//	SysTick->VAL=0;         //CNT������ֵ	
//	SysTick->LOAD=9*us;     //9��ʾ1us
//	SysTick->CTRL|=1<<0;    //������ʱ��	
//	do
//	{
//			tmp=SysTick->CTRL; //��ȡ״̬
//	}while((!(tmp&1<<16))&&(tmp&1<<0));
//	SysTick->VAL=0;         //CNT������ֵ	
//	SysTick->CTRL&=~(1<<0); //�رն�ʱ��	
//#endif	
}



