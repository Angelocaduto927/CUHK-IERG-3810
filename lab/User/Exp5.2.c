#include <stm32f10x.h>
#include "IERG3810_KEY.h"
#include "IERG3810_LED.h"
#include "IERG3810_Buzzer.h"
#include "IERG3810_Clock.h"
#include "IERG3810_USART.h"
#include "IERG3810_Delay.h"
#include "IERG3810_LCD.h"
#include "IERG3810_EXTI.h"
#include "IERG3810_Keypad.h"
#include "IERG3810_Timer.h"

int main(void)
{
	clocktree_init();
	IERG3810_LED_Init();
	IERG3810_Buzzer_Init();
	IERG3810_KEY_Init();
	nvic_setPriorityGroup(5);
	tim3_init(4999,7199);
	tim4_init(2499,7199);
	DS0_Off;
	DS1_Off;
	
	while(1)
	{
		;
	}
}

void TIM3_IRQHandler(void)
{
	if(TIM3->SR & 1<<0)
	{
		DS0_toggle;
	}
	TIM3->SR &= ~(1<<0);
}

void TIM4_IRQHandler(void)
{
	if(TIM4->SR & 1<<0)
	{
		DS1_toggle;
	}
	TIM4->SR &= ~(1<<0);
}
