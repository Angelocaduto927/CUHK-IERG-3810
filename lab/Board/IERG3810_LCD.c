#include "IERG3810_LCD.h"
#include "IERG3810_Delay.h"
#include "FONT.H"
#include "CFONT.H"

void lcd_wr_reg(u16 regval)
{
	LCD->LCD_REG=regval;
}

void lcd_wr_data(u16 data)
{
	LCD->LCD_RAM=data;
}

void lcd_9341_setParameter(void)
{
	lcd_wr_reg(0X01);
	lcd_wr_reg(0X11);
	lcd_wr_reg(0X3A);
	lcd_wr_data(0X55);
	lcd_wr_reg(0X29);
	lcd_wr_reg(0X36);
	lcd_wr_data(0XC8);
}

void lcd_backlight_init(void)
{
	RCC->APB2ENR |= 1<<3;
	GPIOB->CRL&=0XFFFFFFF0;
	GPIOB->CRL|=0X00000003;
}

void lcd_init(void)
{
	RCC->AHBENR |= 1<<8;
	RCC->APB2ENR|=1<<3;
	RCC->APB2ENR|=1<<5;
	RCC->APB2ENR|=1<<6;
	RCC->APB2ENR|=1<<8;
	GPIOB->CRL&=0XFFFFFFF0;
	GPIOB->CRL|=0X00000003;
	
	GPIOD->CRH&=0X00FFF000;
	GPIOD->CRH|=0XBB000BBB;
	GPIOD->CRL&=0XFF00FF00;
	GPIOD->CRL|=0X00BB00BB;
	
	GPIOE->CRH&=0X00000000;
	GPIOE->CRH|=0XBBBBBBBB;
	GPIOE->CRL&=0X0FFFFFFF;
	GPIOE->CRL|=0XB0000000;
	
	GPIOG->CRH&=0XFFF0FFFF;
	GPIOG->CRH|=0X000B0000;
	GPIOG->CRL&=0XFFFFFFF0;
	GPIOG->CRL|=0X0000000B;
	
	FSMC_Bank1->BTCR[6]=0X00000000;
	FSMC_Bank1->BTCR[7]=0X00000000;
	FSMC_Bank1E->BWTR[6]=0x00000000;
	FSMC_Bank1->BTCR[6]|=1<<12;
	FSMC_Bank1->BTCR[6]|=1<<14;
	FSMC_Bank1->BTCR[6]|=1<<4;
	FSMC_Bank1->BTCR[7]|=0<<28;
	FSMC_Bank1->BTCR[7]|=1<<0;
	FSMC_Bank1->BTCR[7]|=0xF<<8;
	FSMC_Bank1E->BWTR[6]|=0<<28;
	FSMC_Bank1E->BWTR[6]|=0<<0;
	FSMC_Bank1E->BWTR[6]|=3<<8;
	FSMC_Bank1->BTCR[6]|=1<<0;
	
	lcd_9341_setParameter();
	
	lcd_backlight_init();
	LCD_LIGHT_ON;
}

void lcd_drawDot(u16 x, u16 y, u16 color)
{
	lcd_wr_reg(0X2A);
	lcd_wr_data(x>>8);
	lcd_wr_data(x & 0XFF);
	lcd_wr_data(0X01);
	lcd_wr_data(0X3F);
	lcd_wr_reg(0X2B);
	lcd_wr_data(y>>8);
	lcd_wr_data(y & 0XFF);
	lcd_wr_data(0X01);
	lcd_wr_data(0XDF);
	lcd_wr_reg(0X2C);
	lcd_wr_data(color);
}

void lcd_fillRectangle(u16 color, u16 start_x, u16 length_x, u16 start_y, u16 length_y)
{
	u32 index=0;
	lcd_wr_reg(0x2A);
	lcd_wr_data(start_x>>8);
	lcd_wr_data(start_x&0xFF);
	lcd_wr_data((length_x + start_x -1) >> 8);
	lcd_wr_data((length_x + start_x -1) & 0xFF);
	lcd_wr_reg(0x2B);
	lcd_wr_data(start_y>>8);
	lcd_wr_data(start_y&0xFF);
	lcd_wr_data((length_y + start_y -1) >> 8);
	lcd_wr_data((length_y + start_y -1) & 0xFF);
	lcd_wr_reg(0x2C);
	delay(100);
	for(index=0;index<length_x*length_y;index++)
	{
		lcd_wr_data(color);
	}
}

void lcd_draw_vertical_line(u16 color, u16 start_x, u16 start_y, u16 length)
{
	u32 index = 0;
	lcd_wr_reg(0x2A);
	lcd_wr_data(start_x>>8);
	lcd_wr_data(start_x&0xFF);
	lcd_wr_data(start_x>>8);
	lcd_wr_data(start_x&0xFF);
	lcd_wr_reg(0x2B);
	lcd_wr_data(start_y>>8);
	lcd_wr_data(start_y&0xFF);
	lcd_wr_data((length + start_y -1) >> 8);
	lcd_wr_data((length + start_y -1) & 0xFF);
	lcd_wr_reg(0x2C);
	delay(100);
	for(index=0;index<length;index++)
	{
		lcd_wr_data(color);
		delay(10000);
	}
}

void lcd_sevenSegment(u16 color, u16 start_x, u16 start_y, u8 digit)
{
	if (digit == 0)
	{
		lcd_fillRectangle(color, start_x+10, 60, start_y, 10); //底横线
		lcd_fillRectangle(color, start_x+10, 60, start_y+150, 10); //上横线
		lcd_fillRectangle(color, start_x, 10, start_y+10, 65); //左下竖线
		lcd_fillRectangle(color, start_x, 10, start_y+85, 65); //左上竖线
		lcd_fillRectangle(color, start_x+70, 10, start_y+10, 65); //右下竖线
		lcd_fillRectangle(color, start_x+70, 10, start_y+85, 65); //右上竖线
	}
	if (digit == 1)
	{
		lcd_fillRectangle(color, start_x+70, 10, start_y+10, 65); //右下竖线
		lcd_fillRectangle(color, start_x+70, 10, start_y+85, 65); //右上竖线
	}
	if (digit == 2)
	{
		lcd_fillRectangle(color, start_x+10, 60, start_y, 10); //底横线
		lcd_fillRectangle(color, start_x+10, 60, start_y+75, 10); //中横线
		lcd_fillRectangle(color, start_x+10, 60, start_y+150, 10); //上横线
		lcd_fillRectangle(color, start_x, 10, start_y+10, 65); //左下竖线
		lcd_fillRectangle(color, start_x+70, 10, start_y+85, 65); //右上竖线
	}
	if (digit == 3)
	{
		lcd_fillRectangle(color, start_x+10, 60, start_y, 10); //底横线
		lcd_fillRectangle(color, start_x+10, 60, start_y+75, 10); //中横线
		lcd_fillRectangle(color, start_x+10, 60, start_y+150, 10); //上横线
		lcd_fillRectangle(color, start_x+70, 10, start_y+10, 65); //右下竖线
		lcd_fillRectangle(color, start_x+70, 10, start_y+85, 65); //右上竖线
	}
	if (digit == 4)
	{
		lcd_fillRectangle(color, start_x+10, 60, start_y+75, 10); //中横线
		lcd_fillRectangle(color, start_x, 10, start_y+85, 65); //左上竖线
		lcd_fillRectangle(color, start_x+70, 10, start_y+10, 65); //右下竖线
		lcd_fillRectangle(color, start_x+70, 10, start_y+85, 65); //右上竖线
	}
	if (digit == 5)
	{
		lcd_fillRectangle(color, start_x+10, 60, start_y, 10); //底横线
		lcd_fillRectangle(color, start_x+10, 60, start_y+75, 10); //中横线
		lcd_fillRectangle(color, start_x+10, 60, start_y+150, 10); //上横线
		lcd_fillRectangle(color, start_x, 10, start_y+85, 65); //左上竖线
		lcd_fillRectangle(color, start_x+70, 10, start_y+10, 65); //右下竖线
	}
	if (digit == 6)
	{
		lcd_fillRectangle(color, start_x+10, 60, start_y, 10); //底横线
		lcd_fillRectangle(color, start_x+10, 60, start_y+75, 10); //中横线
		lcd_fillRectangle(color, start_x+10, 60, start_y+150, 10); //上横线
		lcd_fillRectangle(color, start_x, 10, start_y+10, 65); //左下竖线
		lcd_fillRectangle(color, start_x, 10, start_y+85, 65); //左上竖线
		lcd_fillRectangle(color, start_x+70, 10, start_y+10, 65); //右下竖线
	}
	if (digit == 7)
	{
		lcd_fillRectangle(color, start_x+10, 60, start_y+150, 10); //上横线
		lcd_fillRectangle(color, start_x+70, 10, start_y+10, 65); //右下竖线
		lcd_fillRectangle(color, start_x+70, 10, start_y+85, 65); //右上竖线
	}
	if (digit == 8)
	{
		lcd_fillRectangle(color, start_x+10, 60, start_y, 10); //底横线
		lcd_fillRectangle(color, start_x+10, 60, start_y+75, 10); //中横线
		lcd_fillRectangle(color, start_x+10, 60, start_y+150, 10); //上横线
		lcd_fillRectangle(color, start_x, 10, start_y+10, 65); //左下竖线
		lcd_fillRectangle(color, start_x, 10, start_y+85, 65); //左上竖线
		lcd_fillRectangle(color, start_x+70, 10, start_y+10, 65); //右下竖线
		lcd_fillRectangle(color, start_x+70, 10, start_y+85, 65); //右上竖线
	}
	if (digit == 9)
	{
		lcd_fillRectangle(color, start_x+10, 60, start_y, 10); //底横线
		lcd_fillRectangle(color, start_x+10, 60, start_y+75, 10); //中横线
		lcd_fillRectangle(color, start_x+10, 60, start_y+150, 10); //上横线
		lcd_fillRectangle(color, start_x, 10, start_y+85, 65); //左上竖线
		lcd_fillRectangle(color, start_x+70, 10, start_y+10, 65); //右下竖线
		lcd_fillRectangle(color, start_x+70, 10, start_y+85, 65); //右上竖线
	}
}

void lcd_showChar(u16 x, u16 y, u8 ascii, u16 color, u16 bgcolor)
{
	u8 i, b, temp1, temp2;
	u16 tempX, tempY;
	if (ascii<32 || ascii>127) return;
	ascii -= 32;
	tempX= x;
	for (i=0; i<16; i=i+2)
	{
		temp1 = asc2_1608[ascii][i];
		temp2 = asc2_1608[ascii][i+1];
		tempY = y;
		for (b=0;b<8;b++)
		{
			if (temp1%2 == 1) lcd_drawDot(tempX, tempY+8, color);
			if (temp2%2 == 1) lcd_drawDot(tempX, tempY, color);
			temp1 = temp1 >> 1;
			temp2 = temp2 >> 1;
			tempY++;
		}
		tempX++;
	}
}

void lcd_showChinChar(u16 x, u16 y, u8 ascii, u16 color)
{
	u8 i, b, temp1, temp2;
	u16 tempX, tempY;
	if (ascii>9) return;
	tempX= x;
	for (i=0; i<32; i=i+2)
	{
		temp1 = chi_1616[ascii][i];
		temp2 = chi_1616[ascii][i+1];
		tempY = y;
		for (b=0;b<8;b++)
		{
			if (temp1%2 == 1) lcd_drawDot(tempX, tempY+8, color);
			if (temp2%2 == 1) lcd_drawDot(tempX, tempY, color);
			temp1 = temp1 >> 1;
			temp2 = temp2 >> 1;
			tempY++;
		}
		tempX++;
	}
}

void lcd_showChar_with_bg(u16 x, u16 y, u8 ascii, u16 color,u16 bgcolor, u16 setcolor)
{
	u8 i, b, temp1, temp2;
	u16 tempX, tempY;
	if (ascii<32 || ascii>127) return;
	ascii -= 32;
	tempX= x;
	for (i=0; i<16; i=i+2)
	{
		temp1 = asc2_1608[ascii][i];
		temp2 = asc2_1608[ascii][i+1];
		tempY = y;
		for (b=0;b<8;b++)
		{
			if (temp1%2 == 1) lcd_drawDot(tempX, tempY+8, color);
			if (temp1%2 == 0) lcd_drawDot(tempX, tempY+8, setcolor);
			if (temp2%2 == 1) lcd_drawDot(tempX, tempY, color);
			if (temp2%2 == 0) lcd_drawDot(tempX, tempY, setcolor);
			temp1 = temp1 >> 1;
			temp2 = temp2 >> 1;
			tempY++;
		}
		tempX++;
	}
}
