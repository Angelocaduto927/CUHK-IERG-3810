#pragma once
#include "stm32f10x.h"

void tim2_init(u16 arr, u16 psc);
void tim3_init(u16 arr, u16 psc);
void tim4_init(u16 arr, u16 psc);
void tim3_init_pwm(u16 arr, u16 psc);
void systick_init_10ms(void);
void systick_init_1ms(void);
void systick_init_40ms(void);
void tim3_init_pwm_rgb(u16 arr, u16 psc);
void systick_init_100ms(void);
