#include <stm32f10x.h>
#include "weapon_setting.h"
#include "character_setting.h"
#include "action_set.h"
#include "level_setting.h"
#include "draw.h"

u8 LANDING_CHECK(CHARACTER* character)
{
	for(int i = 0; i < LEVEL_GROUND_COUNT; i++) {
		if ((character->x == level_ground[i].height + 6) && (character->y >= level_ground[i].start) && (character->y <= level_ground[i].end))
		{
			character->level = level_ground[i];	
			return 1;
		}
	}
	return 0;
}
void JUMP_UP_ONE_PIXEL(CHARACTER* character) 
{
	CLEAR_CHARACTER(*character);
	DRAW_ARENA();
	character->x += 10;
	character->jump_pixel_left--;
	DRAW_CHARACTER(*character);
}

void DROP_DOWN_ONE_PIXEL(CHARACTER* character)
{
	CLEAR_CHARACTER(*character);
	DRAW_ARENA();
	character->x -= 10;
	DRAW_CHARACTER(*character);
}

void MOVE_LEFT(CHARACTER* character)
{
	if(character->y >=300 && character->facing == RIGHT && character->y <= 308)
	{
		character->facing = LEFT;
		DRAW_CHARACTER(*character);
		return;
	}
	else if(character->y >= 300 && (character->facing == LEFT || character->y > 308))
	{
		return;
	}
	else{
		CLEAR_CHARACTER(*character);
		character->y+=15;
		character->facing = LEFT;
		if((character->y > character->level.end) && (character->status == STANDING))
		{
			character->status = DROPING;
			character->level = level_ground[0];
		}
		DRAW_CHARACTER(*character);
	}	
}

void MOVE_RIGHT(CHARACTER* character)
{
	if(character->y <=20 && character->facing == LEFT && character->y >= 12)
	{
		character->facing = LEFT;
		DRAW_CHARACTER(*character);
		return;
	}
	else if(character->y <= 20 && (character->facing == RIGHT || character->y < 12))
	{
		return;
	}
	else{
		CLEAR_CHARACTER(*character);
		character->y-=15;
		character->facing = RIGHT;
		if((character->y < character->level.start) && (character->status == STANDING))
		{
			character->status =DROPING;
			character->level = level_ground[0];
		}
		DRAW_CHARACTER(*character);
	}
}
