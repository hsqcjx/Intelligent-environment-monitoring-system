//文件名必须保存为 dht111.h
#ifndef __DHT11_H_
#define __DHT11_H_

#include "stm32f10x.h"
#include <stdio.h>
#include "sys.h"
#include "delay.h"

#define DHT11_OUT_MODE {GPIOB->CRH&=0xFFFF0FFF;GPIOB->CRH|=0x00003000;}
#define DHT11_IN_MODE  {GPIOB->CRH&=0xFFFF0FFF;GPIOB->CRH|=0x00008000;}

//请根据自己的 dht11 接的 IO 口来改动位定义
#define  dht11_out   PBout(11)
#define  dht11_in    PBin(11)
//设定标志(static unsigned char status)的宏值
#define OK 1
#define ERROR 0
extern void Delay_1ms(unsigned int ms);
//函数的返回值表示读取数据是否成功 OK 表示成功 ERROR 表示失败
extern unsigned char DHT11_ReadTempAndHumi(void);
#endif

