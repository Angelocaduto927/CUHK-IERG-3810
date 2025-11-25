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

void ds0_turnOff(void)
{
	GPIOB->BSRR = 1<<5;
}

void ds0_turnOff2(void)
{
	ds0_turnOff();
}

int main(void)
{
	clocktree_init();
	IERG3810_LED_Init();
	IERG3810_Buzzer_Init();
	IERG3810_KEY_Init();
	nvic_setPriorityGroup(5);
	DS0_Off;
	DS1_Off;
	tim3_init(4999,7199);
	
	while(1)
	{
	/*
		DS0_On;
		DS0_Off;
		DS0_On;
		ds0_turnOff();
		DS0_On;
		ds0_turnOff2();
		DS0_On;
		*/
	}
}

void TIM3_IRQHandler(void)
{
	
	DS0_On;
	DS0_Off;
	DS0_On;
	ds0_turnOff();
	DS0_On;
	ds0_turnOff2();
	DS0_On;
	TIM3->SR &= ~(1<<0);
	TIM3->SR &= ~(1<<0);
}

