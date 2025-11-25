#pragma once
#include "stm32f10x.h"
#define DS0_Off (GPIOB->BSRR = 1<<5)
#define DS0_On (GPIOB->BRR = 1<<5)
#define DS1_Off (GPIOE->BSRR = 1<<5)
#define DS1_On (GPIOE->BRR = 1<<5)
#define DS1_toggle (GPIOE->ODR ^= 1<<5)
#define DS0_toggle (GPIOB->ODR ^= 1<<5)
void IERG3810_LED_Init(void);
