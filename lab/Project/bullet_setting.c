#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <cstring>
#include "stm32f10x.h"
#include "bullet_setting.h"

BulletList bulletlist1;
BulletList bulletlist2;

void Bullet_list_init(BulletList* list) {
    list->size = 0;
}

/*
void Bullet_list_free(BulletList* list) {
    free(list->bullet);
    list->bullet = NULL;
    list->size = 0;
    list->capacity = 0;
}

static void Bullet_list_grow(BulletList* list) {
    list->capacity *= 2;
    BULLET* new_bullet = realloc(list->bullet, list->capacity * sizeof(BULLET));
    if (!new_bullet) {
        fprintf(stderr, "Realloc failed!\n");
        exit(1);
    }
    list->bullet = new_bullet;
}
*/

void Bullet_list_push(BulletList* list, BULLET entity) {
    if (list->size == 100) {
        return;
    }
    list->bullets[list->size] = entity;
    list->size++;
}

void Bullet_list_remove_at(BulletList* list, size_t index) {
    if (index >= list->size) return;
    memmove(&list->bullets[index], &list->bullets[index + 1],
            (list->size - index - 1) * sizeof(BULLET));
    list->size--;
}

const BULLET* Bullet_list_get(const BulletList* list, size_t index) {
    if (index >= list->size) return NULL;
    return &list->bullets[index];
}

size_t Bullet_list_size(const BulletList* list) {
    return list->size;
}

