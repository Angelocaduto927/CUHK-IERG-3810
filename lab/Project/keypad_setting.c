#include <stm32f10x.h>
#include "IERG3810_Keypad.h"

extern u32 TASKS[10];

int READ_KEYPAD()
{
	ps2count = 0;
	EXTI->IMR |= (1<<11);
	TASKS[4] = 3;
	if (ps2dataReady == 1)
	{
		EXTI->IMR &= ~(1<<11);
		u8 key_data  = (ps2key>>1) & 0xFF;
		if (kp2_pressed)
		{
			return 1;
		}
		if (kp8_pressed)
		{
			return 2;
		}
		if (kp4_pressed)
		{
			return 3;
		}
		if (kp6_pressed)
		{
			return 4;
		}
		if (kp9_pressed)
		{
			return 5;
		}
	}	
	else{}
	return 0;
}
