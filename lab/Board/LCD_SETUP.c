#include "stm32f10x.h"
#include "LCD_SETUP.h"
#include "IERG3810_Clock.h"
#include "IERG3810_Delay.h"

extern u32 TASKS[10];

///remember to replace delay with systick
typedef struct
{
	u16 LCD_REG;
	u16 LCD_RAM;
} 	LCD_TypeDef;




void lcd_backlight_init(void)
{
	RCC ->APB2ENR |= 1 << 3;
	GPIOB->CRL &= 0xFFFFFFF0; 
	GPIOB->CRL |= 0x00000003;
}

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
	lcd_wr_reg(0x01);
	lcd_wr_reg(0x11);
	lcd_wr_reg(0x3A);
	lcd_wr_data(0x55);
	lcd_wr_reg(0x29);
	lcd_wr_reg(0x36);
	lcd_wr_data(0xC8);
}


void lcd_init(void)  //set FSMC
{
	RCC->AHBENR|=1<<8;  //FSMC
	RCC->APB2ENR|=1<<3;  //PortB
	RCC->APB2ENR|=1<<5;  //PortD
	RCC->APB2ENR|=1<<6;  //PortE
	RCC->APB2ENR|=1<<8;  //PortG
	GPIOB->CRL&=0xFFFFFFF0;  //PB0
	GPIOB->CRL|=0x00000003;
	//PortD
	GPIOD->CRH&=0x00FFF000;
	GPIOD->CRH|=0xBB000BBB;
	GPIOD->CRL&=0xFF00FF00;
	GPIOD->CRL|=0x00BB00BB;
	//PortE
	GPIOE->CRH&=0x00000000;
	GPIOE->CRH|=0xBBBBBBBB;
	GPIOE->CRL&=0x0FFFFFFF;
	GPIOE->CRL|=0xB0000000;
	//PortG12
	GPIOG->CRH&=0xFFF0FFFF;
	GPIOG->CRH|=0x000B0000;
	GPIOG->CRL&=0xFFFFFFF0; //PG0->RS
	GPIOG->CRL|=0x0000000B;


	//LCD uses FSMC Bank 4 memory bank.
	// Use mode A
	FSMC_Bank1->BTCR[6]=0x00000000; //FSMC_BCR4 (reset)
	FSMC_Bank1->BTCR[7]=0x00000000;  //FSMC_BTR4 (reset)
	FSMC_Bank1E->BWTR[6]=0x00000000; //FSMC_BWTR4 (reset)
	FSMC_Bank1->BTCR[6]|=1<<12;	 //FSMC_BCR4->WREN write enable  p541
	FSMC_Bank1->BTCR[6]|=1<<14;  //FSMC_BCR4->EXTMOD
	FSMC_Bank1->BTCR[6]|=1<<4;   //FSMC_BCR4->MWID  16bits
	FSMC_Bank1->BTCR[7]|=0<<28;  //FSMC_BTR4->ACCMOD modeA  p544
	FSMC_Bank1->BTCR[7]|=1<<0;   //FSMC_BTR4->ADDSET 2xHCLK clock cycles
	FSMC_Bank1->BTCR[7]|=0xF<<8; //FSMC_BTR4->DATAST 8xHCLK clock cycles
	FSMC_Bank1E->BWTR[6]|=0<<28; //FSMC_BWTR4->ACCMOD modeA  p547
	FSMC_Bank1E->BWTR[6]|=0<<0;  //FSMC_BWTR4->ADDSET 1xHCLK clock cycles
	FSMC_Bank1E->BWTR[6]|=3<<8;  //FSMC_BWTR4->DATAST 4xHCLK clock cycles
	FSMC_Bank1->BTCR[6]|=1<<0;   //FSMC_BCR4->MBKEN memory bank enable
	 
	lcd_9341_setParameter();
	
	lcd_backlight_init();
	LCD_LIGHT_ON;
}

void lcd_drawDot(u16 x, u16 y, u16 color)
{
lcd_wr_reg(0x2A); //set x position
	lcd_wr_data(x>>8);
	lcd_wr_data(x & 0xFF);
	lcd_wr_data(0x01);
	lcd_wr_data(0x3F);
lcd_wr_reg(0x2B); // set y position
	lcd_wr_data(y>>8);
	lcd_wr_data(y & 0xFF);
	lcd_wr_data(0x01);
	lcd_wr_data(0xDF);
lcd_wr_reg(0x2C); //set point with color
lcd_wr_data(color);
}


void lcd_fillRectangle(u16 color, u16 start_x,
  u16 length_x, u16 start_y, u16 length_y)
{
	u32 index=0;
	lcd_wr_reg(0x2A);
		lcd_wr_data(start_x>>8);
		lcd_wr_data(start_x & 0xFF);
		lcd_wr_data((length_x + start_x - 1)>>8);
		lcd_wr_data((length_x + start_x - 1) & 0xFF);
	lcd_wr_reg(0x2B);
		lcd_wr_data(start_y>>8);
		lcd_wr_data(start_y & 0xFF);
		lcd_wr_data((length_y + start_y - 1)>>8);
		lcd_wr_data((length_y + start_y - 1) & 0xFF);
	lcd_wr_reg(0x2C); //LCD_WeiteRAM_Prepare();
	delay(100); // systick
	for(index=0;index<length_x *length_y; index++)
	{
		lcd_wr_data(color);
	}
}

