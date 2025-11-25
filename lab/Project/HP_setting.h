#pragma once
#include "stm32f10x.h"

typedef struct {
  int x, y;
	int status;
}HP;

typedef struct {
    HP hps[10];
    size_t size;
} HPList;

extern HPList hplist;

void HP_list_init(HPList* list);

void HP_list_push(HPList* list, HP entity);

void HP_list_remove_at(HPList* list, size_t index);

const HP* HP_list_get(const HPList* list, size_t index);

size_t HP_list_size(const HPList* list);

void INIT_HP_PACKS_DROP(void);

void HP_PACKS_FALLING(void);
