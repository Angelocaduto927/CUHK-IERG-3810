#ifndef __IERG3810_LCD_SETUP_H
#define __IERG3810_LCD_SETUP_H
#include "stm32f10x.h"

// put procedure header here

#define LCD_BASE		((u32)(0x6C000000|0x000007FE))
#define LCD					((LCD_TypeDef *) LCD_BASE)

#define c_black 0x0000
#define c_white 0xFFFF
#define c_RED 0xF800
#define c_GREEN 0x07E0
#define c_BLUE 0x001F
#define c_YELLOW 0xFFE0
#define c_TAN 0xD591
#define c_SADDLE_BROWN 0x8A22
#define c_LIGHT_GRAY 0xC618
#define c_GRAY 0x8410
#define c_DARK_GRAY 0x4208




#define LCD_LIGHT_OFF GPIOB->BRR = 1
#define LCD_LIGHT_ON GPIOB->BSRR = 1 



void lcd_backlight_init(void);
void lcd_wr_reg(u16 regval);
void lcd_wr_data(u16 data);
void lcd_9341_setParameter(void);
void lcd_init(void);
void lcd_drawDot(u16 x, u16 y, u16 color);
void lcd_fillRectangle(u16 color, u16 start_x,
  u16 length_x, u16 start_y, u16 length_y);


#endif
