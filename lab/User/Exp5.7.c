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

#define LED0_PWM_VAL TIM3->CCR2
u16 led0pwmval = 0;
u8 dir = 1;
extern u32 heartbeat[10];

void program_one(void)
{
	if (heartbeat[0] == 51)
	{
		TIM3->CCR1 = 0;
		TIM3->CCR2 = 5000;
		TIM3->CCR3 = 5000;
	}
	if (heartbeat[0] == 41)
	{
		TIM3->CCR1 = 0;
		TIM3->CCR2 = 0;
		TIM3->CCR3 = 5000;
	}
	if (heartbeat[0] == 31)
	{
		TIM3->CCR1 = 5000;
		TIM3->CCR2 = 0;
		TIM3->CCR3 = 5000;
	}
	if (heartbeat[0] == 21)
	{
		TIM3->CCR1 = 5000;
		TIM3->CCR2 = 0;
		TIM3->CCR3 = 0;
	}
	if (heartbeat[0] == 11)
	{
		TIM3->CCR1 = 5000;
		TIM3->CCR2 = 5000;
		TIM3->CCR3 = 0;
	}
	if (heartbeat[0] == 1)
	{
		heartbeat[0] = 60;
		TIM3->CCR1 = 0;
		TIM3->CCR2 = 5000;
		TIM3->CCR3 = 0;
	}
}

void program_two(void)
{
	if (heartbeat[1] == 111)
	{
		TIM3->CCR1 = 0;
		TIM3->CCR2 = 5000;
		TIM3->CCR3 = 5000;
	}
	if (heartbeat[1] == 101)
	{
		TIM3->CCR1 = 5000;
		TIM3->CCR2 = 5000;
		TIM3->CCR3 = 5000;
	}
	if (heartbeat[1] == 91)
	{
		TIM3->CCR1 = 0;
		TIM3->CCR2 = 0;
		TIM3->CCR3 = 5000;
	}
	if (heartbeat[1] == 81)
	{
		TIM3->CCR1 = 5000;
		TIM3->CCR2 = 5000;
		TIM3->CCR3 = 5000;
	}
	if (heartbeat[1] == 71)
	{
		TIM3->CCR1 = 5000;
		TIM3->CCR2 = 0;
		TIM3->CCR3 = 5000;
	}
	if (heartbeat[1] == 61)
	{
		TIM3->CCR1 = 5000;
		TIM3->CCR2 = 5000;
		TIM3->CCR3 = 5000;
	}
	if (heartbeat[1] == 51)
	{
		TIM3->CCR1 = 5000;
		TIM3->CCR2 = 0;
		TIM3->CCR3 = 0;
	}
	if (heartbeat[1] == 41)
	{
		TIM3->CCR1 = 5000;
		TIM3->CCR2 = 5000;
		TIM3->CCR3 = 5000;
	}
	if (heartbeat[1] == 31)
	{
		TIM3->CCR1 = 5000;
		TIM3->CCR2 = 5000;
		TIM3->CCR3 = 0;
	}
	if (heartbeat[1] == 21)
	{
		TIM3->CCR1 = 5000;
		TIM3->CCR2 = 5000;
		TIM3->CCR3 = 5000;
	}
	if (heartbeat[1] == 11)
	{
		TIM3->CCR1 = 0;
		TIM3->CCR2 = 5000;
		TIM3->CCR3 = 0;
	}
	if (heartbeat[1] == 1)
	{
		heartbeat[1] = 120;
		TIM3->CCR1 = 5000;
		TIM3->CCR2 = 5000;
		TIM3->CCR3 = 5000;
	}
}
	
int main(void)
{
	IERG3810_LED_Init();
	IERG3810_KEY_Init();
	IERG3810_Buzzer_Init();
	clocktree_init();
	usart2_init(36,9600);
	tim3_init_pwm_rgb(4999,95);
	systick_init_100ms();
	heartbeat[0]= 60;
	heartbeat[1]= 120;
	DS1_Off;
	DS0_Off;
	
	while(1)
	{
		//program_one();
		program_two();
	}
}

