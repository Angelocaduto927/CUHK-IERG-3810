#include "IERG3810_Timer.h"

void tim2_init(u16 arr, u16 psc)
{
	RCC->APB1ENR|=1<<0;
	TIM2->ARR=arr;
	TIM2->PSC=psc;
	TIM2->DIER|=1<<0;
	TIM2->CR1|=0X01;
	NVIC->IP[28] = 0X11;
	NVIC->ISER[0] |= (1<<28);
}

void tim3_init(u16 arr, u16 psc)
{
	RCC->APB1ENR|=1<<1;
	TIM3->ARR=arr;
	TIM3->PSC=psc;
	TIM3->DIER|=1<<0;
	TIM3->CR1|=0X01;
	NVIC->IP[29] = 0X45;
	NVIC->ISER[0] |= (1<<29);
}

void tim4_init(u16 arr, u16 psc)
{
	RCC->APB1ENR|=1<<2;
	TIM4->ARR=arr;
	TIM4->PSC=psc;
	TIM4->DIER|=1<<0;
	TIM4->CR1|=0X01;
	NVIC->IP[30] = 0X45;
	NVIC->ISER[0] |= (1<<30);
}

void systick_init_10ms(void)
{
	SysTick->CTRL = 0;
	SysTick->LOAD = (720000-1);
	SysTick->CTRL |= 0X07;
}

void systick_init_1ms(void)
{
	SysTick->CTRL = 0;
	SysTick->LOAD = (72000-1);
	SysTick->CTRL |= 0X07;
}

void systick_init_100ms(void)
{
	SysTick->CTRL = 0;
	SysTick->LOAD = (7200000-1);
	SysTick->CTRL |= 0X07;
}

void systick_init_40ms(void)
{
	SysTick->CTRL = 0;
	SysTick->LOAD = (2880000-1);
	SysTick->CTRL |= 0X07;
}

void tim3_init_pwm_rgb(u16 arr, u16 psc)
{
	RCC->APB2ENR |= 1<<4;
	GPIOC->CRL &= 0X00FFFFFF;
	GPIOC->CRL |= 0XBB000000;
	GPIOC->CRH &= 0XFFFFFFF0;
	GPIOC->CRH |= 0X0000000B;
	RCC->APB2ENR |= 1<<0;
	AFIO->MAPR &= 0XFFFFF3FF;
	AFIO->MAPR |= 3<<10;
	RCC->APB1ENR |= 1<<1;
	TIM3->ARR = arr;
	TIM3->PSC = psc;
	TIM3->CCMR1 |= 7<<12;
	TIM3->CCMR1 |= 7<<4;
	TIM3->CCMR1 |= 1<<11;
	TIM3->CCMR1 |= 1<<2;
	TIM3->CCMR2 |= 7<<4;
	TIM3->CCMR2 |= 1<<2;
	TIM3->CCER |= 1<<4;
	TIM3->CCER |= 1<<0;
	TIM3->CCER |= 1<<8;
	TIM3->CR1 = 0X0080;
	TIM3->CR1 |= 0X01;
}

void tim3_init_pwm(u16 arr, u16 psc)
{
	RCC->APB2ENR |= 1<<3;
	GPIOB->CRL &= 0XFF0FFFFF;
	GPIOB->CRL |= 0X00B00000;
	RCC->APB2ENR |= 1<<0;
	AFIO->MAPR &= 0XFFFFF3FF;
	AFIO->MAPR |= 1<<11;
	RCC->APB1ENR |= 1<<1;
	TIM3->ARR = arr;
	TIM3->PSC = psc;
	TIM3->CCMR1 |= 7<<12;
	TIM3->CCMR1 |= 1<<11;
	TIM3->CCER |= 1<<4;
	TIM3->CR1 = 0X0080;
	TIM3->CR1 |= 0X01;
}
