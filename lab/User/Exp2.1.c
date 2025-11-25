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
	usart2_init(36, 9600);
	delay(2000000);
	while(1)
	{
		USART2->DR = 0x41;
		delay(20000);
		USART2->DR = 0x42;
		//delay(50000);
		delay(20000);
	}
}
