#include <stm32f10x.h>
#include "stm32f10x_it.h"
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
extern u32 heartbeat[10];

int main(void)
{
	clocktree_init();
	IERG3810_LED_Init();
	IERG3810_Buzzer_Init();
	IERG3810_KEY_Init();
	nvic_setPriorityGroup(5);
	systick_init_10ms();
	DS0_Off;
	DS1_Off;
	heartbeat[0] = 11;
	heartbeat[1] = 17;
	
	while(1)
	{
		if(heartbeat[0] == 1)
		{
			heartbeat[0] = 11;
			GPIOB->ODR ^= 1<<5;
		}
		if(heartbeat[1] == 1)
		{
			heartbeat[1] = 17;
			GPIOE->ODR ^= 1<<5;
		}
	}
}

