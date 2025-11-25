#include <stm32f10x.h>
#include "IERG3810_KEY.h"
#include "IERG3810_LED.h"
#include "IERG3810_Buzzer.h"
#include "IERG3810_Clock.h"
#include "IERG3810_USART.h"
#include "IERG3810_Delay.h"
#include "IERG3810_LCD.h"
#include "IERG3810_EXTI.h"

void EXTI2_IRQHandler(void)
{
	u8 i;
	for (i=0;i<10;i++)
	{
		DS0_On;
		delay(1000000);
		DS0_Off;
		delay(1000000);
	}
	EXTI->PR = 1<<2;
}

void EXTI0_IRQHandler(void)
{
	u8 j;
	for (j=0;j<10;j++)
	{
		DS1_On;
		delay(1000000);
		DS1_Off;
		delay(1000000);
	}
	EXTI->PR = 1<<0;
}

int main(void)
{
	IERG3810_LED_Init();
	IERG3810_KEY_Init();
	IERG3810_Buzzer_Init();
	clocktree_init();
	usart2_init(36,9600);
	nvic_setPriorityGroup(6);
	key2_extiInit();
	keyup_extiInit(	);
	DS0_Off;
	
	
	while(1)
	{
		usart_print_txe(2,"42");
		delay(500000);
	}
	
}
