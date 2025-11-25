#pragma once
#include "stm32f10x.h"

void nvic_setPriorityGroup(u8 priGroup);
void key2_extiInit(void);
void keyup_extiInit(void);
void key0_extiInit(void);
void key1_extiInit(void);
void ps2key_extiInit(void);
