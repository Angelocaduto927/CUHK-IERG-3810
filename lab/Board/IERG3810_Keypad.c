/*#include "IERG3810_Keypad.h"
#include "stdbool.h"

u8 ps2count = 0;
u16 full_data = 0;
u8 key_data = 0;
u8 last_one_data = 0;
u8 last_two_data = 0;
u8 ones = 0;
u8 parity_check_index = 0;

void EXTI15_10_IRQHandler(void)
{
	if (EXTI->PR & 1<<11)
	{
		full_data |= ((GPIOC->IDR & 0X00000400) >> 10) << ps2count;
		ps2count ++;
		EXTI->PR = 1<<11;
		EXTI->PR = 1<<11;
	}	
}


*/

#include "IERG3810_Keypad.h"
#include "stdbool.h"

u8 ps2key = 0;
u32 ps2count = 0;
u8 ps2dataReady = 0;

void EXTI15_10_IRQHandler(void)
{
	u8 tmp=0;

	
	tmp = ((GPIOC->IDR>>10) & 0x01);
	if (ps2count<11)
	{
		ps2key |= (tmp << ps2count);
		ps2count++;
	
	}
	if (ps2count == 11) ps2dataReady = 1;
	EXTI->PR = 1<<11;
	EXTI->PR = 1<<11;
}
/*
u8 parity_check(u16 data)
{
	ps2key = (data>>1) & 0xFF;
	for(parity_check_index=0; parity_check_index<=7; parity_check_index++)
	{
		if ((key_data & 1<<parity_check_index)>>parity_check_index == 1)
		{
			ones++;
		}
	}
	if((ones + ((data & 1<<9)>>9))%2 == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}*/
