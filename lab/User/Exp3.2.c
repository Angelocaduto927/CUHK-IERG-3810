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
	//lcd_drawDot(120, 160, c_YELLOW);
	lcd_fillRectangle(c_YELLOW, 0,240,0,320);
	lcd_fillRectangle(c_BLUE, 95,50,135,50);
}
