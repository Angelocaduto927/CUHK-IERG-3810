#include <stm32f10x.h>
#include "IERG3810_KEY.h"
#include "IERG3810_LED.h"
#include "IERG3810_Buzzer.h"
#include "IERG3810_Clock.h"
#include "IERG3810_USART.h"
#include "IERG3810_Delay.h"
#include "IERG3810_LCD.h"

int main(void)
{
	u8 i;
	lcd_init();
	delay(1000000);
	//lcd_drawDot(120, 160, c_YELLOW);//lcd_fillRectangle(c_GREEN, 120,100,160,100);
	/*lcd_draw_vertical_line(c_black, 10, 10, 100);lcd_draw_vertical_line(c_white, 20, 10, 100);lcd_draw_vertical_line(c_GREEN, 30, 10, 100);lcd_draw_vertical_line(c_RED, 40, 10, 100);lcd_draw_vertical_line(c_BLUE, 50, 10, 100);
	*/
	for(i = 10; i< 110; i++)
	{
		lcd_drawDot(10, i, c_black);
	}
	for(i = 10; i< 110; i++)
	{
		lcd_drawDot(20, i, c_white);
	}
	for(i = 10; i< 110; i++)
	{
		lcd_drawDot(30, i, c_GREEN);
	}
	for(i = 10; i< 110; i++)
	{
		lcd_drawDot(40, i, c_RED);
	}
	for(i = 10; i< 110; i++)
	{
		lcd_drawDot(50, i, c_BLUE);
	}
}
