#include "stm32f10x.h"


//--Exp0
void Delay(u32 count)
{
	u32 i;
	for(i=0;i<count;i++);
}

#define key2_down ((GPIOE->IDR & 0x0004) == 0)
#define key1_down ((GPIOE->IDR & 0x0008) == 0)
#define keyup_down ((GPIOA->IDR & 0x0001) == 0x0001)
#define key2_up ((GPIOE->IDR & 0x0004) == 0x0004)
#define key1_up ((GPIOE->IDR & 0x0008) == 0x0008)
#define keyup_up ((GPIOA->IDR & 0x0001) == 0)
#define key1_update last_key_1 = now_key_1; now_key_1 = (GPIOE->IDR & 0x0008) != 0
#define keyup_update last_key_UP = now_key_UP; now_key_UP = (GPIOA->IDR & 0x0001) != 0
#define key1_press (last_key_1 == 0 && now_key_1 == 1)
#define keyup_press (last_key_UP == 1 && now_key_UP == 0)
#define DS0_Off (GPIOB->BSRR = 1<<5)
#define DS0_On (GPIOB->BRR = 1<<5)
#define DS1_Off (GPIOE->BSRR = 1<<5)
#define DS1_On (GPIOE->BRR = 1<<5)
#define Buzzer_Off (GPIOB->BSRR = 1<<8)
#define Buzzer_On (GPIOB->BRR = 1<<8)
#define DS1_toggle (GPIOE->ODR ^= 1<<5)
#define Buzzer_toggle (GPIOB->ODR ^= 1<<8)


int main(void)
{
	static uint32_t last_key_1 =1;
	static uint32_t now_key_1 = 1;
	static uint32_t last_key_UP =1;
	static uint32_t now_key_UP = 1;
	
	RCC->APB2ENR |= 1<<3;
	RCC->APB2ENR |= 1<<6;
	RCC->APB2ENR |= 1<<2;
	//LED0 AND BUZZER
	GPIOB->CRL &= 0xFF0FFFFF;
	GPIOB->CRL |= 0x00300000;
	GPIOB->CRH &= 0xFFFFFFF0;
	GPIOB->CRH |= 0x00000003;
	//KEY1 AND KEY2 AND LED1
	GPIOE->CRL &= 0xFF0F00FF;
	GPIOE->CRL |= 0x00308800;
	GPIOE->ODR &= 0xFFF3;
	GPIOE->ODR |= 0x000C;
	//KEY_UP
	GPIOA->CRL &= 0xFFFFFFF0;
	GPIOA->CRL |= 0x00000008;
	GPIOA->ODR &= 0xFFFE;
	GPIOA->ODR |= 0x0000;
	
	while(1)
	{
		Delay(5000);
		if (key2_down) DS0_On;
		else DS0_Off;
		
		key1_update;
		if (key1_press) DS1_toggle;
		
		keyup_update;
		if(keyup_press) Buzzer_toggle;
	}
}
