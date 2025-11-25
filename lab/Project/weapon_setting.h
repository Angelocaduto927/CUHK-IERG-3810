#pragma once
#include "stm32f10x.h"
#include <stdlib.h>

typedef struct{
	int x,y;
	int status;
	char name[32];
	int damage;
	long int max_usage_time;
	int fire_rate;
}WEAPON;

typedef enum {
    WEAPON_PISTOL,
    WEAPON_VANDAL,
    WEAPON_PHANTOM,
    WEAPON_ODIN,
    WEAPON_COUNT
} WeaponType;

extern const WEAPON WEAPONS[WEAPON_COUNT];

