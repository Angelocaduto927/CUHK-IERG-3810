#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <cstring>
#include "stm32f10x.h"
#include "HP_setting.h"
#include "randomness.h"
#include "level_setting.h"
#include "draw.h"

HPList hplist;

void HP_list_init(HPList* list) {
    list->size = 0;
}

void HP_list_push(HPList* list, HP entity) {
    if (list->size ==10) {
        //HP_list_grow(list);
			return;
    }
    list->hps[list->size] = entity;
    list->size++;
}

void HP_list_remove_at(HPList* list, size_t index) {
    if (index >= list->size) return;
    memmove(&list->hps[index], &list->hps[index + 1],
            (list->size - index - 1) * sizeof(HP));
    list->size--;
}

const HP* HP_list_get(const HPList* list, size_t index) {
    if (index >= list->size) return NULL;
    return &list->hps[index];
}

size_t HP_list_size(const HPList* list) {
    return list->size;
}

void INIT_HP_PACKS_DROP()
{
	HP hp;
	hp.y = RANDOM_RANGE(20,300);
	hp.x = 197;
	hp.status = 1;
	HP_list_push(&hplist, hp);
}

void HP_PACKS_FALLING()
{
	for(size_t i=0; i<hplist.size; i++)
	{
		if(hplist.hps[i].status == 1)
		{
			CLEAR_HP(hplist.hps[i]);
			hplist.hps[i].x-=10;
			for(int j = 0; j < LEVEL_GROUND_COUNT; j++) {
				if ((hplist.hps[i].x == level_ground[j].height+7) && (hplist.hps[i].y >= level_ground[j].start) && (hplist.hps[i].y <= level_ground[j].end))
				{
					hplist.hps[i].status = 0;	
				}
			}
		}
		DRAW_HP_LOOT(hplist.hps[i]);
	}	
}
