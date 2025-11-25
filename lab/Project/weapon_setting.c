#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <cstring>
#include "stm32f10x.h"
#include "weapon_setting.h"
#include "randomness.h"
#include "level_setting.h"
#include "character_setting.h"
#include "draw.h"
#include "IERG3810_LED.h"

const WEAPON WEAPONS[WEAPON_COUNT] = {
    [WEAPON_PISTOL] = {
        .name = "Pistol",
        .damage = 2,
        .max_usage_time = 300,
        .fire_rate = 200
    },
    [WEAPON_VANDAL] = {
        .name = "Vandal",
        .damage = 10,
        .max_usage_time = 20,
        .fire_rate = 20
    },
    [WEAPON_PHANTOM] = {
        .name = "Phantom",
        .damage = 5,
        .max_usage_time = 20,
        .fire_rate = 100
    },
    [WEAPON_ODIN] = {
        .name = "Odin",
        .damage = 4,
        .max_usage_time = 20,
        .fire_rate = 50
    }
};
