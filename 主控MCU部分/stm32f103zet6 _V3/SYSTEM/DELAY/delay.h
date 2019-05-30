#ifndef DELAY_H
#define DELAY_H

#include "stm32f10x.h"
#include "config.h"

void DelayInit(void);
void DelayMs(int ms);
void DelayUs(int us);
#endif
