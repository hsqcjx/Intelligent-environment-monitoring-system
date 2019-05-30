#ifndef TIMER_H
#define TIMER_H
#include "stm32f10x.h"
#include "stdio.h"
#include "sys.h"
#include "usart.h"
void TIMERx_Init(TIM_TypeDef *tim,u32 psc,u32 arr,u8 open);
#endif
