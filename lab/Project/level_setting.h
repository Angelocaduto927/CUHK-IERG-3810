#pragma once
#include <stm32f10x.h>

extern const u16 LEVEL_GROUND_COUNT;

typedef struct {
		u16 height;
    u16 start;
    u16 end;
} LEVEL_BLOCK;

extern const LEVEL_BLOCK level_ground[];
