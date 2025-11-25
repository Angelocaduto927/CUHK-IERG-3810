#include <stm32f10x.h>
#include <stdlib.h>
#include <string.h>
#include "weapon_setting.h"
#include "character_setting.h"
#include "draw.h"
#include "Asset.h"
#include "LCD_SETUP.h"
#include "HP_setting.h"
#include "bullet_setting.h"

void DRAW_ARENA()
{
	Draw_ARENA();
}
void DRAW_CHARACTER(CHARACTER character)
{
	int weapon = 0;
	if (!strcmp(character.weapon.name, "Pistol"))
	{
		weapon = 0;
	}
	else if(!strcmp(character.weapon.name, "Vandal"))
	{
		weapon = 1;
	}
	else if(!strcmp(character.weapon.name, "Phantom"))
	{
		weapon = 2;
	}
	else if(!strcmp(character.weapon.name, "Odin"))
	{
		weapon = 3;
	}
	Draw_Character(character.y, character.x, character.label, character.facing, weapon);
}

void DRAW_HP_VALUE(CHARACTER character)
{
	if(character.label == 1)
	{
		Draw_HPValue1(character.HP);
	}
	if(character.label == 2)
	{
		Draw_HPValue2(character.HP);
	}
}

void DRAW_BULLET1()
{
	for(size_t i=0; i<bulletlist1.size;i++)
	{
		Draw_Bullet(bulletlist1.bullets[i].x, bulletlist1.bullets[i].y, c_BLUE);
	}
}
void DRAW_BULLET2()
{
	for(size_t i=0; i<bulletlist2.size;i++)
	{
		Draw_Bullet(bulletlist2.bullets[i].x, bulletlist2.bullets[i].y, c_RED);
	}
}

void DRAW_HP_LOOT(HP hp)
{
	Draw_HealPack(hp.x, hp.y);
}

void DRAW_TIMER(u16 time)
{
	u8 min = (time / 600);
	u8 sec = (time % 600) / 10;
	Draw_Countdown(min, sec);
}

void DRAW_BACKGROUND()
{
	lcd_fillRectangle(c_white, 0,240,0,320);
}

void CLEAR_CHARACTER(CHARACTER character)
{
	if(character.facing == -1){
		lcd_fillRectangle(c_white, character.x-6 , 25, character.y-8, 20);
	}
	if(character.facing == 1){
		lcd_fillRectangle(c_white, character.x-6 , 25, character.y-11, 20);
	}
}

void CLEAR_HP(HP hp)
{
	lcd_fillRectangle(c_white, hp.x-7 , 15, hp.y-8, 16);
}

void CLEAR_BULLET(BULLET bullet)
{
	lcd_fillRectangle(c_white, bullet.x , 2, bullet.y, 10);
}

void CLEAR_TIMER()
{
	lcd_fillRectangle(c_white, 224, 16, 144, 32);
}

void DRAW_FRONT_PAGE()
{
	lcd_fillRectangle(c_black, 0,240,0,320);
	Draw_front_page();
}

void DRAW_INFO_PAGE()
{
	lcd_fillRectangle(c_white, 0,240,0,320);
	Draw_info_page();
}

void DRAW_PLAYER1_WIN()
{
	Draw_player1_win();
}

void DRAW_PLAYER2_WIN()
{
	Draw_player2_win();
}

void DRAW_OVERTIME()
{
	Draw_overtime();
}

void DRAW_PAUSE()
{
	Draw_pause();
}

void CLEAR_PAUSE()
{
	lcd_fillRectangle(c_white, 175, 20, 120, 80);
}

void DRAW_START_PAGE()
{
	start_page();
}

void DRAW_END_PAGE(u8 label)
{
	end_page(label);
}

