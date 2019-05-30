//�ļ������뱣��Ϊ dht111.h
#ifndef __DHT11_H_
#define __DHT11_H_

#include "stm32f10x.h"
#include <stdio.h>
#include "sys.h"
#include "delay.h"

#define DHT11_OUT_MODE {GPIOB->CRH&=0xFFFF0FFF;GPIOB->CRH|=0x00003000;}
#define DHT11_IN_MODE  {GPIOB->CRH&=0xFFFF0FFF;GPIOB->CRH|=0x00008000;}

//������Լ��� dht11 �ӵ� IO �����Ķ�λ����
#define  dht11_out   PBout(11)
#define  dht11_in    PBin(11)
//�趨��־(static unsigned char status)�ĺ�ֵ
#define OK 1
#define ERROR 0
extern void Delay_1ms(unsigned int ms);
//�����ķ���ֵ��ʾ��ȡ�����Ƿ�ɹ� OK ��ʾ�ɹ� ERROR ��ʾʧ��
extern unsigned char DHT11_ReadTempAndHumi(void);
#endif

