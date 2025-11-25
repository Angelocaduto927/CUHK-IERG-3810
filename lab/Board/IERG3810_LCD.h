#pragma once
#include "stm32f10x.h"

#define LCD_BASE ((u32)(0x6C000000 | 0x000007FE))
#define LCD  ((LCD_TypeDef *) LCD_BASE)
#define LCD_LIGHT_ON (GPIOB->BSRR = 0X00000001)
#define LCD_LIGHT_OFF (GPIOB->BSRR = 0X00000000)

#define c_black 0x0000
#define c_white 0xFFFF
#define c_RED 0XF800
#define c_GREEN 0x07E0
#define c_BLUE 0x001F
#define c_YELLOW 0xFFE0

typedef struct
{
	u16 LCD_REG;
	u16 LCD_RAM;
} LCD_TypeDef;

void lcd_wr_reg(u16 regval);
void lcd_wr_data(u16 data);
void lcd_9341_setParameter(void);
void lcd_backlight_init(void);
void lcd_init(void);
void lcd_drawDot(u16 x, u16 y, u16 color);
void lcd_fillRectangle(u16 color, u16 start_x, u16 length_x, u16 start_y, u16 length_y);
void lcd_draw_vertical_line(u16 color, u16 start_x, u16 start_y, u16 length);
void lcd_sevenSegment(u16 color, u16 start_x, u16 start_y, u8 digit);
void lcd_showChar(u16 x, u16 y, u8 ascii, u16 color, u16 bgcolor);
void lcd_showChinChar(u16 x, u16 y, u8 ascii, u16 color);
void lcd_showChar_with_bg(u16 x, u16 y, u8 ascii, u16 color,u16 bgcolor, u16 setcolor);
