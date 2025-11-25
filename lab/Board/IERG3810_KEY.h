#pragma once
#include "stm32f10x.h"
#define key2_down ((GPIOE->IDR & 0x0004) == 0)
#define key1_down ((GPIOE->IDR & 0x0008) == 0)
#define keyup_down ((GPIOA->IDR & 0x0001) == 0x0001)
#define key2_up ((GPIOE->IDR & 0x0004) == 0x0004)
#define key1_up ((GPIOE->IDR & 0x0008) == 0x0008)
#define keyup_up ((GPIOA->IDR & 0x0001) == 0)
#define key1_update last_key_1 = now_key_1; now_key_1 = (GPIOE->IDR & 0x0008) != 0
#define keyup_update last_key_UP = now_key_UP; now_key_UP = (GPIOA->IDR & 0x0001) != 0
#define key1_press (last_key_1 == 0 && now_key_1 == 1)
#define keyup_press (last_key_UP == 1 && now_key_UP == 0)
extern uint32_t last_key_1, now_key_1;
extern uint32_t last_key_UP, now_key_UP;

void IERG3810_KEY_Init(void);
