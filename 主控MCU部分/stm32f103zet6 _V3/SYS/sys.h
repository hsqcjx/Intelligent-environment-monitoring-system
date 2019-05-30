#ifndef _SYS_H
#define _SYS_H
#include "stm32f10x.h"
#include "config.h"
//#include "led.h"
//#include "beep.h"
/*
  ============================================================================================================================
    NVIC_PriorityGroup   | NVIC_IRQChannelPreemptionPriority | NVIC_IRQChannelSubPriority  | Description
  ============================================================================================================================
   NVIC_PriorityGroup_0  |                0                  |            0-15             |   0 bits for pre-emption priority
                         |                                   |                             |   4 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------
   NVIC_PriorityGroup_1  |                0-1                |            0-7              |   1 bits for pre-emption priority
                         |                                   |                             |   3 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_2  |                0-3                |            0-3              |   2 bits for pre-emption priority
                         |                                   |                             |   2 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_3  |                0-7                |            0-1              |   3 bits for pre-emption priority
                         |                                   |                             |   1 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_4  |                0-15               |            0                |   4 bits for pre-emption priority
                         |                                   |                             |   0 bits for subpriority                       
  ============================================================================================================================
	*/
#define NVIC_PriorityGroup_0         ((uint32_t)0x700) /*!< 0 bits for pre-emption priority
                                                            4 bits for subpriority */
#define NVIC_PriorityGroup_1         ((uint32_t)0x600) /*!< 1 bits for pre-emption priority
                                                            3 bits for subpriority */
#define NVIC_PriorityGroup_2         ((uint32_t)0x500) /*!< 2 bits for pre-emption priority
                                                            2 bits for subpriority */
#define NVIC_PriorityGroup_3         ((uint32_t)0x400) /*!< 3 bits for pre-emption priority
                                                            1 bits for subpriority */
#define NVIC_PriorityGroup_4         ((uint32_t)0x300) /*!< 4 bits for pre-emption priority
                                                            0 bits for subpriority */
/*将寄存器的某一位映射成物理地址*/
#define BITBAND(addr,bitnum) ((addr&0xF0000000)+0x2000000+((addr&0xFFFFF)<<5)+(bitnum<<2))
/*将映射出来的物理地址强制转换成vu32的指针  （vu32类型的变量添加了volatile关键字） 并取出内容*/
#define MEMADDR(addr) *(vu32 *)addr

/*定义GPIO口输入输出寄存器的地址*/
#define GPIOA_IDR (0x40010800+0x8)
#define GPIOA_ODR (0x40010800+0xC)
#define GPIOB_IDR (0x40010C00+0x8)
#define GPIOB_ODR (0x40010C00+0xC)
#define GPIOC_IDR (0x40011000+0x8)
#define GPIOC_ODR (0x40011000+0xC)
#define GPIOD_IDR (0x40011400+0x8)
#define GPIOD_ODR (0x40011400+0xC)
#define GPIOE_IDR (0x40011800+0x8)
#define GPIOE_ODR (0x40011800+0xC)
#define GPIOF_IDR (0x40011C00+0x8)
#define GPIOF_ODR (0x40011C00+0xC)
#define GPIOG_IDR (0x40012000+0x8)
#define GPIOG_ODR (0x40012000+0xC)

/*将各个寄存器映射成位带*/
#define PAin(bitnum)  MEMADDR(BITBAND(GPIOA_IDR,bitnum))
#define PAout(bitnum) MEMADDR(BITBAND(GPIOA_ODR,bitnum))
#define PBin(bitnum)  MEMADDR(BITBAND(GPIOB_IDR,bitnum))
#define PBout(bitnum) MEMADDR(BITBAND(GPIOB_ODR,bitnum))
#define PCin(bitnum)  MEMADDR(BITBAND(GPIOC_IDR,bitnum))
#define PCout(bitnum) MEMADDR(BITBAND(GPIOC_ODR,bitnum))
#define PDin(bitnum)  MEMADDR(BITBAND(GPIOD_IDR,bitnum))
#define PDout(bitnum) MEMADDR(BITBAND(GPIOD_ODR,bitnum))
#define PEin(bitnum)  MEMADDR(BITBAND(GPIOE_IDR,bitnum))
#define PEout(bitnum) MEMADDR(BITBAND(GPIOE_ODR,bitnum))
#define PFin(bitnum)  MEMADDR(BITBAND(GPIOF_IDR,bitnum))
#define PFout(bitnum) MEMADDR(BITBAND(GPIOF_ODR,bitnum))
#define PGin(bitnum)  MEMADDR(BITBAND(GPIOG_IDR,bitnum))
#define PGout(bitnum) MEMADDR(BITBAND(GPIOG_ODR,bitnum))


void STM32_NVIC_SetPriority(IRQn_Type IRQn,uint32_t PreemptPriority,uint32_t SubPriority);
void systick_Init(void);
//0,不支持OS
//1,支持OS
#define SYSTEM_SUPPORT_OS		0		//定义系统文件夹是否支持OS
																	    
	 
//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 

//Ex_NVIC_Config专用定义
#define GPIO_A 0
#define GPIO_B 1
#define GPIO_C 2
#define GPIO_D 3
#define GPIO_E 4
#define GPIO_F 5
#define GPIO_G 6 
#define FTIR   1  //下降沿触发
#define RTIR   2  //上升沿触发
								   

//JTAG模式设置定义
#define JTAG_SWD_DISABLE   0X02
#define SWD_ENABLE         0X01
#define JTAG_SWD_ENABLE    0X00	

/////////////////////////////////////////////////////////////////  
void Stm32_Clock_Init(u8 PLL);  //时钟初始化  
void Sys_Soft_Reset(void);      //系统软复位
void Sys_Standby(void);         //待机模式 	
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset);//设置偏移地址
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group);//设置NVIC分组
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group);//设置中断
void Ex_NVIC_Config(u8 GPIOx,u8 BITx,u8 TRIM);//外部中断配置函数(只对GPIOA~G)
void JTAG_Set(u8 mode);
//////////////////////////////////////////////////////////////////////////////
//以下为汇编函数
void WFI_SET(void);		//执行WFI指令
void INTX_DISABLE(void);//关闭所有中断
void INTX_ENABLE(void);	//开启所有中断
void MSR_MSP(u32 addr);	//设置堆栈地址
#endif
