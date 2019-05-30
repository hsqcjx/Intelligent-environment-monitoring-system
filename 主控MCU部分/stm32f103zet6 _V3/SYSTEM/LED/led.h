#ifndef LED_H
#define LED_H

#include "stm32f10x.h"
#include <string.h>
#include "delay.h"
#include "sys.h"
#include <stdio.h>
#define LED1 PEout(5)
#define LED2 PBout(5)
void LED_Init(void);
void LED_Show(int time);
#endif
