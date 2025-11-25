#pragma once
#include <stm32f10x.h>
#include "HP_setting.h"
#include "bullet_setting.h"
#include "character_setting.h"
#include "weapon_setting.h"

void DRAW_ARENA(void);
void DRAW_CHARACTER(CHARACTER character);
void DRAW_HP_VALUE(CHARACTER character);
void DRAW_BULLET1(void);
void DRAW_BULLET2(void);
void DRAW_WEAPON_LOOT(WEAPON weapon);
void DRAW_HP_LOOT(HP hp);
void DRAW_TIMER(u16 time);
void DRAW_BACKGROUND(void);
void CLEAR_CHARACTER(CHARACTER character);
void CLEAR_WEAPON(WEAPON weapon);
void CLEAR_HP(HP hp);
void CLEAR_BULLET(BULLET bullet);
void CLEAR_TIMER(void);
void DRAW_PLAYER1_WIN(void);
void DRAW_PLAYER2_WIN(void);
void DRAW_OVERTIME(void);
void DRAW_FRONT_PAGE(void);
void DRAW_INFO_PAGE(void);
void DRAW_PAUSE(void);
void CLEAR_PAUSE(void);
void DRAW_START_PAGE(void);
void DRAW_END_PAGE(u8 label);

