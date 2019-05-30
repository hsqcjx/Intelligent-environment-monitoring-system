#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "timer.h"	 
#include "nt35310_lcd.h"
#include "gt9147_touch.h"
#include "sys.h"
#include "includes.h" //加入 UCOS_II 的头文件
#include "dht11.h"
#include "adc.h"
//设置任务优先级
#define LED1_TASK_PRIO 5
//设置任务堆栈大小
#define LED1_STK_SIZE 1024
//设置任务运行时使用的堆栈空间(定义一个数组)
OS_STK LED1_TASK_STK[LED1_STK_SIZE];
//任务函数
void LED1_task(void *p_arg);


//设置任务优先级
#define LED2_TASK_PRIO 6
//设置任务堆栈大小
#define LED2_STK_SIZE 2048
//设置任务运行时使用的堆栈空间(定义一个数组)
OS_STK LED2_TASK_STK[LED2_STK_SIZE];
//任务函数
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
//	ADC1_Init_2();    //adc1注入通道初始化
//	RCC->APB2ENR|=1<<3; //PB10  PM2.5LED灯
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
  OSInit();//系统初始
  //创建任务1
  OSTaskCreate(
                LED1_task, //执行任务的函数指针
                (void*)0, //传递给任务的额外参数。
                (OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1], //任务执行时使用的堆栈空间
                LED1_TASK_PRIO //任务的优先级
              );
  
  //创建任务2
  OSTaskCreate(
                LED2_task, //执行任务的函数指针
                (void*)0, //传递给任务的额外参数。
                (OS_STK*)&LED2_TASK_STK[LED2_STK_SIZE-1], //任务执行时使用的堆栈空间
                LED2_TASK_PRIO //任务的优先级
              );
  
  OSStart();//开始进行任务调度
}

/*
任务1: LED1
*/
void LED1_task(void *p_arg)
{
    p_arg=p_arg;
    while(1)
    {
         LED1=!LED1;
				DHT11_ReadTempAndHumi();
				dht11_out=1;
 //        printf("LED1任务正在执行!\n");
         OSTimeDlyHMSM(0,0,0,500);
    }
}


/*
任务2: LED2
*/
void LED2_task(void *p_arg)
{
    p_arg=p_arg;
    while(1)
    {
        LED2=!LED2;
				DHT11_ReadTempAndHumi();
				dht11_out=1;
  //      printf("LED2任务正在执行!\n");
        OSTimeDlyHMSM(0,0,0,500);
    }
}
