#pragma once
#include <stm32f10x.h>
#include "weapon_setting.h"
#include "character_setting.h"

u8 LANDING_CHECK(CHARACTER* character);
void JUMP_UP_ONE_PIXEL(CHARACTER* character);
void DROP_DOWN_ONE_PIXEL(CHARACTER* character);
void MOVE_LEFT(CHARACTER* character);
void MOVE_RIGHT(CHARACTER* character);
