#ifndef ADC_H
#define ADC_H
#include "stm32f10x.h"
void ADC1_Init(void);
u16 ADC1_GetCHx(u8 ch);

void ADC1_Init_2(void);
u16 ADC1_GetCHx_Data(u8 ch);
#endif
