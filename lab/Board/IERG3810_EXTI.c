#include "IERG3810_EXTI.h"
#include "IERG3810_Delay.h"

void nvic_setPriorityGroup(u8 priGroup)
{
	u32 tmp1, tmp2;
	tmp2 = (priGroup & 0x00000007) << 8;
	tmp1 = SCB->AIRCR &= 0x0000F8FF;
	tmp1 |= 0x05FA0000;
	SCB->AIRCR = tmp1 |= tmp2;	
}

void key2_extiInit(void)
{
	RCC->APB2ENR |= 1<<6;
	GPIOE->CRL &= 0XFFFFF0FF;
	GPIOE->CRL |= 0X00000800;
	GPIOE->ODR |= 1<<2;
	RCC->APB2ENR |= 0X01;
	AFIO->EXTICR[0] &= 0XFFFFF0FF;
	AFIO->EXTICR[0] |= 0X00000400;
	EXTI->IMR |= 1<<2;
	EXTI->FTSR |= 1<<2;
	NVIC->IP[8] = 0X35;
	NVIC->ISER[0] |= (1<<8);
}

void key1_extiInit(void)
{
	RCC->APB2ENR |= 1<<6;
	GPIOE->CRL &= 0XFFFF0FFF;
	GPIOE->CRL |= 0X00008000;
	GPIOE->ODR |= 1<<3;
	RCC->APB2ENR |= 0X01;
	AFIO->EXTICR[0] &= 0XFFFF0FFF;
	AFIO->EXTICR[0] |= 0X00004000;
	EXTI->IMR |= 1<<3;
	EXTI->FTSR |= 1<<3;
	NVIC->IP[9] = 0X35;
	NVIC->ISER[0] |= (1<<9);
}

void key0_extiInit(void)
{
	RCC->APB2ENR |= 1<<6;
	GPIOE->CRL &= 0XFFF0FFFF;
	GPIOE->CRL |= 0X00080000;
	GPIOE->ODR |= 1<<4;
	RCC->APB2ENR |= 0X01;
	AFIO->EXTICR[1] &= 0XFFFFFFF0;
	AFIO->EXTICR[1] |= 0X00000004;
	EXTI->IMR |= 1<<4;
	EXTI->FTSR |= 1<<4;
	NVIC->IP[10] = 0X35;
	NVIC->ISER[0] |= (1<<10);
}

void keyup_extiInit(void)
{
	RCC->APB2ENR |= 1<<2;
	GPIOA->CRL &= 0XFFFFFFF0;
	GPIOA->CRL |= 0X00000008;
  GPIOA->ODR |= 0<<0;
	RCC->APB2ENR |= 0X01;
	AFIO->EXTICR[0] &= 0XFFFFFFF0;
	AFIO->EXTICR[0] |= 0X00000000;
	EXTI->IMR |= 1<<0;
	EXTI->FTSR |= 1<<0;
	NVIC->IP[6] = 0X35;
	NVIC->ISER[0] |= (1<<6);
}

void ps2key_extiInit(void)
{
	RCC->APB2ENR |= 1<<4;
	GPIOC->CRH &= 0XFFFF00FF;
	GPIOC->CRH |= 0X00008800;
	GPIOC->ODR |= 1<<11;
	GPIOC->ODR |= 1<<10;
	RCC->APB2ENR |= 0X01;
	AFIO->EXTICR[2] &= 0XFFFF0FFF;
	AFIO->EXTICR[2] |= 0XFFFF2FFF;
	EXTI->IMR |= 1<<11;
	EXTI->FTSR |= 1<<11;
	NVIC->IP[40] = 0X95;
	NVIC->ISER[1] |= (1<<8);
}
