#include <stm32f10x.h>
#include "stm32f10x_it.h"
#include "IERG3810_KEY.h"
#include "IERG3810_LED.h"
#include "IERG3810_Buzzer.h"
#include "IERG3810_Clock.h"
#include "IERG3810_USART.h"
#include "IERG3810_Delay.h"
#include "IERG3810_EXTI.h"
#include "IERG3810_Keypad.h"
#include "IERG3810_Timer.h"
//#include "keypad_setting.h"
#include "USART_FOR_MULTIPLAYER.h"

volatile uint8_t rx_buf[RX_BUFFER_SIZE];
volatile uint8_t rx_head = 0;
volatile uint8_t rx_tail = 0;
volatile uint8_t tx_buf[TX_BUFFER_SIZE];
volatile uint8_t tx_head = 0;
volatile uint8_t tx_tail = 0;

void usart2exti_init(u32 pclkl, u32 baud)
{
	 float temp;
    u16 mantissa;
    u16 fraction;
    temp = (float)((pclkl * 1000000) / (baud * 16));

    mantissa = temp;
    fraction = (temp - mantissa) * 16;
    mantissa <<= 4;
    mantissa += fraction;
    RCC->APB2ENR |= 1 << 2;
    RCC->APB1ENR |= 1 << 17;
    GPIOA->CRL &= 0xFFFF00FF;
    GPIOA->CRL |= 0x00004B00;
    RCC->APB1RSTR |= 1 << 17;
    RCC->APB1RSTR &= ~(1 << 17);
    USART2->BRR = mantissa;
    USART2->CR1 |= 0x202C;   //TXE INTERRUPT ENABLE
		NVIC->IP[38] = 0X95;
		NVIC->ISER[1] |= (1<<6);
}
void USART2_SendByte(u8 data) {
    uint8_t next = (tx_head + 1) % TX_BUFFER_SIZE;
    while(next == tx_tail); 
    tx_buf[tx_head] = data;
    tx_head = next;
    USART2->CR1 |= 0x0080;

}

void USART2_IRQHandler(void) {
 
  if (USART2->SR & 0x20)  // RXNE flag
    {
        uint8_t data = USART2->DR;
        uint8_t next = (rx_head + 1) % RX_BUFFER_SIZE;
        if(next != rx_tail)
				{					
					rx_buf[rx_head] = data;
					rx_head = next;
				}
   
    }
		 if(USART2->SR & 0x80)
		 {
        if(tx_head != tx_tail) {
            USART2->DR = tx_buf[tx_tail];
            tx_tail = (tx_tail + 1) % TX_BUFFER_SIZE;
        } 
				else USART2->CR1 &= ~0x0080;
			}
}

////////////////////////////////////////////////////////////////////////////////////
/*extern u32 TASKS[10];
int main()
{
	clocktree_init();
	//systick_init_40ms();
	systick_init_40ms();
	ps2key_extiInit();
	IERG3810_LED_Init();
	nvic_setPriorityGroup(5);
	usart2exti_init(36, 9600);
	delay(1000000);
	//TASKS[0] = 3;
	while(1)
	{
		//int instruction = 0;
			ps2count = 0;
			//ones = 0;
			full_data = 0;
			EXTI->IMR |= (1<<11);
			TASKS[4] = 10;
			while(TASKS[4] > 1 && ps2count < 11){}
			if(ps2count != 11){}
			else{
				EXTI->IMR &= ~(1<<11);
				if (parity_check(full_data) == 1)
				{
					if (kp2_pressed)
					{
						//return 1;
						USART2_SendByte(0x32);
					}
					if (kp8_pressed)
					{
						//return 2;
						USART2_SendByte(0x38);
					}
					if (kp4_pressed)
					{
						//return 3;
						USART2_SendByte(0x34);
					}
					if (kp6_pressed)
					{
						//return 4;
						USART2_SendByte(0x36);
					}
					if (kp9_pressed)
					{
						//return 5;
						USART2_SendByte(0x39);
					}
				}	
				else{}
				//ps2count = 0;
				//ones = 0;
				//last_two_data = last_one_data;
				//last_one_data = key_data;
				//full_data = 0;
				EXTI->IMR |= (1<<11);
				}
			if (ps2count >= 11) ps2count = 0; 
			}
}

*/
