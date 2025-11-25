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
#include "character_setting.h"
#include "weapon_setting.h"
#include "HP_setting.h"
#include "bullet_setting.h"
#include "randomness.h"
#include "draw.h"
#include "LCD_SETUP.h"
#include "USART_FOR_MULTIPLAYER.h"

extern u32 TASKS[10];
extern volatile uint8_t tx_buf[TX_BUFFER_SIZE];
extern volatile uint8_t tx_head;
extern volatile uint8_t tx_tail;

extern volatile uint8_t rx_buf[RX_BUFFER_SIZE];
extern volatile uint8_t rx_head;
extern volatile uint8_t rx_tail;
extern u8 player1_die_flag;
extern u8 player2_die_flag;
u8 time_start_flag = 1;
u8 update_timer_flag = 1;
extern u8 ps2key;
extern u32 ps2count;
extern u8 ps2dataReady;
CHARACTER character1;
CHARACTER character2;
volatile int time = 1811;
u8 status = 0;
u8 last_status = 6;
u8 val;
u8 winner = 0;
int instruction1;
int instruction2;
int main()
{
	clocktree_init();
	systick_init_10ms();
	IERG3810_LED_Init();
	nvic_setPriorityGroup(5);
	ps2key_extiInit();
	key2_extiInit();
	key1_extiInit();
	key0_extiInit();
	keyup_extiInit();
	usart2exti_init(36, 115200);
	lcd_init();
	NVIC_SetPriority(SysTick_IRQn, 0x0F);
	delay(1000000);
	while(1)
	{
		if (status == 0)
		{
			if(last_status != 0)
			{
				DRAW_FRONT_PAGE();
			}
			last_status = 0;
		}
		else if (status == 1)
		{
			if(last_status != 1)
			{
				DRAW_INFO_PAGE();
			}
			last_status = 1;
		}
		else if (status == 2)
		{
			character1 = CREATE_CHARACTER_1();
			character2 = CREATE_CHARACTER_2();
			player1_die_flag = 0;
			player2_die_flag = 0;
			winner = 0;
			DRAW_START_PAGE();
			TASKS[0] = 3;
			TASKS[1] = 1001;
			TASKS[2] = 101;
			TASKS[5] = 1;
			TASKS[6] = 101;
			lcd_fillRectangle(c_white, 0,240, 0, 320);
			//delay(1000000);
			DRAW_ARENA();
			DRAW_HP_VALUE(character1);
			DRAW_HP_VALUE(character2);
			HP_list_init(&hplist);
			Bullet_list_init(&bulletlist1);
			Bullet_list_init(&bulletlist2);
			status = 3;
			last_status = 2;
		}
		else if (status == 3)
		{
			while(1)
			{
				if(status != 3)
				{
					break;
				}
				if(time_start_flag == 1)
				{
					tim2_init(7999, 8999);
					time_start_flag = 0;
				}
				if(last_status == 5)
				{
					CLEAR_PAUSE();
				}
				
				if(update_timer_flag == 1)
				{
					CLEAR_TIMER();
					DRAW_TIMER(time);
					update_timer_flag = 0;
				}
				
				if(TASKS[0] == 1)
				{	
					TASKS[0] = 3;
					ps2count = 0;
					EXTI->IMR |= (1<<11);
					if (ps2dataReady == 1)
					{
						EXTI->IMR &= ~(1<<11);
						u8 key_data  = (ps2key>>1) & 0xFF;
						if (kp2_pressed) instruction1 = 1;
						
						if (kp8_pressed) instruction1 = 2;
						
						if (kp4_pressed) instruction1 = 3;
						
						if (kp6_pressed) instruction1 = 4;
						
						if (kp9_pressed) instruction1 = 5;
					
						ps2count = 0;
						ps2key = 0;
						ps2dataReady = 0;
						EXTI->IMR |= (1<<11);	
					}
					else instruction1 = 0;
					
					if(RX_AVAILABLE)
					{
						val = rx_buf[rx_tail];
						rx_tail = (rx_tail + 1) % RX_BUFFER_SIZE;
						//if(val ==  0x30  ) instruction2=0;
						if(val ==  0x32  ) instruction2=1;
						if(val ==  0x38  ) instruction2=2;
						if(val ==  0x34  ) instruction2=3;
						if(val ==  0x36  ) instruction2=4;
						if(val ==  0x39  ) instruction2=5;
					}
					else{
						instruction2 = 0;
					}
					
					CHARACTER_MOVE_NEW(&character1, instruction1);
					//delay(100000);
					CHARACTER_MOVE_NEW(&character2, instruction2);
					//delay(100000);
					if(player1_die_flag == 1|| player2_die_flag == 1)
					{
						status = 4;
					}
					UPDATE_BULLET_STATUS(&character1, &character2);
					//delay(100000);
					//WEAPON_PACKS_FALLING();
					HP_PACKS_FALLING();
				}
				if(TASKS[1] == 1)
				{
					TASKS[1] = 1001;
					//int flag = RANDOM_LOOT();
					//flag = 1;
					//if(flag == 0)
					//{
					//	INIT_WEAPON_DROP();
					//}
					//else
					//{
					INIT_HP_PACKS_DROP();
					//}
				}
				/*
				if(TASKS[6] == 1)
				{
					TASKS[6] = 101;
					lcd_fillRectangle(c_white, 223, 17, 0, 113);
					lcd_fillRectangle(c_white, 223, 17, 176, 144);
					DRAW_HP_VALUE(character1);
					DRAW_HP_VALUE(character2);
				}
				*/
				last_status = 3;
				DS1_Off;
				DS0_Off;
			}
		}
		else if (status == 4) //game over stage
		{
			if(last_status != 4)
			{
				if(character1.HP > character2.HP)
				{
					//DRAW_PLAYER1_WIN();
					status = 5;
					winner = 1;
				}
				else if (character2.HP > character1.HP)
				{
					//DRAW_PLAYER2_WIN();
					status = 5;
					winner = 2;
				}
				else
				{
					DRAW_OVERTIME();
					status = 3;
					time = 611;
					time_start_flag = 1;
				}
			}
			last_status = 4;
		}
		else if (status == 5)
		{
			TIM2->CR1 &= 0xFFFFFFFE;
			SysTick->CTRL &= ~(1<<0);
			if(last_status != 4 && last_status != 5)
			{
				DRAW_PAUSE();
			}
			else
			{
				if(winner == 1 && last_status != 5)
				{
					DRAW_END_PAGE(1);
					DRAW_PLAYER1_WIN();
					last_status = 5;
				}
				if(winner == 2 && last_status != 5)
				{
					DRAW_END_PAGE(2);
					DRAW_PLAYER2_WIN();
					last_status = 5;
				}
			}
		}
	}
}

void TIM2_IRQHandler(void)
{
	if(TIM2->SR & 1<<0)
	{
		if(time == 1)
		{
			status = 4;
			TIM2->CR1 &= 0xFFFFFFFE;
		}
		else{
			update_timer_flag = 1;
			//CLEAR_TIMER();
			//DRAW_TIMER(time);
			time-=10;
		}
	}
	TIM2->SR &= ~(1<<0);
}

void EXTI2_IRQHandler(void)
{
	EXTI->IMR &= ~(1<<2);
	//TASKS[6] = 8;
	//while(TASKS[6] != 1){}
	delay(5000);
	if((GPIOE->IDR & (1<<2))==0)
	{
		if(status == 0)
		{
			last_status = status;
			status = 2;
		}
		/*
		else if(status == 3)
		{
			last_status = status;
			status = 5;
		}
		else if(status == 5)
		{
			last_status = status;
			status = 0;
			time = 1801;
			time_start_flag = 1;
			//update_timer_flag = 1;
			SysTick->CTRL |= (1<<0);
			SysTick->CTRL |= (1<<1);
			//CLEAR_PAUSE();
		}
		*/
	}
	EXTI->PR = 1<<2;
	EXTI->IMR |= 1<<2;
}

void EXTI3_IRQHandler(void)
{
	EXTI->IMR &= ~(1<<3);
	delay(5000);
	if((GPIOE->IDR & (1<<3)) == 0)
	{
		if(status == 0)
		{
			last_status = status;
			status = 1;
		}/*
		else if(status == 1)
		{
			last_status = status;
			status = 0;
		}
		*/
		else if(status == 5)
		{
			last_status = status;
			status = 3;
			time_start_flag = 1;
			//update_timer_flag = 1;
			SysTick->CTRL |= (1<<0);
			SysTick->CTRL |= (1<<1);
			//CLEAR_PAUSE();
		}
	}
	EXTI->PR = 1<<3;
	EXTI->IMR |= 1<<3;
}

void EXTI4_IRQHandler(void)
{
	EXTI->IMR &= ~(1<<4);
	delay(5000);
	if((GPIOE->IDR & (1<<4)) == 0)
	{
		if(status == 1)
		{
			last_status = status;
			status = 0;
		}
		/*
		else if(status == 5)
		{
			last_status = status;
			status = 3;
			time_start_flag = 1;
			//update_timer_flag = 1;
			SysTick->CTRL |= (1<<0);
			SysTick->CTRL |= (1<<1);
		}
		*/
		else if(status == 3)
		{
			last_status = status;
			status = 5;
		}
	}
	EXTI->PR = 1<<4;
	EXTI->IMR |= 1<<4;
}

void EXTI0_IRQHandler(void)
{
	EXTI->IMR &= ~(1<<0);
	delay(5000);
	if((GPIOA->IDR & (1<<0)) == 0)
	{
		/*
		if(status == 1)
		{
			last_status = status;
			status = 0;
		}
		else if(status == 5)
		{
			last_status = status;
			status = 3;
			time_start_flag = 1;
			//update_timer_flag = 1;
			SysTick->CTRL |= (1<<0);
			SysTick->CTRL |= (1<<1);
		}
		*/
		if(status == 5)
		{
			last_status = status;
			status = 0;
			time = 1811;
			time_start_flag = 1;
			//update_timer_flag = 1;
			SysTick->CTRL |= (1<<0);
			SysTick->CTRL |= (1<<1);
			//CLEAR_PAUSE();
		}
	}
	EXTI->PR = 1<<0;
	EXTI->IMR |= 1<<0;
}

