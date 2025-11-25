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
	
int main(void)
{
	IERG3810_LED_Init();
	IERG3810_KEY_Init();
	IERG3810_Buzzer_Init();
	clocktree_init();
	usart2_init(36,9600);
	//tim3_init_pwm(9999,72);
	tim4_init(4999, 7199);
	tim3_init_pwm(4999,95);
	systick_init_1ms();
	heartbeat[0]= 2;
	DS1_Off;
	
	while(1)
	{
		if (heartbeat[0] == 1)
		{
			heartbeat[0] = 2;
			if (dir) led0pwmval++;
			else led0pwmval--;
			if (led0pwmval > 5000) dir = 0;	
			if (led0pwmval == 0) dir = 1;
			LED0_PWM_VAL = led0pwmval;
		}
	}
}

void TIM4_IRQHandler(void)
{
	if(TIM4->SR & 1<<0)
	{
		DS1_toggle;
	}
	TIM4->SR &= ~(1<<0);
}
