#pragma once
#include "stm32f10x.h"
#define Buzzer_Off (GPIOB->BSRR = 1<<8)
#define Buzzer_On (GPIOB->BRR = 1<<8)
#define Buzzer_toggle (GPIOB->ODR ^= 1<<8)

void IERG3810_Buzzer_Init(void);
