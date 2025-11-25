#include "IERG3810_KEY.h"

//KEY STATUS Init
uint32_t last_key_1 =1;
uint32_t now_key_1 = 1;
uint32_t last_key_UP =1;
uint32_t now_key_UP = 1;
void IERG3810_KEY_Init(void)
{
		RCC->APB2ENR |= 1<<6;
		RCC->APB2ENR |= 1<<2;
    // KEY_UP
    GPIOA->CRL &= 0xFFFFFFF0;
    GPIOA->CRL |= 0x00000008;
    GPIOA->ODR &= 0xFFFE;
    GPIOA->ODR |= 0x0000;

    // KEY1
    GPIOE->CRL &= 0xFFFF0FFF;
    GPIOE->CRL |= 0x00008000;
    GPIOE->ODR &= 0xFFF7;
    GPIOE->ODR |= 0x0008;

    // KEY2
    GPIOE->CRL &= 0xFFFFF0FF;
    GPIOE->CRL |= 0x00000800;
    GPIOE->ODR &= 0xFFFB;
    GPIOE->ODR |= 0x0004;
}
