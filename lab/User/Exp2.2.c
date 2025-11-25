#include <stm32f10x.h>
#include "IERG3810_KEY.h"
#include "IERG3810_LED.h"
#include "IERG3810_Buzzer.h"
#include "IERG3810_Clock.h"
#include "IERG3810_USART.h"
#include "IERG3810_Delay.h"

int main(void)
{
	clocktree_init();
	//usart2_init(36, 9600);
	//delay(2000000);
	usart1_init(72, 9600);
	delay(20000000);
	while(1)
	{
		USART1->DR = 0x31;
		delay(50000);
		USART1->DR = 0x31;
		delay(50000);
		USART1->DR = 0x35;
		delay(50000);
		USART1->DR = 0x35;
		delay(50000);
		USART1->DR = 0x32;
		delay(50000);
		USART1->DR = 0x31;
		delay(50000);
		USART1->DR = 0x35;
		delay(50000);
		USART1->DR = 0x31;
		delay(50000);
		USART1->DR = 0x31;
		delay(50000);
		USART1->DR = 0x33;
		delay(50000);
		delay(1000000);
	}
}
