#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "timer.h"	 
#include "nt35310_lcd.h"
#include "gt9147_touch.h"
#include "sys.h"
#include "includes.h" //���� UCOS_II ��ͷ�ļ�
#include "dht11.h"
#include "adc.h"
//�����������ȼ�
#define LED1_TASK_PRIO 5
//���������ջ��С
#define LED1_STK_SIZE 1024
//������������ʱʹ�õĶ�ջ�ռ�(����һ������)
OS_STK LED1_TASK_STK[LED1_STK_SIZE];
//������
void LED1_task(void *p_arg);


//�����������ȼ�
#define LED2_TASK_PRIO 6
//���������ջ��С
#define LED2_STK_SIZE 2048
//������������ʱʹ�õĶ�ջ�ռ�(����һ������)
OS_STK LED2_TASK_STK[LED2_STK_SIZE];
//������
void LED2_task(void *p_arg);
    
extern const unsigned char gImage_Temp[4800];
extern const unsigned char gImage_hum[7200];
extern const unsigned char gImage_Gas[7680];
extern const unsigned char gImage_dust[10560];
int main()
{
	int i=0;
	u16 adc_data;
	USARTX_Init(USART1,72,115200);
	systick_Init(); 
//	ADC1_Init_2();    //adc1ע��ͨ����ʼ��
//	RCC->APB2ENR|=1<<3; //PB10  PM2.5LED��
//	GPIOB->CRH&=0xFFFFF0FF;
//	GPIOB->CRH|=0x00000300;
//	DHT11_OUT_MODE;
	NT35310_LCD_Init();
	NT35310_LCD_Clear(WHITE);
	NT35310_LCD_ShowImage(15,0,40,60,(u8*)gImage_Temp);
	NT35310_LCD_ShowImage(3,60,60,60,(u8*)gImage_hum);
	NT35310_LCD_ShowImage(0,120,64,60,(u8*)gImage_Gas);
	NT35310_LCD_ShowImage(0,180,88,60,(u8*)gImage_dust);
//	NT35310_LCD_ShowChineseFont(u32 x,u32 y,u32 size,u8 *font);
	while(1)
	{
//		DHT11_ReadTempAndHumi();
//		adc_data=ADC1_GetCHx_Data(8);
//		printf("%d=\t%fv\n",i,adc_data*3.3/4095);
//		dht11_out=1;
		
//	NT35310_LCD_Clear(GRAYBLUE);
//		DelayMs(500);
//	NT35310_LCD_ShowImage(0,0,320,480,(u8*)gImage_image);
		DelayMs(500);
	}
  OSInit();//ϵͳ��ʼ
  //��������1
  OSTaskCreate(
                LED1_task, //ִ������ĺ���ָ��
                (void*)0, //���ݸ�����Ķ��������
                (OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1], //����ִ��ʱʹ�õĶ�ջ�ռ�
                LED1_TASK_PRIO //��������ȼ�
              );
  
  //��������2
  OSTaskCreate(
                LED2_task, //ִ������ĺ���ָ��
                (void*)0, //���ݸ�����Ķ��������
                (OS_STK*)&LED2_TASK_STK[LED2_STK_SIZE-1], //����ִ��ʱʹ�õĶ�ջ�ռ�
                LED2_TASK_PRIO //��������ȼ�
              );
  
  OSStart();//��ʼ�����������
}

/*
����1: LED1
*/
void LED1_task(void *p_arg)
{
    p_arg=p_arg;
    while(1)
    {
         LED1=!LED1;
				DHT11_ReadTempAndHumi();
				dht11_out=1;
 //        printf("LED1��������ִ��!\n");
         OSTimeDlyHMSM(0,0,0,500);
    }
}


/*
����2: LED2
*/
void LED2_task(void *p_arg)
{
    p_arg=p_arg;
    while(1)
    {
        LED2=!LED2;
				DHT11_ReadTempAndHumi();
				dht11_out=1;
  //      printf("LED2��������ִ��!\n");
        OSTimeDlyHMSM(0,0,0,500);
    }
}
