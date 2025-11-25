#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include <stdio.h>
#include <cstring>
#include "weapon_setting.h"
#include "character_setting.h"
#include "action_set.h"
#include "level_setting.h"
#include "HP_setting.h"
#include "bullet_setting.h"
#include "randomness.h"
#include "keypad_setting.h"
#include "draw.h"
#include "Asset.h"
#include "IERG3810_Timer.h"
#include "IERG3810_LED.h"
#include "LCD_SETUP.h"

extern HPList hplist;
extern BulletList bulletlist;
extern u32 TASKS[10];
u8 player2_die_flag = 0;
u8 player1_die_flag = 0;

CHARACTER CREATE_CHARACTER_1()
{
	CHARACTER character;
	character.x = 196;
	character.y = RANDOM_RANGE(160, 290);
	character.label = 1;
	character.HP = INIT_BLOOD;
	character.facing = RIGHT;
	character.weapon = WEAPONS[WEAPON_VANDAL];
	character.jump_pixel_left = 7;
	character.level = level_ground[0];
	character.status = DROPING;
	return character;
}

CHARACTER CREATE_CHARACTER_2()
{
	CHARACTER character;
	character.x = 196;
	character.y = RANDOM_RANGE(30,159);
	character.label = 2;
	character.HP = INIT_BLOOD;
	character.facing = LEFT;
	character.weapon = WEAPONS[WEAPON_VANDAL];
	character.jump_pixel_left = 7;
	character.level = level_ground[0];
	character.status = DROPING;
	return character;
}	


void UPDATE_BULLET_STATUS(CHARACTER* character1, CHARACTER* character2)
{
	for(size_t i = bulletlist2.size; i > 0; i--)
	{
		CLEAR_BULLET(bulletlist2.bullets[i-1]);
		if(bulletlist2.bullets[i-1].facing == LEFT)
		{
			bulletlist2.bullets[i-1].y += SPEED;
		}
		else
		{
			bulletlist2.bullets[i-1].y -= SPEED;
		}
		if((bulletlist2.bullets[i-1].x <= character1->x + 10) && (bulletlist2.bullets[i-1].x >= character1->x - 10) && (bulletlist2.bullets[i-1].y >= character1->y - 10) && (bulletlist2.bullets[i-1].y <= character1->y + 10))
		{
			if(character1->HP <= character2->weapon.damage)
			{
				player1_die_flag = 1;
				character1->HP = 0;
			}
			else {character1->HP -= character2->weapon.damage;}
			//DRAW_HP_VALUE(*character1);
			DRAW_HP_VALUE(*character1);
			
			Bullet_list_remove_at(&bulletlist2, i-1);
		}
		if((bulletlist2.bullets[i-1].y >= 308) || (bulletlist2.bullets[i-1].y <= 2))
		{
			Bullet_list_remove_at(&bulletlist2, i-1);
		}
	}
	DRAW_BULLET2();
	for(size_t i = bulletlist1.size; i > 0; i--)
	{
		CLEAR_BULLET(bulletlist1.bullets[i-1]);
		if(bulletlist1.bullets[i-1].facing == LEFT)
		{
			bulletlist1.bullets[i-1].y += SPEED;
		}
		else
		{
			bulletlist1.bullets[i-1].y -= SPEED;
		}
		if((bulletlist1.bullets[i-1].x <= character2->x + 10) && (bulletlist1.bullets[i-1].x >= character2->x - 10) && (bulletlist1.bullets[i-1].y >= character2->y - 10) && (bulletlist1.bullets[i-1].y <= character2->y + 10))
		{
			if(character2->HP <= character1->weapon.damage)
			{
				player2_die_flag = 1;
				character2->HP = 0;
			}
			else {character2->HP -= character1->weapon.damage;}
			DRAW_HP_VALUE(*character2);
			Bullet_list_remove_at(&bulletlist1, i-1);
		}
		if((bulletlist1.bullets[i-1].y >= 308) || (bulletlist1.bullets[i-1].y <= 2))
		{
			Bullet_list_remove_at(&bulletlist1, i-1);
		}
	}
	DRAW_BULLET1();
}


void CHARACTER_MOVE_NEW(CHARACTER* character, int instruction)
{
	int moved = 0;
	if(character->status == DROPING)
	{
		DROP_DOWN_ONE_PIXEL(character);
		if(LANDING_CHECK(character) == 1)
		{
			character->status = STANDING;
		}
		moved = 1;
	}
	else if(character->status == JUMPING)
	{
		if(character->jump_pixel_left > 0)
		{
			JUMP_UP_ONE_PIXEL(character);
		}
		else
		{
			DROP_DOWN_ONE_PIXEL(character);
			character->status = DROPING;
			character->jump_pixel_left=7;
		}
		moved = 1;
	}
	else if(character->status == STANDING)
	{
		if (instruction == 1)
		{
			if(character->x > 20)
			{
				DROP_DOWN_ONE_PIXEL(character);
				character->status = DROPING;
				character->level = level_ground[0];
				moved = 1;
			}
		}
		if (instruction == 2)
		{
			character->jump_pixel_left = MAX_JUMP_HEIGHT;
			JUMP_UP_ONE_PIXEL(character);
			character->status = JUMPING;
			character->level = level_ground[0];
			moved = 1;
		}
	}
	if (instruction == 3)
	{
		MOVE_LEFT(character);
		moved = 1;
	}
	if (instruction == 4)
	{
		MOVE_RIGHT(character);
		moved = 1;
	}
	if (instruction == 5)
	{
		
		if(TASKS[5] == 1)
		{
			INIT_BULLET(character);
			TASKS[5] = character->weapon.fire_rate;
		}
	}
	if(moved == 1)
	{
		HP_PICKED(character);
	}
}


void CHARACTER_HEAL(CHARACTER* character)
{
	character->HP = ((character->HP+HP_RECOVERY) > (100) ? (100) : (character->HP+HP_RECOVERY));
	DRAW_HP_VALUE(*character);
}

void HP_PICKED(CHARACTER* character)
{
	for(size_t i = hplist.size; i > 0; i--)
	{
		if((character->x >= hplist.hps[i-1].x-15) && (character->x <= hplist.hps[i-1].x+15) && (character->y >= hplist.hps[i-1].y - 15) && (character->y <= hplist.hps[i-1].y + 15))
		{
			CHARACTER_HEAL(character);
			CLEAR_HP(hplist.hps[i-1]);
			HP_list_remove_at(&hplist, i-1);
			DRAW_CHARACTER(*character);
		}
	}	
}

void INIT_BULLET(CHARACTER* character)
{
	if(character->label == 1)
	{
		BULLET bullet;
		bullet.x = character->x;
		if(character->facing == LEFT)
		{
			bullet.y = character->y + 8;
		}
		else
		{
			bullet.y = character->y - 18;
		}
		bullet.facing = character->facing;
		bullet.rate = character->weapon.fire_rate;
		Bullet_list_push(&bulletlist1, bullet);
	}
	else
	{
		BULLET bullet;
		bullet.x = character->x;
		if(character->facing == LEFT)
		{
			bullet.y = character->y + 8;
		}
		else
		{
			bullet.y = character->y - 18;
		}
		bullet.facing = character->facing;
		bullet.rate = character->weapon.fire_rate;
		Bullet_list_push(&bulletlist2, bullet);
	}
}

