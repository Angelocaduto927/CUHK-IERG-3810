#include <stm32f10x.h>
#include "stm32f10x_it.h"
#include "IERG3810_KEY.h"
#include "IERG3810_LED.h"
#include "IERG3810_Buzzer.h"
#include "IERG3810_Clock.h"
#include "IERG3810_USART.h"
#include "IERG3810_Delay.h"
#include "LCD_SETUP.h"
#include "IERG3810_EXTI.h"
#include "IERG3810_Keypad.h"
#include "IERG3810_Timer.h"
#include "USART_FOR_MULTIPLAYER.h"
#include "keypad_setting.h"

extern volatile uint8_t tx_buf[TX_BUFFER_SIZE];
extern volatile uint8_t tx_head;
extern volatile uint8_t tx_tail;

extern volatile uint8_t rx_buf[RX_BUFFER_SIZE];
extern volatile uint8_t rx_head;
extern volatile uint8_t rx_tail;
int instruction2;
u8 val;
extern u32 TASKS[10];
	
int main()
{
	clocktree_init();
	//systick_init_40ms();
	systick_init_100ms();
	ps2key_extiInit();
	IERG3810_LED_Init();
	nvic_setPriorityGroup(5);
	usart2exti_init(36, 115200);
	while(1)
	{
		val = 0x30;
		TASKS[0] = 3;
		ps2count = 0;
		EXTI->IMR |= (1<<11);
		if(ps2dataReady == 1){
			EXTI->IMR &= ~(1<<11);
			u8 key_data  = (ps2key>>1) & 0xFF;
			if (kp2_pressed)
			{
				//return 1;
				val = 0x32; 
				DS0_toggle;
			}
			if (kp8_pressed)
			{
				//return 2;
				val = 0x38;
				DS0_toggle;
			}
			if (kp4_pressed)
			{
				//return 3;
				val = 0x34;
				DS0_toggle;
			}
			if (kp6_pressed)
			{
				//return 4;
				val = 0x36;
				DS0_toggle;
			}
			if (kp9_pressed)
			{
				//return 5;
				val = 0x39;
				DS0_toggle;
			}
			USART2_SendByte(val);
		}
	}
}
