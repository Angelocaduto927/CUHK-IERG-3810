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
	lcd_init();
	delay(1000000);
	lcd_fillRectangle(c_black, 0,240,0, 320);
	delay(5000000);
	lcd_showChar(80, 200, 49, c_YELLOW, c_BLUE);
	lcd_showChar(88, 200, 49, c_YELLOW, c_BLUE);
	lcd_showChar(96, 200, 53, c_YELLOW, c_BLUE);
	lcd_showChar(104, 200, 53, c_YELLOW, c_BLUE);
	lcd_showChar(112, 200, 50, c_YELLOW, c_BLUE);
	lcd_showChar(120, 200, 49, c_YELLOW, c_BLUE);
	lcd_showChar(128, 200, 53, c_YELLOW, c_BLUE);
	lcd_showChar(136, 200, 49, c_YELLOW, c_BLUE);
	lcd_showChar(144, 200, 49, c_YELLOW, c_BLUE);
	lcd_showChar(152, 200, 51, c_YELLOW, c_BLUE);
	
	lcd_showChar(80, 100, 49, c_YELLOW, c_BLUE);
	lcd_showChar(88, 100, 49, c_YELLOW, c_BLUE);
	lcd_showChar(96, 100, 53, c_YELLOW, c_BLUE);
	lcd_showChar(104, 100, 53, c_YELLOW, c_BLUE);
	lcd_showChar(112, 100, 50, c_YELLOW, c_BLUE);
	lcd_showChar(120, 100, 49, c_YELLOW, c_BLUE);
	lcd_showChar(128, 100, 53, c_YELLOW, c_BLUE);
	lcd_showChar(136, 100, 48, c_YELLOW, c_BLUE);
	lcd_showChar(144, 100, 57, c_YELLOW, c_BLUE);
	lcd_showChar(152, 100, 56, c_YELLOW, c_BLUE);
}
