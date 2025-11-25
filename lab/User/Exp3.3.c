#include <stm32f10x.h>
#include "IERG3810_KEY.h"
#include "IERG3810_LED.h"
#include "IERG3810_Buzzer.h"
#include "IERG3810_Clock.h"
#include "IERG3810_USART.h"
#include "IERG3810_Delay.h"
#include "IERG3810_LCD.h"

u8 i = 10;
int main(void)
{
	lcd_init();
	delay(10000000);
	//lcd_drawDot(120, 160, c_YELLOW);
	lcd_fillRectangle(c_black, 0, 240, 0, 320);
	delay(10000000);
	lcd_sevenSegment(c_YELLOW, 80, 80, 8);
	delay(10000000);
	for(i = 10; i>0; i--)
	{
		lcd_fillRectangle(c_black, 0, 240, 0, 320);
		lcd_sevenSegment(c_YELLOW, 80, 80, i-1);
		delay(10000000);
		
	}
}
