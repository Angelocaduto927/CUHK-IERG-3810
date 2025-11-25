#include <stm32f10x.h>
#include "level_setting.h"

const LEVEL_BLOCK level_ground[] = {
		{0, 2, 1},
    {10, 0, 320},
    {60, 0, 120},
		{60, 200, 320},
		{110, 80, 240}
};

const u16 LEVEL_GROUND_COUNT = sizeof(level_ground) / sizeof(level_ground[0]);
