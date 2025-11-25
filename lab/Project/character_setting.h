#pragma once
#include "stm32f10x.h"
#include "level_setting.h"
#include "weapon_setting.h"

#define INIT_BLOOD 100
#define LEFT 1
#define RIGHT -1
#define HP_RECOVERY 10
#define JUMPING 1
#define DROPING 2
#define STANDING 0
#define MAX_JUMP_HEIGHT 7
extern u8 player1_die_flag;
extern u8 player2_die_flag;

typedef struct{
	int x;
	int y;
	int label;
	int jump_pixel_left;
	int HP;
	int facing;
	int status;
	LEVEL_BLOCK level;
	WEAPON weapon;
} CHARACTER;

CHARACTER CREATE_CHARACTER_1(void);
CHARACTER CREATE_CHARACTER_2(void);
void CHARACTER_MOVE(CHARACTER* character);
void CHARACTER_MOVE_NEW(CHARACTER* character, int instruction);
void CHARACTER_HEAL(CHARACTER* character);
void CHARACTER_SHOT_FIRE(CHARACTER* character);
void INIT_BULLET(CHARACTER* character);
void HP_PICKED(CHARACTER* character);
void UPDATE_BULLET_STATUS(CHARACTER* character1, CHARACTER* character2);
