#include "stm32f10x.h"
#include "LCD_SETUP.h"
#include "IERG3810_Clock.h"
#include "FONT.h"
#include "CFONT.h"
#include "IERG3810_Delay.h"


const u8 Character1[25][20]=  //red 1 black 2  dark gray 3  gray 4 light gray 5
{
	{0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0},
	{0,0,0,0,0,2,2,4,4,2,2,2,2,2,2,4,0,0,0,0},
	{0,0,0,0,2,4,4,2,2,4,4,4,4,4,2,2,4,0,0,0},
	{0,0,2,2,4,4,2,2,4,4,4,4,4,4,4,4,2,2,0,0},
	{0,0,2,4,4,2,2,4,4,4,4,2,2,4,4,4,4,2,4,0},
	{0,2,2,2,2,4,4,4,2,4,4,2,2,4,4,2,4,4,2,4},
	{0,2,4,4,2,4,4,2,2,4,4,2,2,4,4,2,2,4,2,4},
	{0,2,4,4,2,4,4,2,2,4,4,2,2,4,4,2,2,4,2,4},
	{0,2,2,2,2,4,4,2,2,4,4,2,2,4,4,2,2,4,2,4},
	{0,2,4,2,2,4,4,2,2,4,4,2,2,4,4,2,2,4,2,4},
	{0,2,4,4,2,4,4,2,2,4,4,2,2,4,4,2,2,4,2,4},
	{0,2,2,4,2,2,4,4,2,4,4,2,2,4,4,2,4,2,2,0},
	{0,0,2,2,2,2,2,4,4,4,4,4,4,4,4,4,2,2,0,0},
	{0,0,3,3,3,4,2,2,2,2,2,2,2,2,2,2,3,3,3,0},
	{0,3,3,3,3,3,5,5,5,5,5,6,5,5,5,3,3,3,3,3},
	{0,3,3,3,3,3,2,2,2,5,5,5,5,2,2,2,3,3,3,3},
	{0,0,0,0,2,2,5,2,2,2,2,2,2,2,2,2,0,0,0,0},
	{0,0,0,0,2,2,5,5,5,5,5,5,5,5,5,2,0,0,0,0},
	{0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0},
	{0,0,0,0,0,3,3,3,0,0,0,0,3,3,3,0,0,0,0,0},
	{0,0,0,0,0,0,3,3,0,0,0,0,0,3,3,0,0,0,0,0},
};
const u8 Character2[25][20]=  //red 1 black 2  dark gray 3  gray 4 light gray 5
{
	{0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0},
	{0,0,0,0,0,2,2,2,4,4,4,4,2,2,2,2,0,0,0,0},
	{0,0,0,0,2,2,4,4,4,4,4,4,4,4,2,2,2,0,0,0},
	{0,0,2,2,2,4,4,4,4,4,4,4,4,4,4,2,2,2,0,0},
	{0,0,2,2,2,4,4,4,4,4,4,4,4,4,4,4,4,2,2,0},
	{0,2,2,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,2,2},
	{0,2,2,4,4,4,4,2,2,2,2,2,2,2,2,2,4,4,2,2},
	{0,2,2,4,4,4,2,2,2,2,2,2,2,2,2,2,2,4,2,2},
	{0,2,2,4,4,4,4,2,2,2,2,2,2,2,2,2,4,4,2,2},
	{0,2,2,4,4,4,4,4,4,4,4,2,2,2,4,4,4,4,2,2},
	{0,2,2,4,4,4,4,4,4,4,4,2,2,2,4,4,4,4,2,2},
	{0,0,2,2,2,2,4,4,4,4,4,2,2,2,4,4,4,2,2,0},
	{0,0,2,2,2,2,2,4,4,4,4,2,2,2,4,4,2,2,0,0},
	{0,0,3,3,3,4,2,2,2,2,2,2,2,2,2,2,3,3,3,0},
	{0,3,3,3,3,3,5,5,5,5,5,6,5,5,5,3,3,3,3,3},
	{0,3,3,3,3,3,2,2,2,5,5,5,5,2,2,2,3,3,3,3},
	{0,0,0,0,2,2,5,2,2,2,2,2,2,2,2,2,0,0,0,0},
	{0,0,0,0,2,2,5,5,5,5,5,5,5,5,5,2,0,0,0,0},
	{0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0},
	{0,0,0,0,0,3,3,3,0,0,0,0,3,3,3,0,0,0,0,0},
	{0,0,0,0,0,0,3,3,0,0,0,0,0,3,3,0,0,0,0,0},
};


const u8 weapon0[6][20]=     //pistol
{
{0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,},
{0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
};
const u8 weapon1[6][20]=     //vandal
{
{0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,},
{0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,},
{0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,},
{0,0,2,2,0,0,2,2,0,0,0,2,2,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,2,0,0,0,0,0,2,2,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,},
};

const u8 weapon2[6][20]=     //empty
{

{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
};

const u8 weapon3[6][20]=     //Odin
{

{0,5,5,0,5,5,5,5,5,5,5,5,5,5,5,5,0,0,0,0,},
{5,0,5,5,5,2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,},
{5,5,5,5,5,2,5,5,5,5,5,5,5,5,5,5,5,5,0,0,},
{0,0,0,5,5,2,5,5,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,},
};
void drawDotForChar(u8 color, u16 x, u16 y)   
{
	if(color == 1) lcd_drawDot(x, y, c_RED);
	if(color == 2) lcd_drawDot(x, y, c_black);
	if(color == 3) lcd_drawDot(x, y, c_DARK_GRAY);
	if(color == 4) lcd_drawDot(x, y, c_GRAY);
	if(color == 5) lcd_drawDot(x, y, c_LIGHT_GRAY);
	if(color == 6) lcd_drawDot(x, y, c_GREEN);
}

void lcd_showChar(u16 x, u16 y, u8 ascii, u16 color)
{
	u8 i, b, temp1, temp2;
	u16 tempX, tempY;
	if (ascii<32 || ascii >127) return;
	ascii -= 32;
	tempX = x;
	for (i=0; i<16; i=i+2)
	{
		temp1 = asc2_1608[ascii][i];
		temp2 = asc2_1608[ascii][i+1];
		tempY = y;
		for (b=0;b<9;b++)
		{
			if(temp1%2 == 1) lcd_drawDot(tempY+8, tempX, color);
			if(temp2%2 == 1) lcd_drawDot(tempY, tempX, color);
			temp1 = temp1 >>1;
			temp2 = temp2 >>1;
			tempY++;
		}
		tempX--;
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
			if (temp1%2 == 1) lcd_drawDot(tempY+8, tempX, color);
			if (temp2%2 == 1) lcd_drawDot(tempY, tempX, color);
			temp1 = temp1 >> 1;
			temp2 = temp2 >> 1;
			tempY++;
		}
		tempX--;
	}
}


void drawgun(u16 x, u16 y)
{
		u8 tempcolor,i,j;
		u16 coordx,coordy;
		for(i=0;i<6;i++)
			{
				for(j=0;j<20;j++)
				{
					tempcolor = weapon1[i][j];
					coordy = y + 2 - i; 
					coordx = x - (11 - j);
					drawDotForChar(tempcolor, coordy, coordx);
			}
		}
}



/////////////////////////////////////////Only use below function////////////////////////////////////////
void Draw_Character(u16 x, u16 y, u8 which, s8 d, u8 weapon) // d directtion can be 1 (right) or -1 (left)
{	
	u8 tempcolor,i,j;
	u16 coordx,coordy;
	if(which == 1)
	{
		for(i=0;i<25;i++)
		{
			for(j=0;j<20;j++)
			{
				tempcolor = Character1[i][j];
				coordy = y + 18 - i; 
				coordx = x - (11 - j)*d;// change direction
				drawDotForChar(tempcolor, coordy, coordx);
			}
		}
	}
	else
	{
		for(i=0;i<25;i++)
		{
			for(j=0;j<20;j++)
			{
				tempcolor = Character2[i][j];
				coordy = y + 18 - i; 
				coordx = x - (11 - j)*d;// change direction
				drawDotForChar(tempcolor, coordy, coordx);
			}
		}
	}
	//draw weapon/////////////////////////////////////////////
	if(weapon==0)
	{
	for(i=0;i<6;i++)
		{
			for(j=0;j<20;j++)
			{
				tempcolor = weapon0[i][j];
				coordy = y + 2 - i; 
				coordx = x - (11 - j)*d;// change direction
				drawDotForChar(tempcolor, coordy, coordx);
			}
		}
	}
	else if(weapon==1)
	{
		for(i=0;i<6;i++)
			{
				for(j=0;j<20;j++)
				{
					tempcolor = weapon1[i][j];
					coordy = y + 2 - i; 
					coordx = x - (11 - j)*d;// change direction
					drawDotForChar(tempcolor, coordy, coordx);
			}
		}
	}
	else if(weapon==2)
	{
		for(i=0;i<6;i++)
			{
				for(j=0;j<20;j++)
				{
					tempcolor = weapon2[i][j];
					coordy = y + 2 - i; 
					coordx = x - (11 - j)*d;// change direction
					drawDotForChar(tempcolor, coordy, coordx);
			}
		}
	}
	else if(weapon==3)
	{
		for(i=0;i<6;i++)
			{
				for(j=0;j<20;j++)
				{
					tempcolor = weapon3[i][j];
					coordy = y + 2 - i; 
					coordx = x - (11 - j)*d;// change direction
					drawDotForChar(tempcolor, coordy, coordx);
			}
		}
	}
}
void Draw_ARENA(void)
{
	lcd_fillRectangle(c_black,0,10,0,320); //level 1
	
	lcd_fillRectangle(c_black,50,10,0,120); //level 2
	lcd_fillRectangle(c_black,50,10,200,120);
	
	lcd_fillRectangle(c_black,100,10,80,160); //level 3
	
}

void Draw_HPValue1(u8 HP_value1)
{
	lcd_fillRectangle(c_black,223,14,213,104);
	if(HP_value1 > 0)
	{
		lcd_fillRectangle(c_GREEN,225,10,315-HP_value1,HP_value1);
	}
}

void Draw_HPValue2(u8 HP_value2)
{
	lcd_fillRectangle(c_black,223,14,3,104);
	if(HP_value2 > 0)
	{	
		lcd_fillRectangle(c_GREEN,225,10,5,HP_value2);
	}
}


void Draw_Countdown(u8 min, u8 sec)
{
	u8 sec1,sec2;
	sec2 = sec%10;
	sec1 = sec/10; 
	lcd_showChar(176, 224, 0x30+min, c_black);
	lcd_showChar(168, 224, 0x3A, c_black);
	lcd_showChar(160, 224, 0x30+sec1, c_black);
	lcd_showChar(152, 224, 0x30+sec2, c_black);
}

void Draw_HealPack(u16 x, u16 y)
{
	lcd_fillRectangle(c_LIGHT_GRAY, x-7, 15, y-8, 16);
	//lcd_showChar(x-3, y+4, 0x48, c_YELLOW);
	lcd_showChar(y+3, x-7, 0x48, c_YELLOW);
}


void Draw_Bullet(u16 x, u16 y, u16 color)
{
	lcd_fillRectangle(color, x, 2, y, 10);
}

void Draw_front_page()
{
	lcd_showChar(128, 210, 109, c_YELLOW);
	lcd_showChar(136, 210, 101, c_YELLOW);
	lcd_showChar(144, 210, 104, c_YELLOW);
	lcd_showChar(152, 210, 121, c_YELLOW);
	lcd_showChar(160, 210, 97, c_YELLOW);
	lcd_showChar(168, 210, 77, c_YELLOW);
	lcd_showChar(176, 210, 32, c_YELLOW);
	lcd_showChar(184, 210, 110, c_YELLOW);
	lcd_showChar(192, 210, 117, c_YELLOW);
	lcd_showChar(200, 210, 71, c_YELLOW);
	
	lcd_showChar(120, 190, 115, c_YELLOW);
	lcd_showChar(128, 190, 114, c_YELLOW);
	lcd_showChar(136, 190, 111, c_YELLOW);
	lcd_showChar(144, 190, 116, c_YELLOW);
	lcd_showChar(152, 190, 117, c_YELLOW);
	lcd_showChar(160, 190, 98, c_YELLOW);
	lcd_showChar(168, 190, 105, c_YELLOW);
	lcd_showChar(176, 190, 114, c_YELLOW);
	lcd_showChar(184, 190, 116, c_YELLOW);
	lcd_showChar(192, 190, 110, c_YELLOW);
	lcd_showChar(200, 190, 111, c_YELLOW);
	lcd_showChar(208, 190, 67, c_YELLOW);
	
	lcd_showChar(104, 170, 56, c_YELLOW);
	lcd_showChar(112, 170, 57, c_YELLOW);
	lcd_showChar(120, 170, 48, c_YELLOW);
	lcd_showChar(128, 170, 53, c_YELLOW);
	lcd_showChar(136, 170, 49, c_YELLOW);
	lcd_showChar(144, 170, 50, c_YELLOW);
	lcd_showChar(152, 170, 53, c_YELLOW);
	lcd_showChar(160, 170, 53, c_YELLOW);
	lcd_showChar(168, 170, 49, c_YELLOW);
	lcd_showChar(176, 170, 49, c_YELLOW);
	lcd_showChinChar(192, 170, 5, c_YELLOW);
	lcd_showChinChar(208, 170, 4, c_YELLOW);
	lcd_showChinChar(224, 170, 3, c_YELLOW);
	
	
	lcd_showChar(104, 150, 51, c_YELLOW);
	lcd_showChar(112, 150, 49, c_YELLOW);
	lcd_showChar(120, 150, 49, c_YELLOW);
	lcd_showChar(128, 150, 53, c_YELLOW);
	lcd_showChar(136, 150, 49, c_YELLOW);
	lcd_showChar(144, 150, 50, c_YELLOW);
	lcd_showChar(152, 150, 53, c_YELLOW);
	lcd_showChar(160, 150, 53, c_YELLOW);
	lcd_showChar(168, 150, 49, c_YELLOW);
	lcd_showChar(176, 150, 49, c_YELLOW);
	lcd_showChinChar(192, 150, 2, c_YELLOW);
	lcd_showChinChar(208, 150, 1, c_YELLOW);
	lcd_showChinChar(224, 150, 0, c_YELLOW);
	
	lcd_fillRectangle(c_YELLOW, 90, 5, 90, 135);
	lcd_fillRectangle(c_YELLOW, 145, 5, 90, 135);
	lcd_fillRectangle(c_YELLOW, 90, 60, 90, 5);
	lcd_fillRectangle(c_YELLOW, 90, 60, 225, 5);
	
	lcd_showChar(128, 123, 101, c_YELLOW);
	lcd_showChar(136, 123, 109, c_YELLOW);
	lcd_showChar(144, 123, 97, c_YELLOW);
	lcd_showChar(152, 123, 71, c_YELLOW);
	lcd_showChar(160, 123, 32, c_YELLOW);
	lcd_showChar(168, 123, 116, c_YELLOW);
	lcd_showChar(176, 123, 114, c_YELLOW);
	lcd_showChar(184, 123, 97, c_YELLOW);
	lcd_showChar(192, 123, 116, c_YELLOW);
	lcd_showChar(200, 123, 83, c_YELLOW);
	
	lcd_showChar(128, 103, 50, c_YELLOW);
	lcd_showChar(136, 103, 121, c_YELLOW);
	lcd_showChar(144, 103, 101, c_YELLOW);
	lcd_showChar(152, 103, 107, c_YELLOW);
	lcd_showChar(160, 103, 32, c_YELLOW);
	lcd_showChar(168, 103, 115, c_YELLOW);
	lcd_showChar(176, 103, 115, c_YELLOW);
	lcd_showChar(184, 103, 101, c_YELLOW);
	lcd_showChar(192, 103, 114, c_YELLOW);
	lcd_showChar(200, 103, 80, c_YELLOW);
	
	lcd_fillRectangle(c_YELLOW, 20, 5, 90, 135);
	lcd_fillRectangle(c_YELLOW, 75, 5, 90, 135);
	lcd_fillRectangle(c_YELLOW, 20, 60, 90, 5);
	lcd_fillRectangle(c_YELLOW, 20, 60, 225, 5);
	
	lcd_showChar(128, 52, 101, c_YELLOW);
	lcd_showChar(136, 52, 103, c_YELLOW);
	lcd_showChar(144, 52, 97, c_YELLOW);
	lcd_showChar(152, 52, 80, c_YELLOW);
	lcd_showChar(160, 52, 32, c_YELLOW);
	lcd_showChar(168, 52, 32, c_YELLOW);
	lcd_showChar(176, 52, 111, c_YELLOW);
	lcd_showChar(184, 52, 102, c_YELLOW);
	lcd_showChar(192, 52, 110, c_YELLOW);
	lcd_showChar(200, 52, 73, c_YELLOW);
	

	lcd_showChar(128, 32, 49, c_YELLOW);
	lcd_showChar(136, 32, 121, c_YELLOW);
	lcd_showChar(144, 32, 101, c_YELLOW);
	lcd_showChar(152, 32, 107, c_YELLOW);
	lcd_showChar(160, 32, 32, c_YELLOW);
	lcd_showChar(168, 32, 115, c_YELLOW);
	lcd_showChar(176, 32, 115, c_YELLOW);
	lcd_showChar(184, 32, 101, c_YELLOW);
	lcd_showChar(192, 32, 114, c_YELLOW);
	lcd_showChar(200, 32, 80, c_YELLOW);
}

void Draw_info_page()
{
	///title:Info Page
	lcd_showChar(196, 224, 73, c_black);
	lcd_showChar(188, 224, 110, c_black);
	lcd_showChar(180, 224, 102, c_black);
	lcd_showChar(172, 224, 111, c_black);
	lcd_showChar(164, 224, 32, c_black);
	lcd_showChar(156, 224, 80, c_black);
	lcd_showChar(148, 224, 97, c_black);
	lcd_showChar(140, 224, 103, c_black);
	lcd_showChar(132, 224, 101, c_black);
	//Player1:
	lcd_showChar(312, 199, 80, c_black);
	lcd_showChar(304, 199, 108, c_black);
	lcd_showChar(296, 199, 97, c_black);
	lcd_showChar(288, 199, 121, c_black);
	lcd_showChar(280, 199, 101, c_black);
	lcd_showChar(272, 199, 114, c_black);
	lcd_showChar(264, 199, 49, c_black);
	lcd_showChar(256, 199, 58, c_black);
	Draw_Character(238, 199, 1, 1, 2);
	
	//Player2:
	lcd_showChar(210, 199, 80, c_black);
	lcd_showChar(202, 199, 108, c_black);
	lcd_showChar(194, 199, 97, c_black);
	lcd_showChar(186, 199, 121, c_black);
	lcd_showChar(178, 199, 101, c_black);
	lcd_showChar(170, 199, 114, c_black);
	lcd_showChar(162, 199, 50, c_black);
	lcd_showChar(154, 199, 58, c_black);
	Draw_Character(136, 199, 2, 1, 2);
	
	//weapon:
	lcd_showChar(312, 167, 87, c_black);
	lcd_showChar(304, 167, 101, c_black);
	lcd_showChar(296, 167, 97, c_black);
	lcd_showChar(288, 167, 112, c_black);
	lcd_showChar(280, 167, 111, c_black);
	lcd_showChar(272, 167, 110, c_black);
	lcd_showChar(264, 167, 58, c_black);
	drawgun(246, 171);
	
	//HP: 100
	lcd_showChar(108, 199, 72, c_black);
	lcd_showChar(100, 199, 80, c_black);
	lcd_showChar(92, 199, 58, c_black);
	lcd_showChar(84, 199, 49, c_black);
	lcd_showChar(76, 199, 48, c_black);
	lcd_showChar(68, 199, 48, c_black);
	//Damage: 10
	
	lcd_showChar(218, 167, 68, c_black);
	lcd_showChar(210, 167, 97, c_black);
	lcd_showChar(202, 167, 109, c_black);
	lcd_showChar(194, 167, 97, c_black);
	lcd_showChar(186, 167, 103, c_black);
	lcd_showChar(178, 167, 101, c_black);
	lcd_showChar(170, 167, 58, c_black);
	lcd_showChar(162, 167, 49, c_black);
	lcd_showChar(154, 167, 48, c_black);
	//fire rate: 1 bullet/sec
	lcd_showChar(138, 167, 70, c_black);
	lcd_showChar(130, 167, 105, c_black);
	lcd_showChar(122, 167, 114, c_black);
	lcd_showChar(114, 167, 101, c_black);
	lcd_showChar(98, 167, 114, c_black);
	lcd_showChar(90, 167, 97, c_black);
	lcd_showChar(82, 167, 116, c_black);
	lcd_showChar(74, 167, 101, c_black);
	lcd_showChar(66, 167, 58, c_black);
	lcd_showChar(58, 167, 49, c_black);
	lcd_showChar(50, 167, 47, c_black);
	lcd_showChar(42, 167, 115, c_black);
	lcd_showChar(34, 167, 101, c_black);
	lcd_showChar(26, 167, 99, c_black);
	
	//Healpack will appear randomly every 30sec 
	lcd_showChar(312, 135, 72, c_black);
	lcd_showChar(304, 135, 101, c_black);
	lcd_showChar(296, 135, 97, c_black);
	lcd_showChar(288, 135, 108, c_black);
	lcd_showChar(280, 135, 112, c_black);
	lcd_showChar(272, 135, 97, c_black);
	lcd_showChar(264, 135, 99, c_black);
	lcd_showChar(256, 135, 107, c_black);
	
	lcd_showChar(248, 135, 40, c_black);
	Draw_HealPack(143,229);
	lcd_showChar(216, 135, 41, c_black);
	
	lcd_showChar(200, 135, 119, c_black); //will
	lcd_showChar(192, 135, 105, c_black);
	lcd_showChar(184, 135, 108, c_black);
	lcd_showChar(176, 135, 108, c_black);
	
	lcd_showChar(160, 135, 97, c_black); //appear
	lcd_showChar(152, 135, 112, c_black);
	lcd_showChar(144, 135, 112, c_black);
	lcd_showChar(136, 135, 101, c_black);
	lcd_showChar(128, 135, 97, c_black);
	lcd_showChar(120, 135, 114, c_black);
	
	lcd_showChar(104, 135, 114, c_black); //randomly
	lcd_showChar(96, 135, 97, c_black);
	lcd_showChar(88, 135, 110, c_black);
	lcd_showChar(80, 135, 100, c_black);
	lcd_showChar(72, 135, 111, c_black);
	lcd_showChar(64, 135, 109, c_black);
	lcd_showChar(56, 135, 108, c_black);
	lcd_showChar(48, 135, 121, c_black);
	
	lcd_showChar(312, 119, 101, c_black);
	lcd_showChar(304, 119, 118, c_black);
	lcd_showChar(296, 119, 101, c_black);
	lcd_showChar(288, 119, 114, c_black);
	lcd_showChar(280, 119, 121, c_black);
		
	lcd_showChar(264, 119, 51, c_black);
	lcd_showChar(256, 119, 48, c_black);
	lcd_showChar(248, 119, 115, c_black);
	lcd_showChar(240, 119, 101, c_black);
	lcd_showChar(232, 119, 99, c_black);
	lcd_showChar(224, 119, 46, c_black);
	
	lcd_showChar(208, 119, 67, c_black); //Collect
	lcd_showChar(200, 119, 111, c_black);
	lcd_showChar(192, 119, 108, c_black);
	lcd_showChar(184, 119, 108, c_black);
	lcd_showChar(176, 119, 101, c_black);
	lcd_showChar(168, 119, 99, c_black);
	lcd_showChar(160, 119, 116, c_black);
	
	lcd_showChar(144, 119, 116, c_black);//to
	lcd_showChar(136, 119, 111, c_black);
	
	lcd_showChar(120, 119, 114, c_black);
	lcd_showChar(112, 119, 101, c_black); //recover
	lcd_showChar(104, 119, 99, c_black);
	lcd_showChar(96, 119, 111, c_black);
	lcd_showChar(88, 119, 118, c_black);
	lcd_showChar(80, 119, 101, c_black);
	lcd_showChar(72, 119, 114, c_black);
	
	lcd_showChar(56, 119, 49, c_black);
	lcd_showChar(48, 119, 48, c_black);//10 HP
	lcd_showChar(32, 119, 72, c_black);
	lcd_showChar(24, 119, 80, c_black);
	lcd_showChar(16, 119, 46, c_black);
	//Collect healpack will recover 10 HP
	//Movement: left(kp4), right(),jump(),down(),shoot()
	lcd_showChar(312, 87, 77, c_black);
	lcd_showChar(304, 87, 111, c_black);//Movement:
	lcd_showChar(296, 87, 118, c_black);
	lcd_showChar(288, 87, 101, c_black);
	lcd_showChar(280, 87, 109, c_black);
	lcd_showChar(272, 87, 101, c_black);
	lcd_showChar(264, 87, 110, c_black);
	lcd_showChar(256, 87, 116, c_black);
	lcd_showChar(248, 87, 58, c_black);
	
	lcd_showChar(232, 87, 108, c_black);
	lcd_showChar(224, 87, 101, c_black); //left(kp4)
	lcd_showChar(216, 87, 102, c_black);
	lcd_showChar(208, 87, 116, c_black);
	lcd_showChar(200, 87, 40, c_black);
	lcd_showChar(192, 87, 107, c_black);
	lcd_showChar(184, 87, 112, c_black);
	lcd_showChar(176, 87, 52, c_black);
	lcd_showChar(168, 87, 41, c_black);
	lcd_showChar(160, 87, 44, c_black);
	
	lcd_showChar(144, 87, 114, c_black);
	lcd_showChar(136, 87, 105, c_black); //right(kp6)
	lcd_showChar(128, 87, 103, c_black);
	lcd_showChar(120, 87, 104, c_black);
	lcd_showChar(112, 87, 116, c_black);
	lcd_showChar(104, 87, 40, c_black);
	lcd_showChar(96, 87, 107, c_black);
	lcd_showChar(88, 87, 112, c_black);
	lcd_showChar(80, 87, 54, c_black);
	lcd_showChar(72, 87, 41, c_black);
	lcd_showChar(64, 87, 44, c_black);
	
	lcd_showChar(312, 71, 106, c_black);
	lcd_showChar(304, 71, 117, c_black);
	lcd_showChar(296, 71, 109, c_black);
	lcd_showChar(288, 71, 112, c_black);//jump(kp8)
	lcd_showChar(280, 71, 40, c_black);
	lcd_showChar(272, 71, 107, c_black);
	lcd_showChar(264, 71, 112, c_black);
	lcd_showChar(256, 71, 56, c_black);
	lcd_showChar(248, 71, 41, c_black);
	lcd_showChar(240, 71, 44, c_black);
	
	lcd_showChar(224, 71, 100, c_black);
	lcd_showChar(216, 71, 111, c_black);
	lcd_showChar(208, 71, 119, c_black);//down(kp2)
	lcd_showChar(200, 71, 110, c_black);
	lcd_showChar(192, 71, 40, c_black);
	lcd_showChar(184, 71, 107, c_black);
	lcd_showChar(176, 71, 112, c_black);
	lcd_showChar(168, 71, 50, c_black);
	lcd_showChar(160, 71, 41, c_black);
	lcd_showChar(152, 71, 44, c_black);
	
	lcd_showChar(136, 71, 115, c_black);
	lcd_showChar(128, 71, 104, c_black);
	lcd_showChar(120, 71, 111, c_black);
	lcd_showChar(112, 71, 111, c_black);//shoot(kp9)
	lcd_showChar(104, 71, 116, c_black);
	lcd_showChar(96, 71, 40, c_black);
	lcd_showChar(88, 71, 107, c_black);
	lcd_showChar(80, 71, 112, c_black);
	lcd_showChar(72, 71, 57, c_black);
	lcd_showChar(64, 71, 41, c_black);
	lcd_showChar(56, 71, 46, c_black);
	
	///PRESS KEYUP/KEY2/KEY1
	
	lcd_fillRectangle(c_black, 5, 5, 215, 100);
	lcd_fillRectangle(c_black, 58, 5, 215, 100);
	lcd_fillRectangle(c_black, 10, 52, 310, 5);
	lcd_fillRectangle(c_black, 5, 55, 215, 5);
	lcd_showChar(233, 37, 101, c_black);
	lcd_showChar(241, 37, 103, c_black);
	lcd_showChar(249, 37, 97, c_black);
	lcd_showChar(257, 37, 80, c_black);
	lcd_showChar(265, 37, 32, c_black);
	lcd_showChar(273, 37, 116, c_black);
	lcd_showChar(281, 37, 110, c_black);
	lcd_showChar(289, 37, 111, c_black);
	lcd_showChar(297, 37, 114, c_black);
	lcd_showChar(305, 37, 70, c_black);
	

	lcd_showChar(233, 17, 49, c_black);
	lcd_showChar(241, 17, 121, c_black);
	lcd_showChar(249, 17, 101, c_black);
	lcd_showChar(257, 17, 107, c_black);
	lcd_showChar(265, 17, 32, c_black);
	lcd_showChar(273, 17, 115, c_black);
	lcd_showChar(281, 17, 115,c_black);
	lcd_showChar(289, 17, 101, c_black);
	lcd_showChar(297, 17, 114, c_black);
	lcd_showChar(305, 17, 80, c_black);
	
	/*lcd_fillRectangle(c_black, 5, 5, 5, 100);
	lcd_fillRectangle(c_black, 58, 5, 5, 100);
	lcd_fillRectangle(c_black, 10, 52, 100, 5);
	lcd_fillRectangle(c_black, 5, 55, 5, 5);
	lcd_showChar(23, 37, 101, c_black);
	lcd_showChar(31, 37, 103, c_black);
	lcd_showChar(39, 37, 97, c_black);
	lcd_showChar(47, 37, 80, c_black);
	lcd_showChar(55, 37, 32, c_black);
	lcd_showChar(63, 37, 32, c_black);
	lcd_showChar(71, 37, 111, c_black);
	lcd_showChar(79, 37, 102, c_black);
	lcd_showChar(87, 37, 110, c_black);
	lcd_showChar(95, 37, 73, c_black);
	

	lcd_showChar(23, 17, 49, c_black);
	lcd_showChar(31, 17, 121, c_black);
	lcd_showChar(39, 17, 101, c_black);
	lcd_showChar(47, 17, 107, c_black);
	lcd_showChar(55, 17, 32, c_black);
	lcd_showChar(63, 17, 115, c_black);
	lcd_showChar(71, 17, 115,c_black);
	lcd_showChar(79, 17, 101, c_black);
	lcd_showChar(87, 17, 114, c_black);
	lcd_showChar(95, 17, 80, c_black);
	*/
}

void Draw_player1_win()
{
	lcd_showChar(96, 180, 33, c_black);
	lcd_showChar(104, 180, 115, c_black);
	lcd_showChar(112, 180, 110, c_black);
	lcd_showChar(120, 180, 111, c_black);
	lcd_showChar(128, 180, 105, c_black);
	lcd_showChar(136, 180, 116, c_black);
	lcd_showChar(144, 180, 97, c_black);
	lcd_showChar(152, 180, 108, c_black);
	lcd_showChar(160, 180, 117, c_black);
	lcd_showChar(168, 180, 116, c_black);
	lcd_showChar(176, 180, 97, c_black);
	lcd_showChar(184, 180, 114, c_black);
	lcd_showChar(192, 180, 103, c_black);
	lcd_showChar(200, 180, 110, c_black);
	lcd_showChar(208, 180, 111, c_black);
	lcd_showChar(216, 180, 67, c_black);
	lcd_showChar(112, 160, 33, c_black);
	lcd_showChar(120, 160, 110, c_black);
	lcd_showChar(128, 160, 105, c_black);
	lcd_showChar(136, 160, 87, c_black);
	lcd_showChar(144, 160, 32, c_black);
	lcd_showChar(152, 160, 49, c_black);
	lcd_showChar(160, 160, 114, c_black);
	lcd_showChar(168, 160, 101, c_black);
	lcd_showChar(176, 160, 121, c_black);
	lcd_showChar(184, 160, 97, c_black);
	lcd_showChar(192, 160, 108, c_black);
	lcd_showChar(200, 160, 80, c_black);
}

void Draw_player2_win()
{
	lcd_showChar(96, 180, 33, c_black);
	lcd_showChar(104, 180, 115, c_black);
	lcd_showChar(112, 180, 110, c_black);
	lcd_showChar(120, 180, 111, c_black);
	lcd_showChar(128, 180, 105, c_black);
	lcd_showChar(136, 180, 116, c_black);
	lcd_showChar(144, 180, 97, c_black);
	lcd_showChar(152, 180, 108, c_black);
	lcd_showChar(160, 180, 117, c_black);
	lcd_showChar(168, 180, 116, c_black);
	lcd_showChar(176, 180, 97, c_black);
	lcd_showChar(184, 180, 114, c_black);
	lcd_showChar(192, 180, 103, c_black);
	lcd_showChar(200, 180, 110, c_black);
	lcd_showChar(208, 180, 111, c_black);
	lcd_showChar(216, 180, 67, c_black);
	lcd_showChar(112, 160, 33, c_black);
	lcd_showChar(120, 160, 110, c_black);
	lcd_showChar(128, 160, 105, c_black);
	lcd_showChar(136, 160, 87, c_black);
	lcd_showChar(144, 160, 32, c_black);
	lcd_showChar(152, 160, 50, c_black);
	lcd_showChar(160, 160, 114, c_black);
	lcd_showChar(168, 160, 101, c_black);
	lcd_showChar(176, 160, 121, c_black);
	lcd_showChar(184, 160, 97, c_black);
	lcd_showChar(192, 160, 108, c_black);
	lcd_showChar(200, 160, 80, c_black);
}

void Draw_overtime(void)
{
	lcd_showChar(124, 180, 33, c_black);
	lcd_showChar(132, 180, 101, c_black);
	lcd_showChar(140, 180, 109, c_black);
	lcd_showChar(148, 180, 105, c_black);
	lcd_showChar(156, 180, 116, c_black);
	lcd_showChar(164, 180, 114, c_black);
	lcd_showChar(172, 180, 101, c_black);
	lcd_showChar(180, 180, 118, c_black);
	lcd_showChar(188, 180, 79, c_black);
	delay(10000000);
	lcd_fillRectangle(c_white, 175, 20, 120, 80);
}




///remember to replace delay with systick
/*int main(void)
{
	delay(1000000);
	lcd_init();
	delay(1000000);
	lcd_fillRectangle(c_SADDLE_BROWN,0,240,0,320);
	Draw_ARENA();
	Draw_Character(11,16,1,1);
	Draw_Character(308,16,2,-1);
	Draw_HPValue(39,88);

  Draw_Countdown(3,12);
	while(1);

}*/


